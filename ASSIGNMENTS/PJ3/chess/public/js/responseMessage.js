let closeMessage= document.getElementById("close-message");
let responseMessage = document.getElementById("response-message");
if(window.location.search){
	if(window.location.search.split("=")[0].substr(1)==="error"){
		responseMessage.classList.add("bg-danger");
	}else{//"success"
		responseMessage.classList.add("bg-success");
	}
	let textToDisplay = "未定义行为/Undefined Behavior";
	switch (window.location.search.split("=")[1]){
		case "null":
			textToDisplay = "异常被成功处理但是操作无法继续进行/Caught An Error";
			break;
		case "username_empty":
			textToDisplay = "没有向我们提供用户名/No Username Provided";
			break;
		case "email_empty":
			textToDisplay = "没有向我们提供电子邮箱/No Email Provided";
			break;
		case"email_bad_format":
			textToDisplay = "提供的电子邮箱不可用/Invalid Email Provided";
			break;
		case"password_empty":
			textToDisplay = "没有向我们提供密码/No Password Provided";
			break;
		case"password_different":
			textToDisplay = "提供的两组密码不相同/Passwords Do Not Match";
			break;
		case"account_existed":
			textToDisplay = "提供的用户名已经被他人使用/Username Already Exists";
			break;
		case"account_not_found":
			textToDisplay = "提供的用户名没有在系统中注册/Account Not Found";
			break;
		case"password_not_correct":
			textToDisplay = "提供的密码不正确/Incorrect Password Provided";
			break;
	}
	responseMessage.querySelector("p").innerText = textToDisplay;
	responseMessage.classList.remove("hidden");

}

closeMessage.addEventListener("click",()=>{
	responseMessage.classList.add("hidden");
});