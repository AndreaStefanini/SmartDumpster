<?php
    include_once("../sd-service/database/database_entrance.php");
    $db->update_state(1);
//$mysqli = new mysqli("localhost", "root", "", "smartdumpster");
//$query_stato = "UPDATE `stato` SET `disponibile`=1";
//$result_stato = $mysqli->query($query_stato) or die(mysqli_error($con));
header("Location:smartdumpster.php");
?>
