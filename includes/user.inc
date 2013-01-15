<?php

class User {
  private $email;
  private $pass;
  private $pass_raw;
  private $lang;

  public function User($email, $pass, $lang) {
    $this->email = $email;
    $this->pass_raw = $pass;
    $this->pass = crypt($pass, HASH_SALT);
    $this->lang = $lang;
  }

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

  public function save() {
    if (!$this->validate()) {
      return FALSE;
    }
    $timezone = new DateTimeZone('UTC');
    $date = new DateTime('now', $timezone);
    return DB::getInstance()->insert("INSERT INTO users (email, pass, lang, created_at) VALUES (:email, :pass, :lang, :created_at)", array(
      ':email' => $this->email,
      ':pass' => $this->pass,
      ':lang' => $this->lang,
      ':created_at' => $date->format('Y-m-d H:i:s'),
    ));
  }

  public static function all() {
    return DB::getInstance()->select('SELECT * from users');
  }

  public static function findByEmail($email) {
    return DB::getInstance()->select('SELECT * from users WHERE email = :email', array(':email' => $email));
  }
}
