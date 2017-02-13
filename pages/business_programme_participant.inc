<?php
/**
 * @author Jaap Jansma (CiviCooP) <jaap.jansma@civicoop.org>
 * @license http://www.gnu.org/licenses/agpl-3.0.html
 */

/**
 * The form for registering a participant on a business case.
 *
 * @param $form
 * @param $form_state
 * @param $case_id
 * @param bool|int $relationship_id
 * @param bool|int $contact_id Use this parameter if you want to add a person based on an existing contact id.
 * @return array a Drupal render array.
 */
function pum_customer_business_programme_participant($form, &$form_state, $case_id, $relationship_id=false, $contact_id=false) {
  // First retrieve necessary data and then build the form.
  civicrm_initialize();
  $businessconfig = pum_customer_businessconfig::singleton();

  // Retrieve a list with all the nationalities. Used for the drop down later.
  $nationalitiesResult = civicrm_api3('OptionValue', 'get', array('option_group_id' => 'nationalities', 'option.limit' => 9999));
  foreach($nationalitiesResult['values'] as $nationality) {
    $nationalities[$nationality['value']] = $nationality['label'];
  }

  // Detect whether there is a Different Data Registering activity.
  // If there is one then redirect back to the business case.
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
  if ($isDataDiscrepancy) {
    drupal_set_message('There is data discrepancy. You cannot change or register participants.', 'error');
    drupal_goto('/customer/business-programme-details/'.$case_id);
  }

  // Retrieve the maximum number of participants on the business case.
  $maxParticipants = (int) CRM_Core_DAO::singleValueQuery("SELECT `".$businessconfig->custom_groups['business_data']['fields']['Number_of_Visitors']['column_name']."` FROM `".$businessconfig->custom_groups['business_data']['table_name']."` WHERE entity_id = %1", array(1=>array($case_id, 'Integer')));
  // Get all participants.
  $participantResult = civicrm_api3('Relationship', 'get', array('case_id' => $case_id, 'relationship_type_id' => $businessconfig->business_participant_relationship_type_id, 'status_id' => 4));
  if (!$relationship_id && count($participantResult['values']) >= $maxParticipants) {
    drupal_set_message('You cannot add a new participant.', 'error');
    drupal_goto('/customer/business-programme-details/'.$case_id);
  }

  // Build the form.
  drupal_set_title('Add a participant');

  $data['first_name'] = '';
  $data['last_name'] = '';
  $data['passport_first_name'] = '';
  $data['passport_last_name'] = '';
  $data['passport_number'] = '';
  $data['passport_expiry_date'] = '';
  $data['gender'] = '';
  $data['birth_date'] = '';
  $data['nationality'] = '';
  $data['email'] = '';
  $data['job_title'] = '';
  if ($relationship_id) {
    $relationship = civicrm_api3('Relationship', 'getsingle', array('id' => $relationship_id));
    $data = _pum_customer_business_programme_particpant_getdetails($relationship['contact_id_b']);
    drupal_set_title('Edit a business link participant');
  } elseif ($contact_id) {
    $data = _pum_customer_business_programme_particpant_getdetails($contact_id);
  }

  $form['case_id']['#type'] = 'hidden';
  $form['case_id']['#name'] = 'case_id';
  $form['case_id']['#value'] = $case_id;

  $form['relationship_id']['#type'] = 'hidden';
  $form['relationship_id']['#name'] = 'relationship_id';
  $form['relationship_id']['#value'] = $relationship_id;

  $form['participant']['#type'] = 'fieldset';

  if ($relationship_id) {
    $form['participant']['edit_help']['#markup'] = '<p><em>Please use this form to update your details of this registration. If you want to cancel the registration, go back, then press cancel and add a new participant if needed.</em></p>';
  }

  $form['participant']['first_name']['#type'] = 'textfield';
  $form['participant']['first_name']['#title'] = 'First name';
  $form['participant']['first_name']['#required'] = true;
  $form['participant']['first_name']['#default_value'] = $data['first_name'];
  $form['participant']['last_name']['#type'] = 'textfield';
  $form['participant']['last_name']['#title'] = 'Last name';
  $form['participant']['last_name']['#required'] = true;
  $form['participant']['last_name']['#default_value'] = $data['last_name'];
  $form['participant']['gender']['#type'] = 'select';
  $form['participant']['gender']['#title'] = 'Gender';
  $form['participant']['gender']['#required'] = true;
  $form['participant']['gender']['#empty_option'] = '- Select -';
  $form['participant']['gender']['#options'] = array ('Male' => 'Male', 'Female' => 'Female');
  $form['participant']['gender']['#default_value'] = $data['gender'];

  $form['participant']['passport_last_name']['#type'] = 'textfield';
  $form['participant']['passport_last_name']['#title'] = 'Last name in Passport';
  $form['participant']['passport_last_name']['#required'] = true;
  $form['participant']['passport_last_name']['#default_value'] = $data['passport_last_name'];
  $form['participant']['passport_first_name']['#type'] = 'textfield';
  $form['participant']['passport_first_name']['#title'] = 'First name in Passport';
  $form['participant']['passport_first_name']['#required'] = true;
  $form['participant']['passport_first_name']['#default_value'] = $data['passport_first_name'];

  $form['participant']['birth_date']['#type'] = 'date_popup';
  $form['participant']['birth_date']['#title'] = 'Date of birth';
  $form['participant']['birth_date']['#date_label_position'] = 'before';
  $form['participant']['birth_date']['#required'] = TRUE;
  $form['participant']['birth_date']['#date_format'] = 'Y-m-d';
  $form['participant']['birth_date']['#date_increment'] = 1;
  $form['participant']['birth_date']['#date_year_range'] = '-140:+2';
  $form['participant']['birth_date']['#default_value'] = $data['birth_date'];

  $form['participant']['nationality']['#type'] = 'select';
  $form['participant']['nationality']['#title'] = 'Nationality';
  $form['participant']['nationality']['#required'] = true;
  $form['participant']['nationality']['#options'] = $nationalities;
  $form['participant']['nationality']['#empty_option'] = '- Select -';
  $form['participant']['nationality']['#default_value'] = $data['nationality'];

  $form['participant']['passport_number']['#type'] = 'textfield';
  $form['participant']['passport_number']['#title'] = 'Passport number';
  $form['participant']['passport_number']['#required'] = true;
  $form['participant']['passport_number']['#default_value'] = $data['passport_number'];

  $form['participant']['passport_expiry_date']['#type'] = 'date_popup';
  $form['participant']['passport_expiry_date']['#title'] = 'Passport Expire Date';
  $form['participant']['passport_expiry_date']['#date_label_position'] = 'before';
  $form['participant']['passport_expiry_date']['#required'] = TRUE;
  $form['participant']['passport_expiry_date']['#date_format'] = 'Y-m-d';
  $form['participant']['passport_expiry_date']['#date_increment'] = 1;
  $form['participant']['passport_expiry_date']['#date_year_range'] = '-2:+20';
  $form['participant']['passport_expiry_date']['#default_value'] = $data['passport_expiry_date'];

  $form['participant']['job_title']['#type'] = 'textfield';
  $form['participant']['job_title']['#title'] = 'Job title';
  $form['participant']['job_title']['#required'] = true;
  $form['participant']['job_title']['#default_value'] = $data['job_title'];

  $form['participant']['email']['#type'] = 'textfield';
  $form['participant']['email']['#title'] = 'E-mail';
  $form['participant']['email']['#required'] = true;
  $form['participant']['email_help']['#markup'] = '<em>Use a personal e-mail address</em>';
  $form['participant']['email']['#default_value'] = $data['email'];

  $form['submit']['#type'] = 'submit';
  $form['submit']['#value'] = 'Submit';

  return $form;
}

