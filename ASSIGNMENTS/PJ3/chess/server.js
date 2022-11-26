//导入express模块
let express = require("express");
let app = express();
//导入dotenv模块
let dotenv = require("dotenv");
dotenv.config();
//导入mysql2模块
let db = require("./config/db");
//导入redis模块
let redisClient = require("./config/redis");
//导入path模块
let path = require("path");
//导入routes模块
let viewRoutes = require("./routes/views/index");
let apiRoutes = require("./routes/api/user");
//变量引入
let port = process.env.PORT ;
//导入cookie模块
let cookieParser = require("cookie-parser");


app.set("view engine","ejs");
app.set("views",path.join(__dirname,"views"));
app.use(express.static(path.join(__dirname,"public")));
app.use(express.json());
app.use(express.urlencoded({extended:true}))
app.use("/",viewRoutes);
app.use("/api",apiRoutes);
db.connect((err => {
	if (err) {
		console.log(err);
		process.exit(1);
	}
	console.log("￥成功：mysql已连接");
}))
app.get("/", (req, res) => {
	res.render("index.ejs");
})
app.listen(port, () => {
	console.log("￥成功：端口%s服务器已连接",port);
})
