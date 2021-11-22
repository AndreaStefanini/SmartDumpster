<?php
  include '../sd-service/database/database_entrance.php';

  $dataPoints1 = $db->get_TrashA();
  $dataPoints2 = $db->get_TrashB();
  $dataPoints3 = $db->get_TrashC();
  $stato = $db->get_state()[0]["disponibile"];
  $rifiuti = $db->get_trash()[0]["rifiuti"];
  $on="";
  $off="";
  if($stato==1){
    $on="<a  class=\"btngreen\">on</a>";
  }else if($stato==0){
    $off="<a  class=\"btnred\">off</a>";
  }
  $pesoTotale = $db->get_all_trash()[0]["peso"];
  $result = $db->get_all_gestore();
?>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" href="//fonts.googleapis.com/css?family=Open+Sans:300,400,600,700&amp;lang=en" />
  <meta name="viewport" content="device-width, initial-scale=1.0, user-scalable=no">
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/charts.css/dist/charts.min.css">
  <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto">

<title> SmartDumpster</title>
<style>
.trashred{
background-color: #f44336;
color: white;
padding: 10px;
border: 10px solid  #f53122;
border-radius: 10px;
}
.trashgreen{
background-color: #04AA6D;
color: white;
padding: 10px;
border: 10px solid  #04915e;
border-radius: 10px;
}
.trashorange{
background-color: #ff9800;
color: white;
padding: 10px;
border: 10px solid #d28006;
border-radius: 10px;
}

.wrapper2 {
  width: 200px;
  height: 200px;
  margin: 125px auto;
  position: relative;
}

.left {
  width: 100px;
  height: 200px;
  position: absolute;
  top: 0;
  left: 0;
  background:green;
  border-radius: 100px 0 0 100px;
  z-index: 1;
  opacity: 0;
  animation: fill 2s steps(1, end) 1;
  animation-fill-mode: forwards;
}

.right {
  width: 100px;
  height: 200px;
  position: absolute;
  top: 0;
  right: 0;
  background: green;
  border-radius: 0 100px 100px 0;
  z-index: 1;
  opacity: 1;
  animation: mask 2s steps(1, end) 1;
  animation-fill-mode: forwards;
}

.mask {
  width: 101px;
  height: 202px;
  position: absolute;
  top: -1px;
  right: -1px;
  background: #ededed;
  z-index: 10;
  transform-origin: 0 50%;
  animation: rotate 2s linear 1;
  animation-fill-mode: forwards;
}

.wrapper:after {
  content: "";
  position: absolute;
  width: 180px;
  height: 180px;
  border-radius: 50%;
  top: 9.75px;
  right: 9.75px;
  background: #ededed;
  z-index: 30;
}

@keyframes rotate {
  0%  {transform: rotate(0deg);}
  100%  {transform: rotate(<?php echo $gradi."deg";?>);}
}

@keyframes fill {
  0%  {opacity: 0;}
  50%, 100%  {opacity: 1;}
}

@keyframes mask {
  0%  {z-index: 10;}
  50%, 100%  {z-index: 30;}
}

.wrapper:hover .left,
.wrapper:hover .right,
.wrapper:hover .mask {
  animation-play-state: paused;
}



a,
a:visited {
  text-decoration: none;
  color: #FDA660;
}

a:focus,
a:hover {
  color: #F37107;
}


#grafico{
  border-top: 1px solid #1e1e1e;
  border-left: 1px solid #1e1e1e;
  border-right: 1px solid #1e1e1e;
  padding: 5px;
}
@import url('https://fonts.googleapis.com/css?family=Open+Sans&display=swap');
#MonthTrash{
  width: 80%;
  height: 600px;
  padding-bottom: 0px;
  padding-left:10%;
}

#spazio{
  margin-bottom: 30px;
}

    .title{text-align: center; font-size: 50px;font: Open Sans}
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
.ul1{
  background-color: #FAFFAD;
  border: 2px solid black;
  padding: 10px 10px 10px;
}
.li1{
  border: 1px solid black;
  padding: 5px 5px 5px;
  background-color: #FFC7AD;
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
      font-family: 'Roboto', serif;

    }
