<?php
     include_once("database/database_entrance.php");
     $obj = json_decode(file_get_contents("php://input"));
     $db->update_state($obj->State);
     

?>