<?php
/**
 * @author Jaap Jansma (CiviCooP) <jaap.jansma@civicoop.org>
 * @license http://www.gnu.org/licenses/agpl-3.0.html
 */

class pum_customer_businessconfig {

  private static $singleton;

  public $custom_groups = array();

  public $business_case_type;

  public $travel_case_type;

  public $completed_case_status;

  public $submitted_status;

  public $in_progress_status;

  public $authorised_contact_relationship_type_id;

  public $expert_relationship_type_id;

  public $business_participant_relationship_type_id;

  public $different_data_registering_activity_type;

  public $scheduled_activity_status;

  private function __construct() {
    civicrm_initialize();
    $this->business_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Business', 'option_group_name' => 'case_type', 'return' => 'value'));
    $this->travel_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'TravelCase', 'option_group_name' => 'case_type', 'return' => 'value'));

    $activity_status = civicrm_api('OptionValue', 'get', array('version' => 3, 'sequential' => 1, 'option_group_name' => 'activity_status'));
    foreach($activity_status['values'] as $key => $value){
      if($value['name'] == 'Submitted'){
        $this->submitted_status = $value['value'];
      }
      if($value['name'] == 'In Progress'){
        $this->in_progress_status = $value['value'];
      }
      if($value['name'] == 'Scheduled'){
        $this->scheduled_activity_status = $value['value'];
      }
    }

    $this->completed_case_status = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Completed', 'option_group_name' => 'case_status', 'return' => 'value'));

    $this->custom_groups['TravelParent'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'travel_parent'));
    $this->custom_groups['TravelParent']['fields']['case_id'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'case_id', 'custom_group_id' => $this->custom_groups['TravelParent']['id']));

    $this->custom_groups['business_data'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Business_Data'));
    $this->custom_groups['business_data']['fields']['Number_of_Visitors'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'Number_of_Visitors', 'custom_group_id' => $this->custom_groups['business_data']['id']));
    $this->custom_groups['business_data']['fields']['Open_for_Registration'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'Open_for_Registration', 'custom_group_id' => $this->custom_groups['business_data']['id']));

    $relationship_types = civicrm_api3('RelationshipType', 'get', array('version' => 3, 'sequential' => 1));
    foreach($relationship_types['values'] as $key => $value) {
      if($value['name_a_b'] == 'Has authorised') {
        $this->authorised_contact_relationship_type_id = $value['id'];
      }
      if($value['name_a_b'] == 'Expert') {
        $this->expert_relationship_type_id = $value['id'];
      }
      if($value['name_a_b'] == 'Business participant is') {
        $this->business_participant_relationship_type_id = $value['id'];
      }
    }

    $this->custom_groups['main_activity_info'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'main_activity_info'));
    $this->custom_groups['main_activity_info']['fields']['start_date'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_start_date', 'custom_group_name' => 'main_activity_info'));
    $this->custom_groups['main_activity_info']['fields']['end_date'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_end_date', 'custom_group_name' => 'main_activity_info'));

    $this->custom_groups['Business_Programme'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Business_Programme'));
    $business_programme_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $this->custom_groups['Business_Programme']['id']));
    foreach($business_programme_fields['values'] as $key => $value){
      if($value['name'] == 'Naam_bedrijf'){
        $this->custom_groups['Business_Programme']['fields']['Naam_bedrijf'] = $value['id'];
      }
      if($value['name'] == 'Location'){
        $this->custom_groups['Business_Programme']['fields']['Location'] = $value['id'];
      }
      if($value['name'] == 'Short_description_Aim_of_Visit'){
        $this->custom_groups['Business_Programme']['fields']['Aim_of_Visit'] = $value['id'];
      }
    }


    $this->custom_groups['Passport_Information']['fields'] = array();
    $passport_fields = civicrm_api3('CustomField', 'get', array('custom_group_name' => 'Passport_Information'));
    foreach ($passport_fields['values'] as $field) {
      $this->custom_groups['Passport_Information']['fields'][$field['name']] = $field;
    }

    $this->custom_groups['Nationality']['fields']['Nationality'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'Nationality', 'custom_group_name' => 'Nationality'));

    $this->different_data_registering_activity_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Different Data Registering', 'option_group_id' => 'activity_type'));
  }

  /**
   * @return \pum_customer_businessconfig
   */
  public static function singleton() {
    if (!self::$singleton) {
      self::$singleton = new pum_customer_businessconfig();
    }
    return self::$singleton;
  }

}