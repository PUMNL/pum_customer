<?php

function pum_customer_cv_proposedexpert($case_id) {
  $page = array();
  civicrm_initialize();
  $config = CRM_Core_Config::singleton();

  $case = civicrm_api3('Case', 'getsingle', array('id' => $case_id));
  $customer_id = $case['client_id'];
  $customer = civicrm_api3('Contact', 'getsingle', array('id' => $customer_id));
  $expert = false;
  foreach($case['contacts'] as $role) {
    switch ($role['role']) {
      case 'Expert':
        $expert = $role;
        break;
    }
  }

  $caseTypeOptionGroupId = civicrm_api3('OptionGroup', 'getvalue', array('name' => 'case_type', 'return' => 'id'));
  $adviceCaseType = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Advice', 'option_group_id' => $caseTypeOptionGroupId, 'return' => 'value'));
  $seminarCaseType = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Seminar', 'option_group_id' => $caseTypeOptionGroupId, 'return' => 'value'));
  $businessCaseType = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Business', 'option_group_id' => $caseTypeOptionGroupId, 'return' => 'value'));
  $remoteCoachingCaseType = civicrm_api3('OptionValue', 'getvalue', array('name' => 'RemoteCoaching', 'option_group_id' => $caseTypeOptionGroupId, 'return' => 'value'));

  $activityTypeOptionGroupId = civicrm_api3('OptionGroup', 'getvalue', array('name' => 'activity_type', 'return' => 'id'));
  $acceptMainActivityTypeId = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Accept Main Activity Proposal', 'option_group_id' => $activityTypeOptionGroupId));

  $mainActivityInfoCustomGroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'main_activity_info'));
  $mainActivityStartDateCustomField = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_start_date', 'custom_group_id' => $mainActivityInfoCustomGroup['id']));
  $mainActivityStartDateCustomFieldName = $mainActivityStartDateCustomField['column_name'];
  $mainActivityEndDateCustomField = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_end_date', 'custom_group_id' => $mainActivityInfoCustomGroup['id']));
  $mainActivityEndDateCustomFieldName = $mainActivityEndDateCustomField['column_name'];

  $acceptMainActivityProposalCustomGroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Add_Keyqualifications'));
  $projectQualificationsCustomField = civicrm_api3('CustomField', 'getsingle', array('name' => 'Key_Qualifications', 'custom_group_id' => $acceptMainActivityProposalCustomGroup['id']));

  $languagesCustomGroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Languages'));
  $languagesField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Language', 'return' => 'column_name', 'custom_group_id' => $languagesCustomGroup['id']));
  $levelField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Level', 'return' => 'column_name', 'custom_group_id' => $languagesCustomGroup['id']));

  $educationCustomGroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Education'));
  $educationNameField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Name_of_Institution', 'return' => 'column_name', 'custom_group_id' => $educationCustomGroup['id']));
  $educationLevelField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Education_level', 'return' => 'column_name', 'custom_group_id' => $educationCustomGroup['id']));
  $educationMajorField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Field_of_study_major', 'return' => 'column_name', 'custom_group_id' => $educationCustomGroup['id']));
  $educationDiplomaField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Diploma_Degree', 'return' => 'column_name', 'custom_group_id' => $educationCustomGroup['id']));
  $educationFromField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Years_From', 'return' => 'column_name', 'custom_group_id' => $educationCustomGroup['id']));
  $educationToField = civicrm_api3('CustomField', 'getvalue', array('name' => 'To', 'return' => 'column_name', 'custom_group_id' => $educationCustomGroup['id']));

  $workhistoryCustomGroup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Workhistory'));
  $workhistoryNameField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Name_of_Organisation', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryTitleField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Job_Title', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryCityField = civicrm_api3('CustomField', 'getvalue', array('name' => 'City', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryCountryField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Country', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryResponsebilitiesField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Responsibilities', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryDescriptionField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Description', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryCompetencesField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Competences_used_in_this_job', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryFromField = civicrm_api3('CustomField', 'getvalue', array('name' => 'Yeard_From', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));
  $workhistoryToField = civicrm_api3('CustomField', 'getvalue', array('name' => 'To', 'return' => 'column_name', 'custom_group_id' => $workhistoryCustomGroup['id']));


  $startDate = '';
  $endDate = '';
  $dao = CRM_Core_DAO::executeQuery("SELECT * FROM `".$mainActivityInfoCustomGroup['table_name']."` WHERE `entity_id` = %1", array(1=>array($case_id, 'Integer')));
  if ($dao->fetch()) {
    if ($dao->$mainActivityStartDateCustomFieldName) {
      $startDate = CRM_Utils_Date::customFormat($dao->$mainActivityStartDateCustomFieldName, $config->dateformatFull);
    }
    if ($dao->$mainActivityEndDateCustomFieldName) {
      $endDate = CRM_Utils_Date::customFormat($dao->$mainActivityEndDateCustomFieldName, $config->dateformatFull);
    }
  }

  $sql = "SELECT `accept_main_activity`.`".$projectQualificationsCustomField['column_name']."`
          FROM civicrm_activity a
          INNER JOIN civicrm_activity_contact ac ON a.id = ac.activity_id
          INNER JOIN civicrm_case_activity ca ON a.id = ca.activity_id
          INNER JOIN `".$acceptMainActivityProposalCustomGroup['table_name']."` accept_main_activity ON a.id = accept_main_activity.entity_id
          WHERE a.is_deleted = '0' AND a.is_current_revision = '1' AND ca.case_id = %1 AND ac.record_type_id = 2 AND ac.contact_id = %2 AND a.activity_type_id = %3
          ORDER BY a.activity_date_time DESC
          LIMIT 0,1";
  $sqlParams[1] = array($case_id, 'Integer');
  $sqlParams[2] = array($expert['contact_id'], 'Integer');
  $sqlParams[3] = array($acceptMainActivityTypeId, 'Integer');
  $projectQualifications = CRM_Core_DAO::singleValueQuery($sql, $sqlParams);

  $sql = "SELECT * FROM `".$languagesCustomGroup['table_name']."` WHERE `entity_id` = %1";
  $sqlParams = array();
  $sqlParams[1] = array($expert['contact_id'], 'Integer');
  $languages = array();
  $dao = CRM_Core_DAO::executeQuery($sql, $sqlParams);
  while ($dao->fetch()) {
    $languages[] = array(
      $dao->$languagesField,
      $dao->$levelField,
    );
  }

  $sql = "SELECT * FROM `".$educationCustomGroup['table_name']."` WHERE `entity_id` = %1 ORDER BY `".$educationFromField."` DESC, `".$educationToField."` DESC";
  $sqlParams = array();
  $sqlParams[1] = array($expert['contact_id'], 'Integer');
  $educations = array();
  $dao = CRM_Core_DAO::executeQuery($sql, $sqlParams);
  while ($dao->fetch()) {
    $educations[] = array(
      $dao->$educationNameField,
      $dao->$educationLevelField,
      $dao->$educationMajorField,
      $dao->$educationDiplomaField ? 'Yes' : 'No',
      $dao->$educationFromField.' - '.$dao->$educationToField,
    );
  }

  $expert_gender = civicrm_api3('Contact', 'getvalue', array('id' => $expert['contact_id'], 'return' => 'gender_id'));
  $title = $expert['display_name'];
  if ($expert_gender == '1') {
    $title = 'Mrs. '.$expert['display_name'];
  } elseif ($expert_gender == '2') {
    $title = 'Mr. '.$expert['display_name'];
  }
  drupal_set_title($title);

  $acceptRejectCvLink = false;
  if ($adviceCaseType == $case['case_type_id']) {
    $acceptRejectCvLink = 'customer/proposed-experts/dis-agree-advice';
  } elseif ($seminarCaseType == $case['case_type_id']) {
    $acceptRejectCvLink = 'customer/proposed-experts/dis-agree-seminar';
  } elseif ($remoteCoachingCaseType == $case['case_type_id']) {
    $acceptRejectCvLink = 'customer/proposed-experts/dis-agree-remote-coaching';
  } elseif ($businessCaseType == $case['case_type_id']) {
    $acceptRejectCvLink = 'customer/proposed-experts/dis-agree-business';
  }
  if ($acceptRejectCvLink) {
    $acceptRejectCvLink = url($acceptRejectCvLink, array(
      'absolute'=> true,
      'query' => array(
        'cid1' => $customer['id'],
        'cid2' => $expert['contact_id'],
        'caseid' => $case_id,
      ),
    ));
    $buttons['accept']['#markup'] = '<a href="'.$acceptRejectCvLink.'" class="button accept-reject-expert">'.t("Accept / Reject Expert").'</a>';
  }

  $questionLink = 'customer/proposedexpert/cv/'.$case_id.'/question';
  $buttons['questions']['#markup'] = '<a href="'.url($questionLink, array('absolute'=>true)).'" class="button question-proposed-cv">'.t("Questions?").'</a>';

  $page['buttons_top'] = $buttons;

  $page['explain']['#type'] = 'markup';
  $page['explain']['#markup'] = '<p>If you have any questions that need to be answered before you can accept/reject the proposed expert, please press \'questions\'. This will send an e-mail to the project officer.</p>';

  $page['availability']['#type'] = 'fieldset';
  $page['availability']['date']['#markup'] = '<p><strong>Period of availability: </strong>'.$startDate.' - '.$endDate.'</p>';

  $page['project_qualifications']['#type'] = 'fieldset';
  $page['project_qualifications']['#title'] = 'Project qualifications';
  $page['project_qualifications']['qualifications']['#markup'] = nl2br($projectQualifications);

  $page['languages_caption']['#markup'] = '<p><strong>Languages</strong></p>';
  $page['languages']['#theme'] = 'table';
  $page['languages']['#header'] = array('Language', 'Level');
  $page['languages']['#rows'] = $languages;
  $page['languages']['#attributes'] = array('width' => '100%');

  $page['education_caption']['#markup'] = '<p><strong>Education</strong></p>';
  $page['education']['#theme'] = 'table';
  $page['education']['#header'] = array('Name', 'Level', 'Field of Study/Major', 'Degree', 'Period');
  $page['education']['#rows'] = $educations;
  $page['education']['#attributes'] = array('width' => '100%');

  $page['workhistory_caption']['#markup'] = '<p><strong>Work Experience</strong></p>';
  $page['workhistory'] = array();
  $sql = "SELECT * FROM `".$workhistoryCustomGroup['table_name']."` WHERE `entity_id` = %1 ORDER BY `".$workhistoryFromField."` DESC, `".$workhistoryToField."` DESC";
  $sqlParams = array();
  $sqlParams[1] = array($expert['contact_id'], 'Integer');
  $dao = CRM_Core_DAO::executeQuery($sql, $sqlParams);
  $i=1;
  while ($dao->fetch()) {
    $job = array();
    $country = '';
    try {
      $country = civicrm_api3('Country', 'getvalue', array('return' => 'name', 'id' => $dao->$workhistoryCountryField));
    } catch (Exception $e) {
          // Do nothing.
    }

    $job['#type'] = 'fieldset';
    $job['company_job_title_label']['#markup'] = '<strong>Company and job title</strong>';
    $job['company_job_title']['#markup'] = '<br>'.$dao->$workhistoryNameField.', '.$dao->$workhistoryTitleField.'<br>';
    $job['city_country_label']['#markup'] = '<br><strong>City and country</strong>';
    $job['city_country']['#markup'] = '<br>'.$dao->$workhistoryCityField.', '.$country.'<br>';
    $job['period_label']['#markup'] = '<br><strong>Period</strong>';
    $job['period']['#markup'] = '<br>'.$dao->$workhistoryFromField.' - '.$dao->$workhistoryToField.'<br>';
    $job['responsibilities_label']['#markup'] = '<br><strong>Responsibilities</strong>';
    $job['responsibilities']['#markup'] = '<br>'.$dao->$workhistoryResponsebilitiesField.'<br>';
    $job['description_label']['#markup'] = '<br><strong>Description</strong>';
    $job['description']['#markup'] = '<br>'.$dao->$workhistoryDescriptionField.'<br>';
    $job['competence_label']['#markup'] = '<br><strong>Competence used in this job</strong>';
    $job['competence']['#markup'] = '<br>'.$dao->$workhistoryCompetencesField.'<br>';

    $page['workhistory']['job_'.$i] = $job;
    $i++;
  }

  $page['buttons_bottom'] = $buttons;

  return $page;
}