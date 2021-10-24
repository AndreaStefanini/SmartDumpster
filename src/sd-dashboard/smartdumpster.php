<!DOCTYPE html>
<html>
<head><meta name="viewport" content="device-width, initial-scale=1.0, user-scalable=no">
<title> SmartDumpster</title>
<style>
    .title{text-align: center; font-size: 50px;}
    .title2{text-align: center; font-size: 25px;}
    .trash {display: inline-block;
    font-size: 20px;
  background-color:orange;
  color: white;
padding: 5px 5px 5px;
}
    .btn {
  border: 2px solid black;
  background-color: white;
  color: black;
  padding: 14px 28px;
  font-size: 16px;
  cursor: pointer;
}
.btngreen{
  color: white;
    padding: 14px 28px;
  background-color: #04AA6D;
}
.btnred{
  color: white;
    padding: 14px 28px;
  background-color: #f44336;
}
ul{
  background-color: white;
  border: 2px solid black;
  padding: 10px 10px 10px;
}
li{
  border: 1px solid black;
  padding: 5px 5px 5px;
  background-color: #f7f7f7;
}

/* Green */
.success {
  border-color: #04AA6D;
  color: green;
}

.success:hover {
  background-color: #04AA6D;
  color: white;
}

/* Blue */
.info {
  border-color: #2196F3;
  color: dodgerblue;
}

.info:hover {
  background: #2196F3;
  color: white;
}

/* Orange */
.warning {
  border-color: #ff9800;
  color: orange;
}

.warning:hover {
  background: #ff9800;
  color: white;
}

/* Red */
.danger {
  border-color: #f44336;
  color: red;
}

.danger:hover {
  background: #f44336;
  color: white;
}

/* Gray */
.default {
  border-color: #ededed;
  color: black;
}

.default:hover {
  background: #e7e7e7;
}
    body{
      background-color: #ededed;
    }
</style>
<script src="script.js">
</script>
<script src="https://www.gstatic.com/charts/loader.js">
</script>
</head>
<body>
  <?php
  $mysqli = new mysqli("localhost", "root", "", "smartdumpster");
  $query = "SELECT * FROM gestore";
  $result = $mysqli->query($query) or die(mysqli_error($con));
  $query_stato = "SELECT * FROM stato";
  $result_stato = $mysqli->query($query_stato) or die(mysqli_error($con));
  while ($row_stato = mysqli_fetch_array($result_stato)) {
   $stato=$row_stato["disponibile"];
   $rifiuti=$row_stato["rifiuti"];
  }
  $on="";
  $off="";
  if($stato==1){
$on="<a  class=\"btngreen\">on</a>";
}else if($stato==0){
  $off="<a  class=\"btnred\">off</a>";
}
  ?>
<center><h1 class="title"> SmartDumpster </h1></center>
<center><h2 class="title2"> Admin Interface </h2></br></br></center>
<center><a  class="btn success" href="on.php">Start Service</a>
  <a  class="btn danger" href="off.php">Stop Service</a></br></br>
</center>
<center></br></br><h2 class="title2">Stato del Servizio: </h2></br></center>
<center> <?php echo $on; echo $off;?></br></center>
<?php
//se il livello di trash non è zero allora il bottone di reset sarà disponibile, altrimenti no ovviamente
if ( true){
    echo "</br>";
 ?>
<center></br></br><h2 class="title2">Stato riempimento cestino: </h2></br></br></center>
<center><a class="btn warning" href="/empty">Empty</a></br></br></center>
<center><p class="trash" id="trash">Trash level:<?php echo $rifiuti;?>kg</p></br></br></center>
<?php } else{ }?>
<div>
   <center></br><h2 class="title2">Grafici</h2></center>
    <center><p>Quantita di rifiuti gettata negli ultimi x giorni:</p></center>
</div>
<div id="MonthTrash"></div>
<?php
while ($row = mysqli_fetch_array($result)) {
    echo '<center><ul>'.$row["data"].'</ul></br></center>';
    echo '<center><li>Peso: '.$row["peso"].'kg</li></br></center>';
    echo '<center><li>Tipologia: '.$row["tipologia"].'</li></br></center>';

}
?>

</body>
</html>
