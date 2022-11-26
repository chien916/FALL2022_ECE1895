let closeMessage= document.getElementById("close-message");
let responseMessage = document.getElementById("response-message");
if(window.location.search){
	let typeOfError = window.location.search.split("=")[1];
	if(window.location.search.split("=")[0].substr(1)==="error"){
		responseMessage.classList.add("bg-danger");
	}else{
		responseMessage.classList.remove("bg-success");
	}
	responseMessage.classList.remove("hidden");
	let errorTextToDisplay = "未定义错误/Undefined Error";
	switch (typeOfError){
		case "error=null":
			errorTextToDisplay = "异常被成功处理但是操作无法继续进行/Caught An Error";
			break;
		case "username_empty":
			errorTextToDisplay = "没有向我们提供用户名/No Username Provided";
			break;
		case "email_empty":
			errorTextToDisplay = "没有向我们提供电子邮箱/No Email Provided";
			break;
		case"email_bad_format":
			errorTextToDisplay = "提供的电子邮箱不可用/Invalid Email Provided";
			break;
		case"password_empty":
			errorTextToDisplay = "没有向我们提供密码/No Password Provided";
			break;
		case"password_different":
			errorTextToDisplay = "提供的两组密码不相同/Passwords Do Not Match";
			break;
		case"account_existed":
			errorTextToDisplay = "提供的用户名已经被他人使用/Username Already Exists";
			break;
		case"account_not_found":
			errorTextToDisplay = "提供的用户名没有在系统中注册/Account Not Found";
			break;
		case"password_not_correct":
			errorTextToDisplay = "提供的密码不正确/Incorrect Password Provided";
			break;
	}
	responseMessage.querySelector("p").innerText = errorTextToDisplay;
}
WEFefgwerterfgrgEGf
closeMessage.addEventListener("click",()=>{
	responseMessage.classList.add("hidden");
});