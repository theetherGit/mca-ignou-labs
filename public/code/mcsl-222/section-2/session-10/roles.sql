-- Session 10, Q42: tables Hibernate generates for Role and the User-Role link.
CREATE TABLE roles (
  id   BIGINT      NOT NULL AUTO_INCREMENT,
  name VARCHAR(30) NOT NULL,            -- 'ROLE_ADMIN', 'ROLE_STUDENT'
  PRIMARY KEY (id),
  UNIQUE KEY uk_roles_name (name)
) ENGINE=InnoDB;

-- join table for @ManyToMany: one row per (user, role) pair
CREATE TABLE user_roles (
  user_id BIGINT NOT NULL,
  role_id BIGINT NOT NULL,
  PRIMARY KEY (user_id, role_id),
  CONSTRAINT fk_user_roles_user FOREIGN KEY (user_id) REFERENCES users (id),
  CONSTRAINT fk_user_roles_role FOREIGN KEY (role_id) REFERENCES roles (id)
) ENGINE=InnoDB;

-- check after the first start-up
SELECT u.username, r.name
FROM users u JOIN user_roles ur ON ur.user_id = u.id JOIN roles r ON r.id = ur.role_id;