function pum_customer_business_programme_participant_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['email'])) {
    form_set_error('email', t('Please provide a valid and personal e-mail address.'));
  }
}

function pum_customer_business_programme_participant_submit($form, &$form_state) {
  civicrm_initialize();
  $case_id = $form_state['values']['case_id'];
  $relationship_id = $form_state['values']['relationship_id'];

  $params = array();
  $params['case_id'] = $case_id;

  // When relationship_id is set we are doing an update.
  if ($relationship_id) {
    $params['relationship_id'] = $relationship_id;
  }

  $params['first_name'] = $form_state['values']['first_name'];
  $params['last_name'] = $form_state['values']['last_name'];
  $params['passport_first_name'] = $form_state['values']['passport_first_name'];
  $params['passport_last_name'] = $form_state['values']['passport_last_name'];
  $params['passport_number'] = $form_state['values']['passport_number'];
  $params['passport_expiry_date'] = $form_state['values']['passport_expiry_date'];
  $params['gender'] = $form_state['values']['gender'];
  $params['birth_date'] = $form_state['values']['birth_date'];
  $params['nationality'] = $form_state['values']['nationality'];
  $params['email'] = $form_state['values']['email'];
  $params['job_title'] = $form_state['values']['job_title'];

  civicrm_api3('BusinessParticipant', 'create', $params);

  drupal_goto('/customer/business-programme-details/'.$case_id);
}

