-- src/main/resources/data.sql : seed rows, runs at every start-up.
-- Explicit ids + INSERT IGNORE so a second start-up does not duplicate rows (MySQL syntax).
INSERT IGNORE INTO programme (id, code, name, duration_years) VALUES
  (1, 'MCA', 'Master of Computer Applications', 2),
  (2, 'BCA', 'Bachelor of Computer Applications', 3);

INSERT IGNORE INTO course (id, code, title, credits, programme_id) VALUES
  (1, 'MCS-221', 'Data Warehousing and Data Mining', 4, 1),
  (2, 'MCSL-222', 'Web Technologies Lab', 2, 1),
  (3, 'BCS-011', 'Computer Basics and PC Software', 3, 2);

INSERT IGNORE INTO student (id, name, email, phone, city, date_of_birth) VALUES
  (1, 'Asha Verma', 'asha@example.com', '9876543210', 'Jaipur', '2002-03-14'),
  (2, 'Ravi Kumar', 'ravi@example.com', '9123456780', 'Patna', '2001-11-02');

INSERT IGNORE INTO admission (id, student_id, programme_id, status, applied_on) VALUES
  (1, 1, 1, 'APPLIED', '2026-07-01'),
  (2, 2, 1, 'APPROVED', '2026-06-20');
