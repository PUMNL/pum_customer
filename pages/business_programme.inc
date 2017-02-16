<?php
/**
 * @author Jaap Jansma (CiviCitineraryap.jansma@civicoop.org>
 * @license http://www.gnu.org/licenses/agpl-3.0.html
 */

/**
 * Detail page business programme for the customer. It shows the programme,
 * the participants, an button to register participants and functionality to upload
 * a tentative flight itinerary.
 *
 * @param $form
 * @param $form_state
 * @param $case_id
 * @return array a Drupal render array.
 */
function pum_customer_business_programme_details($form, &$form_state, $case_id) {
  /**
   * First retrieve the data and then build the form.
   */
  civicrm_initialize();
  $session = CRM_Core_Session::singleton();
  $currentUserContactId = $session->get('userID');
  $businessconfig = pum_customer_businessconfig::singleton();

  // Retrieve the expert and authorised contact role fomr the case.
  $case = civicrm_api3('Case', 'getsingle', array('id' => $case_id));
  $authorised = '';
  foreach($case['contacts'] as $contact) {
    switch ($contact['role']) {
      case 'Authorised contact for':
        $authorised = $contact;
        break;
    }
  }

  $expert_relationship_type = civicrm_api3('RelationshipType', 'getvalue', array('return' => 'id', 'name_a_b' => 'Expert'));
  $expert_relationship = civicrm_api3('Relationship', 'getsingle', array('relationship_type_id' => $expert_relationship_type, 'case_id' => $case_id));
  $expert = civicrm_api3('Contact', 'getsingle', array('return' => 'display_name,sort_name,email,phone,birth_date', 'id' => $expert_relationship['contact_id_b']));
  $expertName = $expert['display_name'];
  $expertEmail = $expert['email'];

  // Retrieve the start and end date from the business case.
  $mainActivityStartDateCustomFieldName = $businessconfig->custom_groups['main_activity_info']['fields']['start_date']['column_name'];
  $mainActivityEndDateCustomFieldName = $businessconfig->custom_groups['main_activity_info']['fields']['end_date']['column_name'];;
  $startDate = '';
  $endDate = '';
  $dao = CRM_Core_DAO::executeQuery("SELECT * FROM `".$businessconfig->custom_groups['main_activity_info']['table_name']."` WHERE `entity_id` = %1", array(1=>array($case_id, 'Integer')));
  if ($dao->fetch()) {
    if ($dao->$mainActivityStartDateCustomFieldName) {
      $startDate = new DateTime($dao->$mainActivityStartDateCustomFieldName);
    }
    if ($dao->$mainActivityEndDateCustomFieldName) {
      $endDate = new DateTime($dao->$mainActivityEndDateCustomFieldName);
    }
  }

  // Retrieve the business programme. Lookup the Business programme activities on the case.
  // Build a list with the name of the company, location and aim of the visit. This list is later
  // used to display it as a table.
  $visitSqlParams = array();
  $visitSqlParams[1] = array($case_id, 'Integer');
  $visitSqlParams[2] = array($businessconfig->in_progress_status, 'Integer');
  $visitSqlParams[3] = array($businessconfig->submitted_status, 'Integer');
  $visitSql = "
    SELECT civicrm_activity.id as activity_id, 
    {$businessconfig->custom_groups['Business_Programme']['fields']['Naam_bedrijf']['column_name']} AS `Naam_bedrijf`,
    {$businessconfig->custom_groups['Business_Programme']['fields']['Location']['column_name']} AS `Location`,
    {$businessconfig->custom_groups['Business_Programme']['fields']['Aim_of_Visit']['column_name']} AS `Aim_of_Visit`
    FROM civicrm_activity 
    INNER JOIN civicrm_case_activity ON civicrm_case_activity.activity_id = civicrm_activity.id
    INNER JOIN {$businessconfig->custom_groups['Business_Programme']['table_name']} ON {$businessconfig->custom_groups['Business_Programme']['table_name']}.entity_id = civicrm_activity.id  
    WHERE civicrm_case_activity.case_id = %1 AND civicrm_activity.is_current_revision = '1' AND civicrm_activity.is_deleted != '1' 
    AND (civicrm_activity.status_id = %2 OR civicrm_activity.status_id = %3)";
  $dao = CRM_Core_DAO::executeQuery($visitSql, $visitSqlParams);
  $programme = array();
  while($dao->fetch()) {
    if (!empty($dao->Naam_bedrijf) || !empty($dao->Location) || !empty($dao->Aim_of_Visit)) {
      $programme[] = array(
        $dao->Naam_bedrijf,
        $dao->Location,
        $dao->Aim_of_Visit
      );
    }
  }

  // Retrieve the maximum number of allowed participants.
  $maxParticipants = (int) CRM_Core_DAO::singleValueQuery("SELECT `".$businessconfig->custom_groups['business_data']['fields']['Number_of_Visitors']['column_name']."` FROM `".$businessconfig->custom_groups['business_data']['table_name']."` WHERE entity_id = %1", array(1=>array($case_id, 'Integer')));

  // Build a list with participants. This list contains the name, an edit details link,
  // and an cancel link. This list is later on used to display a table with participants.
  $participants = array();
  $participantRows = array();
  $participantResult = civicrm_api3('Relationship', 'get', array('case_id' => $case_id, 'relationship_type_id' => $businessconfig->business_participant_relationship_type_id, 'status_id' => 4));
  $travelCases = array();
  foreach($participantResult['values'] as $participant) {
    $participants[$participant['contact_id_b']] = array(
      'relationship_id' => $participant['id'],
      'display_name' => civicrm_api3('Contact', 'getvalue', array('return' => 'display_name', 'id' => $participant['contact_id_b'])),
    );

    $editLink = '<a href="/customer/business-programme-details/' . $case_id . '/participant/'.$participant['id'].'">Edit details</a>';
    $removeLink = '<a href="/customer/business-programme-details/' . $case_id . '/participant/'.$participant['id'].'/remove">Cancel registration</a>';

    $participantRows[] = array(
      $participants[$participant['contact_id_b']]['display_name'],
      array('data' => $editLink, 'style' => 'width: 120px; text-align: right'),
      array('data' => $removeLink, 'style' => 'width: 180px; text-align: right')
    );

    // Find travel case for this participant
    $travelCaseSql = "SELECT civicrm_case.id 
                      FROM civicrm_case 
                      INNER JOIN civicrm_case_contact ON civicrm_case_contact.case_id = civicrm_case.id
                      INNER JOIN `{$businessconfig->custom_groups['TravelParent']['table_name']}` `travel_parent` ON `travel_parent`.entity_id = civicrm_case.id
                      WHERE `travel_parent`.`{$businessconfig->custom_groups['TravelParent']['fields']['case_id']['column_name']}` = %1
                      AND civicrm_case_contact.contact_id = %2
                      AND civicrm_case.is_deleted = 0 
                      AND civicrm_case.case_type_id LIKE %3
    ";
    $travelCaseParams[1] = array($case_id, 'Integer');
    $travelCaseParams[2] = array($participant['contact_id_b'], 'Integer');
    $travelCaseParams[3] = array('%'.CRM_Core_DAO::VALUE_SEPARATOR.$businessconfig->travel_case_type.CRM_Core_DAO::VALUE_SEPARATOR.'%', 'String');
    $travelCaseDao = CRM_Core_DAO::executeQuery($travelCaseSql, $travelCaseParams);
    if ($travelCaseDao->fetch()) {
      $travelCases[$travelCaseDao->id] = $participants[$participant['contact_id_b']]['display_name'];
    }
  }

  // Retrieve the documents on the case and only show the documents which are added by the current user.
  // Build a list with the name of the file and a remove link. This list is later on used
  // for displaying it as a table.
  $documentsRepo = CRM_Documents_Entity_DocumentRepository::singleton();
  $documents = $documentsRepo->getDocumentsByCaseId($case_id);
  $documentRows = array();
  foreach($documents as $document) {
    if ($document->getAddedBy() == $currentUserContactId) {
      $version = $document->getCurrentVersion();
      $downloadUrl = $version->getAttachment()->url;
      $cleanName = $version->getAttachment()->cleanname;
      $removeLink = '<a href="/customer/business-programme-details/'.$case_id.'/removedocument/'.$document->getId().'">Remove</a>';
      $downloadLink = '<a href="'.$downloadUrl.'">'.$cleanName.'</a>';

      $documentRows[] = array(
        '',
        $downloadLink,
        array('data' => $removeLink, 'style' => 'width: 180px; text-align: right')
      );
    }
  }

  foreach($travelCases as $travel_case_id => $participant) {
    $documents = $documentsRepo->getDocumentsByCaseId($travel_case_id);
    foreach($documents as $document) {
      if ($document->getAddedBy() == $currentUserContactId) {
        $version = $document->getCurrentVersion();
        $downloadUrl = $version->getAttachment()->url;
        $cleanName = $version->getAttachment()->cleanname;
        $removeLink = '<a href="/customer/business-programme-details/' . $case_id . '/removedocument/' . $document->getId() . '">Remove</a>';
        $downloadLink = '<a href="' . $downloadUrl . '">' . $cleanName . '</a>';

        $documentRows[] = array(
          $participant,
          $downloadLink,
          array(
            'data' => $removeLink,
            'style' => 'width: 180px; text-align: right'
          )
        );
      }
    }
  }

  // Retrieve whether we have a Different Data Registering activity on the case with the status scheduled.
  // If so block the page for registering participants.
  $dataDiscrepancyParams[1] = array($businessconfig->different_data_registering_activity_type, 'Integer');
  $dataDiscrepancyParams[2] = array($businessconfig->scheduled_activity_status, 'Integer');
  $dataDiscrepancyParams[3] = array($case_id, 'Integer');
  $dataDiscrepancySql = "
    SELECT COUNT(*) 
    FROM civicrm_activity
    INNER JOIN civicrm_case_activity ON civicrm_case_activity.activity_id = civicrm_activity.id
    WHERE is_current_revision = 1 AND is_deleted != 1 AND activity_type_id = %1 AND status_id = %2 AND case_id = %3
  ";
  $isDataDiscrepancy =CRM_Core_DAO::singleValueQuery($dataDiscrepancySql, $dataDiscrepancyParams);

  // Build the page as a Drupal render array.
  $form['#attributes'] = array('enctype' => "multipart/form-data");

  $form['case_id']['#type'] = 'hidden';
  $form['case_id']['#name'] = 'case_id';
  $form['case_id']['#value'] = $case_id;

  $form['period']['#type'] = 'fieldset';
  $form['period']['#title'] = 'Business link period';
  $form['period']['period']['#markup'] = '<p>'.($startDate ? $startDate->format('d F Y') : '').' to '.($endDate ? $endDate->format('d F Y') : '').'</p>';
  $form['expert']['#type'] = 'fieldset';
  $form['expert']['#title'] = 'PUM Expert';
  $form['expert']['expert']['#markup'] = '<p>'.$expertName.' (<a href="mailto:'.$expertEmail.'">'.$expertEmail.'</a>)</p>';

  $form['programme']['#type'] = 'fieldset';
  $form['programme']['#title'] = 'Programme';
  if (count($programme)) {
    $form['programme']['table']['#theme'] = 'table';
    $form['programme']['table']['#header'] = array(
      'Company name',
      'Location',
      'Aim of visit'
    );
    $form['programme']['table']['#attributes'] = array('width' => '100%');
    $form['programme']['table']['#rows'] = $programme;
    $form['programme']['explenation']['#markup'] = '<p>Please note that the programme can be updated by the expert before your business link starts.</p>';
  } else {
    $form['programme']['no_programme']['#markup'] = '<p>No programme available.</p>';
  }

  $form['participants']['#type'] = 'fieldset';
  $form['participants']['#title'] = 'Participants';
  $form['participants']['max_participants']['#markup'] = '<p><em>You can register a maximum of '.$maxParticipants.' participants</em></p>';
  if (!$isDataDiscrepancy) {
    if (count($participants)) {
      $form['participants']['table']['#theme'] = 'table';
      $form['participants']['table']['#rows'] = $participantRows;
      $form['participants']['table']['#attributes'] = array('width' => '100%');
    }
    else {
      $form['participants']['no_participants']['#markup'] = '<p>No participant(s) registered</p>';
    }
    if (count($participants) < $maxParticipants) {
      if (!isset($participants[$authorised['contact_id']])) {
        $form['participants']['buttons']['add_authorised']['#markup'] = '<a href="/customer/business-programme-details/' . $case_id . '/participant/contact/'.$authorised['contact_id'].'" class="button">Add ' . $authorised['display_name'] . ' as participant</a>&nbsp;';
      }
      $form['participants']['buttons']['add_another']['#markup'] = '<a href="/customer/business-programme-details/' . $case_id . '/participant" class="button">Add a new participant</a>';
    }
  } else {
    $form['participants']['data_discrepancy']['#markup'] = '<p>There is data discrepancy. We will contact you about your registration.</p>';
  }

  $form['documents']['#type'] = 'fieldset';
  $form['documents']['#title'] = 'Documents';
  $form['documents']['upload']['#prefix'] = '<div class="upload">';
  $form['documents']['upload']['#suffix'] = '</div>';
  $form['documents']['upload']['explanation']['#markup'] = '<p class="description">Please upload a tentative flight itinerary for each participant. You can upload more than one document</p>';
  $form['documents']['upload']['file']['#title'] = t('File');
  $form['documents']['upload']['file']['#type'] = 'file';
  $form['documents']['upload']['document_travel_case_id']['#required'] = true;
  $form['documents']['upload']['document_travel_case_id']['#title'] = t('Participant');
  $form['documents']['upload']['document_travel_case_id']['#type'] = 'select';
  $form['documents']['upload']['document_travel_case_id']['#options'] = $travelCases;
  $form['documents']['upload']['button']['#type'] = 'submit';
  $form['documents']['upload']['button']['#value'] = 'Upload';
  $form['documents']['upload']['button']['#submit'] = array('pum_customer_business_programme_details_submit_document');

  if (count($documentRows)) {
    $form['documents']['table']['#theme'] = 'table';
    $form['documents']['table']['#rows'] = $documentRows;
    $form['documents']['table']['#attributes'] = array('width' => '100%');
  }

  drupal_add_css(drupal_get_path('module', 'pum_customer') . '/style.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));

  return $form;
}

/**
 * Submit handler for uploading a document on the business programme for customer page.
 *
 * @param $form
 * @param $form_state
 */
function pum_customer_business_programme_details_submit_document($form, &$form_state) {
  civicrm_initialize();
  $case_id = $form_state['values']['case_id'];
  if (!empty($form_state['values']['document_travel_case_id'])) {
    $case_id = $form_state['values']['document_travel_case_id'];
  }
  $file = file_save_upload('file', array(
    'file_validate_extensions' => array('gif png jpg jpeg txt rtf odf pdf doc docx ppt pptx xls xlsx'),
    'file_validate_size' => array(10*1024*1024),
  ));
  if ($file) {
    $case = civicrm_api3('Case', 'getsingle', array("case_id"=>$case_id ));

    $repository = CRM_Documents_Entity_DocumentRepository::singleton();
    $document = new CRM_Documents_Entity_Document();
    $document->setSubject('Customer tentative flight itinerary');
    $document->addCaseid($case_id);
    $document->setContactIds($case['client_id']);
    $version = $document->getCurrentVersion();
    $version->setDescription('Customer tentative flight itinerary');
    $repository->persist($document);
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $filepath = $wrapper->realpath();
    CRM_Documents_Utils_File::copyFileToDocument($filepath, $file->filemime, $document);
  }
}

/**
 * Removes a document from the business programme for customer page.
 *
 * @param $case_id
 * @param $document_id
 */
function pum_customer_business_programme_details_removedocument($case_id, $document_id) {
  civicrm_initialize();
  $repository = CRM_Documents_Entity_DocumentRepository::singleton();
  $document = $repository->getDocumentById($document_id);
  $repository->remove($document);
  drupal_set_message('Removed document');
  drupal_goto('customer/business-programme-details/'.$case_id);
}