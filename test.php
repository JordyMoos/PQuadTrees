<?php

ini_set('display_errors', true);
error_reporting(E_ALL);

echo 'Default parameters: ' . PHP_EOL;
$point = new QuadTreePoint();
echo $point->getX() . PHP_EOL;
echo $point->getY() . PHP_EOL;

echo PHP_EOL;

$point = new QuadTreePoint(1.0, 2.0);
echo $point->getX() . PHP_EOL;
echo $point->getY() . PHP_EOL;

echo PHP_EOL;
echo PHP_EOL;
echo 'Create box with point:' .PHP_EOL;
var_dump($point);

echo PHP_EOL;
echo PHP_EOL;

$box = new QuadTreeBoundingBox($point, 10, 20);
var_dump($box);
echo 'Width: ' . $box->getWidth() . PHP_EOL;

$retrievedPoint = $box->getCenterPoint();
echo 'Retrieved point: ' . PHP_EOL;
var_dump($retrievedPoint);

