CREATE DATABASE online_chess;
USE online_chess;
CREATE TABLE users
(
    id       INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) UNIQUE,
    email    VARCHAR(255) UNIQUE,
    password VARCHAR(255)
);

CREATE TABLE users_info(
    user_id INT,
    user_rank ENUM('beginner','intermediate','advanced','expert'),
    user_points INT DEFAULT 1000,
    KEY userID(user_id),
    CONSTRAINT userID FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE 
)