<?php
function Connect($servername,$username,$password,$dbname){

	// Create connection
	$conn = new mysqli($servername, $username, $password,$dbname);

	// Check connection
	if ($conn->connect_error) {
		die("Connection failed: " . $conn->connect_error);
	}
	//echo nl2br("Connected successfully\n");

	return $conn;
}
function GetSubStringFromTokenIndex($str,$tokenIndex){
        $tokenCounter=0;
        $token = strtok($str,"/");
        $outputStr="";
        while($token !== false){
                $tokenCounter++;
                $token = strtok("/");
                if($tokenCounter >= $tokenIndex){
                        $outputStr=$outputStr."/".$token;
                }
        }
        return $outputStr;
}

function GetSubStringFromDelimiter($str,$delim,$delimIndex){
	$parts = explode($delim, $str);

	$result = "";

	if (count($parts) >= $delimIndex+1) {
		for($i=$delimIndex ; $i<count($parts);$i++)
		if($i==$delimIndex)
			$result.=$parts[$i];
		else
			$result.=$delim.$parts[$i];
			
	}
	return $result;
}
function GetSubStringUptoLastDelimiter($str,$delim){
	$parts = explode($delim, $str);

	$result = "";

	if (count($parts) >= $delimIndex+1) {
		for($i=0 ; $i<count($parts)-2;$i++)
		if($i==$delimIndex)
			$result.=$parts[$i];
		else
			$result.=$delim.$parts[$i];
			
	}
	return $result;
}
function GetFileNameWithoutExtension($str){
	$parts = explode('.',$str);
	return $parts[0];
}
function GetFileExtension($str){
	$parts = explode('.',$str);
	return $parts[count($parts)-1];
}
function GetFileExtensionWithDelim($str,$delim){
	$parts = explode($delim,$str);
	return $parts[count($parts)-1];
}
?>
