<?php

/**
 * Set error reporting to display all errors while developing.
 */
error_reporting(-1);
ini_set('display_errors', TRUE);
ini_set('display_startup_errors', TRUE);


define('HASH_SALT', '5ffblhfe3g4w');

/**
 * Included files
 */
require_once('./includes/user.inc');
require_once('./includes/database.inc');

/**
 * Renders sign-up form.
 * @param array $vars
 */
function render(array $vars) {
  extract($vars);
  include_once('./templates/page.php');
}

if (!empty($_POST) && $_POST['op'] == 'Sign up') {
  $user = new User($_POST['email'], $_POST['pass'], $_POST['lang']);
  if ($user->save()) {
    // TODO: send email notification
    // TODO: redirect to form and show status message
  }
  else {
    // TODO: keep entered data in form and show error message
  }
}

render(array(
    'languages' => array(
      'en' => 'English',
      'ru' => 'Русский',
      'es' => 'Español',
    ),
    //'debug' => $db->query('SELECT * from users')->fetchAll(PDO::FETCH_ASSOC),
    //'debug' => $_POST,
    'debug' => User::all(),
    //'debug' => User::findByEmail('1@example.com'),
    // TODO: output status messages
  )
);
