<?php

/**
 * @file
 * Drush interface to ip_embargo functionality.
 */

/**
 * Drush commands declaration.
 *
 * @return array
 *   drush commands data
 */
function islandora_collection_toggle_publish_drush_command() {
  $items = array();
  $items['islandora-collection-toggle-publish-set'] = array(
    'description' => 'Set whether a pid is published or unpublished.',
    'aliases' => array('ict-pub'),
    'arguments' => array(
      'op' => 'Publish or unpublish',
    ),
    'options' => array(
      'pidsfile' => array(
        'description' => dt('File containing a comma-separated string of pids'),
        'required' => FALSE,
      ),
      'pid' => array(
        'description' => 'Islandora pid to affect.',
        'required' => FALSE,
      ),
    ),
  );
  return $items;
}

function drush_islandora_collection_toggle_publish_set($op) {
  module_load_include('inc', 'islandora_collection_toggle_publish', 'includes/utilities');
  $ops = array('unpublish', 'publish');
  if (!in_array($op, $ops)) {
    throw new Exception("Argument should be either: 'unpublish' or 'publish'");
  }
  $pids = islandora_collection_toggle_publish_pid_or_pids();
  foreach ($pids as $pid) {
    $fn = 'islandora_collection_toggle_publish_'.$op.'_collection';
    $fn($pid);
  }
}


/**
 * Return an array of PIDs, depending on the drush option.
 *
 * @return array
 *   Containing either the value of option --pids, or the array obtained from
 *   passing the contents of option --pidsfile through explode().
 * @throws Exception
 *   Either --pid or --pidsfile must be used, not both.
 */
function islandora_collection_toggle_publish_pid_or_pids() {
  foreach (array('pid', 'pidsfile') as $option) {
    $$option = drush_get_option($option);
  }
  if ($pid Xor $pidsfile) {
    return $pid ? array($pid) : explode(',', file_get_contents($pidsfile));
  }
  else {
    throw new Exception("Must supply either --pid or --pidsfile.");
  }
}
