let mysql = require("mysql2");
let dotenv = require("dotenv");
dotenv.config();
let db = mysql.createConnection({
	user: process.env.MYSQL_USER,
	host: process.env.MYSQL_HOST,
	password: process.env.MYSQL_PASSWORD,
	database: process.env.MYSQL_DATABASE,
	port: process.env.MYSQL_PORT
});
module.exports = db;