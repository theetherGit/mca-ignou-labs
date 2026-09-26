package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.List;

/**
 * Q5: CRUD front controller for the Student table.
 *   GET  /students               list
 *   GET  /students?action=new    empty form
 *   GET  /students?action=edit&id=E  form filled from the database
 *   POST /students  action=insert | update | delete
 */
@WebServlet("/students")
public class StudentServlet extends HttpServlet {

    private final StudentDao dao = new StudentDao();

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String action = request.getParameter("action");
        try {
            if ("new".equals(action)) {
                renderForm(response, new Student(), false);
            } else if ("edit".equals(action)) {
                Student s = dao.findById(request.getParameter("id"));
                if (s == null) {
                    response.sendError(HttpServletResponse.SC_NOT_FOUND, "No such student");
                    return;
                }
                renderForm(response, s, true);
            } else {
                renderList(response, dao.findAll(), request.getParameter("msg"));
            }
        } catch (SQLException e) {
            throw new ServletException("Database error: " + e.getMessage(), e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        String action = request.getParameter("action");
        String msg;
        try {
            switch (action == null ? "" : action) {
                case "insert" -> { dao.insert(fromRequest(request)); msg = "Student added"; }
                case "update" -> { dao.update(fromRequest(request)); msg = "Student updated"; }
                case "delete" -> { dao.delete(request.getParameter("id")); msg = "Student deleted"; }
                default -> msg = "Unknown action";
            }
        } catch (SQLException e) {
            msg = "Database error: " + e.getMessage();   // e.g. duplicate enrolment number
        }
        // Redirect after POST so a browser refresh does not repeat the insert.
        response.sendRedirect("students?msg=" + java.net.URLEncoder.encode(msg, "UTF-8"));
    }

    private static Student fromRequest(HttpServletRequest r) {
        Student s = new Student();
        s.setEnrolmentNo(r.getParameter("enrolmentNo").trim());
        s.setName(r.getParameter("name").trim());
        s.setDob(r.getParameter("dob"));
        s.setGender(r.getParameter("gender"));
        s.setEmail(r.getParameter("email").trim());
        s.setMobile(r.getParameter("mobile").trim());
        s.setAddress(r.getParameter("address"));
        s.setCity(r.getParameter("city"));
        s.setState(r.getParameter("state"));
        s.setPincode(r.getParameter("pincode"));
        s.setProgramme(r.getParameter("programme"));
        s.setSemester(Integer.parseInt(r.getParameter("semester")));
        s.setAdmissionYear(Integer.parseInt(r.getParameter("admissionYear")));
        s.setStudyCentre(r.getParameter("studyCentre"));
        String[] courses = r.getParameterValues("courses");
        s.setCourses(courses == null ? "" : String.join(",", courses));
        return s;
    }

    private void renderList(HttpServletResponse response, List<Student> list, String msg) throws IOException {
        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html><html><head><title>Students</title></head><body>");
            out.println("<h2>IGNOU Students (" + list.size() + ")</h2>");
            if (msg != null) out.println("<p style='color:green'>" + esc(msg) + "</p>");
            out.println("<p><a href='students?action=new'>Add new student</a></p>");
            out.println("<table border='1' cellpadding='4'><tr><th>Enrolment</th><th>Name</th><th>DOB</th>"
                    + "<th>Email</th><th>Mobile</th><th>Programme</th><th>Sem</th><th>Courses</th><th>Actions</th></tr>");
            for (Student s : list) {
                out.println("<tr><td>" + esc(s.getEnrolmentNo()) + "</td><td>" + esc(s.getName()) + "</td><td>"
                        + s.getDob() + "</td><td>" + esc(s.getEmail()) + "</td><td>" + esc(s.getMobile())
                        + "</td><td>" + esc(s.getProgramme()) + "</td><td>" + s.getSemester() + "</td><td>"
                        + esc(s.getCourses()) + "</td><td>"
                        + "<a href='students?action=edit&amp;id=" + esc(s.getEnrolmentNo()) + "'>Edit</a> "
                        + "<form method='post' style='display:inline' onsubmit='return confirm(\"Delete?\")'>"
                        + "<input type='hidden' name='action' value='delete'>"
                        + "<input type='hidden' name='id' value='" + esc(s.getEnrolmentNo()) + "'>"
                        + "<button type='submit'>Delete</button></form></td></tr>");
            }
            out.println("</table></body></html>");
        }
    }

    private void renderForm(HttpServletResponse response, Student s, boolean editing) throws IOException {
        response.setContentType("text/html;charset=UTF-8");
        String[] allCourses = {"MCS-218", "MCS-219", "MCS-220", "MCS-221", "MCSL-222", "MCSL-223"};
        String chosen = s.getCourses() == null ? "" : "," + s.getCourses() + ",";
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html><html><head><title>Student Form</title></head><body>");
            out.println("<h2>" + (editing ? "Edit" : "Add") + " Student</h2>");
            out.println("<form method='post' action='students'>");
            out.println("<input type='hidden' name='action' value='" + (editing ? "update" : "insert") + "'>");
            field(out, "Enrolment No", "enrolmentNo", s.getEnrolmentNo(), editing ? "readonly" : "required");
            field(out, "Name", "name", s.getName(), "required");
            out.println("<p><label>Date of Birth: <input type='date' name='dob' value='" + esc(s.getDob()) + "' required></label></p>");
            out.println("<p>Gender: <label><input type='radio' name='gender' value='M' " + ("F".equals(s.getGender()) || "O".equals(s.getGender()) ? "" : "checked") + "> Male</label> "
                    + "<label><input type='radio' name='gender' value='F' " + ("F".equals(s.getGender()) ? "checked" : "") + "> Female</label> "
                    + "<label><input type='radio' name='gender' value='O' " + ("O".equals(s.getGender()) ? "checked" : "") + "> Other</label></p>");
            field(out, "Email", "email", s.getEmail(), "type='email' required");
            field(out, "Mobile", "mobile", s.getMobile(), "pattern='[0-9]{10}' required");
            field(out, "Address", "address", s.getAddress(), "");
            field(out, "City", "city", s.getCity(), "");
            field(out, "State", "state", s.getState(), "");
            field(out, "Pincode", "pincode", s.getPincode(), "pattern='[0-9]{6}'");
            field(out, "Programme", "programme", s.getProgramme() == null ? "MCA" : s.getProgramme(), "required");
            field(out, "Semester", "semester", s.getSemester() == 0 ? "1" : String.valueOf(s.getSemester()), "type='number' min='1' max='6'");
            field(out, "Admission Year", "admissionYear", s.getAdmissionYear() == 0 ? "2024" : String.valueOf(s.getAdmissionYear()), "type='number' min='2000' max='2099'");
            field(out, "Study Centre", "studyCentre", s.getStudyCentre(), "");
            out.println("<p>Courses:");
            for (String c : allCourses) {
                out.println("<label><input type='checkbox' name='courses' value='" + c + "' "
                        + (chosen.contains("," + c + ",") ? "checked" : "") + "> " + c + "</label>");
            }
            out.println("</p><p><button type='submit'>Save</button> <a href='students'>Cancel</a></p>");
            out.println("</form></body></html>");
        }
    }

    private static void field(PrintWriter out, String label, String name, String value, String extra) {
        out.println("<p><label>" + label + ": <input name='" + name + "' value='" + esc(value) + "' " + extra + "></label></p>");
    }

    private static String esc(String s) {
        if (s == null) return "";
        return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
                .replace("\"", "&quot;").replace("'", "&#39;");
    }
}
