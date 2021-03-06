<?php

$activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));
$rep_payment_id = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Representative payment', 'option_group_id' => $activity_type_option_group, 'return' => 'value'));

$rep_payment_custom_group = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'rep_payment'));
$date_paid_custom_field = civicrm_api3('CustomField', 'getsingle', array('name' => 'date_paid', 'custom_group_id' => $rep_payment_custom_group['id']));

$view = new view();
$view->name = 'representative_payment';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_activity';
$view->human_name = 'Representative payment';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Representative payment';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id_1' => 'id_1',
  'id' => 'id',
  'id_2' => 'id_2',
  'display_name' => 'display_name',
  'title' => 'title',
  'case_type' => 'case_type',
  'activity_date_time' => 'activity_date_time',
  'status' => 'status',
  'amount_rep' => 'amount_rep',
  'comments' => 'comments',
);
$handler->display->display_options['style_options']['default'] = 'activity_date_time';
$handler->display->display_options['style_options']['info'] = array(
  'id_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'id' => array(
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
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'case_type' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'date_paid' => array(
    'sortable' => 0,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'status' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'amount_rep' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'comments' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<p> This overview shows the payments of the last half year as well as future payments. You\'ll find older payments in \'payment history\'.</p>';
$handler->display->display_options['header']['area']['format'] = 'filtered_html';
/* Footer: Global: Text area */
$handler->display->display_options['footer']['area']['id'] = 'area';
$handler->display->display_options['footer']['area']['table'] = 'views';
$handler->display->display_options['footer']['area']['field'] = 'area';
$handler->display->display_options['footer']['area']['empty'] = FALSE;
$handler->display->display_options['footer']['area']['content'] = '<p>Please allow 7 working days for transactions processing after date paid.</p>';
$handler->display->display_options['footer']['area']['format'] = 'filtered_html';
/* Footer: Global: Text area */
$handler->display->display_options['footer']['area_1']['id'] = 'area_1';
$handler->display->display_options['footer']['area_1']['table'] = 'views';
$handler->display->display_options['footer']['area_1']['field'] = 'area';
$handler->display->display_options['footer']['area_1']['empty'] = TRUE;
$handler->display->display_options['footer']['area_1']['content'] = '<p><a href="/representative-payment-history">View your payment history</a></p>';
$handler->display->display_options['footer']['area_1']['format'] = 'filtered_html';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'There are no recent payments.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: CiviCRM Representative Compose: Contact */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_representative_compose';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['required'] = TRUE;
/* Relationship: CiviCRM Contacts: Drupal ID */
$handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
$handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
$handler->display->display_options['relationships']['drupal_id']['relationship'] = 'contact_id';
$handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Activity: Case ID */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Contact: Case Contact's Contact ID */
$handler->display->display_options['relationships']['contact_id_1']['id'] = 'contact_id_1';
$handler->display->display_options['relationships']['contact_id_1']['table'] = 'civicrm_case_contact';
$handler->display->display_options['relationships']['contact_id_1']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id_1']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['contact_id_1']['label'] = 'Client';
$handler->display->display_options['relationships']['contact_id_1']['required'] = TRUE;
/* Relationship: CiviCRM Case Project: Project ID */
$handler->display->display_options['relationships']['project_id']['id'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['table'] = 'civicrm_case_project';
$handler->display->display_options['relationships']['project_id']['field'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['relationship'] = 'case_id';
/* Field: CiviCRM Contacts: Contact ID */
$handler->display->display_options['fields']['id_1']['id'] = 'id_1';
$handler->display->display_options['fields']['id_1']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['id_1']['field'] = 'id';
$handler->display->display_options['fields']['id_1']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['id_1']['label'] = '';
$handler->display->display_options['fields']['id_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_1']['separator'] = '';
/* Field: CiviCRM Project: Project ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'civicrm_project';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'project_id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: CiviCRM Cases: Case ID */
$handler->display->display_options['fields']['id_2']['id'] = 'id_2';
$handler->display->display_options['fields']['id_2']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['id_2']['field'] = 'id';
$handler->display->display_options['fields']['id_2']['relationship'] = 'case_id';
$handler->display->display_options['fields']['id_2']['label'] = '';
$handler->display->display_options['fields']['id_2']['exclude'] = TRUE;
$handler->display->display_options['fields']['id_2']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id_2']['separator'] = '';
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id_1';
$handler->display->display_options['fields']['display_name']['label'] = 'Customer';
$handler->display->display_options['fields']['display_name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['display_name']['alter']['path'] = 'customer-profile/[id_1]';
$handler->display->display_options['fields']['display_name']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Project: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'civicrm_project';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'project_id';
$handler->display->display_options['fields']['title']['label'] = 'Project';
$handler->display->display_options['fields']['title']['exclude'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['text'] = '[title]';
$handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['path'] = 'customer-project/[id]';
$handler->display->display_options['fields']['title']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
/* Field: CiviCRM Cases: Case Type */
$handler->display->display_options['fields']['case_type']['id'] = 'case_type';
$handler->display->display_options['fields']['case_type']['table'] = 'civicrm_case';
$handler->display->display_options['fields']['case_type']['field'] = 'case_type';
$handler->display->display_options['fields']['case_type']['relationship'] = 'case_id';
$handler->display->display_options['fields']['case_type']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['case_type']['alter']['path'] = 'customer/case-details/[id_2]';
$handler->display->display_options['fields']['case_type']['alter']['absolute'] = TRUE;
/* Field: CiviCRM Activities: Activity Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['label'] = 'Status';
/* Field: rep_payment:date_paid */
$handler->display->display_options['fields']['date_paid']['id'] = 'date_paid';
$handler->display->display_options['fields']['date_paid']['table'] = $rep_payment_custom_group['table_name'];
$handler->display->display_options['fields']['date_paid']['field'] = $date_paid_custom_field['column_name'];
$handler->display->display_options['fields']['date_paid']['label'] = 'Date paid';
$handler->display->display_options['fields']['date_paid']['date_format'] = 'custom';
$handler->display->display_options['fields']['date_paid']['custom_date_format'] = 'Y-m-d';
$handler->display->display_options['fields']['date_paid']['second_date_format'] = 'long';
/* Field: CiviCRM Representative Compose: Total amount */
$handler->display->display_options['fields']['amount_rep']['id'] = 'amount_rep';
$handler->display->display_options['fields']['amount_rep']['table'] = 'civicrm_representative_compose';
$handler->display->display_options['fields']['amount_rep']['field'] = 'amount_rep';
/* Field: CiviCRM Representative Compose: Comments */
$handler->display->display_options['fields']['comments']['id'] = 'comments';
$handler->display->display_options['fields']['comments']['table'] = 'civicrm_representative_compose';
$handler->display->display_options['fields']['comments']['field'] = 'comments';
/* Sort criterion: CiviCRM Activities: Activity Status */
$handler->display->display_options['sorts']['status']['id'] = 'status';
$handler->display->display_options['sorts']['status']['table'] = 'civicrm_activity';
$handler->display->display_options['sorts']['status']['field'] = 'status_id';
/* Sort criterion: CiviCRM Custom: Representative Payment: Date paid */
$handler->display->display_options['sorts']['date_paid']['id'] = 'date_paid';
$handler->display->display_options['sorts']['date_paid']['table'] = $rep_payment_custom_group['table_name'];
$handler->display->display_options['sorts']['date_paid']['field'] = $date_paid_custom_field['column_name'];
$handler->display->display_options['sorts']['date_paid']['order'] = 'DESC';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['value'] = array(
  $rep_payment_id => $rep_payment_id,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: CiviCRM Activities: Current Revision */
$handler->display->display_options['filters']['is_current_revision']['id'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_current_revision']['field'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['value'] = '1';
/* Filter criterion: CiviCRM Custom: Representative Payment: Date paid */
$handler->display->display_options['filters']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['filters']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['filters']['activity_date_time']['operator'] = '>=';
$handler->display->display_options['filters']['activity_date_time']['value']['value'] = '-6 months';
$handler->display->display_options['filters']['activity_date_time']['value']['type'] = 'offset';


/* Display: Page */
$handler = $view->new_display('page', 'Representative Payment', 'page');
$handler->display->display_options['path'] = 'representative-payment';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Representative payment';
$handler->display->display_options['menu']['name'] = 'menu-financials';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Representative Payment History */
$handler = $view->new_display('page', 'Representative Payment History', 'page_history');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
$handler->display->display_options['defaults']['footer'] = false;
$handler->display->display_options['defaults']['header'] = false;
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['title'] = 'Representative payment history';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
/* Header: Global: Text area */
$handler->display->display_options['header']['area_1']['id'] = 'area_1';
$handler->display->display_options['header']['area_1']['table'] = 'views';
$handler->display->display_options['header']['area_1']['field'] = 'area';
$handler->display->display_options['header']['area_1']['empty'] = TRUE;
$handler->display->display_options['header']['area_1']['content'] = '<p><a href="/representative-payment">Back to recent payments</a></p>';
$handler->display->display_options['header']['area_1']['format'] = 'filtered_html';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['value'] = array(
  $rep_payment_id => $rep_payment_id,
);
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'drupal_id';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: CiviCRM Activities: Current Revision */
$handler->display->display_options['filters']['is_current_revision']['id'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['is_current_revision']['field'] = 'is_current_revision';
$handler->display->display_options['filters']['is_current_revision']['value'] = '1';
/* Filter criterion: CiviCRM Custom: Representative Payment: Date paid */
$handler->display->display_options['filters']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['filters']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['filters']['activity_date_time']['operator'] = '<';
$handler->display->display_options['filters']['activity_date_time']['value']['value'] = '-6 months';
$handler->display->display_options['filters']['activity_date_time']['value']['type'] = 'offset';

$handler->display->display_options['path'] = 'representative-payment-history';
$handler->display->display_options['menu']['type'] = false;;
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;



$translatables['representative_payment'] = array(
  t('Master'),
  t('Representative payment'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('CiviCRM Contact'),
  t('Drupal User'),
  t('CiviCRM Case, with custom fields'),
  t('Client'),
  t('CiviCRM Project'),
  t('Type'),
  t('.'),
  t('Customer'),
  t('Project'),
  t('[title]'),
  t('Case Type'),
  t('Date'),
  t('Status'),
  t('Total amount'),
  t('Comments'),
  t('Page'),
);
