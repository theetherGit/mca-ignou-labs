package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;

/**
 * Q12: checks the credentials posted by login.jsp and starts a session.
 * Assumption: one fixed admin account is enough for the lab. A real system
 * would look the user up in a Users table and compare a password hash.
 */
@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private static final String USER = "admin";
    private static final String PASSWORD = "ignou123";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.sendRedirect("login.jsp");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String user = request.getParameter("username");
        String pass = request.getParameter("password");

        if (USER.equals(user) && PASSWORD.equals(pass)) {
            HttpSession old = request.getSession(false);
            if (old != null) old.invalidate();          // fresh id on login (session fixation guard)
            HttpSession session = request.getSession(true);
            session.setAttribute("user", user);
            session.setMaxInactiveInterval(10 * 60);
            response.sendRedirect("students");
        } else {
            response.sendRedirect("login.jsp?error=" + java.net.URLEncoder.encode("Invalid username or password", "UTF-8"));
        }
    }
}
