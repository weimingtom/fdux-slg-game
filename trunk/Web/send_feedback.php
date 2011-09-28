<?php

$con = mysql_connect('localhost', 'root', '') or die('Could not connect: ' . mysql_error());
mysql_select_db('feedback') or die('Could not select database');

$date = '';
$feedback = '';
$name = '';
$email = '';

if (array_key_exists('date', $_POST)) $date = $_POST['date'];
if (array_key_exists('feedback', $_POST)) $feedback = $_POST['feedback'];
if (array_key_exists('name', $_POST)) $name = $_POST['name'];
if (array_key_exists('email', $_POST)) $email = $_POST['email'];

$query = "INSERT INTO feedback SET `date`='" . $date . "', feedback='" . $feedback . "', name='" . $name . "', email='" . $email . "'";
mysql_query($query) or die('Query failed: ' . mysql_error());

mysql_close($con);

?>