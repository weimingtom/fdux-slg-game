<html>
<body>

<?php

$con = mysql_connect('localhost', 'root', '') or die('Could not connect: ' . mysql_error());
mysql_select_db('feedback') or die('Could not select database');

$query = 'SELECT * FROM feedback';
$result = mysql_query($query) or die('Query failed: ' . mysql_error());

echo "<div class='db_table'>\n";
while ($row = mysql_fetch_array($result)) {
    echo "\t<div class='db_row'>\n";
    echo "\t\t<p>" . $row[0] . "</p>\n";
	echo "\t\t<p>" . $row[1] . "</p>\n";
	echo "\t\t<p>" . $row[2] . "</p>\n";
	echo "\t\t<p>" . $row[3] . "</p>\n";
	echo "\t\t<p>" . $row[4] . "</p>\n";
    echo "\t</div>\n";
    echo "\t<hr />\n";
}
echo "</div>\n";

mysql_free_result($result);
mysql_close($con);
?>

</body>
</html>
