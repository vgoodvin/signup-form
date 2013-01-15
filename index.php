<?php

/**
 * Hash salt used for passwords.
 */
define('HASH_SALT', '5ffblhfe3g4w');
/**
 * Site domain.
 */
define('DOMAIN', 'signup-example.com');

/**
 * Database credentials.
 */
define('DATABASE_HOST', 'localhost');
define('DATABASE_NAME', 'signup');
define('DATABASE_USER', 'test');
define('DATABASE_PASS', 'test');

/**
 * Included files
 */
require_once('./includes/user.inc');
require_once('./includes/database.inc');

/**
 * Sets a message to display to the user.
 *
 * @param null $message
 *   Message test.
 * @return array
 *   List of all messages which were already set.
 */
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
 *   Array with variables, which will be passed to template.
 */
function render(array $vars) {
  extract($vars);
  include_once('./templates/page.php');
}

if (!empty($_POST) && $_POST['op'] == 'Sign up') {
  $user = new User($_POST['email'], $_POST['pass'], $_POST['lang']);
  if ($user->save()) {
    // Send email notification.
    $user->sendNotification();
    // Redirect to front page.
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
    'form_data' => $_POST,
    'messages' => set_status_message(),
  )
);
