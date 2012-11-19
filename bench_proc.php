<?php

$load_file = "/proc/loadavg";

$times = 10000;
$btime = microtime(true);
for ($i = 0; $i < $times; $i++) {
    // $loads = file_get_contents($load_file);
    $fp = fopen($load_file, 'r');
    $loads = fgets($fp);
    fclose($fp);
    $pos1 = strpos($loads, ' ');
    $min1_load = substr($loads, 0, $pos1);
    // echo $pos1 . "a{$min1_load}a\n";exit;
    // $ploads = explode(' ', $loads);
    // $min1_load = $ploads[0];
    // $min5_load = $ploads[1];
    // $min15_load = $ploads[2];
    
    // $min1_load = strpbrk($loads, ' ');
    // echo $min1_load . "\n";
    // exit;
}

$etime = microtime(true);
$dtime = $etime - $btime;
$rate = $times / $dtime;

echo "used: {$dtime}, rate: {$rate}/sec\n";

/*
  如果出现这个错误，PHP Warning:  fopen(): open_basedir restriction in effect.
  检查php.ini的配置，open_basedir = /srv/http/:/home/:/tmp/:/usr/share/pear/

  检测这个值，平均大概9w/秒
 */
