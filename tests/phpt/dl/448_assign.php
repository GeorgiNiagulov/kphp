@ok benchmark
<?php

  $a = true;
  var_dump ($a);
  $a = 2;
  var_dump ($a);
  $a = 3.0;
  var_dump ($a);
  $a = "4";
  var_dump ($a);
  $a = array (5, "7");
  var_dump ($a);

  for ($i = 0; $i < 40000000; $i++) {
    $a = $a;
  }

  var_dump ($a);

