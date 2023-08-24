<html>
<head>
<script src='js/jquery.js'></script>
<script src='js/helpers.js'></script>
<style>
body {
  margin: 0;
  font-family: Arial, Helvetica, sans-serif;
}


.topnav {
  overflow: hidden;
  background-color: #333;
}

.topnav a {
  float: left;
  color: #f2f2f2;
  text-align: center;
  padding: 14px 16px;
  text-decoration: none;
  font-size: 17px;
}

.topnav a:hover {
  background-color: #ddd;
  color: black;
}

.topnav a.active {
  background-color: #04AA6D;
  color: white;
}
</style>

<script src='js/jquery.js'></script>
<script src='js/helpers.js'></script>
<script>
$(document).ready(function(){

$('#dataStatusDiv').load("ajaxView.php");

$(".links").click(function(){
$(".links").css("background-color","#333");
$(this).css("background-color","#04AA6D");
});

$("#ismranDataStataLink").click(function(event){
event.preventDefault();
$('#dataStatusDiv').show();
//$(this).css("background-color","#04AA6D");

$('#dataStatusDiv').load("ajaxView.php");
$('#elogDiv').show();
$('#elogDiv').load("log.php");
//$('#elogDiv').hide();
});
$("#elogLink").click(function(event){
	
	event.preventDefault();
	//alert("Settign value to DEF..");
	$('#hiddenSearchDate').attr('value','DEF');
	$('#hiddenStoreDate').attr('value',GetTodaysDate());
	//alert("sEtting search Text to : "+GetTodaysDate());
	//$('#searchText').show();
	//$('#searchText').attr('value',GetTodaysDate());
	//alert("Hidden Search Date value : "+$('#hiddenSearchDate').val());
	//alert("Hidden Store Date value : "+$('#hiddenStoreDate').val());
	$('#elogDiv').show();
	$('#elogDiv').load("log.php");
	$('#dataStatusDiv').hide();
});

});

</script>
</head>
<body>
<center><h1>ISMRAN</h1></center>
<div class="topnav">
  <a class="active links" href="ajaxView.php" id="ismranDataStataLink">ISMRAN Data Status</a>
  <a href="log.php" class="links" id="elogLink">ISMRAN ELog</a>
</div>

<div id="dataStatusDiv" name="dataStatusDiv"></div>
<div id="elogDiv" name="elogDiv"></div>
<input type="hidden" id="hiddenSearchDate" name="hiddenSearchDate" value="DEF" />
<input type="hidden" id="hiddenStoreDate" name="hiddenStoreDate" value="DEF" />
</body>
</html>
