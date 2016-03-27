<?php

error_reporting(E_ALL);
ini_set('display_errors', true);

$box = new QuadTreeBoundingBox(
    new QuadTreePoint(100, 100), 200, 200);

$point = new QuadTreePoint(1, 2);

$box->dump();
