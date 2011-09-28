<?php

$con = mysql_connect('localhost', 'root', '') or die('Could not connect: ' . mysql_error());
mysql_select_db('feedback') or die('Could not select database');

$date = '';

if (array_key_exists('date', $_POST)) $date = $_POST['date'];

$query = "INSERT INTO execution_count SET `date`='" . $date . "'";
mysql_query($query) or die('Query failed: ' . mysql_error());

mysql_close($con);

exit();

?>