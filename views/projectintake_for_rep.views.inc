<?php
$case_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_type'));
$project_intake_case_type_id = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Projectintake', 'option_group_id' => $case_type_option_group));
$case_status_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_status'));
$error_case_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Error', 'option_group_id' => $case_status_option_group));
$activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));
$open_case_act_id = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Open Case', 'option_group_id' => $activity_type_option_group));
$local_rep_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Representative is', 'return' => 'id'));

$cgroup_intake = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Intake'));
$asses_rep_field = civicrm_api3('CustomField', 'getsingle', array('name' => 'Assessment_Rep', 'custom_group_id' => $cgroup_intake['id']));


$view = new view();
$view->name = 'projectintake_for_local_rep';
$view->description = '';
$view->tag = 'projectintake';
$view->base_table = 'civicrm_case';
$view->human_name = 'New project requests (for Representative)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'New project requests';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id_1' => 'id_1',
  'id' => 'id',
  'id_2' => 'id_2',
  'activity_date_time' => 'activity_date_time',
  'subject' => 'subject',
  'display_name' => 'display_name',
  'nothing_1' => 'nothing_1',
  'nothing' => 'nothing',
);
$handler->display->display_options['style_options']['default'] = 'activity_date_time';
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
  'id_2' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'activity_date_time' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
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
  'display_name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'nothing_1' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'nothing' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Footer: Global: PHP */
$handler->display->display_options['footer']['redirect_by_one']['id'] = 'redirect_by_one';
$handler->display->display_options['footer']['redirect_by_one']['table'] = 'views';
$handler->display->display_options['footer']['redirect_by_one']['field'] = 'php';
$handler->display->display_options['footer']['redirect_by_one']['php_output'] = '<?php
if (!(isset($view->preview) && $view->preview) && count($results)==1) {
  drupal_goto(\'representative/projects-requests/asses/\', array(
    \'absolute\' => true,
    \'query\' => array(
      \'cid2\' => $results[0]->civicrm_contact_civicrm_case_contact_id,
      \'caseid\' => $results[0]->id
    )));
}
?>';
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['label'] = 'Customer';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from contact A) */
$handler->display->display_options['relationships']['relationship_id_a']['id'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_a']['field'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['relationship'] = 'contact_id';
$handler->display->display_options['relationships']['relationship_id_a']['label'] = 'Representative (relationship)';
$handler->display->display_options['relationships']['relationship_id_a']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_a']['relationship_type'] = $local_rep_rel_type_id;
/* Relationship: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['relationships']['contact_id_b_']['id'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_b_']['field'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['relationship'] = 'relationship_id_a';
$handler->display->display_options['relationships']['contact_id_b_']['label'] = 'Representative';
$handler->display->display_options['relationships']['contact_id_b_']['required'] = TRUE;
/* Relationship: CiviCRM Case Activity: Case Activity's Activity ID */
$handler->display->display_options['relationships']['activity_id']['id'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['activity_id']['field'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['label'] = 'Case Activity';
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['relationship'] = 'contact_id_b_';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Activities: Scheduled Activity Date */
$handler->display->display_options['fields']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['activity_date_time']['label'] = 'Request date';
$handler->display->display_options['fields']['activity_date_time']['date_format'] = 'custom';
$handler->display->display_options['fields']['activity_date_time']['custom_date_format'] = 'j F Y';
$handler->display->display_options['fields']['activity_date_time']['second_date_format'] = 'long';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['display_name']['label'] = 'Customer';
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'View/Assess Requests';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = '/representative/projects-requests/asses?cid2=[id_2]&caseid=[id_1]';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Filter criterion: CiviCRM Cases: Case Type */
$handler->display->display_options['filters']['case_type_1']['id'] = 'case_type_1';
$handler->display->display_options['filters']['case_type_1']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['case_type_1']['field'] = 'case_type';
$handler->display->display_options['filters']['case_type_1']['value'] = array(
	$project_intake_case_type_id => $project_intake_case_type_id,
);
/* Filter criterion: CiviCRM Cases: Is Deleted */
$handler->display->display_options['filters']['is_deleted_1']['id'] = 'is_deleted_1';
$handler->display->display_options['filters']['is_deleted_1']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['is_deleted_1']['field'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted_1']['value'] = '0';
/* Filter criterion: CiviCRM Cases: Case Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['operator'] = 'not in';
$handler->display->display_options['filters']['status']['value'] = array(
  $error_case_status => $error_case_status,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['activity_type']['value'] = array(
	$open_case_act_id => $open_case_act_id,
);
/* Filter criterion: CiviCRM Activities: Current Revision */
$handler->display->display_options['filters']['is_current_revision']['id'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_current_revision']['field'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['is_current_revision']['value'] = '1';
/* Filter criterion: CiviCRM Activities: Is Deleted */
$handler->display->display_options['filters']['is_deleted']['id'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_deleted']['field'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['is_deleted']['value'] = '0';
/* Filter criterion: CiviCRM Custom: Intake: Assessment Rep */
$handler->display->display_options['filters']['assessment_rep']['id'] = $asses_rep_field['column_name'];
$handler->display->display_options['filters']['assessment_rep']['table'] = $cgroup_intake['table_name'];
$handler->display->display_options['filters']['assessment_rep']['field'] = $asses_rep_field['column_name'];
$handler->display->display_options['filters']['assessment_rep']['operator'] = 'empty';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'representative/new-projects-requests';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'New project requests';
$handler->display->display_options['menu']['weight'] = '-3';
$handler->display->display_options['menu']['name'] = 'navigation';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
/* Display: My Work Count Item - Block */
$handler = $view->new_display('block', 'My Work Count Item - Block', 'block_1');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['header'] = FALSE;
$handler->display->display_options['defaults']['footer'] = FALSE;
/* Header: Global: Result summary */
$handler->display->display_options['header']['result']['id'] = 'result';
$handler->display->display_options['header']['result']['table'] = 'views';
$handler->display->display_options['header']['result']['field'] = 'result';
$handler->display->display_options['header']['result']['content'] = '<a href="/representative/new-projects-requests">New Project Requests (@total)</a>';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Activities: Scheduled Activity Date */
$handler->display->display_options['fields']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['activity_date_time']['label'] = 'Request date';
$handler->display->display_options['fields']['activity_date_time']['exclude'] = TRUE;
$handler->display->display_options['fields']['activity_date_time']['date_format'] = 'long';
$handler->display->display_options['fields']['activity_date_time']['second_date_format'] = 'long';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['display_name']['label'] = 'Customer';
$handler->display->display_options['fields']['display_name']['exclude'] = TRUE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
$handler->display->display_options['fields']['nothing_2']['table'] = 'views';
$handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_2']['label'] = '';
$handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_2']['hide_empty'] = TRUE;

