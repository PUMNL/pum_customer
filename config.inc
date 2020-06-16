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

        $case_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_type'));
        $this->project_intake_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Projectintake', 'option_group_id' => $case_type_option_group));
        $this->fact_finding_case_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'FactFinding', 'option_group_id' => $case_type_option_group));

        $case_status_id = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_status'));
        $this->matching_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Matching', 'option_group_id' => $case_status_id));
        $this->preparation_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Preparation', 'option_group_id' => $case_status_id));
        $this->execution_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Execution', 'option_group_id' => $case_status_id));
        $this->rejected_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Rejected', 'option_group_id' => $case_status_id));
        $this->declined_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Declined', 'option_group_id' => $case_status_id));
        $this->postponed_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Postponed', 'option_group_id' => $case_status_id));
        $this->error_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Error', 'option_group_id' => $case_status_id));
        $this->cancelled_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Cancelled', 'option_group_id' => $case_status_id));
        $this->ongoing_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'label' => 'Ongoing', 'option_group_id' => $case_status_id));
        $case_type_id = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_type'));
        $this->advice_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Advice', 'option_group_id' => $case_type_id, 'return' => 'value'));
        $this->seminar_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Seminar', 'option_group_id' => $case_type_id, 'return' => 'value'));
        $this->business_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Business', 'option_group_id' => $case_type_id, 'return' => 'value'));
        $this->remote_coaching_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'RemoteCoaching', 'option_group_id' => $case_type_id, 'return' => 'value'));

        $activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));

        $this->completableActivities[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Conditions', 'option_group_id' => $activity_type_option_group));

        $this->conditions[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Conditions', 'option_group_id' => $activity_type_option_group));
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