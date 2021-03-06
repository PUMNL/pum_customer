<?php

$case_type_id = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_type'));
$travel_case_type_id = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'TravelCase', 'option_group_id' => $case_type_id));

$td_info = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'travel_data'));
$pickup = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'pickup'));

$inboundArrivalTime = civicrm_api3('CustomField', 'getvalue', array('name' => 'arrival_time', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));
$outboundDepartureTime = civicrm_api3('CustomField', 'getvalue', array('name' => 'return_departure_time', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));
$destination = civicrm_api3('CustomField', 'getvalue', array('name' => 'destination', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));
$flight_nr = civicrm_api3('CustomField', 'getvalue', array('name' => 'flight_number', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));
$return_travel_from = civicrm_api3('CustomField', 'getvalue', array('name' => 'return_from', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));
$return_flight_number = civicrm_api3('CustomField', 'getvalue', array('name' => 'return_flight_number', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));
$notes = civicrm_api3('CustomField', 'getvalue', array('name' => 'notes', 'return' => 'column_name', 'custom_group_id' => $td_info['id']));

$pickup_name = civicrm_api3('CustomField', 'getvalue', array('name' => 'pickup_name', 'return' => 'column_name', 'custom_group_id' => $pickup['id']));
$pickup_telephone = civicrm_api3('CustomField', 'getvalue', array('name' => 'pickup_telephone', 'return' => 'column_name', 'custom_group_id' => $pickup['id']));
$accommodation_name = civicrm_api3('CustomField', 'getvalue', array('name' => 'accommodation_name', 'return' => 'column_name', 'custom_group_id' => $pickup['id']));
$accommodation_telephone = civicrm_api3('CustomField', 'getvalue', array('name' => 'accommodation_telephone', 'return' => 'column_name', 'custom_group_id' => $pickup['id']));
$pickup_notes = civicrm_api3('CustomField', 'getvalue', array('name' => 'pickup_notes', 'return' => 'column_name', 'custom_group_id' => $pickup['id']));

