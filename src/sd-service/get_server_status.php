<?php
    require_once("database/database_entrance.php");
    $array = $db->get_state()[0];
    echo $array["disponibile"];
?>