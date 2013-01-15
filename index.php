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

function set_status_message($message = NULL) {
  if ($message) {
    if (!isset($_SESSION['messages'])) {
      $_SESSION['messages'] = array();
    }
    $_SESSION['messages'][] = $message;
  }
  return isset($_SESSION['messages']) ? $_SESSION['messages'] : array();
}

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
    header("Location: /", TRUE, 301);
    exit();
  }
}

render(array(
    'languages' => array(
      'en' => 'English',
      'ru' => 'Русский',
      'es' => 'Español',
    ),
    'debug' => User::all(),
    'form_data' => $_POST,
    'messages' => set_status_message(),
  )
);
