<?php

class pum_customer_mycases_config {

    protected static $singleton;

    protected $conditions = array();

    protected $completableActivities = array();

    public $cgConditions = array();

    public $cfConditionsCustomerRemark = array();

    protected function __construct() {
        civicrm_initialize();

        $activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));

        $this->completableActivities[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Conditions', 'option_group_id' => $activity_type_option_group));

        $this->conditions[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Conditions', 'option_group_id' => $activity_type_option_group));
        $this->conditions[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Condition: Customer Contribution.', 'option_group_id' => $activity_type_option_group));

        $this->cgConditions = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Condition'));
        $this->cfConditionsCustomerRemark = civicrm_api3('CustomField', 'getsingle', array('name' => 'Remark_Customer', 'custom_group_id' => $this->cgConditions['id']));
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