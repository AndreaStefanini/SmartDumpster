<?php 
class database {
    
    public $connection;

    public function __construct(){
        $this->connection = new mysqli('localhost', 'root', '', 'smartdumpster');
        if($this->connection->connect_error){
            die("An error occurred during the connection to the database, please retry". $this->connection->connect_error);
        }
    }
    //questa funzione è solo come da esempio, da cancellare prima di terminare il progetto
    public function add_user($nome, $cognome, $email, $userpassword, $data_nascita, $usertype, $profileimage){
       $insertquery=$this->connection->prepare("INSERT INTO users(Nome,Cognome,email,password,Data_Nascita,Tipo_User, ProfileImage) VALUES(?,?,?,?,?,?,?)");
       $insertquery->bind_param('sssssss',$nome,$cognome,$email,$userpassword,$data_nascita,$usertype,$profileimage);
       $insertquery->execute();

    }
    //questa funzione è solo come da esempio, da cancellare prima di terminare il progetto
    public function login($email, $password){
        $login=$this->connection->prepare("SELECT ID ,Nome, Cognome, Tipo_User, ProfileImage FROM users WHERE email= ? and password= ?");
        $login->bind_param("ss", $email, $password);
        $login->execute();
        $result = $login->get_result();
        return $result->fetch_all(MYSQLI_ASSOC);
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

}

?>
