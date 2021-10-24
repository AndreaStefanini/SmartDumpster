<?php
$mysqli = new mysqli("localhost", "root", "", "smartdumpster");
$query_stato = "UPDATE `stato` SET `disponibile`=0";
$result_stato = $mysqli->query($query_stato) or die(mysqli_error($con));
header("Location:smartdumpster.php");
?>
