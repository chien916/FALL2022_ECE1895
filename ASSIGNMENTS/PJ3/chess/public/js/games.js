//get dom elements:
let gamesDivElement = document.getElementById("games");
//skipped rank filter
let gameList = document.getElementById("game-list");
let noGameMessage = document.getElementById("no-games-found");//?id correct?


let createRoomButton = document.getElementById("create-room");

let createRoomFormContainer = document.getElementById("create-room--form-container");
let createRoomForm = document.getElementById("create-room-form");
let roomId = document.getElementById("room-id");
//skipped game-time
let closeCreateRoomFormButton = document.getElementById("close-create-form");
let addPassword = document.getElementById("add-password");
let passwordInputGroup = document.getElementById("password-input-group");
let roomPasswordCreate = document.getElementById("room-password-create");



let joinRoomFormContainer = document.getElementById("join-room-form-container");
let joinRoomForm = document.getElementById("join-room-form");
let closeJoinRoomFormButton = document.getElementById("close-join-form");
let roomPasswordJoin = document.getElementById("room-password-join");

let user;
let gameId = null;
//skipped interval