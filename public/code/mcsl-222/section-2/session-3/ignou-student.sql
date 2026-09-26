-- Student table of the IGNOU database created in Session 1, Question 5.
-- If your Session 1 table used other column names, change the @Column names
-- in Student.java; hibernate.hbm2ddl.auto=update adds any column that is missing.
CREATE DATABASE IF NOT EXISTS ignou;
USE ignou;

CREATE TABLE IF NOT EXISTS student (
  id              BIGINT AUTO_INCREMENT PRIMARY KEY,
  enrolment_no    VARCHAR(12) UNIQUE,
  name            VARCHAR(80)  NOT NULL,
  email           VARCHAR(120) NOT NULL,
  mobile          VARCHAR(10)  NOT NULL,
  dob             DATE         NOT NULL,
  address         VARCHAR(255),
  programme       VARCHAR(10)  NOT NULL,
  courses         VARCHAR(255),
  hostel_required BIT(1)       NOT NULL DEFAULT 0
);

INSERT INTO student (enrolment_no, name, email, mobile, dob, address, programme, courses, hostel_required) VALUES
  ('2201234567', 'Asha Verma',  'asha@example.com',  '9876543210', '2003-04-12', 'Sector 4, Rohini, Delhi', 'MCA', 'MCS-218,MCS-220', 1),
  ('2201234568', 'Rahul Singh', 'rahul@example.com', '9123456780', '2002-11-30', 'Boring Road, Patna',      'MCA', 'MCS-219',         0);
