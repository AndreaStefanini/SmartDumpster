<?php
    
    header("content-type: application/json");
    include_once('database /database_entrance.php');
    function random_strings($length_of_string){
  
    $str_result = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz';
  
    return substr(str_shuffle($str_result), 0, $length_of_string);
}
    $state = $db->get_state()[0];
    if($state["disponibile"]==1){
        $array["token"] = random_strings(10);
        echo json_encode($array);
    }else{
        $array["token"]= "NULL";
        echo json_encode($array);
    }
    /**
     * before generating any token i need to check if the dumpster is available, if not i need to send a negative response
     * if the dumpster is available i can generate the token and send it.
     * TO DO:
     * - create a query to make sure the dumpster is stil running DONE
     * - implement the control above mentioned DONE
     * - search for the correct way to send a negative response MAYBE
     * - handle the negative response on the android side.
     *
     */
    

 ?>