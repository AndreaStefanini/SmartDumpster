<?php
    include_once("../sd-service/database/database_entrance.php");
    $db->empty();
//$mysqli = new mysqli("localhost", "root", "", "smartdumpster");
//$query_stato = "DELETE FROM gestore";
//$result_stato = $mysqli->query($query_stato) or die(mysqli_error($con));
header("Location:smartdumpster.php");


?>
