<?php

// gets sender ip address
$realip = NULL;

if (isset($_SERVER)){
	if (isset($_SERVER['HTTP_X_FORWARDED_FOR'])){
		$arr = explode(',', $_SERVER['HTTP_X_FORWARDED_FOR']);
		foreach ($arr AS $ip){
			$ip = trim($ip); 
			if ($ip != 'unknown'){
				$realip = $ip; 
				break;
			}
		}
	}
	elseif (isset($_SERVER['HTTP_CLIENT_IP'])) $realip = $_SERVER['HTTP_CLIENT_IP'];
	else{
		if (isset($_SERVER['REMOTE_ADDR'])) $realip = $_SERVER['REMOTE_ADDR'];
		else $realip = '0.0.0.0';
	}
}
else{
	if (getenv('HTTP_X_FORWARDED_FOR')) $realip = getenv('HTTP_X_FORWARDED_FOR');
	elseif (getenv('HTTP_CLIENT_IP')) $realip = getenv('HTTP_CLIENT_IP');
	else $realip = getenv('REMOTE_ADDR');
}

preg_match("/[\d\.]{7,15}/", $realip, $onlineip);
$realip = !empty($onlineip[0]) ? $onlineip[0] : '0.0.0.0';

// queries database for date & time (as string)
// 1) result is empty => store current date & time for this ip address, then continue
// 2) result is non-empty => compare current date & time with the stored value
//   a) difference is less than 1 minute => exit();
//   b) difference is more than 1 minute => update date & time for this ip address, then continue

$con = mysql_connect('localhost', 'root', '') or die('Could not connect: ' . mysql_error());
mysql_select_db('feedback') or die('Could not select database');

$query = "SELECT `timestamp`.`time` FROM `timestamp` WHERE `timestamp`.`ip`='" . $realip . "'";
$result = mysql_query($query) or die('Query failed: ' . mysql_error());
if (mysql_num_rows($result) == 0) {
	$crttime = time();

	$query = "INSERT INTO `timestamp` SET `timestamp`.`ip`='" . $realip . "', `timestamp`.`time`='" . $crttime . "'";
	mysql_query($query) or die('Query failed: ' . mysql_error());
}
else {
	$row = mysql_fetch_assoc($result);
	$time = intval($row['time']);
	$crttime = time();

	($crttime - $time > 60) or die('Please wait at least 1 minute to send another feedback');

	$query = "UPDATE `timestamp` SET `timestamp`.`time`='" . $crttime . "' WHERE `timestamp`.`ip`='" . $realip . "'";
	mysql_query($query) or die('Query failed: ' . mysql_error());
}

mysql_free_result($result);
mysql_close($con);

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

$query = "INSERT INTO `feedback` SET `feedback`.`date`='" . $date . "', `feedback`.`feedback`='" . $feedback . "', `feedback`.`name`='" . $name . "', `feedback`.`email`='" . $email . "'";
mysql_query($query) or die('Query failed: ' . mysql_error());

mysql_close($con);

exit();

?>