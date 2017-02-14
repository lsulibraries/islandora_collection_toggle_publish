<?php

function islandora_collection_toggle_publish_settings_form($form, &$form_state) {

  $form['published'] = array(
    '#type' => 'checkbox',
    '#title' => t("Published by default."),
    '#default_value' => variable_get('islandora_collection_toggle_publish_by_default', 1),
    '#description' => t("Check this option if you want to make collections unpublished by default."),
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  return $form;
}

function islandora_collection_toggle_publish_settings_form_submit($form, &$form_state) {
  variable_set('islandora_collection_toggle_publish_by_default', $form_state['values']['published'] ? 1 : 0);
}