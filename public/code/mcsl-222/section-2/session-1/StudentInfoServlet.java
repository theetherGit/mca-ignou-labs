package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;

/** Q2: reads the fields posted by student-form.html and echoes them. URL: /studentInfo */
@WebServlet("/studentInfo")
public class StudentInfoServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        show(request, response);
    }

    /** Also answer GET so the form can be switched to method="get" for comparison. */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        show(request, response);
    }

    private void show(HttpServletRequest request, HttpServletResponse response)
            throws IOException {
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");

        String[] courses = request.getParameterValues("courses");
        String courseList = courses == null ? "none" : String.join(", ", courses);

        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html><html><head><title>Student Details</title></head><body>");
            out.println("<h2>Submitted Student Information</h2>");
            out.println("<p>HTTP method: " + request.getMethod()
                    + ", protocol: " + request.getProtocol()
                    + ", content type: " + request.getContentType() + "</p>");
            out.println("<table border='1' cellpadding='4'>");
            row(out, "Enrolment No", request.getParameter("enrolmentNo"));
            row(out, "Name", request.getParameter("name"));
            row(out, "Date of Birth", request.getParameter("dob"));
            row(out, "Email", request.getParameter("email"));
            row(out, "Mobile", request.getParameter("mobile"));
            row(out, "Programme", request.getParameter("programme"));
            row(out, "Courses", courseList);
            out.println("</table>");
            out.println("<p><a href='student-form.html'>Back to form</a></p>");
            out.println("</body></html>");
        }
    }

    private static void row(PrintWriter out, String label, String value) {
        out.println("<tr><th align='left'>" + label + "</th><td>" + esc(value) + "</td></tr>");
    }

    /** Escape user input before writing it back into HTML (stops script injection). */
    private static String esc(String s) {
        if (s == null) return "";
        return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace("\"", "&quot;");
    }
}
