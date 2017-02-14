<?php

function islandora_collection_toggle_publish_settings_form($form, &$form_state) {

  $form['published'] = array(
    '#type' => 'checkbox',
    '#title' => t("Published by default."),
    '#default_value' => variable_get('islandora_collection_toggle_publish_by_default', 1),
    '#description' => t("Check this option if you want to make collections unpublished by default."),
  );
  $form['multisites_to_update'] = array(
    '#type' => 'textfield',
    '#title' => t("Also update these multisite locations."),
    '#default_value' => variable_get('islandora_collection_toggle_publish_multisites_to_update', ''),
    '#description' => t("If you are running this module in a multisite configuration, list here the directories that drush can use to update other relevant sites (comma-separated)."),
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;
}

function islandora_collection_toggle_publish_settings_form_submit($form, &$form_state) {
  variable_set('islandora_collection_toggle_publish_by_default', $form_state['values']['published'] ? 1 : 0);
  $multisites = implode(',', array_map('trim', explode(',', $form_state['values']['multisites_to_update'])));
  variable_set('islandora_collection_toggle_publish_multisites_to_update', $multisites);
}