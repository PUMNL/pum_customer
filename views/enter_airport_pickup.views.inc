<?php

$activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));
$pick_info_activity = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Pick Up Information', 'option_group_id' => $activity_type_option_group));

$travel_data = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'travel_data'));
$departure_time = civicrm_api3('CustomField', 'getvalue', array('name' => 'return_departure_time', 'return' => 'column_name', 'custom_group_id' => $travel_data['id']));
$arrival_time = civicrm_api3('CustomField', 'getvalue', array('name' => 'arrival_time', 'return' => 'column_name', 'custom_group_id' => $travel_data['id']));
$destination = civicrm_api3('CustomField', 'getvalue', array('name' => 'destination', 'return' => 'column_name', 'custom_group_id' => $travel_data['id']));
$flight_nr = civicrm_api3('CustomField', 'getvalue', array('name' => 'flight_number', 'return' => 'column_name', 'custom_group_id' => $travel_data['id']));
$return_flight_number = civicrm_api3('CustomField', 'getvalue', array('name' => 'return_flight_number', 'return' => 'column_name', 'custom_group_id' => $travel_data['id']));

$view = new view();
$view->name = 'enter_airport_pickup_info';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_case_activity';
$view->human_name = 'Enter airport pickup info';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Enter airport pickup info';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Customer', 'Customer (contact)', 'Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
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
);
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Explenation';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'When airport pick up information is available, you will find the details here. You will then also be able to provide the details of the pick up person and accommodation.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: CiviCRM Case Activity: Case Activity's Activity ID */
$handler->display->display_options['relationships']['activity_id']['id'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['activity_id']['field'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['label'] = 'Activity';
$handler->display->display_options['relationships']['activity_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Activity: Case ID */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['relationship'] = 'activity_id';
$handler->display->display_options['relationships']['case_id']['label'] = 'Case';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Parent case: Parent case */
$handler->display->display_options['relationships']['case_id_1']['id'] = 'case_id_1';
$handler->display->display_options['relationships']['case_id_1']['table'] = 'civicrm_value_travel_parent';
$handler->display->display_options['relationships']['case_id_1']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id_1']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['case_id_1']['label'] = 'Parent case';
$handler->display->display_options['relationships']['case_id_1']['required'] = TRUE;
/* Relationship: CiviCRM Cases: CiviCRM Relationship (starting from contact case ID) */
$handler->display->display_options['relationships']['relationship_id']['id'] = 'relationship_id';
$handler->display->display_options['relationships']['relationship_id']['table'] = 'civicrm_case';
$handler->display->display_options['relationships']['relationship_id']['field'] = 'relationship_id';
$handler->display->display_options['relationships']['relationship_id']['relationship'] = 'case_id_1';
$handler->display->display_options['relationships']['relationship_id']['label'] = 'CiviCRM Case role';
$handler->display->display_options['relationships']['relationship_id']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id']['relationship_type'] = '0';
/* Relationship: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['relationships']['contact_id_b_']['id'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['table'] = 'civicrm_relationship';
$handler->display->display_options['relationships']['contact_id_b_']['field'] = 'contact_id_b_';
$handler->display->display_options['relationships']['contact_id_b_']['relationship'] = 'relationship_id';
$handler->display->display_options['relationships']['contact_id_b_']['label'] = 'Case contact';
$handler->display->display_options['relationships']['contact_id_b_']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['relationship'] = 'contact_id_b_';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id_1']['id'] = 'contact_id_1';
$handler->display->display_options['relationships']['contact_id_1']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id_1']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id_1']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['contact_id_1']['label'] = 'Traveler';
$handler->display->display_options['relationships']['contact_id_1']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['relationship'] = 'case_id_1';
$handler->display->display_options['relationships']['contact_id']['label'] = 'Customer';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Activities: Activity ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_3']['id'] = 'id_3';
$handler->display->display_options['fields']['id_3']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_3']['field'] = 'id';
$handler->display->display_options['fields']['id_3']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['id_3']['label'] = '';
$handler->display->display_options['fields']['id_3']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_3']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_3']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name_1']['id'] = 'display_name_1';
$handler->display->display_options['fields']['display_name_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name_1']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name_1']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['display_name_1']['label'] = 'Customer';
$handler->display->display_options['fields']['display_name_1']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name_1']['alter']['path'] = 'customer-profile/[id_3]';
$handler->display->display_options['fields']['display_name_1']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['display_name_1']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['label'] = 'Traveler';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id_1';
/* Field: CiviCRM Custom: Travel Data: Arrival date/time */
$handler->display->display_options['fields']['arrival_time']['id'] = 'arrival_time';
$handler->display->display_options['fields']['arrival_time']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['arrival_time']['field'] = $arrival_time;
$handler->display->display_options['fields']['arrival_time']['relationship'] = 'case_id';
$handler->display->display_options['fields']['arrival_time']['date_format'] = 'short';
/* Field: CiviCRM Custom: Travel Data: Destination */
$handler->display->display_options['fields']['destination']['id'] = 'destination';
$handler->display->display_options['fields']['destination']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['destination']['field'] = $destination;
$handler->display->display_options['fields']['destination']['relationship'] = 'case_id';
$handler->display->display_options['fields']['destination']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Travel Data: Flight number */
$handler->display->display_options['fields']['flight_number']['id'] = 'flight_number';
$handler->display->display_options['fields']['flight_number']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['flight_number']['field'] = $flight_nr;
$handler->display->display_options['fields']['flight_number']['relationship'] = 'case_id';
$handler->display->display_options['fields']['flight_number']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Travel Data: Departure date/time */
$handler->display->display_options['fields']['departure_time']['id'] = 'departure_time';
$handler->display->display_options['fields']['departure_time']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['departure_time']['field'] = $departure_time;
$handler->display->display_options['fields']['departure_time']['label'] = '(Return) Departure time';
$handler->display->display_options['fields']['departure_time']['relationship'] = 'case_id';
$handler->display->display_options['fields']['departure_time']['date_format'] = 'short';
/* Field: CiviCRM Custom: Travel Data: Flight number */
$handler->display->display_options['fields']['return_flight_number']['id'] = 'return_flight_number';
$handler->display->display_options['fields']['return_flight_number']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['return_flight_number']['field'] = $return_flight_number;
$handler->display->display_options['fields']['return_flight_number']['relationship'] = 'case_id';
$handler->display->display_options['fields']['return_flight_number']['alter']['strip_tags'] = TRUE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Provide pickup info';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'enter-pickup-info/form?cid2=[id]&caseid=[id_1]&aid=[id_2]';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Filter criterion: CiviCRM Activities: Current Revision */
$handler->display->display_options['filters']['is_current_revision']['id'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_current_revision']['field'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['is_current_revision']['value'] = '1';
/* Filter criterion: CiviCRM Activities: Activity Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['status']['value'] = array(
  1 => '1', //scheduled
);
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['activity_type']['value'] = array(
  $pick_info_activity => $pick_info_activity,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'enter-airport-pickup-info';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Enter airport pickup info';
$handler->display->display_options['menu']['weight'] = '0';
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
/* Header: Global: Result summary */
$handler->display->display_options['header']['result']['id'] = 'result';
$handler->display->display_options['header']['result']['table'] = 'views';
$handler->display->display_options['header']['result']['field'] = 'result';
$handler->display->display_options['header']['result']['content'] = '<a href="/enter-airport-pickup-info">Airport Pickup info (@total)</a>';
$handler->display->display_options['defaults']['empty'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Activities: Activity ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['display_name']['exclude'] = TRUE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Custom: Travel Data: Arrival date/time */
$handler->display->display_options['fields']['arrival_time']['id'] = 'arrival_time';
$handler->display->display_options['fields']['arrival_time']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['arrival_time']['field'] = $arrival_time;
$handler->display->display_options['fields']['arrival_time']['relationship'] = 'case_id';
$handler->display->display_options['fields']['arrival_time']['exclude'] = TRUE;
$handler->display->display_options['fields']['arrival_time']['date_format'] = 'short';
$handler->display->display_options['fields']['arrival_time']['second_date_format'] = 'long';
/* Field: CiviCRM Custom: Travel Data: Destination */
$handler->display->display_options['fields']['destination']['id'] = 'destination';
$handler->display->display_options['fields']['destination']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['destination']['field'] = $destination;
$handler->display->display_options['fields']['destination']['relationship'] = 'case_id';
$handler->display->display_options['fields']['destination']['exclude'] = TRUE;
$handler->display->display_options['fields']['destination']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Travel Data: Flight number */
$handler->display->display_options['fields']['flight_number']['id'] = 'flight_number';
$handler->display->display_options['fields']['flight_number']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['flight_number']['field'] = $flight_nr;
$handler->display->display_options['fields']['flight_number']['relationship'] = 'case_id';
$handler->display->display_options['fields']['flight_number']['exclude'] = TRUE;
$handler->display->display_options['fields']['flight_number']['alter']['strip_tags'] = TRUE;
/* Field: CiviCRM Custom: Travel Data: (Return) Departure date/time */
$handler->display->display_options['fields']['departure_time']['id'] = 'departure_time';
$handler->display->display_options['fields']['departure_time']['table'] = $travel_data['table_name'];
$handler->display->display_options['fields']['departure_time']['field'] = $departure_time;
$handler->display->display_options['fields']['departure_time']['relationship'] = 'case_id';
$handler->display->display_options['fields']['departure_time']['label'] = '(Return) Departure time';
$handler->display->display_options['fields']['departure_time']['exclude'] = TRUE;
$handler->display->display_options['fields']['departure_time']['date_format'] = 'short';
$handler->display->display_options['fields']['departure_time']['second_date_format'] = 'long';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Provide pickup info';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'enter-pickup-info/form?cid2=[id]&caseid=[id_1]&aid=[id_2]';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_1']['hide_empty'] = TRUE;
$translatables['enter_airport_pickup_info'] = array(
  t('Master'),
  t('Enter airport pickup info'),
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
  t('Explenation'),
  t('When you are asked to provide airport pickup information you will see here for who you have to provide those details.'),
  t('Activity'),
  t('Activity Contact ID'),
  t('Drupal User'),
  t('Case'),
  t('Traveler'),
  t('Case ID'),
  t('.'),
  t('Display Name'),
  t('Arrival date/time'),
  t('Departure date/time'),
  t('Destination'),
  t('Flight number'),
  t('Provide pickup info'),
  t('Page'),
  t('My Work Count Item - Block'),
  t('Airport Pickup info (@total)'),
);
