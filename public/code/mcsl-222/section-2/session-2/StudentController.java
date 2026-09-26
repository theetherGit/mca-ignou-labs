package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.sql.SQLException;

/**
 * Q12: servlet controller; the JSPs under WEB-INF/views/ are the views.
 * Every request first checks the session; without a logged-in user it
 * redirects to login.jsp. Uses Student and StudentDao from Session 1, Q5.
 *   GET  /students                 list
 *   GET  /students?action=new      empty form
 *   GET  /students?action=edit&id= filled form
 *   POST /students  action=insert | update | delete
 */
@WebServlet("/students")
public class StudentController extends HttpServlet {

    private final StudentDao dao = new StudentDao();

    private boolean loggedIn(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession(false);
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.jsp?error=" + java.net.URLEncoder.encode("Please login first", "UTF-8"));
            return false;
        }
        return true;
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        if (!loggedIn(request, response)) return;
        String action = request.getParameter("action");
        try {
            if ("new".equals(action)) {
                request.setAttribute("student", new Student());
                request.setAttribute("editing", false);
                request.getRequestDispatcher("/WEB-INF/views/student-form.jsp").forward(request, response);
            } else if ("edit".equals(action)) {
                Student s = dao.findById(request.getParameter("id"));
                if (s == null) throw new ServletException("No student with enrolment number " + request.getParameter("id"));
                request.setAttribute("student", s);
                request.setAttribute("editing", true);
                request.getRequestDispatcher("/WEB-INF/views/student-form.jsp").forward(request, response);
            } else {
                request.setAttribute("students", dao.findAll());
                request.getRequestDispatcher("/WEB-INF/views/students.jsp").forward(request, response);
            }
        } catch (SQLException e) {
            // Wrapped and rethrown: web.xml routes it to error.jsp
            throw new ServletException("Database error: " + e.getMessage(), e);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        if (!loggedIn(request, response)) return;
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
        } catch (SQLException | NumberFormatException e) {
            msg = "Could not save: " + e.getMessage();  // duplicate key, bad number, and so on
        }
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
}
