<?php

error_reporting(E_ALL);
ini_set('display_errors', true);

$pointA = new QuadTreePoint(100, 100);
$box = new QuadTreeBoundingBox($pointA, 200, 200);

$pointB = new QuadTreePoint(100, 100);
$otherBox = new QuadTreeBoundingBox($pointB, 100, 100);

$point1 = new QuadTreePoint(10, 10);
$point2 = new QuadTreePoint(20, 20);
$point3 = new QuadTreePoint(30, 30);
$point4 = new QuadTreePoint(40, 40);
$point5 = new QuadTreePoint(50, 50);
$point6 = new QuadTreePoint(60, 60);
$point7 = new QuadTreePoint(70, 70);
$point8 = new QuadTreePoint(80, 80);
$point9 = new QuadTreePoint(90, 90);
$point10 = new QuadTreePoint(100, 100);

$tree = new QuadTree($box);
$box->dump();
$tree->dump();

echo PHP_EOL;

$tree->insert($point1);
$tree->insert($point2);
$tree->insert($point3);
$tree->insert($point4);
$tree->insert($point5);
$tree->insert($point6);
$tree->insert($point7);
$tree->insert($point8);
$tree->insert($point9);
$tree->insert($point10);

$tree->dump();

echo PHP_EOL;
echo PHP_EOL;
echo PHP_EOL;

var_dump($point1);

echo PHP_EOL;

var_dump($tree->search($otherBox));
