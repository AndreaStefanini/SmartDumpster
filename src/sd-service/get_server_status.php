<?php
    require_once("database/database_entrance.php");
    $result["disponibile"] = $db->get_state()[0]["disponibile"];
    $result["rifiuti"] = $db->get_trash()[0]["rifiuti"];
    echo json_encode($result);
?>