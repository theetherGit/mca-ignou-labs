-- Q5: IGNOU database and Student table.
-- Run in MySQL Workbench or:  mysql -u root -p < schema.sql
-- One table holds basics, contact and enrolment details; the courses column is a
-- comma-separated list of course codes (assumption: a student registers for at most
-- a handful of courses, so a separate Course table is not needed for this lab).

CREATE DATABASE IF NOT EXISTS IGNOU CHARACTER SET utf8mb4;
USE IGNOU;

DROP TABLE IF EXISTS Student;

CREATE TABLE Student (
    -- basics
    enrolment_no    VARCHAR(12)  NOT NULL,
    name            VARCHAR(80)  NOT NULL,
    dob             DATE         NOT NULL,
    gender          ENUM('M', 'F', 'O') NOT NULL DEFAULT 'M',
    -- contact
    email           VARCHAR(120) NOT NULL,
    mobile          CHAR(10)     NOT NULL,
    address         VARCHAR(200),
    city            VARCHAR(60),
    state           VARCHAR(60),
    pincode         CHAR(6),
    -- enrolment details
    programme       VARCHAR(10)  NOT NULL,          -- MCA, BCA, MSc ...
    semester        TINYINT      NOT NULL DEFAULT 1,
    admission_year  YEAR         NOT NULL,
    study_centre    VARCHAR(10),                    -- e.g. 0710
    courses         VARCHAR(200),                   -- 'MCS-218,MCS-219,MCS-220'
    PRIMARY KEY (enrolment_no),
    UNIQUE KEY uq_student_email (email),
    CONSTRAINT chk_mobile CHECK (mobile REGEXP '^[0-9]{10}$'),
    CONSTRAINT chk_semester CHECK (semester BETWEEN 1 AND 6)
);

-- Application login used by the servlet: create once, grant only what the lab needs.
CREATE USER IF NOT EXISTS 'ignou'@'localhost' IDENTIFIED BY 'ignou123';
GRANT SELECT, INSERT, UPDATE, DELETE ON IGNOU.* TO 'ignou'@'localhost';

INSERT INTO Student (enrolment_no, name, dob, gender, email, mobile, address, city, state, pincode,
                     programme, semester, admission_year, study_centre, courses) VALUES
('2451001234', 'Asha Verma',  '2001-03-14', 'F', 'asha.verma@example.com',  '9876543210', '12 MG Road', 'Jaipur',  'Rajasthan', '302001', 'MCA', 2, 2024, '0710', 'MCS-218,MCS-219,MCS-220,MCS-221'),
('2451001235', 'Rahul Singh', '2000-11-02', 'M', 'rahul.singh@example.com', '9123456780', '4 Park Street', 'Kolkata', 'West Bengal', '700016', 'MCA', 2, 2024, '2801', 'MCS-218,MCS-220,MCS-221'),
('2451001236', 'Meera Nair',  '2002-07-25', 'F', 'meera.nair@example.com',  '9988776655', '9 Beach Road', 'Kochi',   'Kerala', '682001', 'MCA', 1, 2025, '1401', 'MCS-211,MCS-212,MCS-213');

SELECT enrolment_no, name, programme, semester, courses FROM Student;
