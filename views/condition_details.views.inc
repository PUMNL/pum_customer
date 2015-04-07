<?php

$config = pum_customer_mycases_config::singleton();
$conditions = $config->getConditions();

$view = new view();
$view->name = 'condition_details_for_customer_and_representative_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_activity';
$view->human_name = 'Condition (details for customer and representative)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Condition details';
$handler->display->display_options['css_class'] = 'pum-list-view';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Customer', 'Customer (contact)', 'Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '1';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: CiviCRM Activities: Activity ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Activities: Subject */
$handler->display->display_options['fields']['subject']['id'] = 'subject';
$handler->display->display_options['fields']['subject']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['subject']['field'] = 'subject';
$handler->display->display_options['fields']['subject']['label'] = '';
$handler->display->display_options['fields']['subject']['element_type'] = 'h2';
$handler->display->display_options['fields']['subject']['element_label_colon'] = FALSE;
/* Field: CiviCRM Activities: Details */
$handler->display->display_options['fields']['details']['id'] = 'details';
$handler->display->display_options['fields']['details']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['details']['field'] = 'details';
$handler->display->display_options['fields']['details']['label'] = '';
$handler->display->display_options['fields']['details']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['details']['text_format'] = 'full_html';
/* Field: CiviCRM Activities: Scheduled Activity Date */
$handler->display->display_options['fields']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['label'] = 'Date';
$handler->display->display_options['fields']['activity_date_time']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['activity_date_time']['date_format'] = 'custom';
$handler->display->display_options['fields']['activity_date_time']['custom_date_format'] = 'Y-m-d';
$handler->display->display_options['fields']['activity_date_time']['second_date_format'] = 'long';
/* Field: CiviCRM Activities: Activity Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['type']['field'] = 'activity_type';
$handler->display->display_options['fields']['type']['label'] = 'Type';
$handler->display->display_options['fields']['type']['element_label_type'] = 'strong';
/* Field: CiviCRM Activities: Activity Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['label'] = 'Status';
$handler->display->display_options['fields']['status']['element_label_type'] = 'strong';
/* Field: CiviCRM Activities: Details */
$handler->display->display_options['fields']['remark']['id'] = 'remark';
$handler->display->display_options['fields']['remark']['table'] = $config->cgConditions['table_name'];
$handler->display->display_options['fields']['remark']['field'] = $config->cfConditionsCustomerRemark['column_name'];
$handler->display->display_options['fields']['remark']['label'] = 'Remark customer';
$handler->display->display_options['fields']['remark']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['remark']['text_format'] = 'full_html';
/* Field: Global: PHP */
$handler->display->display_options['fields']['attachment']['id'] = 'attachment';
$handler->display->display_options['fields']['attachment']['table'] = 'views';
$handler->display->display_options['fields']['attachment']['field'] = 'php';
$handler->display->display_options['fields']['attachment']['label'] = 'Attachments';
$handler->display->display_options['fields']['attachment']['element_label_type'] = 'strong';
$handler->display->display_options['fields']['attachment']['use_php_setup'] = 0;
$handler->display->display_options['fields']['attachment']['php_output'] = '<?php echo _pum_customer_condition_attachment($row->id); ?>';
$handler->display->display_options['fields']['attachment']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['attachment']['php_click_sortable'] = '';
/* Field: Global: PHP */
$handler->display->display_options['fields']['php']['id'] = 'php';
$handler->display->display_options['fields']['php']['table'] = 'views';
$handler->display->display_options['fields']['php']['field'] = 'php';
$handler->display->display_options['fields']['php']['label'] = '';
$handler->display->display_options['fields']['php']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['path'] = 'customer/condition/update/[id]';
$handler->display->display_options['fields']['php']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['php']['alter']['link_class'] = 'button';
$handler->display->display_options['fields']['php']['use_php_setup'] = 0;
$handler->display->display_options['fields']['php']['php_value'] = 'if ($row->status == 1 && _pum_customer_is_condition_completable_by_customer($row->type)) {
  return \'Mark condition as completed\';
}
return \'\'';
$handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
$handler->display->display_options['fields']['php']['php_click_sortable'] = '';
/* Contextual filter: CiviCRM Activities: Activity ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_activity';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
/* Filter criterion: CiviCRM Activities: Current Revision */
$handler->display->display_options['filters']['is_current_revision']['id'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_current_revision']['field'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['value'] = '1';
/* Filter criterion: CiviCRM Activities: Is Deleted */
$handler->display->display_options['filters']['is_deleted']['id'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_deleted']['field'] = 'is_deleted';
$handler->display->display_options['filters']['is_deleted']['value'] = '0';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['value'] = $conditions;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'customer/condition-details';
$translatables['condition_details_for_customer_and_representative_'] = array(
  t('Master'),
  t('Condition details'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('.'),
  t('Status'),
  t('PHP'),
  t('All'),
  t('Page'),
);
