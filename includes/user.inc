<?php

class User {
  private $email;
  private $pass;
  private $pass_raw;
  private $lang;
  private $verification_id;

  public function User($email, $pass, $lang) {
    $this->email = $email;
    $this->pass_raw = $pass;
    $this->pass = crypt($pass, HASH_SALT);
    $this->lang = $lang;
    $this->verification_id = md5(uniqid($email, true));
  }

  /**
   * Validates user fields.
   */
  private function validate() {
    $errors = array();
    if (!filter_var($this->email, FILTER_VALIDATE_EMAIL)) {
      $errors[] = 'Please enter valid email address';
    }
    elseif (self::findByEmail($this->email)) {
      $errors[] = 'User with given email address already exists. Please specify another email.';
    }
    if (strlen($this->pass_raw) < 6) {
      $errors[] = 'Please enter at least 6 symbols in the password field';
    }
    if (empty($errors)) {
      return TRUE;
    }
    array_walk($errors, function ($error) {
      set_status_message($error);
    });
    return FALSE;
  }

  /**
   * Saves user to the database.
   *
   * @return bool
   *   TRUE if user was raved and FALSE otherwise.
   */
  public function save() {
    if (!$this->validate()) {
      return FALSE;
    }
    $timezone = new DateTimeZone('UTC');
    $date = new DateTime('now', $timezone);
    return DB::getInstance()->query("INSERT INTO users (email, pass, lang, token, created_at) VALUES (:email, :pass, :lang, :token, :created_at)", array(
      ':email' => $this->email,
      ':pass' => $this->pass,
      ':lang' => $this->lang,
      ':token' => $this->verification_id,
      ':created_at' => $date->format('Y-m-d H:i:s'),
    ));
  }

  /**
   * Sends email notification via SMTP.
   */
  public function sendNotification() {
    $domain = DOMAIN;
    $query_string = http_build_query(array(
      'verification_id' => $this->verification_id,
      'email' => $this->email,
    ));
    $verification_link = "http://{$domain}?{$query_string}";
    $body = "Congratulations!\n\nYou just created account at {$domain}\n Follow {$verification_link} to activate your account. \r\n";
    $connect = fsockopen('localhost', 25, $errno, $errstr, 30);
    fputs($connect, "HELO localhost\r\n");
    fputs($connect, "MAIL FROM: admin@{$domain}\n");
    fputs($connect, "RCPT TO: {$this->email}\n");
    fputs($connect, "DATA\r\n");
    fputs($connect, "Content-Type: text/plain; charset=utf-8\n");
    fputs($connect, "To: {$this->email}\n");
    fputs($connect, "Subject: You just created account at {$domain}\n");
    fputs($connect, "\n\n");
    fputs($connect, $body);
    fputs($connect, ".\r\n");
    fputs($connect, "RSET\r\n");
  }

  /**
   * Gets all users from database.
   *
   * @return array
   *   Array of users.
   */
  public static function all() {
    return DB::getInstance()->select('SELECT * from users');
  }

  /**
   * Gets user with specified email.
   *
   * @param $email
   *   User's email.
   * @return array
   *   Associative array with user information.
   */
  public static function findByEmail($email) {
    $user = DB::getInstance()->select('SELECT * from users WHERE email = :email', array(':email' => $email));
    return reset($user);
  }

  /**
   * Activates user account.
   *
   * @param $email
   *   User's email.
   * @param $verification_id
   *   Verification token.
   * @return bool
   *   TRUE if account was activated and FALSE otherwise.
   */
  public static function activate($email, $verification_id) {
    $sql = 'UPDATE users SET token = NULL, status = 1 WHERE email = :email AND token = :token AND token IS NOT NULL';
    $rowsAffected = DB::getInstance()->update($sql, array(
      ':email' => $email,
      ':token' => $verification_id,
    ));
    return (bool) $rowsAffected;
  }
}
