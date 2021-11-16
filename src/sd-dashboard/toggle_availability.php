<?php
include '../sd-service/database/database_entrance.php';
$value = intval($_POST["aval"]);
$db->update_state($value);
header("Location:index.php");
?>