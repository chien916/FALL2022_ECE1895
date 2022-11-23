let redis = require("redis");
let dotenv = require("dotenv");
dotenv.config();
let port = process.env.REDIS_PORT;
let host = process.env.REDIS_HOST || "localhost";
let redisClient = redis.createClient({host: host, port: port});
redisClient.on("error", (err) => {
	console.log(err);
	process.exit(1);
})
redisClient.on("connect", () => {
	console.log("￥成功：redis已连接");
})

module.exports = redisClient;