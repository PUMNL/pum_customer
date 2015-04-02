<?php

$config = pum_customer_mycases_config::singleton();
$conditions = $config->getConditions();

$authorised_contact_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Has authorised', 'return' => 'id'));
$local_rep_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Representative is', 'return' => 'id'));

$view = new view();
$view->name = 'conditions';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_activity';
$view->human_name = 'Conditions';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Conditions';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Customer', 'Customer (contact)', 'Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'details' => 'details',
  'subject' => 'subject',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'case_type' => 'case_type',
  'activity_date_time' => 'activity_date_time',
  'start_date' => 'start_date',
  'end_date' => 'end_date',
  'subject' => 'subject',
  'details' => 'details',
  'display_name' => 'display_name',
  'nothing' => 'nothing',
);
$handler->display->display_options['style_options']['default'] = 'activity_date_time';
$handler->display->display_options['style_options']['info'] = array(
  'id' => array(
    'sortable' => 0,
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
  'activity_date_time' => array(
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
  'subject' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'details' => array(
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
$handler->display->display_options['empty']['area']['content'] = 'There are no conditions';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: CiviCRM Case Activity: Case ID */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['label'] = 'Case';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['contact_id']['label'] = 'Client';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from contact A) */
$handler->display->display_options['relationships']['relationship_id_a']['id'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_a']['field'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['relationship'] = 'contact_id';
$handler->display->display_options['relationships']['relationship_id_a']['label'] = 'Rep/Authorised relationship';
$handler->display->display_options['relationships']['relationship_id_a']['required'] = TRUE;
/* Relationship: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['relationships']['contact_id_b_']['id'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_b_']['field'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['relationship'] = 'relationship_id_a';
$handler->display->display_options['relationships']['contact_id_b_']['label'] = 'Rep/Authorised';
$handler->display->display_options['relationships']['contact_id_b_']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['relationship'] = 'contact_id_b_';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Field: CiviCRM Activities: Activity ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['relationship'] = 'case_id';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Cases: Contact ID */
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
$handler->display->display_options['fields']['activity_date_time']['label'] = 'Date';
$handler->display->display_options['fields']['activity_date_time']['alter']['text'] = '[display_name] ([activity_date_time])';
$handler->display->display_options['fields']['activity_date_time']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['activity_date_time']['date_format'] = 'custom';
$handler->display->display_options['fields']['activity_date_time']['custom_date_format'] = 'Y-m-d';
$handler->display->display_options['fields']['activity_date_time']['second_date_format'] = 'long';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['display_name']['label'] = 'Customer';
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
$handler->display->display_options['fields']['display_name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name']['alter']['path'] = '/customer-profile/[id_2]';
$handler->display->display_options['fields']['display_name']['alter']['absolute'] = TRUE;
/* Field: CiviCRM Cases: Case Type */
$handler->display->display_options['fields']['case_type']['id'] = 'case_type';
$handler->display->display_options['fields']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['case_type']['field'] = 'case_type';
$handler->display->display_options['fields']['case_type']['relationship'] = 'case_id';
$handler->display->display_options['fields']['case_type']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['case_type']['alter']['path'] = '/customer/case-details/[id_1]';
$handler->display->display_options['fields']['case_type']['alter']['absolute'] = TRUE;
/* Field: CiviCRM Activities: Activity Type */
$handler->display->display_options['fields']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['fields']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['fields']['activity_type']['relationship'] = 'activity_id';
/* Field: CiviCRM Activities: Subject */
$handler->display->display_options['fields']['subject']['id'] = 'subject';
$handler->display->display_options['fields']['subject']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['subject']['field'] = 'subject';
$handler->display->display_options['fields']['subject']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['subject']['alter']['path'] = 'customer/condition-details/[id]';
$handler->display->display_options['fields']['subject']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['subject']['empty'] = '<a href="/customer/condition-details/[id]">View condition</a>';
/* Field: CiviCRM Activities: Subject */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['label'] = 'Status';
/* Contextual filter: CiviCRM Cases: Case ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_case';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['relationship'] = 'case_id';
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
/* Filter criterion: CiviCRM Activities: Is Deleted */
$handler->display->display_options['filters']['is_deleted']['id'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_deleted']['field'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['is_deleted']['value'] = '0';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['activity_type']['value'] = $conditions;
/* Filter criterion: CiviCRM Relationships: Relationship Type A-to-B */
$handler->display->display_options['filters']['relationship_type']['id'] = 'relationship_type';
$handler->display->display_options['filters']['relationship_type']['table'] = 'civicrm_relationship';
$handler->display->display_options['filters']['relationship_type']['field'] = 'relationship_type';
$handler->display->display_options['filters']['relationship_type']['relationship'] = 'relationship_id_a';
$handler->display->display_options['filters']['relationship_type']['value'] = array(
  $local_rep_rel_type_id => $local_rep_rel_type_id,
  $authorised_contact_rel_type_id => $authorised_contact_rel_type_id,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/conditions';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Conditions';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['conditions'] = array(
  t('Master'),
  t('Conditions'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('There are no conditions'),
  t('Case'),
  t('Client'),
  t('Rep/Authorised relationship'),
  t('Rep/Authorised'),
  t('Drupal User'),
  t('.'),
  t('Case Type'),
  t('Case subject'),
  t('Start Date'),
  t('End Date'),
  t('Subject'),
  t('Customer'),
  t('Page'),
);
