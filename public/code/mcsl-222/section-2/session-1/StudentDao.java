package ignou;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * Data access for the Student table (IGNOU database). Every query uses a
 * PreparedStatement, so values are sent separately from the SQL text and a
 * quote in a name cannot break or hijack the statement.
 */
public class StudentDao {

    private static final String URL =
            "jdbc:mysql://localhost:3306/IGNOU?useSSL=false&serverTimezone=Asia/Kolkata";
    private static final String USER = "ignou";
    private static final String PASSWORD = "ignou123";

    private static final String COLUMNS =
            "enrolment_no, name, dob, gender, email, mobile, address, city, state, pincode, "
          + "programme, semester, admission_year, study_centre, courses";

    // Connector/J 8 registers itself through META-INF/services; no Class.forName needed.
    private Connection connect() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }

    public List<Student> findAll() throws SQLException {
        List<Student> list = new ArrayList<>();
        String sql = "SELECT " + COLUMNS + " FROM Student ORDER BY enrolment_no";
        try (Connection con = connect();
             PreparedStatement ps = con.prepareStatement(sql);
             ResultSet rs = ps.executeQuery()) {
            while (rs.next()) list.add(map(rs));
        }
        return list;
    }

    public Student findById(String enrolmentNo) throws SQLException {
        String sql = "SELECT " + COLUMNS + " FROM Student WHERE enrolment_no = ?";
        try (Connection con = connect();
             PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, enrolmentNo);
            try (ResultSet rs = ps.executeQuery()) {
                return rs.next() ? map(rs) : null;
            }
        }
    }

    public int insert(Student s) throws SQLException {
        String sql = "INSERT INTO Student (" + COLUMNS + ") VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
        try (Connection con = connect();
             PreparedStatement ps = con.prepareStatement(sql)) {
            ps.setString(1, s.getEnrolmentNo());
            bind(ps, 2, s);
            return ps.executeUpdate();
        }
    }

    public int update(Student s) throws SQLException {
        String sql = "UPDATE Student SET name=?, dob=?, gender=?, email=?, mobile=?, address=?, "
                   + "city=?, state=?, pincode=?, programme=?, semester=?, admission_year=?, "
                   + "study_centre=?, courses=? WHERE enrolment_no=?";
        try (Connection con = connect();
             PreparedStatement ps = con.prepareStatement(sql)) {
            bind(ps, 1, s);
            ps.setString(15, s.getEnrolmentNo());
            return ps.executeUpdate();
        }
    }

    public int delete(String enrolmentNo) throws SQLException {
        try (Connection con = connect();
             PreparedStatement ps = con.prepareStatement("DELETE FROM Student WHERE enrolment_no = ?")) {
            ps.setString(1, enrolmentNo);
            return ps.executeUpdate();
        }
    }

    /** Binds the 14 non-key columns starting at parameter index {@code from}. */
    private static void bind(PreparedStatement ps, int from, Student s) throws SQLException {
        ps.setString(from, s.getName());
        ps.setString(from + 1, s.getDob());
        ps.setString(from + 2, s.getGender());
        ps.setString(from + 3, s.getEmail());
        ps.setString(from + 4, s.getMobile());
        ps.setString(from + 5, s.getAddress());
        ps.setString(from + 6, s.getCity());
        ps.setString(from + 7, s.getState());
        ps.setString(from + 8, s.getPincode());
        ps.setString(from + 9, s.getProgramme());
        ps.setInt(from + 10, s.getSemester());
        ps.setInt(from + 11, s.getAdmissionYear());
        ps.setString(from + 12, s.getStudyCentre());
        ps.setString(from + 13, s.getCourses());
    }

    private static Student map(ResultSet rs) throws SQLException {
        Student s = new Student();
        s.setEnrolmentNo(rs.getString("enrolment_no"));
        s.setName(rs.getString("name"));
        s.setDob(rs.getString("dob"));
        s.setGender(rs.getString("gender"));
        s.setEmail(rs.getString("email"));
        s.setMobile(rs.getString("mobile"));
        s.setAddress(rs.getString("address"));
        s.setCity(rs.getString("city"));
        s.setState(rs.getString("state"));
        s.setPincode(rs.getString("pincode"));
        s.setProgramme(rs.getString("programme"));
        s.setSemester(rs.getInt("semester"));
        s.setAdmissionYear(rs.getInt("admission_year"));
        s.setStudyCentre(rs.getString("study_centre"));
        s.setCourses(rs.getString("courses"));
        return s;
    }
}
