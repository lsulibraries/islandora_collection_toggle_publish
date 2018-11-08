<?php


function islandora_collection_toggle_publish_properties($form, &$form_state) {
  $submitted = $form_state['values']['islandora_collection_toggle_publish_is_published'];
  if ($submitted != islandora_collection_toggle_publish_collection_is_published($form_state['values']['pid'])) {
    $submitted ? islandora_collection_toggle_publish_publish_collection($form_state['values']['pid']) : islandora_collection_toggle_publish_unpublish_collection($form_state['values']['pid']);
    $multisites = variable_get('islandora_collection_toggle_publish_multisites_to_update','');
    if (!empty($multisites)) {
      foreach (explode(',', $multisites) as $site) {
	$drupal_root = DRUPAL_ROOT;
	$pid         = $form_state['values']['pid'];
        $op          = $submitted ? 'publish' : 'unpublish';
        $command     = "cd $drupal_root/sites/$site && drush ict-pub $op --pid=$pid";
        exec($command);
      }
    }
  }
}

function islandora_collection_toggle_publish_collection_is_published ($pid) {
  $records = db_select('islandora_collection_toggle_publish_collections', 'c')
    ->fields('c', array('pid'))
    ->condition('pid', $pid)
    ->execute();
  $unpublished = $records->rowCount();
  return !$unpublished;
}


function islandora_collection_toggle_publish_unpublish_collection ($pid) {
  db_insert('islandora_collection_toggle_publish_collections')
  ->fields(array('pid' => $pid))
  ->execute();
}

function islandora_collection_toggle_publish_publish_collection ($pid) {
  db_delete('islandora_collection_toggle_publish_collections')
  ->condition('pid', $pid)
  ->execute();
}


/**
 *
 * @param type $islandora_object
 * @return boolean
 */
function is_collection($islandora_object) {
  $models = $islandora_object->relationships->get('info:fedora/fedora-system:def/model#', 'hasModel');
  foreach ($models as $model) {
    if ($model['object']['value'] === "islandora:collectionCModel") {
      return TRUE;
    }
  }
  return FALSE;
}

function get_parent_collection ($islandora_object) {
  $rels = $islandora_object->relationships->get("info:fedora/fedora-system:def/relations-external#", "isMemberOfCollection");
  foreach ($rels as $collection) {
      return $collection['object']['value'];
  }
}
