<?php

$btime = microtime(true);

$times = 10;

for ($i = 0; $i < $times; $i++) {
    $fc = file_get_contents('http://localhost:8080/nimp');
    file_put_contents('/tmp/efg.jpg', $fc);
}

$etime = microtime(true);
$dtime = $etime - $btime;

echo $dtime/$times . "\n";

