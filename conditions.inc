<?php

function pum_customer_condition_update_form($form, &$form_state, $activity_id) {
  civicrm_initialize();
  $config = pum_customer_mycases_config::singleton();
  $activity = civicrm_api3('Activity', 'getsingle', array('id' => $activity_id));
  $remarks = CRM_Core_DAO::singleValueQuery("SELECT `".$config->cfConditionsCustomerRemark['column_name']."` FROM `".$config->cgConditions['table_name']."` WHERE entity_id = %1", array(1 => array($activity_id, 'Integer')));

  $form['activity_id']['#type'] = 'hidden';
  $form['activity_id']['#name'] = 'activity_id';
  $form['activity_id']['#value'] = $activity_id;
  
  $form['condition_subject']['#type'] = 'markup';
  $form['condition_subject']['#markup'] = '<h2>'.$activity['subject'].'</h2>';
  
  $form['condition_details']['#type'] = 'markup';
  $form['condition_details']['#markup'] = '<div>'.$activity['details'].'</div>';

  $form['remarks'] = array(
    '#type' => 'textarea',
    '#required' => false,
    '#title' => t('Remarks'),
    '#default_value' => $remarks,
  );

  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Attachment'),
  );
  
  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Mark condition as completed'),
  );

  return $form;
}

function pum_customer_condition_update_form_submit($form, &$form_state) {

  $config = pum_customer_mycases_config::singleton();
  $activity_id = $form_state['values']['activity_id'];
  $remarks = $form_state['values']['remarks'];
  $case_id = CRM_Core_DAO::singleValueQuery("SELECT case_id FROM civicrm_case_activity where activity_id = %1", array(1=>array($activity_id, 'Integer')));

  $status = CRM_Core_OptionGroup::getValue('activity_status', 'Submitted', 'name');

  $params['id'] = $activity_id;
  $params['status_id'] = $status; //completed
  $params['custom_'.$config->cfConditionsCustomerRemark['id']] = $remarks;

  civicrm_api3('Activity', 'create', $params);

  $file = file_save_upload('upload');
  if ($file) {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $filepath = $wrapper->realpath();
    CRM_Core_BAO_File::deleteEntityFile('civicrm_activity', $activity_id);
    _pum_customer_condition_save_attachment($filepath, $file->filemime, $activity_id);
  }

  drupal_goto('customer/case-details/'.$case_id);
}

function _pum_customer_condition_attachment($activity_id) {
  $files = CRM_Core_BAO_File::getEntityFile('civicrm_activity', $activity_id);
  $return = '';
  foreach($files as $file) {
    $return .= $file['href']."<br>\r\n";
  }
  return $return;
}

function _pum_customer_condition_save_attachment($file, $mimeType, $activity_id) {
  $config = CRM_Core_Config::singleton();

  $path = explode('/', $file);
  $filename = $path[count($path) - 1];
  $directoryName = $config->customFileUploadDir;
  CRM_Utils_File::createDir($directoryName);

  if (!copy($file, $directoryName . DIRECTORY_SEPARATOR . $filename)) {
    throw new Exception('Could not copy file from '.$file.' to '.$directoryName . DIRECTORY_SEPARATOR . $filename);
  }

  $entityTable = 'civicrm_activity';
  $entityID = $activity_id;

  list($sql, $params) = CRM_Core_BAO_File::sql($entityTable, $entityID, 0);

  $dao = CRM_Core_DAO::executeQuery($sql, $params);
  $dao->fetch();

  $fileDAO = new CRM_Core_DAO_File();
  $op = 'create';
  if (isset($dao->cfID) && $dao->cfID) {
    $op = 'edit';
    $fileDAO->id = $dao->cfID;
    unlink($directoryName . DIRECTORY_SEPARATOR . $dao->uri);
  }

  $fileDAO->uri = $filename;
  $fileDAO->mime_type = $mimeType;
  $fileDAO->upload_date = date('Ymdhis');
  $fileDAO->save();

  // need to add/update civicrm_entity_file
  $entityFileDAO = new CRM_Core_DAO_EntityFile();
  if (isset($dao->cefID) && $dao->cefID) {
    $entityFileDAO->id = $dao->cefID;
  }
  $entityFileDAO->entity_table = $entityTable;
  $entityFileDAO->entity_id = $entityID;
  $entityFileDAO->file_id = $fileDAO->id;
  $entityFileDAO->save();

  // lets call the post hook here so attachments code can do the right stuff
  CRM_Utils_Hook::post($op, 'File', $fileDAO->id, $fileDAO);
}