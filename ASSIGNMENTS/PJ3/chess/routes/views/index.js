let {Router} = require("express");
let {getRegisterPage,getLoginPage} = require("../../controllers/views");
let router = Router();

router.get("/register", getRegisterPage);

router.get("/login", getLoginPage);

module.exports = router;