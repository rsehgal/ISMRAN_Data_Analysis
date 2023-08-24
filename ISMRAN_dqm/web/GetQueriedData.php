<?php
include "helpers.php";

echo  "<script>
        $(document).ready(function(){
                $('.popper').click(function (event) {
                        event.preventDefault();
                        var href = $(this).attr('href');
                        window.open(href, 'popup', 'directories=no,titlebar=no,toolbar=no,location=no,status=no,menubar=no,height=400,width=600');
                });
        });
        </script>";


//$servername = "127.0.0.1";
$servername = "10.44.11.130";
$username = "ismran";
$password = "ismran123";
$dbname="ismran_db";
$day=$_POST['day'];
$day=sprintf("%02d", $day);
$month=$_POST['month'];
$year=$_POST['year'];

$queryDate=$day.$month.$year;
echo "<center>";
echo $queryDate."<br/><br/>";
echo "</center>";

$conn=Connect($servername,$username,$password,$dbname);
$sqlQuery="SELECT * from ismran_files where fileName LIKE '%".$queryDate."%'";
$results=$conn->query($sqlQuery);

echo "<center><table border='1'>";
echo "<tr bgcolor='yellow'><th>Source Path </th><th>Destination Path</th> <th>File Name</th> <th>Near <br/> Rates</th><th>Far <br/> Rates</th><th>Coinc <br/> Rates</th> <th>Calibration File </th>";
//echo "<th>File Integrity</th>;
echo "</tr>";
if($results->num_rows > 0){
	
	while($row=$results->fetch_assoc()){
		if($row['integrityCheck']==1)
			echo "<tr bgcolor='#56de91'>";
		else
			echo "<tr>";
		if($row['fileExistInSourceDir']==0)
		echo "<td bgcolor='#ec7063'>".$row["filePath"]."</td>";
		else
		echo "<td>".$row["filePath"]."</td>";
		echo "<td>".$row['remoteFilePath']."</td>";
		$hrefPath=GetSubStringFromTokenIndex($row['remoteFilePath'],2);
		if($row["currenFile"]==1 && $row["currenFile"])
                echo "<td class='blink'><b><font color='red'>".$row['fileName']."</font></b></td>";
                else
		echo "<td><a href='.".$hrefPath."/".$row['fileName']."'>".$row['fileName']."</a></td>";
		//echo "<td><a href='".$row['remoteFilePath']."/".$row['fileName']."'>".$row['fileName']."</a></td>";
		$substring = GetSubStringFromDelimiter($row['fileName'],'_',2);
		$substring = GetFileNameWithoutExtension($substring);
		$substring.='.png';
		//$hrefPathForPng=GetSubStringUptoLastDelimiter($row['remoteFilePath'],'/')."/image";
		$hrefPathForPng=GetSubStringUptoLastDelimiter($hrefPath,'/')."/images";
		echo "<td><a href='."."$hrefPathForPng/NearRate_$substring' class='popper'>Plot</a></td>";
		echo "<td><a href='."."$hrefPathForPng/FarRate_$substring' class='popper'>Plot</a></td>";
		echo "<td><a href='."."$hrefPathForPng/CoincRate_$substring' class='popper'>Plot</a></td>";
		echo "<td>".$row["calibrationTag"]."</td>";
		echo "</tr>";
	}
	 
}else{
	echo "0 results";
}
echo "</table></center>";
echo "</body></html>";
$conn->close();

?>
