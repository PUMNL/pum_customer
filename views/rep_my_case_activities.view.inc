<?php


$activity_names = [
  'Assessment Project Request by Rep',
  'Condition',
  'Advice Debriefing Representative',
  'Representative payment',
  'Seminar Debriefing Representative',
  'Remote Coaching Debriefing Representative',
  'Condition: Customer Contribution',
  'Contact with Customer by Rep'
];

$activities = civicrm_api3('OptionValue', 'get', [
  'sequential' => 1,
  'option_group_id' => "activity_type",
  'options' => ['limit' => 0]
])['values'];

$activity_ids = [];
foreach($activities as $activity){
  if(in_array($activity['label'],$activity_names)){
    $activity_ids[$activity['value']] = $activity['value'];
  }
}

$view = new view();
$view->name = 'rep_my_case_activities';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_case_activity';
$view->human_name = 'Case Actitivities for a Representative';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_expert_mycases_get_role_ids(array('Representative'));
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id_1' => 'id_1',
  'id' => 'id',
  'subject' => 'subject',
  'start_date' => 'start_date',
);
$handler->display->display_options['style_options']['class'] = '';
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'id_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'subject' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'start_date' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Relationship: CiviCRM Case Activity: Case Activity's Activity ID */
$handler->display->display_options['relationships']['activity_id']['id'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['activity_id']['field'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['required'] = TRUE;
/* Header: Global: PHP */
$handler->display->display_options['header']['php']['id'] = 'php';
$handler->display->display_options['header']['php']['table'] = 'views';
$handler->display->display_options['header']['php']['field'] = 'php';
$handler->display->display_options['header']['php']['empty'] = TRUE;
$handler->display->display_options['header']['php']['php_output'] = '
   <?php $case_id = reset($view->args); ?>
   <a href="/customer/rep/new-contact-with-customer/<?php echo $case_id ?>?destination=/customer/case-details/<?php echo $case_id ?>" class="button">Add summary of contact with customer</a>
';
/* Field: CiviCRM Activities: Scheduled Activity Date */
$handler->display->display_options['fields']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['activity_date_time']['date_format'] = 'custom';
$handler->display->display_options['fields']['activity_date_time']['custom_date_format'] = 'd M Y';
$handler->display->display_options['fields']['activity_date_time']['second_date_format'] = 'long';
/* Field: CiviCRM Activities: Activity Type */
$handler->display->display_options['fields']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['fields']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['fields']['activity_type']['relationship'] = 'activity_id';

/* Field: CiviCRM Activities: Subject */
$handler->display->display_options['fields']['subject_1']['id'] = 'subject_1';
$handler->display->display_options['fields']['subject_1']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['subject_1']['field'] = 'subject';
$handler->display->display_options['fields']['subject_1']['relationship'] = 'activity_id';
/* Field: CiviCRM Activities: Activity ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: Global: View */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['label'] = 'With';
$handler->display->display_options['fields']['view']['view'] = 'activity_contacts_expert_';
$handler->display->display_options['fields']['view']['arguments'] = '3/[!id]';
/* Field: Global: View */
$handler->display->display_options['fields']['view_1']['id'] = 'view_1';
$handler->display->display_options['fields']['view_1']['table'] = 'views';
$handler->display->display_options['fields']['view_1']['field'] = 'view';
$handler->display->display_options['fields']['view_1']['label'] = 'Assigned to';
$handler->display->display_options['fields']['view_1']['view'] = 'activity_contacts_expert_';
$handler->display->display_options['fields']['view_1']['arguments'] = '1/[!id]';
/* Field: Global: View */
$handler->display->display_options['fields']['view_2']['id'] = 'view_2';
$handler->display->display_options['fields']['view_2']['table'] = 'views';
$handler->display->display_options['fields']['view_2']['field'] = 'view';
$handler->display->display_options['fields']['view_2']['label'] = 'Reported by';
$handler->display->display_options['fields']['view_2']['element_default_classes'] = FALSE;
$handler->display->display_options['fields']['view_2']['view'] = 'activity_contacts_expert_';
$handler->display->display_options['fields']['view_2']['arguments'] = '2/[!id]';
/* Field: View details */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['label'] = '';
$handler->display->display_options['fields']['php']['exclude'] = FALSE;
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_value'] = '
   $destination="/customer/case-details/" . $view->args[0];
   return _pum_expert_show_activity_details($row->id, $row->activity_type,$destination);
';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
$handler->display->display_options['fields']['php']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['text'] = 'View details';
$handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['path'] = '[php]';
$handler->display->display_options['fields']['php']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
/* Contextual filter: CiviCRM Cases: Case ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_case';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'empty';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
/* Filter criterion: CiviCRM Activities: Current Revision */
$handler->display->display_options['filters']['is_current_revision']['id'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_current_revision']['field'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['is_current_revision']['value'] = '1';
/* Filter criterion: CiviCRM Cases: Is Deleted */
$handler->display->display_options['filters']['is_deleted']['id'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['is_deleted']['field'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['value'] = '0';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['activity_type']['value'] = $activity_ids;
