function GetTodaysDate(){
	var date = new Date();
	var day = date.getDate();
	var month = date.getMonth() + 1;
	var year = date.getFullYear();
	if (month < 10) month = '0' + month;
	if (day < 10) day = '0' + day;
	var today = year + '-' + month + '-' + day;
	return today;
}
function GetMonthName(monthNumber) {

	var months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
		return months[monthNumber - 1];

}

function GetDataOnClick(){
                                var date = new Date($('#searchText').val());
                                var day = date.getDate();
                                var month = date.getMonth() + 1;
                                var year = date.getFullYear();
                                var monthName = GetMonthName(month);

                                var form_data = new FormData();
                                form_data.append("day",day);
                                form_data.append("month",monthName);
                                form_data.append("year",year);

                                var urlLink = 'GetQueriedData.php';
                                $.ajax({url: urlLink,
                                                cache:false,
                                                type:'post',
                                                data:form_data,
                                                processData: false,
                                                contentType: false,
                                                success: function(result){
                                                $('#queriedData').html(result)
                                                //console.log(result);
                                                //$.getScript('js/custom.js');
                                                }}
                                      );
		$('#elogDiv').show();
		$('#elogDiv').load("log.php");
		//$('#loggedMessages').show();
		//$('#loggedMessages').load("GetLoggedMessages.php");
		//$('#loggedMessages').load("GetLoggedMessages.php?searchFor="+todaysDate);

                }

function GetELogPage(){
	//$('#newMessage').show();
	$('#loadElog').click(function(event){
		event.preventDefault();
		GetElogNewEntryForm();
		//alert("HiddenSearchData from GetELogPage : "+$('#hiddenSearchDate').val());
	        //alert("HiddenStoreData from GetELogPage : "+$('#hiddenStoreDate').val());
	});

	//var today = GetTodaysDate();
	//alert("Today : "+today );
	var searchDate = $('#searchText').val();
	//var hiddenSearchDate = $('#hiddenSearchDate').val();
	$('#loggedMessages').show();
	//$('#loggedMessages').load("GetLoggedMessages.php?searchFor="+today);
	var urlLink="GetLoggedMessages.php";
	var form_data = new FormData();
	//alert("HiddenSearchData from GetELogPage : "+$('#hiddenSearchDate').val());
	//alert("HiddenStoreData from GetELogPage : "+$('#hiddenStoreDate').val());
	form_data.append("hiddenStoreDate",$('#hiddenStoreDate').val());
	form_data.append("hiddenSearchDate",$('#hiddenSearchDate').val());
	//form_data.append("searchFor",today);

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
		}
	       }
	);
}

function GetElogNewEntryForm(){
	$('#newMessage').show();
	$('#newMessage').load("elog.php");
	//$('#loggedMessages').hide();

}

