<?php

class pum_customer_mycases_config {

    protected static $singleton;

    protected $conditions = array();

    protected function __construct() {
        civicrm_initialize();

        $activity_type_option_group = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'activity_type'));

        $this->conditions[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Conditions', 'option_group_id' => $activity_type_option_group));
        $this->conditions[] = civicrm_api3('OptionValue', 'getsingle', array('name' => 'Condition: Customer Contribution.', 'option_group_id' => $activity_type_option_group));
    }

    public function getConditions() {
        $return = array();
        foreach($this->conditions as $cond) {
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