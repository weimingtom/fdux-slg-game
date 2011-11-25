<html>
<body>

<?php

$con = mysql_connect('localhost', 'root', '') or die('Could not connect: ' . mysql_error());
mysql_select_db('feedback') or die('Could not select database');

$query = 'SELECT * FROM `feedback` ORDER BY `feedback`.`id` DESC';
$result = mysql_query($query) or die('Query failed: ' . mysql_error());

echo "<div class='db_table'>\n";
while ($row = mysql_fetch_array($result)) {
    echo "\t<div class='db_row'>\n";
    echo "\t\t<p>ID :  " . $row[0] . " | 时间 : " . $row[1] . " | 玩家 : " . $row[3] . " | 邮箱 : " . $row[4] . " | 反馈 : " . $row[2] . "</p>\n";
    echo "\t</div>\n";
    echo "\t<hr />\n";
}
echo "</div>\n";

mysql_free_result($result);
mysql_close($con);
?>

</body>
</html>