</style>

<script src="script.js">
</script>
<script src="https://www.gstatic.com/charts/loader.js">
</script>
<script>
window.onload = function () {
 
 var chart = new CanvasJS.Chart("chartContainer", {
   animationEnabled: true,
   theme: "light1",
   title:{
     text: "Andamento dei rifiuti"
   },
   legend:{
     cursor: "pointer",
     verticalAlign: "center",
     horizontalAlign: "right",
     itemclick: toggleDataSeries
   },
   data: [{
     type: "line",
     name: "kg of A type trash",
     indexLabel: "{y}",
     yValueFormatString: "#0.##",
     showInLegend: true,
     dataPoints: <?php echo json_encode($dataPoints1, JSON_NUMERIC_CHECK); ?>
   },{
     type: "line",
     name: "kg of B type trash",
     indexLabel: "{y}",
     yValueFormatString: "#0.##",
     showInLegend: true,
     dataPoints: <?php echo json_encode($dataPoints2, JSON_NUMERIC_CHECK); ?>
   },{
     type: "line",
     name: "kg of C type trash",
     indexLabel: "{y}",
     yValueFormatString: "#0.##",
     showInLegend: true,
     dataPoints: <?php echo json_encode($dataPoints3, JSON_NUMERIC_CHECK); ?>
   }]
 });
 chart.render();
  
 function toggleDataSeries(e){
   if (typeof(e.dataSeries.visible) === "undefined" || e.dataSeries.visible) {
     e.dataSeries.visible = false;
   }
   else{
     e.dataSeries.visible = true;
   }
   chart.render();
 }
  
 }
 </script>
</head>
<body>
<center><h1 class="title"> SmartDumpster </h1></center>
<center><h2 class="title2"> Admin Interface </h2></br></br></center>
<center><a  class="btn success" style="color:green;" href="on.php">Start Service</a>
  <a  class="btn danger" style="color:red;"  href="off.php">Stop Service</a></br></br>
</center>
<center></br></br><h2 class="title2">Stato del Servizio: </h2></br></center>
<center> <?php echo $on; echo $off;?></br></center>
<?php
//se il livello di trash non è zero allora il bottone di reset sarà disponibile, altrimenti no ovviamente
if ( true){
    echo "</br>";
 ?>
<center></br></br><h2 class="title2">Stato riempimento cestino: </h2></br></br></center>



<center><a class="btn warning" href="empty.php">Empty</a></br></br></center>

<center></br></br><h2 class="title2">INSERIMENTO RIFIUTO:</h2></br><h2 class="title2"> (extra)</h2></br></br></center>
<center>
<form action="record.php" method="post">
<p>Tipo: </p><input type="text" name="tipo"></br></br><!--
<select id="tipo" name="tipo" required>
  <option value="a" name="tipo" type="text">a</option>
  <option value="b" name="tipo" type="text">b</option>
  <option value="c" name="tipo" type="text">c</option>
</select>-->


<p>Peso: </p><input type="number" name="peso" max="100" min="1" required></br></br>
<input type="submit">
</form>
</center>


<?php } else{ }?>
<div>






 <center></br><h2 class="title2">Grafici</h2></center>


<div id="MonthTrash">
<div id="chartContainer" style="height: 370px; width: 100%;"></div>
<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
<center></br><h2 id="trash">Peso rifiuti totali buttati: <?php echo $pesoTotale;?>kg</h2></center>
</div>
</div>  
<?php
echo "<center><h2 class=\"title2\"> Record Depositi</h2></center></br>";
foreach ($result as $row):
    echo '<center><ul class="ul1">'.$row["data"].'</ul></br></center>';
    echo '<center><li class="li1">Peso: '.$row["peso"].'kg</li></br></center>';
    echo '<center><li class="li1">Tipologia: '.$row["tipologia"].'</li></br></center>';
endforeach;

?>

</body>
</html> 