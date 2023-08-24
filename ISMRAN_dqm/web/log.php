<html>
<head>
<script src='js/jquery.min.js'></script>
<script src='js/helpers.js'></script>
<link rel="stylesheet" href="css/bootstrap.min.css">
<script src="js/bootstrap.min.js"></script>

<style>
.form-control:focus {
    border-color: red;
    box-shadow: 0px 1px 1px rgba(0, 0, 0, 0.075) inset, 0px 0px 8px rgba(255, 100, 255, 0.5);
}

.my-text-area:focus{
    border-color: red;
    box-shadow: 0px 1px 1px rgba(0, 0, 0, 0.075) inset, 0px 0px 8px rgba(255, 100, 255, 0.5);
}
</style>
<script>
$(document).ready(function(){
        $('#success-newLogMessage').hide();
	GetELogPage();
});

</script>

</head>
<?php

/*<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script> 
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>*/

echo "<br/><center><h2>ELog</h2><a href='' id='loadElog' name='loadElog'> <b><font color='red'>Enter a new log message</font></b></center></a>";
echo "<br/>";
echo "<center>";
echo "<div id='newMessage' name='newMessage'></div>";
echo '<div class="alert alert-success" id="success-newLogMessage">
  <button type="button" class="close" data-dismiss="alert">x</button>
  <strong>Log Entry saved successfully !! </strong> 
</div>';

echo "<div id='loggedMessages' name='loggedMessages'></div>";
echo "</center>";

?>
</html>
