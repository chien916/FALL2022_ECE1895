CREATE DATABASE online_chess;-- 创建新的数据库
USE online_chess;-- 使用此数据库
CREATE TABLE users
(
    id       INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) UNIQUE,
    email    VARCHAR(255) UNIQUE,
    password VARCHAR(255)
);
/*CREATE TABLE users_info
(
    user_id     INT,
    user_rank   ENUM ('beginner','intermediate','advanced','expert') DEFAULT 'beginner',
    user_points INT DEFAULT 1000,
    KEY userID (user_id),
    CONSTRAINT userID FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE
);
DROP TABLE users_info;*/
-- 创建一个procedure
DELIMITER $$
CREATE PROCEDURE createUser(
IN _username VARCHAR(255),
IN _email VARCHAR(255),
IN _password VARCHAR(255)
)
BEGIN
    DECLARE userId INT;
    INSERT INTO users(username,email,password) VALUES (_username,_email,_password);
/*    SELECT id INTO userId FROM users WHERE username=_username; -- 在users表里找出和输入的用户名对应的用户;
    INSERT INTO users_info(user_id) VALUE(user_id);*/
END $$

SELECT * from users;