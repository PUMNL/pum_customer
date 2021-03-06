<?php

$case_status = civicrm_api3('OptionGroup', 'getvalue', array('name' => 'case_status', 'return' => 'id'));
$error = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Error', 'return' => 'value', 'option_group_id' => $case_status));

$authorised_contact_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Has authorised', 'return' => 'id'));
$main_activity_info = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'main_activity_info'));
$start_date = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_start_date', 'custom_group_id' => $main_activity_info['id']));
$end_date = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_end_date', 'custom_group_id' => $main_activity_info['id']));

$view = new view();
$view->name = 'my_projects_by_organisation_for_customer_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_contact';
$view->human_name = 'My projects by customer (for customer)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'My projects by organisation';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Customer (contact)'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'id_1' => 'id_1',
  'display_name' => 'display_name',
  'title' => 'title',
  'start_date' => 'start_date',
  'end_date' => 'end_date',
  'nothing' => 'nothing',
);
$handler->display->display_options['style_options']['default'] = 'display_name';
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
  'display_name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
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
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'There are no active projects';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from Contact B) */
$handler->display->display_options['relationships']['relationship_id_b']['id'] = 'relationship_id_b';
$handler->display->display_options['relationships']['relationship_id_b']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_b']['field'] = 'relationship_id_b';
$handler->display->display_options['relationships']['relationship_id_b']['label'] = 'Expert relationship';
$handler->display->display_options['relationships']['relationship_id_b']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_b']['relationship_type'] = $authorised_contact_rel_type_id;
/* Relationship: CiviCRM Relationships: Case ID */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['relationship'] = 'relationship_id_b';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Relationships: Contact ID A */
$handler->display->display_options['relationships']['contact_id_a_']['id'] = 'contact_id_a_';
$handler->display->display_options['relationships']['contact_id_a_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_a_']['field'] = 'contact_id_a_';
$handler->display->display_options['relationships']['contact_id_a_']['relationship'] = 'relationship_id_b';
$handler->display->display_options['relationships']['contact_id_a_']['label'] = 'Customer';
$handler->display->display_options['relationships']['contact_id_a_']['required'] = TRUE;
/* Relationship: CiviCRM Case Project: Project ID */
$handler->display->display_options['relationships']['project_id']['id'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['table'] = 'civicrm_case_project';
$handler->display->display_options['relationships']['project_id']['field'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['project_id']['required'] = TRUE;
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Project: Project ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_project';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['relationship'] = 'project_id';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id_a_';
$handler->display->display_options['fields']['display_name']['label'] = 'Organisation';
$handler->display->display_options['fields']['display_name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name']['alter']['path'] = 'customer-profile/[id]';
$handler->display->display_options['fields']['display_name']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Project: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'civicrm_project';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'project_id';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'View project';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'customer-project/[id_1]';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Sort criterion: CiviCRM Contacts: Display Name */
$handler->display->display_options['sorts']['display_name']['id'] = 'display_name';
$handler->display->display_options['sorts']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['sorts']['display_name']['field'] = 'display_name';
$handler->display->display_options['sorts']['display_name']['relationship'] = 'contact_id_a_';
/* Sort criterion: CiviCRM Project: Start date */
$handler->display->display_options['sorts']['start_date']['id'] = 'start_date';
$handler->display->display_options['sorts']['start_date']['table'] = 'civicrm_project';
$handler->display->display_options['sorts']['start_date']['field'] = 'start_date';
$handler->display->display_options['sorts']['start_date']['relationship'] = 'project_id';
$handler->display->display_options['sorts']['start_date']['order'] = 'DESC';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'OR',
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$handler->display->display_options['filters']['uid_current']['group'] = 1;
/* Filter criterion: CiviCRM Cases: Case Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'case_id';
$handler->display->display_options['filters']['status']['operator'] = 'not in';
$handler->display->display_options['filters']['status']['value'] = array(
  $error => $error,
);
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: CiviCRM Project: End date */
$handler->display->display_options['filters']['end_date']['id'] = 'end_date';
$handler->display->display_options['filters']['end_date']['table'] = 'civicrm_project';
$handler->display->display_options['filters']['end_date']['field'] = 'end_date';
$handler->display->display_options['filters']['end_date']['relationship'] = 'project_id';
$handler->display->display_options['filters']['end_date']['operator'] = 'empty';
$handler->display->display_options['filters']['end_date']['group'] = 2;
$handler->display->display_options['filters']['end_date']['expose']['operator_id'] = 'end_date_op';
$handler->display->display_options['filters']['end_date']['expose']['label'] = 'End date';
$handler->display->display_options['filters']['end_date']['expose']['operator'] = 'end_date_op';
$handler->display->display_options['filters']['end_date']['expose']['identifier'] = 'end_date';
/* Filter criterion: CiviCRM Project: End date */
$handler->display->display_options['filters']['end_date_1']['id'] = 'end_date_1';
$handler->display->display_options['filters']['end_date_1']['table'] = 'civicrm_project';
$handler->display->display_options['filters']['end_date_1']['field'] = 'end_date';
$handler->display->display_options['filters']['end_date_1']['relationship'] = 'project_id';
$handler->display->display_options['filters']['end_date_1']['operator'] = '>=';
$handler->display->display_options['filters']['end_date_1']['value']['value'] = 'now';
$handler->display->display_options['filters']['end_date_1']['value']['type'] = 'offset';
$handler->display->display_options['filters']['end_date_1']['group'] = 2;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/my-projects-by-organisation';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'By Organisation';
$handler->display->display_options['menu']['name'] = 'menu-my-projects';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['my_cases_for_expert_'] = array(
  t('Master'),
  t('My cases'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« first'),
  t('‹ previous'),
  t('next ›'),
  t('last »'),
  t('Drupal User'),
  t('Expert relationship'),
  t('CiviCRM Case'),
  t('Customer'),
  t('.'),
  t('Case Type'),
  t('Start Date'),
  t('End Date'),
  t('Page'),
);
