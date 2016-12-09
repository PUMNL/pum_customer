<?php
/**
 * @author Jaap Jansma (CiviCooP) <jaap.jansma@civicoop.org>
 * @license http://www.gnu.org/licenses/agpl-3.0.html
 */

class pum_customer_businessconfig {

  private static $singleton;

  public $custom_groups = array();

  public $business_case_type;

  public $completed_case_status;

  public $submitted_status;

  public $authorised_contact_relationship_type_id;

  public $expert_relationship_type_id;

  public $business_participant_relationship_type_id;

  public $different_data_registering_activity_type;

  public $scheduled_activity_status;

  private function __construct() {
    civicrm_initialize();
    $case_type_id = civicrm_api3('OptionGroup', 'getvalue', array('return' => 'id', 'name' => 'case_type'));
    $this->business_case_type = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Business', 'option_group_id' => $case_type_id, 'return' => 'value'));

    $this->completed_case_status = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Completed', 'option_group_id' => 'case_status', 'return' => 'value'));

    $this->custom_groups['business_data'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Business_Data'));
    $this->custom_groups['business_data']['fields']['Number_of_Visitors'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'Number_of_Visitors', 'custom_group_id' => $this->custom_groups['business_data']['id']));
    $this->custom_groups['business_data']['fields']['Open_for_Registration'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'Open_for_Registration', 'custom_group_id' => $this->custom_groups['business_data']['id']));

    $this->authorised_contact_relationship_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Has authorised', 'return' => 'id'));
    $this->expert_relationship_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Expert', 'return' => 'id'));
    $this->business_participant_relationship_type_id = civicrm_api3('RelationshipType', 'getvalue', array('name_a_b' => 'Business participant is', 'return' => 'id'));

    $this->custom_groups['main_activity_info'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'main_activity_info'));
    $this->custom_groups['main_activity_info']['fields']['start_date'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_start_date', 'custom_group_id' => $this->custom_groups['main_activity_info']['id']));
    $this->custom_groups['main_activity_info']['fields']['end_date'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'main_activity_end_date', 'custom_group_id' => $this->custom_groups['main_activity_info']['id']));

    $this->custom_groups['Business_Programme'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Business_Programme'));
    $this->custom_groups['Business_Programme']['fields']['Naam_bedrijf'] = civicrm_api3('CustomField', 'getsingle', array(
      'name' => 'Naam_bedrijf',
      'custom_group_id' => $this->custom_groups['Business_Programme']['id']
    ));
    $this->custom_groups['Business_Programme']['fields']['Location'] = civicrm_api3('CustomField', 'getsingle', array(
      'name' => 'Location',
      'custom_group_id' => $this->custom_groups['Business_Programme']['id']
    ));
    $this->custom_groups['Business_Programme']['fields']['Aim_of_Visit'] = civicrm_api3('CustomField', 'getsingle', array(
      'name' => 'Short_description_Aim_of_Visit',
      'custom_group_id' => $this->custom_groups['Business_Programme']['id']
    ));

    $this->custom_groups['Passport_Information'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Passport_Information'));
    $this->custom_groups['Passport_Information']['fields'] = array();
    $passport_fields = civicrm_api3('CustomField', 'get', array('custom_group_id' => $this->custom_groups['Passport_Information']['id']));
    foreach ($passport_fields['values'] as $field) {
      $this->custom_groups['Passport_Information']['fields'][$field['name']] = $field;
    }
    $this->custom_groups['Nationality'] = civicrm_api3('CustomGroup', 'getsingle', array('name' => 'Nationality'));
    $this->custom_groups['Nationality']['fields']['Nationality'] = civicrm_api3('CustomField', 'getsingle', array('name' => 'Nationality', 'custom_group_id' => $this->custom_groups['Nationality']['id']));

    $this->submitted_status = civicrm_api3('OptionValue', 'getvalue', array('name' => 'Submitted', 'return' => 'value', 'option_group_id' => 'activity_status'));

    $this->different_data_registering_activity_type = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Different Data Registering', 'option_group_id' => 'activity_type'));
    $this->scheduled_activity_status = civicrm_api3('OptionValue', 'getvalue', array('return' => 'value', 'name' => 'Scheduled', 'option_group_id' => 'activity_status'));
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