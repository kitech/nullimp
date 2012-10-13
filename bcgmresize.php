<?php

$gmhs = array();

$fname = "/home/gzleo/dlnk/shots27.png";
$fcontent = file_get_contents($fname);
for ($i = 0; $i < 100; $i++) {
    $gmh = new Gmagick();
    // $gmh->readimage($fname);
    $gmh->readimageblob($fcontent);
    $gmhs[] = $gmh;
}

echo "read source file done.\n";

$btime = microtime(true);
for ($i = 0; $i < 100; $i ++) {
    $gmh = $gmhs[$i];
    $gmh->scaleimage(100, 80);
}
$etime = microtime(true);
$dtime = $etime - $btime;
$avg_cnt = $dtime / 100;
echo "dtime: {$dtime}, {$avg_cnt} s \n";

// 还是比使用C编写的速度慢，用php的话，平均使用29ms，而C版本的平均使用30ms


