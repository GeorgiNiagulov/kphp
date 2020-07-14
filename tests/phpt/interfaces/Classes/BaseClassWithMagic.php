<?php

namespace Classes;

require_once 'polyfills.php';

class BaseClassWithMagic {
    /**
     * @kphp-infer
     * @return int
     */
    static public function do_magic() {
      return self::demo("magic");
    }

    /**
     * @kphp-infer
     * @param string $key
     * @return int
     */
    static protected function demo($key) {
        if (0) new AAA();
        $data_from_cache = instance_cache_fetch(AAA::class, $key);

        if ($data_from_cache instanceof AAA) {
          return $data_from_cache->x;
        }
        instance_cache_store($key, AAA::create());
        return 1;
    }
}

