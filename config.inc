<?php

class pum_customer_mycases_config {

  protected static $singleton;

  protected $conditions = array();

  protected $completableActivities = array();

  public $cgConditions = array();

  public $cfConditionsCustomerRemark = array();

  public $advice_case_type;

  public $remote_coaching_case_type;

  public $seminar_case_type;

  public $business_case_type;

  public $matching_status;

  public $preparation_status;

  public $execution_status;

  public $rejected_status;

  public $declined_status;

  public $postponed_status;

  public $error_status;

  public $cancelled_status;

  public $ongoing_status;

  public $completed_status;

  public $expert_relationship_type;

  public $project_intake_case_type;

  public $fact_finding_case_type;

  public $main_activity_info;

  public $ma_start_date;

  public $ma_end_date;

  public $travel_data;

  public $inbound_arrival_time;

  public $contact_with_customer_by_rep;

  public $current_user;

  protected function __construct() {
    civicrm_initialize();

    $this->project_intake_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Projectintake', 'option_group_name' => 'case_type'));
    $this->fact_finding_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'FactFinding', 'option_group_name' => 'case_type'));

    $case_status_option_values = civicrm_api('OptionValue', 'get', array('version' => 3, 'sequential' => 1, 'option_group_name' => 'case_status'));
    foreach($case_status_option_values['values'] as $key => $value){
      if($value['name'] === 'Matching'){
        $this->matching_status = $value['value'];
      }
      if($value['name'] === 'Preparation'){
        $this->preparation_status = $value['value'];
      }
      if($value['name'] === 'Execution'){
        $this->execution_status = $value['value'];
      }
      if($value['name'] === 'Rejected'){
        $this->rejected_status = $value['value'];
      }
      if($value['name'] === 'Declined'){
        $this->declined_status = $value['value'];
      }
      if($value['name'] === 'Postponed'){
        $this->postponed_status = $value['value'];
      }
      if($value['name'] === 'Error'){
        $this->error_status = $value['value'];
      }
      if($value['name'] === 'Cancelled'){
        $this->cancelled_status = $value['value'];
      }
      if($value['name'] === 'Ongoing'){
        $this->ongoing_status = $value['value'];
      }
      if($value['name'] === 'Completed'){
        $this->completed_status = $value['value'];
      }
    }

    $case_type_option_values = civicrm_api('OptionValue', 'get', array('version' => 3, 'sequential' => 1, 'option_group_name' => 'case_type'));
    foreach($case_type_option_values['values'] as $key => $value){
      if($value['name'] === 'Advice'){
        $this->advice_case_type = $value['value'];
      }
      if($value['name'] === 'Seminar'){
        $this->seminar_case_type = $value['value'];
      }
      if($value['name'] === 'Business'){
        $this->business_case_type = $value['value'];
      }
      if($value['name'] === 'RemoteCoaching'){
        $this->remote_coaching_case_type = $value['value'];
      }
    }

    $activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));
    $conditions_option_group = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Conditions', 'option_group_id' => $activity_type_option_group));
    $this->completableActivities[] = $conditions_option_group;

    $this->conditions[] = $conditions_option_group;
    $this->conditions[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Condition: Customer Contribution.', 'option_group_id' => $activity_type_option_group));

    $this->cgConditions = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Condition'));
    $this->cfConditionsCustomerRemark = civicrm_api3('CustomField', 'getsingle', array('name' => 'Remark_Customer', 'custom_group_id' => $this->cgConditions['id']));

    $this->expert_relationship_type = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Expert', 'return' => 'id'));

    $this->main_activity_info = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'main_activity_info'));
    $this->ma_start_date = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_start_date', 'custom_group_id' => $this->main_activity_info['id']));
    $this->ma_end_date = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_end_date', 'custom_group_id' => $this->main_activity_info['id']));

    $this->travel_data = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'travel_data'));
    $this->inbound_arrival_time = civicrm_api3('CustomField', 'getsingle', array('name' => 'arrival_time', 'custom_group_id' => $this->travel_data['id']));
    $this->contact_with_customer_by_rep = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Contact with Customer by Rep', 'option_group_id' => $activity_type_option_group));

    global $user;
    try {
      if($user->uid > 0) {
        $this->current_user = civicrm_api3('UFMatch', 'getsingle', array('uf_id' => $user->uid));
        $this->current_user['user'] = $user;
      }
    } catch (Exception $e){
      CRM_Core_Error::debug_log_message('Unable to retrieve CiviCRM Contact for Drupal ID: '.$user->uid);
    }
  }

  public function getConditions() {
    $return = array();
    foreach($this->conditions as $cond) {
      $return[$cond['value']] = $cond['value'];
    }
    return $return;
  }

  public function getCompletableConditions() {
    $return = array();
    foreach($this->completableActivities as $cond) {
      $return[$cond['value']] = $cond['value'];
    }
    return $return;
  }

  public function getContactWithCustomerByRepActivityId(){
    return $this->contact_with_customer_by_rep['value'];
  }


  /**
   * @return pum_customer_mycases_config
   */
  public static function singleton() {
    if (!self::$singleton) {
      self::$singleton = new pum_customer_mycases_config();
    }
    return self::$singleton;
  }
}