<html>
<title>
ISMRAN ELog
</title>
<head>
<!-- <script src='js/jquery.js'></script>-->
<script src='js/jquery.min.js'></script>
<script src='js/helpers.js'></script>
<link rel="stylesheet" href="css/bootstrap.min.css">
<script src="js/bootstrap.min.js"></script>
<style>
.form-control:focus {
    border-color: purple;
    box-shadow: 0px 1px 1px rgba(0, 0, 0, 0.075) inset, 0px 0px 8px rgba(255, 100, 255, 0.5);
}
</style>


<script>
$("form").submit(function (event) {
                    event.preventDefault();
		    //alert($('#hiddenSearchDate').val()+" : "+$('#hiddenSearchDate').val());
		    //alert("Date to be set for hidden text : "+$('#hiddenSearchDate').val());
		    if($('#tempPresHumi').is(":checked")){
			    var formData = {
			      name: $("#name").val(),
			      msg: $("#msg").val(),
			      neartemp:$('#neartemp').val(),
			      fartemp:$('#fartemp').val(),
			      ambtemp:$('#ambtemp').val(),
			      ambpressure:$('#ambpressure').val(),
			      ambhumidity:$('#ambhumidity').val(),
			      hiddenSearchDate:$('#hiddenSearchDate').val(),	
			      hiddenStoreDate:$('#hiddenStoreDate').val(),	
			    };
		    }else{
				//alert("Checkbox not selected....");
			    var formData = {
			      name: $("#name").val(),
			      msg: $("#msg").val(),
			      neartemp:0,
			      fartemp:0,
			      ambtemp:0,
			      ambpressure:0,
			      ambhumidity:0,
			      hiddenSearchDate:$('#hiddenSearchDate').val(),	
			      hiddenStoreDate:$('#hiddenStoreDate').val(),	
			    };
		    }

                    $.ajax({
                      type: "POST",
                      url: "StoreFormData.php",
                      data: formData,
                      dataType: "json",
                      encode: true,
                    }).done(function (data) {
                      console.log(data);
                    });

		    $('#newMessage').hide();
		    $('#loggedMessages').show();
		    $("#success-newLogMessage").fadeTo(2000, 500).slideUp(500, function(){
        	    $("#success-newLogMessage").slideUp(500);
		    });
		    //$('#loggedMessages').load("GetLoggedMessages.php");
		    var urlLink = "GetLoggedMessages.php";
		    $.ajax({url: urlLink,
				cache:false,
				type:'post',
				data:form_data,
				processData: false,
				contentType: false,
				success: function(result){
				$('#loggedMessages').html(result)
				//console.log(result);
				//$.getScript('js/custom.js');
				}}
                     );


                  });

$(document).ready(function(){
	$('#success-newLogMessage').hide();
	$('#tempPresHumi').click(function(){
	//alert("Temp Press Humi Clicked....");
	$('#temp-pres-humi').load("GetTempPresHumiTable.php");
	if($('#tempPresHumi').is(":checked")){
	$('#temp-pres-humi').show();
	}else{
	$('#temp-pres-humi').hide();
	}
	});

	$('#hideButton').click(function(){
		$('#newMessage').hide();
	});
});

</script>

<style>
.my-text-area:focus{
    border-color: red;
    box-shadow: 0px 1px 1px rgba(0, 0, 0, 0.075) inset, 0px 0px 8px rgba(255, 100, 255, 0.5);
}
</style>

</style>

</head>
<body>
<?php
/*echo '<div class="alert alert-success" id="success-newLogMessage">
  <button type="button" class="close" data-dismiss="alert">x</button>
  <strong>Log Entry saved successfully !! </strong> 
</div>';*/


echo "<form id='elog_form' method='POST' action='StoreFormData.php'>";
echo "<table class='table table-hover table-condensed table-bordered table-dark' border='0'>";
echo "<tr class='success'>";
echo "<td>";
//echo "<label for='name' id='label_name'>Your Name*</label>";
echo "Your Name*";
echo "</td>";

echo "<td>";
echo "<input type='text' name='name' id='name' placeholder='Your Name' required></input> <br/>";
echo "</td>";
echo "</tr>";

echo "<tr class='success'>";
echo "<td></td>";
echo "<td>";
echo "<textarea id='msg' name='msg' class='form-control' rows='4' placeholder='Enter your Log message' cols='50'></textarea>";
echo "</td>";
echo "</tr>";

echo "<tr class='success'></tr>";

echo "<tr class='success'>";
echo "<td>";
echo "Temperature <br> Pressure 
<input type='checkbox' id='tempPresHumi' name='tempPresHumi'/>
<br/> Humidity";
echo "</td>";
echo "<td>";
echo "<div id='temp-pres-humi' name='temp-pres-humi'></div>";
echo "</td>";
echo "</tr>";

echo "<tr class='success'>";
echo "<td></td>";
echo "<td>";
echo "<input type='submit' id='submit' class='btn-primary'></input>";
echo "&nbsp;&nbsp&nbsp&nbsp";
echo "<input type='button' id='hideButton' name='hideButton' value='Hide' class='btn-warning'></input>";
echo "</td>";
echo "</tr>";

echo "</table>";
echo "</form>";
?>
<body>
</html>
