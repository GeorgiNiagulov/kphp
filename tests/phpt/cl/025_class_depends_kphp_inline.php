@ok
<?php

class A {
  /** @var A[] */
  private static $b = [];

  public function __construct() {}

  /**
   * @kphp-inline
   * @kphp-infer
   * @return bool
   */
  public static function foo() {
    return isset(self::$b[0]);
  }
}

A::foo();
