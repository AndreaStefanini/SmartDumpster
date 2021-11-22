<?php

$mysqli = new mysqli("localhost", "root", "", "smartdumpster");





















$date = date("Y/m/d");
$date=date("Y-m-d",strtotime($date));

$type=$_POST["tipo"];
$weight=$_POST["peso"];



$message = "wrong answer";
echo "<script type='text/javascript'>alert('$message');</script>";

  $values= "VALUES ('".$weight."','".$type."','".$date."')";
  $query = "INSERT INTO gestore (peso,tipologia,data)".$values;
  echo $query;
echo "tipo: ".$type."</br>";
echo "peso: ".$weight."</br>";
echo "data: ".$date."</br>";
// lancio la query
$result = $mysqli->query($query);

echo "result:".$result;
header("Location:smartdumpster.php");


?>
