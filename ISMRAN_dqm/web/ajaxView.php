<!--header('Content-type: text/html');-->
<html>
<head>
<title>Ismran Data Status</title>
<script src='js/jquery.js'></script>
<script src='js/helpers.js'></script>
<script>
$(document).ready(function(){
	var today = GetTodaysDate();
	$('#searchText').attr('value',today);
	$('#hiddenSearchDate').attr('value',$('#searchText').val());
	$('#hiddenStoreDate').attr('value',$('#searchText').val());
	GetDataOnClick();

	$('#searchButton').click(function(){
		$('#hiddenSearchDate').attr('value',$('#searchText').val());
		$('#hiddenStoreDate').attr('value',$('#searchText').val());
        	GetDataOnClick();
        });
});
</script>
</head>
<body>

<?php

echo "<center><h2>Data Status</h2>";
echo "<center> <h3>The current file is shown in <font color='red'>Red Color</font></h3></center><br/>";
//$dateFromServer= date('d/m/Y');
//echo "<input type='date' name='searchText' id='searchText' value='$dateFromServer'> ";
echo "<input type='date' name='searchText' id='searchText' > ";
echo "<input type='button' name='searchButton' id='searchButton' value='Search'/>";
echo "</center><br/>";
echo "<div id='queriedData' name='queriedData'/>";

?>
</body>
</html>