$view = new view();
$view->name = 'pickup_info_for_customer_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_case';
$view->human_name = 'Pickup info (for customer and rep)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Pickup info';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'php';
$handler->display->display_options['access']['php_access'] = '$hasrole = FALSE;
$url = $_SERVER["REQUEST_URI"];
$url_path = parse_url($url, PHP_URL_PATH);
$case_id = explode("/",$_GET[\'q\']);

civicrm_initialize();
$contact_id = CRM_Core_Session::singleton()->getLoggedInContactID(); //$session->get(\'userID\');
$civi_config = CRM_Core_Config::singleton();
$civi_dsn = DB::parseDSN($civi_config->dsn);
$civicrm_db = $civi_dsn[\'database\'];

if (!empty($civicrm_db) && !empty($case_id[2])) {
	$relationships = db_query("SELECT case_id, contact_id FROM (
  SELECT rel.case_id AS \'case_id\', rel.contact_id_b AS \'contact_id\' FROM $civicrm_db.civicrm_case c
  LEFT JOIN $civicrm_db.civicrm_relationship rel ON c.id = rel.case_id
  LEFT JOIN $civicrm_db.civicrm_relationship_type rt ON rel.relationship_type_id = rt.id
  LEFT JOIN $civicrm_db.civicrm_case_contact cc ON cc.case_id = c.id
  WHERE rel.case_id = :case_id OR rel.case_id = (SELECT case_id FROM $civicrm_db.civicrm_value_travel_parent WHERE entity_id = :case_id) AND rel.is_active = :is_active
  GROUP BY rel.contact_id_b
  UNION ALL
  SELECT ccc.case_id, ccc.contact_id FROM $civicrm_db.civicrm_case_contact ccc WHERE ccc.case_id = :case_id OR ccc.case_id = (SELECT case_id FROM $civicrm_db.civicrm_value_travel_parent WHERE entity_id = :case_id) GROUP BY ccc.contact_id
  UNION ALL
  SELECT rel2.case_id AS \'case_id\', rel2.contact_id_b AS \'contact_id\' FROM $civicrm_db.civicrm_case c2
  LEFT JOIN $civicrm_db.civicrm_relationship rel2 ON c2.id = rel2.case_id
  LEFT JOIN $civicrm_db.civicrm_relationship_type rt2 ON rel2.relationship_type_id = rt2.id
  LEFT JOIN $civicrm_db.civicrm_case_contact cc2 ON cc2.case_id = c2.id
  WHERE rel2.case_id = (SELECT case_id FROM $civicrm_db.civicrm_value_travel_parent WHERE entity_id = :case_id) AND rel2.is_active = :is_active
) result
GROUP BY contact_id",
array(\':case_id\'=>check_plain($case_id[2]),\':is_active\'=>\'1\'))->fetchAll();

foreach($relationships as $rel) {
	if ($rel->contact_id == $contact_id) {
		$hasrole = TRUE;
	}
}
}
return $hasrole;';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: CiviCRM Parent case: Child case */
$handler->display->display_options['relationships']['entity_id']['id'] = 'entity_id';
$handler->display->display_options['relationships']['entity_id']['table'] = 'civicrm_value_travel_parent';
$handler->display->display_options['relationships']['entity_id']['field'] = 'entity_id';
$handler->display->display_options['relationships']['entity_id']['required'] = TRUE;
/* Relationship: CiviCRM Parent case: Parent case */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_value_travel_parent';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['relationship'] = 'entity_id';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['label'] = 'Client';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id_1']['id'] = 'contact_id_1';
$handler->display->display_options['relationships']['contact_id_1']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id_1']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id_1']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['contact_id_1']['label'] = 'Parent client';
$handler->display->display_options['relationships']['contact_id_1']['required'] = TRUE;
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['parent_id']['id'] = 'parent_id';
$handler->display->display_options['fields']['parent_id']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['parent_id']['field'] = 'id';
$handler->display->display_options['fields']['parent_id']['relationship'] = 'case_id';
$handler->display->display_options['fields']['parent_id']['label'] = '';
$handler->display->display_options['fields']['parent_id']['exclude'] = TRUE;
$handler->display->display_options['fields']['parent_id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['parent_id']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['fields']['contact_id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['contact_id']['field'] = 'id';
$handler->display->display_options['fields']['contact_id']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['contact_id']['label'] = '';
$handler->display->display_options['fields']['contact_id']['exclude'] = TRUE;
$handler->display->display_options['fields']['contact_id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['contact_id']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['display_name']['label'] = 'Client';
$handler->display->display_options['fields']['display_name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name']['alter']['path'] = 'customer-profile/[id_1]';
$handler->display->display_options['fields']['display_name']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
$handler->display->display_options['fields']['display_name']['element_type'] = 'span';
$handler->display->display_options['fields']['display_name']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['display_name']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Cases: Case Type */
$handler->display->display_options['fields']['case_type']['id'] = 'case_type';
$handler->display->display_options['fields']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['case_type']['field'] = 'case_type';
$handler->display->display_options['fields']['case_type']['relationship'] = 'case_id';
$handler->display->display_options['fields']['case_type']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['case_type']['alter']['path'] = 'customer/case-details/[parent_id]';
$handler->display->display_options['fields']['case_type']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['case_type']['element_type'] = 'span';
$handler->display->display_options['fields']['case_type']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['case_type']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Travel Data: Destination */
$handler->display->display_options['fields']['destination']['id'] = 'destination';
$handler->display->display_options['fields']['destination']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['destination']['field'] = $destination;
$handler->display->display_options['fields']['destination']['alter']['trim_whitespace'] = TRUE;
$handler->display->display_options['fields']['destination']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['destination']['element_type'] = 'span';
$handler->display->display_options['fields']['destination']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['destination']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Travel Data: Arrival date/time */
$handler->display->display_options['fields']['requested_departure_date']['id'] = 'requested_departure_date';
$handler->display->display_options['fields']['requested_departure_date']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['requested_departure_date']['field'] = $inboundArrivalTime;
$handler->display->display_options['fields']['requested_departure_date']['date_format'] = 'short';
$handler->display->display_options['fields']['requested_departure_date']['element_type'] = 'span';
$handler->display->display_options['fields']['requested_departure_date']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['requested_departure_date']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Travel Data: Flight number */
$handler->display->display_options['fields']['flight_number']['id'] = 'flight_number';
$handler->display->display_options['fields']['flight_number']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['flight_number']['field'] = $flight_nr;
$handler->display->display_options['fields']['flight_number']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['flight_number']['element_wrapper_type'] = 'p';
$handler->display->display_options['fields']['flight_number']['element_type'] = 'span';
$handler->display->display_options['fields']['flight_number']['element_label_type'] = 'strong';
/* Field: CiviCRM Custom: Travel Data: Return from */
$handler->display->display_options['fields']['return_travel_from']['id'] = 'return_travel_from';
$handler->display->display_options['fields']['return_travel_from']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['return_travel_from']['field'] = $return_travel_from;
$handler->display->display_options['fields']['return_travel_from']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['return_travel_from']['element_wrapper_type'] = 'p';
$handler->display->display_options['fields']['return_travel_from']['element_type'] = 'span';
$handler->display->display_options['fields']['return_travel_from']['element_label_type'] = 'strong';
/* Field: CiviCRM Custom: Info for travel agency: Requested return date */
$handler->display->display_options['fields']['requested_return_date']['id'] = 'requested_return_date';
$handler->display->display_options['fields']['requested_return_date']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['requested_return_date']['field'] = $outboundDepartureTime;
$handler->display->display_options['fields']['requested_return_date']['element_type'] = 'span';
$handler->display->display_options['fields']['requested_return_date']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['requested_return_date']['element_wrapper_type'] = 'p';
$handler->display->display_options['fields']['requested_return_date']['date_format'] = 'short';
/* Field: CiviCRM Custom: Travel Data: Flight number */
$handler->display->display_options['fields']['return_flight_number']['id'] = 'return_flight_number';
$handler->display->display_options['fields']['return_flight_number']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['return_flight_number']['field'] = $return_flight_number;
$handler->display->display_options['fields']['return_flight_number']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['return_flight_number']['element_wrapper_type'] = 'p';
$handler->display->display_options['fields']['return_flight_number']['element_type'] = 'span';
$handler->display->display_options['fields']['return_flight_number']['element_label_type'] = 'strong';
/* Field: CiviCRM Custom: Pickup Data: Notes */
$handler->display->display_options['fields']['notes_1']['id'] = 'notes_1';
$handler->display->display_options['fields']['notes_1']['table'] = $td_info['table_name'];
$handler->display->display_options['fields']['notes_1']['label'] = 'Travel remarks';
$handler->display->display_options['fields']['notes_1']['field'] = $notes;
$handler->display->display_options['fields']['notes_1']['alter']['nl2br'] = TRUE;
$handler->display->display_options['fields']['notes_1']['element_type'] = 'div';
$handler->display->display_options['fields']['notes_1']['element_label_type'] = 'h3';
$handler->display->display_options['fields']['notes_1']['element_wrapper_type'] = 'div';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Pickup confirmation';
$handler->display->display_options['fields']['nothing']['element_label_type'] = 'h3';
/* Field: CiviCRM Custom: Pickup Data: Name of pickup person */
$handler->display->display_options['fields']['pickup_name']['id'] = 'pickup_name';
$handler->display->display_options['fields']['pickup_name']['table'] = $pickup['table_name'];
$handler->display->display_options['fields']['pickup_name']['field'] = $pickup_name;
$handler->display->display_options['fields']['pickup_name']['alter']['trim_whitespace'] = TRUE;
$handler->display->display_options['fields']['pickup_name']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['pickup_name']['element_type'] = 'span';
$handler->display->display_options['fields']['pickup_name']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['pickup_name']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Pickup Data: Telephone number of pickup person */
$handler->display->display_options['fields']['pickup_telephone']['id'] = 'pickup_telephone';
$handler->display->display_options['fields']['pickup_telephone']['table'] = $pickup['table_name'];
$handler->display->display_options['fields']['pickup_telephone']['field'] = $pickup_telephone;
$handler->display->display_options['fields']['pickup_telephone']['alter']['trim_whitespace'] = TRUE;
$handler->display->display_options['fields']['pickup_telephone']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['pickup_telephone']['element_type'] = 'span';
$handler->display->display_options['fields']['pickup_telephone']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['pickup_telephone']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Pickup Data: Name and address details of Hotel or Guesthouse */
$handler->display->display_options['fields']['accommodation_name']['id'] = 'accommodation_name';
$handler->display->display_options['fields']['accommodation_name']['table'] = $pickup['table_name'];
$handler->display->display_options['fields']['accommodation_name']['field'] = $accommodation_name;
$handler->display->display_options['fields']['accommodation_name']['alter']['trim_whitespace'] = TRUE;
$handler->display->display_options['fields']['accommodation_name']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['accommodation_name']['element_type'] = 'span';
$handler->display->display_options['fields']['accommodation_name']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['accommodation_name']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Pickup Data: Telephone number Hotel or Guesthouse */
$handler->display->display_options['fields']['accommodation_telephone']['id'] = 'accommodation_telephone';
$handler->display->display_options['fields']['accommodation_telephone']['table'] = $pickup['table_name'];
$handler->display->display_options['fields']['accommodation_telephone']['field'] = $accommodation_telephone;
$handler->display->display_options['fields']['accommodation_telephone']['alter']['trim_whitespace'] = TRUE;
$handler->display->display_options['fields']['accommodation_telephone']['alter']['strip_tags'] = TRUE;
$handler->display->display_options['fields']['accommodation_telephone']['element_type'] = 'span';
$handler->display->display_options['fields']['accommodation_telephone']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['accommodation_telephone']['element_wrapper_type'] = 'p';
/* Field: CiviCRM Custom: Pickup Data: Notes */
$handler->display->display_options['fields']['notes']['id'] = 'notes';
$handler->display->display_options['fields']['notes']['table'] = $pickup['table_name'];
$handler->display->display_options['fields']['notes']['field'] = $pickup_notes;
$handler->display->display_options['fields']['notes']['alter']['nl2br'] = TRUE;
$handler->display->display_options['fields']['notes']['label'] = 'Pickup remarks';
$handler->display->display_options['fields']['notes']['element_type'] = 'span';
$handler->display->display_options['fields']['notes']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['notes']['element_wrapper_type'] = 'p';
/* Contextual filter: CiviCRM Cases: Case ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_case';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
/* Filter criterion: CiviCRM Cases: Case Type */
$handler->display->display_options['filters']['case_type']['id'] = 'case_type';
$handler->display->display_options['filters']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['case_type']['field'] = 'case_type';
$handler->display->display_options['filters']['case_type']['value'] = array(
  $travel_case_type_id => $travel_case_type_id,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/pickup-details';
$translatables['pickup_info_for_customer_'] = array(
  t('Master'),
  t('Pickup info'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('CiviCRM Case (child)'),
  t('CiviCRM Case (parent)'),
  t('Client'),
  t('Parent client'),
  t('.'),
  t('Case Type'),
  t('Destination'),
  t('Arrival date/time'),
  t('Flight number'),
  t('(Return) From'),
  t('(Return) Departure date/time'),
  t('(Return) Flight number'),
  t('Travel remarks'),
  t('Pickup confirmation'),
  t('Name of pickup person'),
  t('Telephone number of pickup person'),
  t('Name and address details of Hotel or Guesthouse'),
  t('Telephone number Hotel or Guesthouse'),
  t('Pickup remarks'),
  t('All'),
  t('Page'),
);
