<?php

ini_set('display_errors', true);
error_reporting(E_ALL);

echo 'Default parameters: ' . PHP_EOL;
$defaultPoint = new QuadTreePoint();
echo $defaultPoint->getX() . PHP_EOL;
echo $defaultPoint->getY() . PHP_EOL;

echo PHP_EOL;

$point = new QuadTreePoint(100.0, 200.0);
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
echo 'X: ' . $retrievedPoint->getX() . PHP_EOL;

echo PHP_EOL;
echo PHP_EOL;

var_dump($box->containsPoint($defaultPoint));
var_dump($box->containsPoint($point));

echo PHP_EOL;
echo PHP_EOL;

$box2 = new QuadTreeBoundingBox($point, 5, 5);
var_dump($box2->intersects($box));

echo PHP_EOL;
echo PHP_EOL;

$box3 = new QuadTreeBoundingBox($defaultPoint, 5, 5);
var_dump($box3->intersects($box));

echo PHP_EOL;
echo PHP_EOL;



