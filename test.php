<?php

ini_set('display_errors', true);
error_reporting(E_ALL);

$point = new QuadTreePoint(1.0, 2.0);
echo $point->getX() . PHP_EOL;
echo $point->getY() . PHP_EOL;

echo PHP_EOL;

echo 'Default parameters: ' . PHP_EOL;
$point = new QuadTreePoint();
echo $point->getX() . PHP_EOL;
echo $point->getY() . PHP_EOL;

echo PHP_EOL;

$box = new QuadTreeBoundingBox($point, 10, 20);


