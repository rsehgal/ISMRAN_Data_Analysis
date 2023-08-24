<script>
$(document).ready(function() {
	$("#success-alert").hide();
	//$("#success-newLogMessage").hide();
});
$('.updateButton').click(function() {
	//alert("updateButton click");
	$("#success-alert").fadeTo(2000, 500).slideUp(500, function(){
	$("#success-alert").slideUp(500);
});
});
/*$('form').click(function() {
	//alert("updateButton click");
	$("#success-newLogMessage").fadeTo(5000, 500).slideUp(5000, function(){
	$("#success-newLogMessage").slideUp(5000);
});
});*/

$('.updateButton').click(function (event) {
//$('#raman').click(function (event) {
                    //alert("updateButton click");
                    //event.preventDefault();
                    var formData = {
                      name: $("#name_"+$(this).attr("id")).val(),
                      msg: $("#msg_"+$(this).attr("id")).val(),
                      neartemp: $("#neartemp_"+$(this).attr("id")).val(),
                      fartemp: $("#fartemp_"+$(this).attr("id")).val(),
                      ambtemp: $("#ambtemp_"+$(this).attr("id")).val(),
                      ambpressure: $("#ambpressure_"+$(this).attr("id")).val(),
                      ambhumidity: $("#ambhumidity_"+$(this).attr("id")).val(),
                      id: $(this).attr("id"),
                      update:1
                    };
                    console.log("----------------");
                    console.log(formData);
                    console.log("----------------");

                    $.ajax({
                      type: "POST",
                      url: "StoreFormData.php",
                      data: formData,
                      dataType: "json",
                      encode: true,
		      success: function (response) {
    			    //$('p').append('status: ' + status + ', data: ' + data);
				alert("Response from StoreFormData : "+response);
    		      }

                    });/*.done(function (data) {
			alert(data);
                      console.log(data);
                    });*/

                    $('#newMessage').hide();
                    $('#loggedMessages').show();
                    //$('#loggedMessages').load("GetLoggedMessages.php");
                  });

</script>

<?php
include "helpers.php";

//$servername = "127.0.0.1";
$servername = "10.44.11.130";
//$servername = "localhost";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";

$searchStoreDate=$_POST['hiddenStoreDate'];
$hiddenSearchDate=$_POST['hiddenSearchDate'];
/*$day=$_POST['day'];
$month=$_POST['month'];
$year=$_POST['year'];

$queryDate=$day.$month.$year;
echo "<center>";
echo $queryDate."<br/><br/>";
echo "</center>";*/

$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="";
if($hiddenSearchDate=="DEF")
$sqlQuery="SELECT * from elog order by ts DESC";
else
$sqlQuery="SELECT * from elog where ts like '%$hiddenSearchDate%' order by ts DESC";
//$sqlQuery="SELECT * from elog order by logid DESC";
$results=$conn->query($sqlQuery);

//echo "<center><a href='elog.php'> <b><font color='red'>Enter a new log message</font></b></center></a>";
//echo "<br/>";
echo '<div class="alert alert-success" id="success-alert">
  <button type="button" class="close" data-dismiss="alert">x</button>
  <strong>Data updated !! </strong> 
</div>';
/*echo '<div class="alert alert-success" id="success-newLogMessage">
  <button type="button" class="close" data-dismiss="alert">x</button>
  <strong>Log Entry saved successfully !! </strong> 
</div>';
*/

//echo "<center>Searched For : $searchFor</center>";

echo "<center><table border='1' class='table table-hover table-condensed table-bordered table-dark'>";
//echo "<tr bgcolor='yellow'><th>Log Message </th><th> Near<br/> Temperature </th> <th>Far <br/> Temperature </th> <th>Ambient <br/> Temperature </th> <th>Ambient <br/> Pressure</th> <th>Ambient <br/> Humidity</th> <th>Date Time</th> <th>Reported By</th> <th></th>";
echo "<tr class='warning'><th>Log Message </th><th> Near (<sup>o</sup>C)<br/> Temperature <br/></th> <th>Far (<sup>o</sup>C)<br/> Temperature </th> <th>Ambient(<sup>o</sup>C) <br/> Temperature </th> <th>Ambient(mB) <br/> Pressure</th> <th>Ambient(%) <br/> Humidity</th> <th>Date Time</th> <th>Reported By</th> <th></th>";
echo "</tr>";
if($results->num_rows > 0){
	
	while($row=$results->fetch_assoc()){
		$id=$row['logid'];
		echo "<tr class='success'>";
		echo "<td><textarea id='msg_$id' class='form-control' name='msg_$id' rows='4' cols='50' >".$row['message']."</textarea></td>"; 
		echo "<td><input type='text' class='btn form-control' id='neartemp_$id' name='neartemp_$id' size=5      value='".$row['neartemp']."'/></td>"; 
		echo "<td><input type='text' class='btn form-control' id='fartemp_$id' name='fartemp_$id'  size=5       value='".$row['fartemp']."'/></td>"; 
		echo "<td><input type='text' class='btn form-control' id='ambtemp_$id' name='ambtemp_$id'  size=5       value='".$row['ambtemp']."'/></td>"; 
		echo "<td><input type='text' class='btn form-control' id='ambpressure_$id' name='ambpressure_$id' size=5  value='".$row['ambpressure']."'/></td>"; 
		echo "<td><input type='text' class='btn form-control' id='ambhumidity_$id' name='ambhumidity_$id' size=5 value='".$row['ambhumidity']."'/></td>"; 
		echo "<td><input type='text' class='btn form-control' id='datetime_$id' name='datetime_$id' size=10 value='".$row['ts']."'/></td>";
		echo "<td><input type='text' class='btn form-control' id='name_$id' name='name_$id' size=10 value='".$row['name']."'/></td>";
		echo "<td><input type='button' class='updateButton btn-primary' id=$id name=$id value='Update' /></td>";
		echo "</tr>";
		
	}
	 
}else{
	echo "0 results";
}
echo "</table></center>";
echo "</body></html>";
$conn->close();

?>
