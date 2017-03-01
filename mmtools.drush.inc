<?php
/**
 * @file mmm_revert.drush.inc
 */

use clever_systems\mmm_runtime\Runtime;

/**
 * Implements hook_drush_command().
 */
function mmtools_drush_command() {
  $items = array();

  $items['mmtools-db-caches-clean'] = array(
    'aliases' => ['dbcc'],
    'description' => 'Clean all unused database caches.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  $items['mmtools-site-install'] = array(
    'aliases' => ['mmsi'],
    'description' => 'Install site with autodetected defaults.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'arguments' => [
      'name' => 'The site name (also lowercased DB prefix), defaults to Dev.'
    ],
  );

  return $items;
}

function drush_mmtools_db_caches_clean() {
  // @todo Suit to drupal 8.
  // Flush unused cache tables.
  /** @see drupal_flush_all_caches */
  /** @see cache_clear_all */
  $core = array('cache', 'cache_path', 'cache_filter', 'cache_bootstrap', 'cache_page');
  $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
  foreach ($cache_tables as $table) {
    $cache = _cache_get_object($table);
    drush_log(dt('Cache class: !table', ['!table' => get_class($cache)]));
    if (!$cache instanceof \DrupalDatabaseCache) {
      //$cache->clear('*', TRUE);
      try {
        db_query('truncate table ' . db_escape_table($table));
        drush_log(dt('Cleaned cache table !table', ['!table' => $table]), 'ok');
      } catch (\PDOException $e) {
        // There are caches like ctools_css that don't have a table.
        drush_log(dt('Ignored nonexisting cache table !table', ['!table' => $table]));
      }
    }
    else {
      drush_log(dt('Ignored DB cache table !table', ['!table' => $table]));
    }
  }
}

/**
 * Implements drush_hook_COMMAND for site-install.
 */
function drush_mmtools_site_install($name = 'Dev') {
  if (defined('DRUPAL_ROOT')) {
    @include DRUPAL_ROOT . '/../vendor/autoload.php';
  }
  $environment = Runtime::getEnvironment();

  // We booted to drupal_root, so no settings available. Make fake ones.
  $settings = [];
  $databases = [];

  $db_record =& $databases['default']['default'];
  if (!is_array($db_record)) {
    $db_record = [];
  }

  $machine_name = preg_replace('#[^a-z0-9]#u', '_', strtolower($name));
  $db_record += [
    'database' => $environment->getUser() . '_' . $machine_name,
  ];

  $environment->settings($settings, $databases);

  if (
    !empty($databases['default']['default']['username'])
    && !empty($databases['default']['default']['host'])
    && !empty($databases['default']['default']['password'])
  ) {
    $username = $db_record['username'];
    $host = $db_record['host'];
    $password = $db_record['password'];

    $db_record += [
      'driver' => 'mysql',
      'port' => '3306',
      'prefix' => '',
    ];
    $driver = $db_record['driver'];
    $port = $db_record['port'];
    $prefix = $db_record['prefix'];
    $database = $db_record['database'];

    $db_url = "$driver://$username:$password@$host:$port/$database";
    /* @see drush_context_names() */
    drush_set_default('db-url', $db_url);
    drush_set_default('db-prefix', $prefix);
    drush_set_default('account-name', 'gott');
    drush_set_default('locale', 'de');
    drush_set_default('site-name', dirname(DRUPAL_ROOT));

    drush_invoke('site-install');
  }
}
