<?php

class DB {
  private static $instance = NULL;
  private $db;

  private function DB() {
    $db_host = DATABASE_HOST;
    $db_name = DATABASE_NAME;
    $this->db = new PDO("mysql:host={$db_host};dbname={$db_name}", DATABASE_USER, DATABASE_PASS);
  }

  /**
   * Gets instance of the class according to the Singleton pattern.
   * @return DB
   */
  public static function getInstance() {
    if (!isset(self::$instance)) {
      self::$instance = new DB();
    }
    return self::$instance;
  }

  /**
   * Executes SQL-query and returns PDOStatement object.
   *
   * @param $query
   *   SQL query. For example "SELECT * FROM users WHERE email = :email"
   * @param array $args
   *   Arguments for the query. For example: array(':email' => 'test@example.com')
   * @return PDOStatement
   */
  public function query($query, array $args = array()) {
    $dbq = $this->db->prepare($query);
    $dbq->execute($args);
    return $dbq;
  }

  /**
   * Executes SELECT query and returns array with results.
   *
   * @param $query
   *   SQL query. For example "SELECT * FROM users WHERE email = :email"
   * @param array $args
   *   Arguments for the query. For example: array(':email' => 'test@example.com')
   * @return array
   */
  public function select($query, array $args = array()) {
    return $this->query($query, $args)->fetchAll(PDO::FETCH_ASSOC);
  }

  /**
   * Executes UPDATE query and returns PDOStatement object.
   *
   * @param $query
   *   SQL query. For example "UPDATE users SET email = :email WHERE id = :id"
   * @param array $args
   *   Arguments for the query. For example: array(':email' => 'test@example.com', ':id' => 1)
   * @return PDOStatement
   */
  public function update($query, array $args = array()) {
    return $this->query($query, $args)->rowCount();
  }
}
