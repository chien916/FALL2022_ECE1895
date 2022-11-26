let router = require("express").Router();
let check = require("express-validator").check;
let register = require("../../config/jwt").register;
let login = require("../../config/jwt").login;
router.post("/register", [
	check("username", "username_empty").notEmpty(),
	check("email", "email_empty").notEmpty(),
	check("email", "email_bad_format").isEmail(),
	check("password", "password_empty").notEmpty()
],register);
router.post("/login", [
	check("email", "email_empty").notEmpty(),
	check("email", "email_bad_format").isEmail(),
	check("password", "password_empty").notEmpty()
],login);
module.exports = router;