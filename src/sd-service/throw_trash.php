<?php
    include_once('database/database_entrance.php');
    $obj = json_decode(file_get_contents("php://input"));
    $peso = $obj->Quantity;
    $tipo = $obj->Type;
    $db->throw_trash($tipo,$peso);
    
?>