<?php

$intake =civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Intake'));
$intake_gid = $intake['id'];
$intake_table = $intake['table_name'];

$assesment_rep =civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Assessment_Project_Request_by_Rep'));
$gid = $assesment_rep['id'];
$table = $assesment_rep['table_name'];

$view = new view();
$view->name = 'assesment_rep_for_rep_';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'civicrm_case_project';
$view->human_name = 'Assesment Rep (for representative)';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Representative Assement';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = pum_customer_get_role_ids(array('Representative'));
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: CiviCRM Case Project: Case ID */
$handler->display->display_options['relationships']['case_id']['id'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['table'] = 'civicrm_case_project';
$handler->display->display_options['relationships']['case_id']['field'] = 'case_id';
$handler->display->display_options['relationships']['case_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Project: Project ID */
$handler->display->display_options['relationships']['project_id']['id'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['table'] = 'civicrm_case_project';
$handler->display->display_options['relationships']['project_id']['field'] = 'project_id';
$handler->display->display_options['relationships']['project_id']['required'] = TRUE;
/* Relationship: CiviCRM Case Activity: Case Activity's Activity ID */
$handler->display->display_options['relationships']['activity_id']['id'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['table'] = 'civicrm_case_activity';
$handler->display->display_options['relationships']['activity_id']['field'] = 'activity_id';
$handler->display->display_options['relationships']['activity_id']['relationship'] = 'case_id';
$handler->display->display_options['relationships']['activity_id']['required'] = TRUE;
/* Relationship: CiviCRM Activity Contacts: Activity Contact ID */
$handler->display->display_options['relationships']['contact_id']['id'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['table'] = 'civicrm_activity_contact';
$handler->display->display_options['relationships']['contact_id']['field'] = 'contact_id';
$handler->display->display_options['relationships']['contact_id']['relationship'] = 'activity_id';
$handler->display->display_options['relationships']['contact_id']['label'] = 'Reported by';
$handler->display->display_options['relationships']['contact_id']['record_type'] = '2';
/* Field: CiviCRM Custom: Intake: Assessment Rep */
$handler->display->display_options['fields']['assessment_rep_138']['id'] = 'assessment_rep_138';
$handler->display->display_options['fields']['assessment_rep_138']['table'] = $intake_table;
$handler->display->display_options['fields']['assessment_rep_138']['field'] = civicrm_api3('CustomField', 'getvalue', array('name' => 'Assessment_Rep', 'custom_group_id' => $intake_gid, 'return' => 'column_name'));
$handler->display->display_options['fields']['assessment_rep_138']['relationship'] = 'case_id';
$handler->display->display_options['fields']['assessment_rep_138']['label'] = '';
$handler->display->display_options['fields']['assessment_rep_138']['element_type'] = 'h4';
$handler->display->display_options['fields']['assessment_rep_138']['element_label_colon'] = FALSE;
/* Field: CiviCRM Activities: Activity Status */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['status']['label'] = '';
$handler->display->display_options['fields']['status']['exclude'] = TRUE;
$handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
/* Field: CiviCRM Contacts: Display Name */
$handler->display->display_options['fields']['display_name']['id'] = 'display_name';
$handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
$handler->display->display_options['fields']['display_name']['field'] = 'display_name';
$handler->display->display_options['fields']['display_name']['relationship'] = 'contact_id';
$handler->display->display_options['fields']['display_name']['label'] = '';
$handler->display->display_options['fields']['display_name']['exclude'] = TRUE;
$handler->display->display_options['fields']['display_name']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 0;
/* Field: CiviCRM Activities: Scheduled Activity Date */
$handler->display->display_options['fields']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['fields']['activity_date_time']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['activity_date_time']['label'] = '';
$handler->display->display_options['fields']['activity_date_time']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['activity_date_time']['alter']['text'] = '[activity_date_time] ([status]) by [display_name]';
$handler->display->display_options['fields']['activity_date_time']['element_type'] = 'em';
$handler->display->display_options['fields']['activity_date_time']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['activity_date_time']['date_format'] = 'custom';
$handler->display->display_options['fields']['activity_date_time']['custom_date_format'] = 'j F Y';
$handler->display->display_options['fields']['activity_date_time']['second_date_format'] = 'long';
/* Field: CiviCRM Custom: Intake: Comment Rep */
$handler->display->display_options['fields']['comment_rep_139']['id'] = 'comment_rep_139';
$handler->display->display_options['fields']['comment_rep_139']['table'] = $intake_table;
$handler->display->display_options['fields']['comment_rep_139']['field'] =  civicrm_api3('CustomField', 'getvalue', array('name' => 'Comment_Rep', 'custom_group_id' => $intake_gid, 'return' => 'column_name'));
$handler->display->display_options['fields']['comment_rep_139']['relationship'] = 'case_id';
$handler->display->display_options['fields']['comment_rep_139']['label'] = 'Comment';
$handler->display->display_options['fields']['comment_rep_139']['element_label_type'] = 'h4';
/* Field: CiviCRM Activities: Details */
$handler->display->display_options['fields']['details_1']['id'] = 'details_1';
$handler->display->display_options['fields']['details_1']['table'] = 'civicrm_activity';
$handler->display->display_options['fields']['details_1']['field'] = 'details';
$handler->display->display_options['fields']['details_1']['relationship'] = 'activity_id';
$handler->display->display_options['fields']['details_1']['label'] = 'Submitted assesment';
$handler->display->display_options['fields']['details_1']['element_label_type'] = 'h4';
$handler->display->display_options['fields']['details_1']['text_format'] = 'full_html';
/* Sort criterion: CiviCRM Activities: Scheduled Activity Date */
$handler->display->display_options['sorts']['activity_date_time']['id'] = 'activity_date_time';
$handler->display->display_options['sorts']['activity_date_time']['table'] = 'civicrm_activity';
$handler->display->display_options['sorts']['activity_date_time']['field'] = 'activity_date_time';
$handler->display->display_options['sorts']['activity_date_time']['relationship'] = 'activity_id';
$handler->display->display_options['sorts']['activity_date_time']['order'] = 'DESC';
/* Contextual filter: CiviCRM Project: Project ID */
$handler->display->display_options['arguments']['id']['id'] = 'id';
$handler->display->display_options['arguments']['id']['table'] = 'civicrm_project';
$handler->display->display_options['arguments']['id']['field'] = 'id';
$handler->display->display_options['arguments']['id']['relationship'] = 'project_id';
$handler->display->display_options['arguments']['id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
/* Filter criterion: CiviCRM Activities: Activity Type */
$handler->display->display_options['filters']['activity_type']['id'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['table'] = 'civicrm_activity';
$handler->display->display_options['filters']['activity_type']['field'] = 'activity_type';
$handler->display->display_options['filters']['activity_type']['relationship'] = 'activity_id';
$handler->display->display_options['filters']['activity_type']['value'] = array(
73 => '73',
);
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

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'representative/project-rep-assesment';
$translatables['assesment_rep_for_expert_'] = array(
t('Master'),
t('Representative Assement'),
t('more'),
t('Apply'),
t('Reset'),
t('Sort by'),
t('Asc'),
t('Desc'),
t('CiviCRM Case'),
t('CiviCRM Project'),
t('CiviCRM Activity, with custom fields'),
t('Is active'),
t('Page'),
);