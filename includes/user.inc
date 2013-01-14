<?php

class User {
  private $email;
  private $pass;
  private $lang;

  public function User($email, $pass, $lang) {
    $this->email = $email;
    $this->pass = crypt($pass, HASH_SALT);
    $this->lang = $lang;
  }

  private function validate() {
    return TRUE;
  }

  public function save() {
    if (!$this->validate()) {
      //TODO: set errors
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
