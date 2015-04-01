<?php

$view = new view();
$view->name = 'case_details_for_customer_and_representative_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_case';
$view->human_name = 'Case details (for customer and representative)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Case details';
$handler->display->display_options['css_class'] = 'pum-grid-view';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Customer', 'Customer (contact)', 'Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '1';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: Global: View */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['label'] = 'Conditions';
$handler->display->display_options['fields']['view']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view']['view'] = 'customer_my_cases_conditions';
$handler->display->display_options['fields']['view']['arguments'] = '[!id]';
/* Field: Global: View */
$handler->display->display_options['fields']['view_1']['id'] = 'view_1';
$handler->display->display_options['fields']['view_1']['table'] = 'views';
$handler->display->display_options['fields']['view_1']['field'] = 'view';
$handler->display->display_options['fields']['view_1']['label'] = 'Roles';
$handler->display->display_options['fields']['view_1']['element_label_type'] = 'h2';
$handler->display->display_options['fields']['view_1']['view'] = 'case_roles_for_customer_';
$handler->display->display_options['fields']['view_1']['arguments'] = '[!id]';
/* Contextual filter: CiviCRM Cases: Case ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_case';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/case-details';
$translatables['case_details_for_customer_and_representative_'] = array(
  t('Master'),
  t('Case details'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('.'),
  t('Conditions'),
  t('Roles'),
  t('All'),
  t('Page'),
);
