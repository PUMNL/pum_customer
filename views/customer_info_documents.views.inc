<?php

$authorised_contact_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Has authorised', 'return' => 'id'));
$local_rep_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Representative is', 'return' => 'id'));

$view = new view();
$view->name = 'customer_documents_for_customer_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_document';
$view->human_name = 'Customer documents (for customer and rep)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Customer documents';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Customer', 'Customer (contact)', 'Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'There are no documents';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: CiviCRM Document contact: Contact ID of document contact */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_document_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Relationship: CiviCRM Document: Added by */
$handler->display->display_options['relationships']['added_by']['id'] = 'added_by';
$handler->display->display_options['relationships']['added_by']['table'] = 'civicrm_document';
$handler->display->display_options['relationships']['added_by']['field'] = 'added_by';
$handler->display->display_options['relationships']['added_by']['label'] = 'Added by';
/* Relationship: CiviCRM Document: Updated by */
$handler->display->display_options['relationships']['updated_by']['id'] = 'updated_by';
$handler->display->display_options['relationships']['updated_by']['table'] = 'civicrm_document';
$handler->display->display_options['relationships']['updated_by']['field'] = 'updated_by';
$handler->display->display_options['relationships']['updated_by']['label'] = 'Updated by';
/* Relationship: CiviCRM Document case: Case ID of document case */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_document_case';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from contact A) */
$handler->display->display_options['relationships']['relationship_id_a']['id'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_a']['field'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a']['relationship'] = 'contact_id';
$handler->display->display_options['relationships']['relationship_id_a']['label'] = 'Authorised relationship';
$handler->display->display_options['relationships']['relationship_id_a']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_a']['relationship_type'] = $authorised_contact_rel_type_id;
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from contact A) */
$handler->display->display_options['relationships']['relationship_id_a_1']['id'] = 'relationship_id_a_1';
$handler->display->display_options['relationships']['relationship_id_a_1']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_a_1']['field'] = 'relationship_id_a';
$handler->display->display_options['relationships']['relationship_id_a_1']['relationship'] = 'contact_id';
$handler->display->display_options['relationships']['relationship_id_a_1']['label'] = 'Representative';
$handler->display->display_options['relationships']['relationship_id_a_1']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_a_1']['relationship_type'] = $local_rep_rel_type_id;
/* Field: CiviCRM Document: Document ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_document';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['relationship'] = 'added_by';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'updated_by';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['fields']['contact_id_b_']['id'] = 'contact_id_b_';
$handler->display->display_options['fields']['contact_id_b_']['table'] = 'civicrm_relationship';
$handler->display->display_options['fields']['contact_id_b_']['field'] = 'contact_id_b_';
$handler->display->display_options['fields']['contact_id_b_']['relationship'] = 'relationship_id_a';
$handler->display->display_options['fields']['contact_id_b_']['label'] = '';
$handler->display->display_options['fields']['contact_id_b_']['exclude'] = TRUE;
$handler->display->display_options['fields']['contact_id_b_']['element_label_colon'] = FALSE;
/* Field: CiviCRM Relationships: Contact ID B */
$handler->display->display_options['fields']['contact_id_b__1']['id'] = 'contact_id_b__1';
$handler->display->display_options['fields']['contact_id_b__1']['table'] = 'civicrm_relationship';
$handler->display->display_options['fields']['contact_id_b__1']['field'] = 'contact_id_b_';
$handler->display->display_options['fields']['contact_id_b__1']['relationship'] = 'relationship_id_a_1';
$handler->display->display_options['fields']['contact_id_b__1']['label'] = '';
$handler->display->display_options['fields']['contact_id_b__1']['exclude'] = TRUE;
$handler->display->display_options['fields']['contact_id_b__1']['element_label_colon'] = FALSE;
/* Field: CiviCRM Document: Subject */
$handler->display->display_options['fields']['subject']['id'] = 'subject';
$handler->display->display_options['fields']['subject']['table'] = 'civicrm_document';
$handler->display->display_options['fields']['subject']['field'] = 'subject';
/* Field: CiviCRM Document: Date updated */
$handler->display->display_options['fields']['date_updated']['id'] = 'date_updated';
$handler->display->display_options['fields']['date_updated']['table'] = 'civicrm_document';
$handler->display->display_options['fields']['date_updated']['field'] = 'date_updated';
$handler->display->display_options['fields']['date_updated']['date_format'] = 'short';
$handler->display->display_options['fields']['date_updated']['second_date_format'] = 'long';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name_1']['id'] = 'display_name_1';
$handler->display->display_options['fields']['display_name_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name_1']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name_1']['relationship'] = 'updated_by';
$handler->display->display_options['fields']['display_name_1']['label'] = 'Updated by';
$handler->display->display_options['fields']['display_name_1']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Cases: Case Type */
$handler->display->display_options['fields']['case_type']['id'] = 'case_type';
$handler->display->display_options['fields']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['case_type']['field'] = 'case_type';
$handler->display->display_options['fields']['case_type']['relationship'] = 'case_id';
/* Field: CiviCRM Cases: Subject */
$handler->display->display_options['fields']['subject_1']['id'] = 'subject_1';
$handler->display->display_options['fields']['subject_1']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['subject_1']['field'] = 'subject';
$handler->display->display_options['fields']['subject_1']['relationship'] = 'case_id';
$handler->display->display_options['fields']['subject_1']['label'] = 'Case subject';
/* Field: CiviCRM Document: Document Download link */
$handler->display->display_options['fields']['download_link']['id'] = 'download_link';
$handler->display->display_options['fields']['download_link']['table'] = 'civicrm_document';
$handler->display->display_options['fields']['download_link']['field'] = 'download_link';
$handler->display->display_options['fields']['download_link']['label'] = 'Download';
$handler->display->display_options['fields']['download_link']['separator'] = '';
$handler->display->display_options['fields']['download_link']['download_link'] = TRUE;
/* Contextual filter: CiviCRM Contacts: Contact ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['relationship'] = 'contact_id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'OR',
);

/* Filter criterion: CiviCRM Cases: Case ID */
$handler->display->display_options['filters']['id']['id'] = 'id';
$handler->display->display_options['filters']['id']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['id']['field'] = 'id';
$handler->display->display_options['filters']['id']['relationship'] = 'case_id';
$handler->display->display_options['filters']['id']['operator'] = 'empty';
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare']['id'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['group'] = 1;
$handler->display->display_options['filters']['fields_compare']['right_field'] = 'contact_id_b_';
$handler->display->display_options['filters']['fields_compare']['left_field'] = 'id_1';
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare_1']['id'] = 'fields_compare_1';
$handler->display->display_options['filters']['fields_compare_1']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare_1']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare_1']['group'] = 1;
$handler->display->display_options['filters']['fields_compare_1']['right_field'] = 'contact_id_b_';
$handler->display->display_options['filters']['fields_compare_1']['left_field'] = 'id_2';
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare_2']['id'] = 'fields_compare_2';
$handler->display->display_options['filters']['fields_compare_2']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare_2']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare_2']['group'] = 1;
$handler->display->display_options['filters']['fields_compare_2']['right_field'] = 'contact_id_b__1';
$handler->display->display_options['filters']['fields_compare_2']['left_field'] = 'id_1';
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare_3']['id'] = 'fields_compare_3';
$handler->display->display_options['filters']['fields_compare_3']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare_3']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare_3']['group'] = 1;
$handler->display->display_options['filters']['fields_compare_3']['right_field'] = 'contact_id_b__1';
$handler->display->display_options['filters']['fields_compare_3']['left_field'] = 'id_2';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer-profile/documents';
$translatables['customer_documents_for_expert_'] = array(
  t('Master'),
  t('Customer documents'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Contact ID of document contact'),
  t('Added by'),
  t('Updated by'),
  t('Document ID'),
  t('.'),
  t('Subject'),
  t('Date added'),
  t('Date updated'),
  t('Document Download link'),
  t('Display Name'),
  t('All'),
  t('Page'),
);
