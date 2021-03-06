<?php

$config = pum_customer_mycases_config::singleton();

$view = new view();
$view->name = 'case_roles_for_customer_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Case roles (for customer and representative)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Case roles';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  7 => '7',
  8 => '8',
);
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from Contact B) */
$handler->display->display_options['relationships']['relationship_id_b']['id'] = 'relationship_id_b';
$handler->display->display_options['relationships']['relationship_id_b']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_b']['field'] = 'relationship_id_b';
$handler->display->display_options['relationships']['relationship_id_b']['label'] = 'relationship';
$handler->display->display_options['relationships']['relationship_id_b']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_b']['relationship_type'] = '0';
$handler->display->display_options['relationships']['relationship_id_b']['relationship_state'] = 0;
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Relationships: Relationship Type A-to-B */
$handler->display->display_options['fields']['relationship_type']['id'] = 'relationship_type';
$handler->display->display_options['fields']['relationship_type']['table'] = 'civicrm_relationship';
$handler->display->display_options['fields']['relationship_type']['field'] = 'relationship_type';
$handler->display->display_options['fields']['relationship_type']['relationship'] = 'relationship_id_b';
$handler->display->display_options['fields']['relationship_type']['label'] = 'Role';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['label'] = 'Name';
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Email: Email Address */
$handler->display->display_options['fields']['email']['id'] = 'email';
$handler->display->display_options['fields']['email']['table'] = 'civicrm_email';
$handler->display->display_options['fields']['email']['field'] = 'email';
$handler->display->display_options['fields']['email']['label'] = 'E-mail address';
$handler->display->display_options['fields']['email']['location_type'] = '0';
$handler->display->display_options['fields']['email']['location_op'] = '0';
$handler->display->display_options['fields']['email']['is_primary'] = 1;
/* Field: CiviCRM Phone Details: Phone Number */
$handler->display->display_options['fields']['phone']['id'] = 'phone';
$handler->display->display_options['fields']['phone']['table'] = 'civicrm_phone';
$handler->display->display_options['fields']['phone']['field'] = 'phone';
$handler->display->display_options['fields']['phone']['label'] = 'Phone';
$handler->display->display_options['fields']['phone']['location_type'] = '0';
$handler->display->display_options['fields']['phone']['location_op'] = '0';
$handler->display->display_options['fields']['phone']['is_primary'] = 1;
$handler->display->display_options['fields']['phone']['phone_type'] = '0';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['label'] = '';
$handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['path'] = 'customer/expert/[id]/!1';
$handler->display->display_options['fields']['php']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['php']['use_php_setup'] = 1;
$handler->display->display_options['fields']['php']['php_setup'] = '$static[\'expert_rel_type_id\'] = civicrm_api3(\'RelationshipType\', \'getvalue\', array(\'name_a_b\' => \'Expert\', \'return\' => \'id\'));';
$handler->display->display_options['fields']['php']['php_value'] = 'if ($data->civicrm_relationship_civicrm_contact_relationship_type_id == $static[\'expert_rel_type_id\']) {
  return \'View CV\';
}';
/* Contextual filter: CiviCRM Relationships: Case ID */
$handler->display->display_options['arguments']['case_id']['id'] = 'case_id';
$handler->display->display_options['arguments']['case_id']['table'] = 'civicrm_relationship';
$handler->display->display_options['arguments']['case_id']['field'] = 'case_id';
$handler->display->display_options['arguments']['case_id']['relationship'] = 'relationship_id_b';
$handler->display->display_options['arguments']['case_id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['case_id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['case_id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['case_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['case_id']['summary_options']['items_per_page'] = '25';
/* Contextual filter: CiviCRM Relationships: Case ID */
$handler->display->display_options['arguments']['case_id_1']['id'] = 'case_id_1';
$handler->display->display_options['arguments']['case_id_1']['table'] = 'civicrm_relationship';
$handler->display->display_options['arguments']['case_id_1']['field'] = 'case_id';
$handler->display->display_options['arguments']['case_id_1']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['case_id_1']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['case_id_1']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['case_id_1']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['case_id_1']['specify_validation'] = TRUE;
$handler->display->display_options['arguments']['case_id_1']['validate']['type'] = 'php';
$handler->display->display_options['arguments']['case_id_1']['validate_options']['code'] = 'return pum_customer_user_has_role_on_case($handler->argument);';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'OR',
);
/* Filter criterion: CiviCRM Relationships: Relationship Type A-to-B */
$handler->display->display_options['filters']['relationship_type']['id'] = 'relationship_type';
$handler->display->display_options['filters']['relationship_type']['table'] = 'civicrm_relationship';
$handler->display->display_options['filters']['relationship_type']['field'] = 'relationship_type';
$handler->display->display_options['filters']['relationship_type']['relationship'] = 'relationship_id_b';
$handler->display->display_options['filters']['relationship_type']['operator'] = 'not in';
$handler->display->display_options['filters']['relationship_type']['value'] = array(
  17 => '17',
);
$handler->display->display_options['filters']['relationship_type']['group'] = 1;
/* Filter criterion: CiviCRM Cases: Case Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'civicrm_case';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'relationship_id_b';
$handler->display->display_options['filters']['status']['operator'] = 'not in';
$handler->display->display_options['filters']['status']['value'] = array(
  5 => '5',
);
$handler->display->display_options['filters']['status']['group'] = 1;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/my-cases/case-roles';
$translatables['case_roles_for_customer_'] = array(
    t('Master'),
    t('Case roles'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('relationship'),
		t('.'),
    t('Role'),
    t('Name'),
    t('E-mail address'),
    t('Phone'),
    t('All'),
    t('Page'),
);
