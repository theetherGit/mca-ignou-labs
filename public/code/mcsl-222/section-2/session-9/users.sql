-- Session 9, Q37: what Hibernate generates for the User entity (ddl-auto=update).
-- Run by hand only if you keep ddl-auto=none.
CREATE TABLE users (
  id       BIGINT       NOT NULL AUTO_INCREMENT,
  username VARCHAR(50)  NOT NULL,
  password VARCHAR(100) NOT NULL,   -- BCrypt hash, always 60 chars
  enabled  BIT          NOT NULL,
  PRIMARY KEY (id),
  UNIQUE KEY uk_users_username (username)
) ENGINE=InnoDB;
