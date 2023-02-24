<?php
date_default_timezone_set('UTC');
$start = microtime(true);

if (isset($_GET['inputY'])) $y = $_GET['inputY'];
if (isset($_GET['inputR'])) $r = $_GET['inputR'];
if (isset($_GET['inputX'])) $x = $_GET['inputX'];
$check = false;
$fail = '';
if ($x == -5 || $x == -4 || $x == -3 || $x == -2 || $x == -1 || $x == 0 || $x == 1 || $x == 2 || $x == 3 ) $x = $x;
else $x = 'Error';
if ($y<=-3  || $y>=3 || (!is_numeric($y)) ) $y = 'Error';
if ($r<=1 || $r>=4 || (!is_numeric($r)) ) $r = 'Error';
elseif ($y != null && $r != null) {
    if ($x <= 0 && $x >= -$r && $y >= -$r / 2 && $y <= 0) $check .= true;
    elseif ($x <= 0 && $y >= 0 && $y <= ($x + $r) / 2) $check .= true;
    elseif ($x >= 0 && $y <= 0 && $y >= -sqrt($r * $r - $x * $x)) $check .= true;
}


if ($check) $fail .= 'Yes';
else $fail .="No";



$finish = microtime(true);
$time = number_format($finish-$start,6) * 1000;
$e = date('H:i:s');
echo "$x,$y,$r,$time,$fail,$e";


