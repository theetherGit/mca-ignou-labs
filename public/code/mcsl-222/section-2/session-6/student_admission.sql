-- Student admission life cycle: one programme has many courses; a student
-- applies to one programme, picks courses, and moves PENDING -> APPROVED/REJECTED.
CREATE DATABASE IF NOT EXISTS student_admission;
USE student_admission;

CREATE TABLE programme (
  id    BIGINT AUTO_INCREMENT PRIMARY KEY,
  code  VARCHAR(10) NOT NULL UNIQUE,
  name  VARCHAR(80) NOT NULL
);

CREATE TABLE course (
  id           BIGINT AUTO_INCREMENT PRIMARY KEY,
  code         VARCHAR(10)  NOT NULL UNIQUE,
  title        VARCHAR(120) NOT NULL,
  programme_id BIGINT       NOT NULL,
  FOREIGN KEY (programme_id) REFERENCES programme(id)
);

CREATE TABLE student (
  id              BIGINT AUTO_INCREMENT PRIMARY KEY,
  enrolment_no    VARCHAR(12) UNIQUE,
  name            VARCHAR(80)  NOT NULL,
  email           VARCHAR(120) NOT NULL,
  mobile          VARCHAR(10)  NOT NULL,
  dob             DATE         NOT NULL,
  address         VARCHAR(255) NOT NULL,
  hostel_required BIT(1)       NOT NULL,
  programme_id    BIGINT       NOT NULL,
  status          ENUM('PENDING','APPROVED','REJECTED') NOT NULL DEFAULT 'PENDING',
  applied_on      DATE         NOT NULL,
  FOREIGN KEY (programme_id) REFERENCES programme(id)
);

-- join table with its own data (when the course was taken), so it is an entity
CREATE TABLE student_course (
  id          BIGINT AUTO_INCREMENT PRIMARY KEY,
  student_id  BIGINT NOT NULL,
  course_id   BIGINT NOT NULL,
  enrolled_on DATE   NOT NULL,
  UNIQUE (student_id, course_id),
  FOREIGN KEY (student_id) REFERENCES student(id) ON DELETE CASCADE,
  FOREIGN KEY (course_id)  REFERENCES course(id)
);

-- every status change of every application, oldest first
CREATE TABLE admission_status (
  id         BIGINT AUTO_INCREMENT PRIMARY KEY,
  student_id BIGINT NOT NULL,
  status     ENUM('PENDING','APPROVED','REJECTED') NOT NULL,
  changed_on DATETIME(6) NOT NULL,
  remark     VARCHAR(255),
  FOREIGN KEY (student_id) REFERENCES student(id) ON DELETE CASCADE
);

INSERT INTO programme (code, name) VALUES
  ('MCA', 'Master of Computer Applications'),
  ('BCA', 'Bachelor of Computer Applications');

INSERT INTO course (code, title, programme_id) VALUES
  ('MCS-218', 'Data Communication and Computer Networks', 1),
  ('MCS-219', 'Object Oriented Analysis and Design',      1),
  ('MCS-220', 'Web Technologies',                         1),
  ('MCS-221', 'Data Warehousing and Data Mining',         1),
  ('BCS-011', 'Computer Basics and PC Software',          2),
  ('BCS-012', 'Basic Mathematics',                        2);
