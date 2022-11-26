let jwt = require("jsonwebtoken");
let bcrypt = require("bcryptjs");
let db = require("./db");
let validationResult = require("express-validator").validationResult;
let dotenv = require("dotenv");
dotenv.config();
let register = (req, res) => {
	try {
		let errors = validationResult(req);
		if (errors.isEmpty() === false) {
			return res.redirect("/register?error=" + errors.array()[0].msg);
		}
		let {username, email, password, confirmPassword} = req.body;
		if (password !== confirmPassword) {
			return res.redirect("/register?error=password_different");
		}
		let query = `SELECT id FROM users WHERE username='${username}' OR email='${email}'`;
		db.query(query, async (err, result) => {
			if (err) throw err;
			if (result.length > 0)
				return res.redirect("/register?error=account_existed");
			let encryptedPassword = await bcrypt.hash(password, 10);
			query = `CALL createUser('${username}','${email}','${encryptedPassword}')`;
			db.query(query, err => {
				if (err) throw err;
/*				query = `SELECT id FROM users WHERE email='${email}'`;
				let userId = result[0];
				let payload = {
					id: userId,
					username: username,
					email: email
				};*/
/*				jwt.sign(payload, process.env.JWT_SECRET, (err, token) => {
					if (err) throw err;

					// //return res.redirect("/register?success=You have registered your user successfully");
					// res.json({user: payload, token});
				})*/
				return res.redirect("/register?success=register_success");
			})

		})
	} catch (err) {
		console.log(err);
		return res.red("/register?error=null");
		// res.status(500).json({error: err.message});
	}
};
let login = (req, res) => {
	try {
		let errors = validationResult(req);
		if (errors.isEmpty() === false) {
			return res.redirect("/login?error=" + errors.array()[0].msg);
		}
		let {email, password} = req.body;
		let query = `SELECT * FROM users WHERE email='${email}'`;
		db.query(query, async (err, result) => {
			if (err) throw err;
			if (result.length === 0) return res.redirect("/login?error=account_not_found");
			let user = result[0];
			let isMatch = await bcrypt.compare(password, user.password);
			// let isMatch = await password===user.password;
			if (isMatch === false) return res.redirect("/login?error=password_not_correct");
			//skipped user information query step
			let payload = {id: user.id, username: user.username, email: user.email};
/*			jwt.sign(payload, process.env.JWT_SECRET, (err, token) => {
				if(err) throw err;

			})*/
			return res.redirect("/login?success=login_success");
		})
	} catch (err) {
		console.log(err);
		res.redirect("/login?error=null");
	}
}

exports.register = register;
exports.login = login;
// module.exports = register;