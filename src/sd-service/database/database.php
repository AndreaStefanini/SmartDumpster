<?php 
class database {
    
    public $connection;

    public function __construct(){
        $this->connection = new mysqli('localhost', 'root', '', 'smartdumpster');
        if($this->connection->connect_error){
            die("An error occurred during the connection to the database, please retry". $this->connection->connect_error);
        }
    }
    public function throw_trash($type, $weight){
        $throw = $this->connection->prepare("INSERT INTO gestore(tipologia, peso) VALUES(?,?)");
        $throw->bind_param("si", $type, $weight);
        $throw->execute();
        $rif = $this->get_trash()[0]["rifiuti"];
        $rif+=1;
        $new_trash = $this->connection->prepare("UPDATE `stato` SET `rifiuti`=? WHERE 1");
        $new_trash->bind_param("i",$rif);
        $new_trash->execute();

        //devo creare la seconda e terza query per fare l'update dello stato
    }
    public function get_state(){
        $state = $this->connection->prepare("SELECT disponibile FROM stato");
        $state->execute();
        $result= $state->get_result();
        return $result->fetch_all(MYSQLI_ASSOC);
    }
    public function update_state($state){
        $new_state = $this->connection->prepare("UPDATE `stato` SET `disponibile`=? WHERE 1");
        $new_state->bind_param("i",$state);
        $new_state->execute();
    }
    public function empty_trash(){
        $new_state = $this->connection->prepare("UPDATE `stato` SET `rifiuti`=0 WHERE 1");
        $new_state->execute();
    }
    public function get_trash(){
        $trash = $this->connection->prepare("SELECT rifiuti FROM `stato` WHERE 1");
        $trash->execute();
        $result = $trash->get_result();
        return $result->fetch_all(MYSQLI_ASSOC);

    }
    public function get_TrashA(){
        $trashA = $this->connection->prepare("SELECT SUM(peso) as peso, data FROM gestore WHERE tipologia='A' GROUP BY data");
        $trashA->execute();
        $results = $trashA->get_result()->fetch_all(MYSQLI_ASSOC);
        if(!empty($results)){
            foreach($results as $result):
                $datas[] = array("label"=>$result["data"],"y"=>$result["peso"]);
            endforeach;
            return $datas;
        }else{
            die("error");
        }
        
    }
    public function get_TrashB(){
        $trashB = $this->connection->prepare("SELECT SUM(peso) as peso, data FROM gestore WHERE tipologia='B' GROUP BY data");
        $trashB->execute();
        $results = $trashB->get_result()->fetch_all(MYSQLI_ASSOC);
        if(!empty($results)){
            foreach($results as $result):
                $datas[] = array("label"=>$result["data"],"y"=>$result["peso"]);
            endforeach;
            return $datas;
        }else{
            die("error");
        }
    }
    public function get_TrashC(){
        $trashC = $this->connection->prepare("SELECT SUM(peso) as peso, data FROM gestore WHERE tipologia='C' GROUP BY data");
        $trashC->execute();
        $results = $trashC->get_result()->fetch_all(MYSQLI_ASSOC);
        if(!empty($results)){
            foreach($results as $result):
                $datas[] = array("label"=>$result["data"],"y"=>$result["peso"]);
            endforeach;
            return $datas;
        }else{
            die("error");
        }
    }

}

?>