function pum_customer_business_programme_participant_remove($case_id, $relationship_id) {
  civicrm_initialize();
  $businessconfig = pum_customer_businessconfig::singleton();
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

  if ($isDataDiscrepancy) {
    drupal_set_message('There is data discrepancy. You cannot change or register participants.', 'error');
    drupal_goto('/customer/business-programme-details/'.$case_id);
  }

  civicrm_api3('BusinessParticipant', 'remove', array('relationship_id' => $relationship_id));

  drupal_goto('/customer/business-programme-details/'.$case_id);
}

function _pum_customer_business_programme_particpant_getdetails($contact_id) {
  civicrm_initialize();
  $config = pum_customer_businessconfig::singleton();

  $contact = civicrm_api3('Contact', 'getsingle', array(
    'id' => $contact_id,
    'return.first_name' => 1,
    'return.last_name' => 1,
    'return.gender' => 1,
    'return.email' => 1,
    'return.job_title' => 1,
    'return.birth_date' => 1,
    'return.custom_'.$config->custom_groups['Nationality']['fields']['Nationality']['id'] => '1',
    'return.custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Name']['id'] => '1',
    'return.custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Name_Last_Name']['id'] => '1',
    'return.custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Number']['id'] => '1',
    'return.custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Valid_until']['id'] => '1',
  ));

  $data['first_name'] = isset($contact['first_name']) ? $contact['first_name'] : '';
  $data['last_name'] = isset($contact['last_name']) ? $contact['last_name'] : '';
  $data['passport_first_name'] = isset($contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Name']['id']]) ? $contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Name']['id']] : '';
  $data['passport_last_name'] = isset($contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Name_Last_Name']['id']]) ? $contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Name_Last_Name']['id']] : '';
  $data['passport_number'] = isset($contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Number']['id']]) ? $contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Number']['id']] : '';
  $data['passport_expiry_date'] = '';
  if (isset($contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Valid_until']['id']])) {
    $expiry_date = new DateTime($contact['custom_'.$config->custom_groups['Passport_Information']['fields']['Passport_Valid_until']['id']]);
    $data['passport_expiry_date'] = $expiry_date->format('Y-m-d');
  }
  $data['gender'] = isset($contact['gender']) ? $contact['gender'] : '';
  $data['birth_date'] = '';
  if (!empty($contact['birth_date'])) {
    $birth_date = new DateTime($contact['birth_date']);
    $data['birth_date'] = $birth_date->format('Y-m-d');
  }
  $data['nationality'] = isset($contact['custom_'.$config->custom_groups['Nationality']['fields']['Nationality']['id']]) ? $contact['custom_'.$config->custom_groups['Nationality']['fields']['Nationality']['id']] : '';
  $data['email'] = isset($contact['email']) ? $contact['email'] : '';
  $data['job_title'] = isset($contact['job_title']) ? $contact['job_title'] : '';

  return $data;
}