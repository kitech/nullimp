<?php

/*
  计数+队列
 */

/*
$list_head_key = crc32('shm_list_head');
$list_tail_key = crc32('shm_list_tail');
$list_head_lock = crc32('sem_list_head');
$list_tail_lock = crc32('sem_list_tail');


$list_head_rh = shm_attach($list_head_key);
$list_tail_rh = shm_attach($list_tail_key);

if (!shm_has_var($list_head_rh, $list_head_key)) {
    shm_put_var($list_head_rh, $list_head_key, 1);
}
$nval = shm_get_var($list_head_rh, $list_head_key);
var_dump($nval);

if (!shm_has_var($list_tail_rh, $list_tail_key)) {
    shm_put_var($list_tail_rh, $list_tail_key, 1);
}
$nval = shm_get_var($list_tail_rh, $list_tail_key);
var_dump($nval);
*/

$sq = new ShmQueue('abc');
$sq->dump();
$sq->reset();
$sq->dump();
$sq->enqueue();
$sq->enqueue();
$sq->dump();
$sq->dequeue();
$sq->dump();

$ttimes = 100000;
$btime = microtime(true);
for ($i = 0; $i < $ttimes; $i++) {
    $sq->enqueue();
    $dval = $sq->dequeue();
}
$etime = microtime(true);
$dtime = $etime - $btime;
$rate = $ttimes / $dtime;
$qs = $sq->size();
echo "bt={$btime}, et={$etime}, dt={$dtime}, rate={$rate}, size={$qs}\n";
// bt=1353261731.0004, et=1353261731.0203, dt=0.019963979721069, rate=500902.13172509
$sq->dump();

$ttimes = 10000;
$btime = microtime(true);
for ($i = 0; $i < $ttimes; $i++) {
    $name = "q{$i}";
    $sq = new ShmQueue($name);
    $sq->destroy();
}
$etime = microtime(true);
$dtime = $etime - $btime;
$rate = $ttimes / $dtime;
// $qs = $sq->size();
echo "bt={$btime}, et={$etime}, dt={$dtime}, rate={$rate}, size={$qs}\n";


class ShmQueue
{
    private $list_head_key = null;
    private $list_tail_key = null;
    private $list_head_lock_key = null;
    private $list_tail_lock_key = null;

    private $list_head_rh = null;
    private $list_tail_rh = null;

    private $list_head_lh = null;
    private $list_tail_lh = null;

    private $_name = '';

    public function __construct($name)
    {
        $this->_name = $name;

        $this->list_head_key = crc32('shm_list_head_' . $name);
        $this->list_tail_key = crc32('shm_list_tail_' . $name);
        $this->list_head_lock_key = crc32('sem_list_head_' . $name);
        $this->list_tail_lock_key = crc32('sem_list_tail_' . $name);
        
        $this->list_head_rh = shm_attach($this->list_head_key);
        $this->list_tail_rh = shm_attach($this->list_tail_key);

        if (!shm_has_var($this->list_head_rh, $this->list_head_key)) {
            shm_put_var($this->list_head_rh, $this->list_head_key, 0);
        }

        if (!shm_has_var($this->list_tail_rh, $this->list_tail_key)) {
            shm_put_var($this->list_tail_rh, $this->list_tail_key, 0);
        }

        $this->list_head_lh = sem_get($this->list_head_lock_key);
        $this->list_tail_lh = sem_get($this->list_tail_lock_key);
    }

    public function enqueue()
    {
        if (sem_acquire($this->list_head_lh)) {
            $head_num = shm_get_var($this->list_head_rh, $this->list_head_key);
            shm_put_var($this->list_head_rh, $this->list_head_key, $head_num + 1);
            
            sem_release($this->list_head_lh);
            return true;
        }
        return false;
    }

    public function dequeue()
    {
        if (sem_acquire($this->list_head_lh)) {
            $dval = false;
            $head_num = shm_get_var($this->list_head_rh, $this->list_head_key);
            $tail_num = shm_get_var($this->list_tail_rh, $this->list_tail_key);
            
            if ($head_num == $tail_num && $head_num == 0) {
                sem_release($this->list_head_lh);
                return false;
            }

            if ($tail_num + 1 <= $head_num) {
                $dval = $tail_num + 1;
                shm_put_var($this->list_tail_rh, $this->list_tail_key, $dval);
            }
            
            sem_release($this->list_head_lh);
            return $dval;
        }
        return false;
    }

    public function size()
    {
        $head_num = shm_get_var($this->list_head_rh, $this->list_head_key);
        $tail_num = shm_get_var($this->list_tail_rh, $this->list_tail_key);

        return $head_num - $tail_num;
    }

    public function isEmpty()
    {
        $head_num = shm_get_var($this->list_head_rh, $this->list_head_key);
        $tail_num = shm_get_var($this->list_tail_rh, $this->list_tail_key);

        if ($head_num == $tail_num) {
            return true;
        }
        return false;
    }

    public function reset()
    {
        shm_put_var($this->list_head_rh, $this->list_head_key, 0);
        shm_put_var($this->list_tail_rh, $this->list_tail_key, 0);
    }

    public function destroy()
    {
        shm_remove_var($this->list_head_rh, $this->list_head_key);
        shm_remove_var($this->list_tail_rh, $this->list_tail_key);
        shm_remove($this->list_head_rh);
        shm_remove($this->list_tail_rh);
        sem_remove($this->list_head_lh);
        sem_remove($this->list_tail_lh);
    }

    public function dump()
    {
        $head_num = shm_get_var($this->list_head_rh, $this->list_head_key);
        $tail_num = shm_get_var($this->list_tail_rh, $this->list_tail_key);

        var_dump($head_num, $tail_num);
    }
};