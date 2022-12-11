let openChatButton = document.getElementById("open-chat");
let closeChatButton = document.getElementById("close-chat");
let chat = document.getElementById("chat");
let messages = document.getElementById("messages");
let chatForm = document.getElementById("chat-form");
let messageInput = document.getElementById("message-input");

let displayMessage = function (message) {
	messages.innerText +=
		<li>
			<span class="time">${message.created_at}</span>
			<p>
				<strong>${message.user}</strong>${message.text}
			</p>
		</li>
}

let handleSubmit = function (err) {
	err.preventDefault();
	let text = messageInput.value;
	let date = new Date();
	let message = {
		text: text,
		user: user.username,
		created_at: `${date.getFullYear()}.${date.getMonth() + 1}.${date.getDate() + 1}${date.getHours()}:${date.getMinutes()}:${date.getMilliseconds()} `
	};
	messageInput.value = "";
	displayMessage(message);
	Socket.emit("send-message", text, user.username);
}

openChatButton.addEventListener("click", function () {
	chat.classList.add("open");
})

closeChatButton.addEventListener("click",function ())