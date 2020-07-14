<?php

namespace Classes;

class B {
    /** @var int */
    var $magic = 0;

    /**
     * @kphp-infer
     * @param int $magic
     */
    public function __construct($magic = 0) {
        $this->magic = $magic;
    }

    public function print_magic() {
        var_dump("B: {$this->magic}");
    }
}
