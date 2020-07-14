@ok
<?php

interface Foo {
  /**
   * @kphp-infer
   * @param int $a
   * @return int|false
   */
  public function foo($a);
}

class B implements Foo {
  /**
   * @kphp-infer
   * @param int $a
   * @return int|false
   */
  public function foo($a) {
    return $a + 30;
  }
}

class D extends B {
  /**
   * @kphp-infer
   * @param int $a
   * @return int|false
   */
  public function foo($a) {
    return false;
  }
}

class B2 implements Foo {
  /**
   * @kphp-infer
   * @param int $a
   * @return int|false
   */
  public function foo($a) {
    return $a + 10;
  }
}

$call_foo = function(Foo $f) {
  var_dump($f->foo(536));
};

$call_foo(new B());
$call_foo(new D());
$call_foo(new B2());

