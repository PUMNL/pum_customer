<?php

$case_status = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_status'));
$case_type = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_type'));

$submit_case_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Submitted', 'option_group_id' => $case_status));
$matching_case_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Matching', 'option_group_id' => $case_status));
$preparation_case_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Preparation', 'option_group_id' => $case_status));
$execution_case_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Execution', 'option_group_id' => $case_status));
$debriefing_case_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Debriefing', 'option_group_id' => $case_status));

$advice_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Advice', 'option_group_id' => $case_type));
$business_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Business', 'option_group_id' => $case_type));
$remote_coaching_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'RemoteCoaching', 'option_group_id' => $case_type));
$seminar_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Seminar', 'option_group_id' => $case_type));
$grant_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Grant', 'option_group_id' => $case_type));

$expert_rel_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Expert', 'return' => 'id'));
$representative_rel_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Representative is', 'return' => 'id'));
$main_activity_info = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'main_activity_info'));
$start_date = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_start_date', 'custom_group_id' => $main_activity_info['id']));
$end_date = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_end_date', 'custom_group_id' => $main_activity_info['id']));

$view = new view();
$view->name = 'rep_all_cases';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_case_project';
$view->human_name = 'All cases (for representative)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'By current main activity';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'id_1' => 'id_1',
  'display_name' => 'display_name',
  'case_type' => 'case_type',
  'status' => 'status',
  'nothing' => 'nothing',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
    'id' => array(
        'sortable' => 0,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'id_1' => array(
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
    'display_name' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'case_type' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'status' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'start_date' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'end_date' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'display_name_1' => array(
        'sortable' => 1,
        'default_sort_order' => 'asc',
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'php' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
    'php_1' => array(
        'align' => '',
        'separator' => '',
        'empty_column' => 0,
    ),
);
/* Relationship: CiviCRM Case Project: Case ID */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_case_project';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Project: Project ID */
$handler->display->display_options['relationships']['project_id']['id'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['table'] = 'civicrm_case_project';
$handler->display->display_options['relationships']['project_id']['field'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['contact_id']['label'] = 'Client';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Relationship: CiviCRM Cases: CiviCRM Relationship (starting from contact case ID) */
$handler->display->display_options['relationships']['relationship_id']['id'] = 'relationship_id';
$handler->display->display_options['relationships']['relationship_id']['table'] = 'civicrm_case';
$handler->display->display_options['relationships']['relationship_id']['field'] = 'relationship_id';
$handler->display->display_options['relationships']['relationship_id']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['relationship_id']['label'] = 'expert_relationship';
$handler->display->display_options['relationships']['relationship_id']['relationship_type'] = $expert_rel_id;
/* Relationship: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['relationships']['contact_id_b_']['id'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_b_']['field'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['relationship'] = 'relationship_id';
$handler->display->display_options['relationships']['contact_id_b_']['label'] = 'Expert';
/* Relationship: CiviCRM Cases: CiviCRM Relationship (starting from contact case ID) */
$handler->display->display_options['relationships']['relationship_id_1']['id'] = 'relationship_id_1';
$handler->display->display_options['relationships']['relationship_id_1']['table'] = 'civicrm_case';
$handler->display->display_options['relationships']['relationship_id_1']['field'] = 'relationship_id';
$handler->display->display_options['relationships']['relationship_id_1']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['relationship_id_1']['label'] = 'Representative relationship';
$handler->display->display_options['relationships']['relationship_id_1']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_1']['relationship_type'] = $representative_rel_id;
/* Relationship: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['relationships']['contact_id_b__1']['id'] = 'contact_id_b__1';
$handler->display->display_options['relationships']['contact_id_b__1']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_b__1']['field'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b__1']['relationship'] = 'relationship_id_1';
$handler->display->display_options['relationships']['contact_id_b__1']['label'] = 'Representative';
$handler->display->display_options['relationships']['contact_id_b__1']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['relationship'] = 'contact_id_b__1';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['relationship'] = 'case_id';
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'contact_id_b_';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['display_name']['label'] = 'Client';
$handler->display->display_options['fields']['display_name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name']['alter']['path'] = 'customer-profile/[id_1]';
$handler->display->display_options['fields']['display_name']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Cases: Case Type */
$handler->display->display_options['fields']['case_type']['id'] = 'case_type';
$handler->display->display_options['fields']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['case_type']['field'] = 'case_type';
$handler->display->display_options['fields']['case_type']['relationship'] = 'case_id';
/* Field: CiviCRM Cases: Case Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['relationship'] = 'case_id';
$handler->display->display_options['fields']['status']['label'] = 'Status';
/* Field: CiviCRM Custom: (Main) Activity information: Activity Start Date */
$handler->display->display_options['fields']['start_date']['id'] = 'start_date';
$handler->display->display_options['fields']['start_date']['table'] = $main_activity_info['table_name'];
$handler->display->display_options['fields']['start_date']['field'] = $start_date['column_name'];
$handler->display->display_options['fields']['start_date']['label'] = 'Start Date';
$handler->display->display_options['fields']['start_date']['relationship'] = 'case_id';
$handler->display->display_options['fields']['start_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['start_date']['custom_date_format'] = 'j F Y';
$handler->display->display_options['fields']['start_date']['second_date_format'] = 'long';
/* Field: CiviCRM Custom: (Main) Activity information: Activity End Date */
$handler->display->display_options['fields']['end_date']['id'] = 'end_date';
$handler->display->display_options['fields']['end_date']['table'] = $main_activity_info['table_name'];
$handler->display->display_options['fields']['end_date']['field'] = $end_date['column_name'];
$handler->display->display_options['fields']['end_date']['label'] = 'End Date';
$handler->display->display_options['fields']['end_date']['relationship'] = 'case_id';
$handler->display->display_options['fields']['end_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['end_date']['custom_date_format'] = 'j F Y';
$handler->display->display_options['fields']['end_date']['second_date_format'] = 'long';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name_1']['id'] = 'display_name_1';
$handler->display->display_options['fields']['display_name_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name_1']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name_1']['relationship'] = 'contact_id_b_';
$handler->display->display_options['fields']['display_name_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['display_name_1']['label'] = 'Expert';
$handler->display->display_options['fields']['display_name_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name_1']['alter']['path'] = 'customer/expert/[id_2]/[id]';
$handler->display->display_options['fields']['display_name_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['display_name_1']['link_to_civicrm_contact'] = 0;
/* Field: Global: PHP */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['label'] = 'Expert';
$handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['path'] = 'customer/expert/[id_2]/[id]';
$handler->display->display_options['fields']['php']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_value'] = 'if (pum_customer_check_case_for_matching($row->status)) {
  return \'\';
}
return $row->display_name_1;';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php_1']['id'] = 'php_1';
$handler->display->display_options['fields']['php_1']['table'] = 'views';
$handler->display->display_options['fields']['php_1']['field'] = 'php';
$handler->display->display_options['fields']['php_1']['label'] = '';
$handler->display->display_options['fields']['php_1']['exclude'] = FALSE;
$handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php_1']['php_value'] = 'return _pum_customer_link_to_case_details($row->id, $row->case_type);';
$handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
$handler->display->display_options['fields']['php_1']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['php_1']['alter']['text'] = 'View case';
$handler->display->display_options['fields']['php_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php_1']['alter']['path'] = '[php_1]';
$handler->display->display_options['fields']['php_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php_1']['element_label_colon'] = FALSE;
/* Sort criterion: CiviCRM Cases: Case Status */
$handler->display->display_options['sorts']['status']['id'] = 'status';
$handler->display->display_options['sorts']['status']['table'] = 'civicrm_case';
$handler->display->display_options['sorts']['status']['field'] = 'status';
$handler->display->display_options['sorts']['status']['relationship'] = 'case_id';
$handler->display->display_options['sorts']['status']['order'] = 'weight';
/* Sort criterion: CiviCRM Custom: (Main) Activity information: Activity Start Date */
$handler->display->display_options['sorts']['start_date']['id'] = 'start_date';
$handler->display->display_options['sorts']['start_date']['table'] = $main_activity_info['table_name'];
$handler->display->display_options['sorts']['start_date']['field'] = $start_date['column_name'];
$handler->display->display_options['sorts']['start_date']['relationship'] = 'case_id';
/* Filter criterion: CiviCRM Cases: Case Type */
$handler->display->display_options['filters']['case_type']['id'] = 'case_type';
$handler->display->display_options['filters']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['case_type']['field'] = 'case_type';
$handler->display->display_options['filters']['case_type']['relationship'] = 'case_id';
$handler->display->display_options['filters']['case_type']['operator'] = 'in';
$handler->display->display_options['filters']['case_type']['value'] = array(
    $advice_case_type => $advice_case_type,
    $business_case_type => $business_case_type,
    $grant_case_type => $grant_case_type,
    $seminar_case_type => $seminar_case_type,
    $remote_coaching_case_type => $remote_coaching_case_type,
);
/* Filter criterion: CiviCRM Cases: Case Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'case_id';
$handler->display->display_options['filters']['status']['operator'] = 'in';
$handler->display->display_options['filters']['status']['value'] = array(
  $submit_case_status => $submit_case_status,
  $matching_case_status => $matching_case_status,
  $preparation_case_status => $preparation_case_status,
  $execution_case_status => $execution_case_status,
  $debriefing_case_status => $debriefing_case_status,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/by-main-activity';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'By current main activity';
$handler->display->display_options['menu']['name'] = 'menu-my-projects';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['project_cases_for_expert_'] = array(
  t('Master'),
  t('Project cases'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('CiviCRM Case'),
  t('CiviCRM Project'),
  t('Is active'),
  t('All'),
  t('Page'),
);
