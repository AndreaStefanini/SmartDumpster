<?php
    
    header("content-type: application/json");
    function random_strings($length_of_string){
  
    $str_result = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
  
    return substr(str_shuffle($str_result), 0, $length_of_string);
}
    //include_once('database.php');
    //$db = new database();
    //$db->throw_trash($_POST["type"]),$_POST["weight"]);
    //http_response_code(200);
    $array["token"] = random_strings(10);
    echo json_encode($array);
    

 ?>