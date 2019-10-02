<?php

$expert_rel_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Expert', 'return' => 'id'));

$view = new view();
$view->name = 'expert_info_for_customer';
$view->description = 'CV of proposed expert for customer';
$view->tag = 'main activity';
$view->base_table = 'civicrm_contact';
$view->human_name = 'Expert info for customer';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Expert';
$handler->display->display_options['css_class'] = 'pum-list-view';
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

if (!empty($civicrm_db) && !empty($case_id[3])) {
	$relationships = db_query("SELECT c.id AS \'case_id\', rel.contact_id_b AS \'contact_id\', rt.label_b_a AS \'rel_description\' FROM $civicrm_db.civicrm_case_project cp
											LEFT JOIN $civicrm_db.civicrm_case c ON cp.case_id = c.id
											LEFT JOIN $civicrm_db.civicrm_relationship rel ON c.id = rel.case_id
											LEFT JOIN $civicrm_db.civicrm_relationship_type rt ON rel.relationship_type_id = rt.id
											LEFT JOIN $civicrm_db.civicrm_case_contact cc ON cc.case_id = c.id
											WHERE rel.case_id = :case_id AND rel.is_active = :is_active",
											array(\':case_id\'=>check_plain($case_id[3]),\':is_active\'=>\'1\'))->fetchAll();

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
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: CiviCRM Contacts: CiviCRM Relationship (starting from Contact B) */
$handler->display->display_options['relationships']['relationship_id_b']['id'] = 'relationship_id_b';
$handler->display->display_options['relationships']['relationship_id_b']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['relationship_id_b']['field'] = 'relationship_id_b';
$handler->display->display_options['relationships']['relationship_id_b']['label'] = 'Expert';
$handler->display->display_options['relationships']['relationship_id_b']['required'] = TRUE;
$handler->display->display_options['relationships']['relationship_id_b']['relationship_type'] = $expert_rel_type_id;
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Contacts: Gender */
$handler->display->display_options['fields']['gender']['id'] = 'gender';
$handler->display->display_options['fields']['gender']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['gender']['field'] = 'gender';
$handler->display->display_options['fields']['gender']['label'] = '';
$handler->display->display_options['fields']['gender']['exclude'] = TRUE;
$handler->display->display_options['fields']['gender']['element_label_colon'] = FALSE;
/* Field: Global: PHP */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['exclude'] = TRUE;
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_value'] = 'return pum_customer_get_gender($row->gender);';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
/* Field: CiviCRM Contacts: Prefix */
$handler->display->display_options['fields']['prefix_id']['id'] = 'prefix_id';
$handler->display->display_options['fields']['prefix_id']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['prefix_id']['field'] = 'prefix_id';
$handler->display->display_options['fields']['prefix_id']['label'] = '';
$handler->display->display_options['fields']['prefix_id']['exclude'] = TRUE;
$handler->display->display_options['fields']['prefix_id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['prefix_id']['empty'] = '[php]';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['label'] = '';
$handler->display->display_options['fields']['display_name']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['display_name']['alter']['text'] = '[prefix_id] [display_name]';
$handler->display->display_options['fields']['display_name']['element_type'] = 'h2';
$handler->display->display_options['fields']['display_name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: Project qualifications */
$handler->display->display_options['fields']['view_3']['id'] = 'view_3';
$handler->display->display_options['fields']['view_3']['table'] = 'views';
$handler->display->display_options['fields']['view_3']['field'] = 'view';
$handler->display->display_options['fields']['view_3']['ui_name'] = 'Project qualifications';
$handler->display->display_options['fields']['view_3']['label'] = 'Project qualifications';
$handler->display->display_options['fields']['view_3']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_3']['view'] = 'expert_cv_project_qualifications_';
$handler->display->display_options['fields']['view_3']['arguments'] = '!1/!2';
/* Field: Languages */
$handler->display->display_options['fields']['view_1']['id'] = 'view_1';
$handler->display->display_options['fields']['view_1']['table'] = 'views';
$handler->display->display_options['fields']['view_1']['field'] = 'view';
$handler->display->display_options['fields']['view_1']['ui_name'] = 'Languages';
$handler->display->display_options['fields']['view_1']['label'] = 'Languages';
$handler->display->display_options['fields']['view_1']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_1']['view'] = 'expert_cv_languages_';
$handler->display->display_options['fields']['view_1']['arguments'] = '[id]';
/* Field: Education */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['ui_name'] = 'Education';
$handler->display->display_options['fields']['view']['label'] = 'Education';
$handler->display->display_options['fields']['view']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view']['view'] = 'expert_cv_education_';
$handler->display->display_options['fields']['view']['arguments'] = '[id]';
/* Field: Work history */
$handler->display->display_options['fields']['view_2']['id'] = 'view_2';
$handler->display->display_options['fields']['view_2']['table'] = 'views';
$handler->display->display_options['fields']['view_2']['field'] = 'view';
$handler->display->display_options['fields']['view_2']['ui_name'] = 'Work history';
$handler->display->display_options['fields']['view_2']['label'] = 'Work history';
$handler->display->display_options['fields']['view_2']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view_2']['view'] = 'expert_cv_work_experience_';
$handler->display->display_options['fields']['view_2']['arguments'] = '[id]';
/* Contextual filter: CiviCRM Contacts: Contact ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
/* Contextual filter: CiviCRM Relationships: Case ID */
$handler->display->display_options['arguments']['case_id']['id'] = 'case_id';
$handler->display->display_options['arguments']['case_id']['table'] = 'civicrm_relationship';
$handler->display->display_options['arguments']['case_id']['field'] = 'case_id';
$handler->display->display_options['arguments']['case_id']['relationship'] = 'relationship_id_b';
$handler->display->display_options['arguments']['case_id']['default_action'] = 'access denied';
$handler->display->display_options['arguments']['case_id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['case_id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['case_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['case_id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/expert';
$translatables['expert_info_for_customer'] = array(
  t('Master'),
  t('Expert'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('.'),
	t('PHP'),
  t('[php]'),
  t('[prefix_id] [display_name]'),
  t('Project qualifications'),
  t('Languages'),
  t('Education'),
  t('Work history'),
  t('All'),
  t('Page'),
);
