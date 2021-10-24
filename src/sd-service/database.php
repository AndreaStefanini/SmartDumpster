<?php 
class database {
    
    public $connection;

    public function __construct(){
        $this->connection = new mysqli('localhost', 'root', '', 'bopleve');
        if($this->connection->connect_error){
            die("An error occurred during the connection to the database, please retry". $this->connection->connect_error);
        }
    }
    public function add_user($nome, $cognome, $email, $userpassword, $data_nascita, $usertype, $profileimage){
       $insertquery=$this->connection->prepare("INSERT INTO users(Nome,Cognome,email,password,Data_Nascita,Tipo_User, ProfileImage) VALUES(?,?,?,?,?,?,?)");
       $insertquery->bind_param('sssssss',$nome,$cognome,$email,$userpassword,$data_nascita,$usertype,$profileimage);
       $insertquery->execute();

    }
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
    }

}

?>
