<%-- Q9: src/main/webapp/student-list.jsp
     Reads the Student table of the IGNOU database (Session 1, Q5) with plain JDBC. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.sql.Connection, java.sql.DriverManager, java.sql.PreparedStatement, java.sql.ResultSet, java.sql.SQLException" %>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Student List (JDBC)</title></head>
<body>
    <h2>Students in IGNOU database</h2>
<%
    String url = "jdbc:mysql://localhost:3306/IGNOU?useSSL=false&serverTimezone=Asia/Kolkata";
    String sql = "SELECT enrolment_no, name, dob, email, mobile, programme, semester, courses "
               + "FROM Student ORDER BY enrolment_no";
    int count = 0;
    // try-with-resources closes ResultSet, PreparedStatement and Connection in reverse order
    try (Connection con = DriverManager.getConnection(url, "ignou", "ignou123");
         PreparedStatement ps = con.prepareStatement(sql);
         ResultSet rs = ps.executeQuery()) {
%>
    <table border="1" cellpadding="4">
        <tr><th>Enrolment</th><th>Name</th><th>DOB</th><th>Email</th><th>Mobile</th>
            <th>Programme</th><th>Semester</th><th>Courses</th></tr>
<%
        while (rs.next()) {
            count++;
%>
        <tr>
            <td><%= rs.getString("enrolment_no") %></td>
            <td><%= rs.getString("name") %></td>
            <td><%= rs.getDate("dob") %></td>
            <td><%= rs.getString("email") %></td>
            <td><%= rs.getString("mobile") %></td>
            <td><%= rs.getString("programme") %></td>
            <td><%= rs.getInt("semester") %></td>
            <td><%= rs.getString("courses") %></td>
        </tr>
<%
        }
%>
    </table>
    <p>Total students: <%= count %></p>
<%
    } catch (SQLException e) {
%>
    <p style="color:red">Database error: <%= e.getMessage() %></p>
    <p>Check that MySQL is running, schema.sql was executed and mysql-connector-j is in WEB-INF/lib.</p>
<%
    }
%>
</body>
</html>
