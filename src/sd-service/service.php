<?
 include_once('database.php');
  $db = new database();

  public getNewTrash(){
      $db->throw_trash($_POST["type"]),$_POST["weight"]);
  }

 ?>