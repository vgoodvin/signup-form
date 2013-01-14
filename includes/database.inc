<?php

class DB {
  private static $instance = NULL;
  private $db;

  private function DB() {
    $this->db = new PDO('mysql:host=localhost;dbname=megamarka', 'test', 'test');
  }

  /**
   * @return DB
   */
  public static function getInstance() {
    if (!isset(self::$instance)) {
      self::$instance = new DB();
    }
    return self::$instance;
  }

  private function query($query, array $args = array()) {
    $dbq = $this->db->prepare($query);
    $dbq->execute($args);
    return $dbq;
  }

  public function select($query, array $args = array()) {
    return $this->query($query, $args)->fetchAll(PDO::FETCH_ASSOC);
  }

  public function insert($query, array $args = array()) {
    return $this->query($query, $args);
  }
}
