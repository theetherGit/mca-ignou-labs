package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

/**
 * Q4: session management with HttpSession plus a cookie that survives the session.
 * URL: /session          shows counters and session details
 * URL: /session?action=logout  invalidates the session and deletes the cookie
 */
@WebServlet("/session")
public class SessionTrackingServlet extends HttpServlet {

    private static final String NAME_COOKIE = "visitorName";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        if ("logout".equals(request.getParameter("action"))) {
            HttpSession old = request.getSession(false);
            if (old != null) old.invalidate();
            Cookie gone = new Cookie(NAME_COOKIE, "");
            gone.setMaxAge(0);                       // max age 0 tells the browser to delete it
            gone.setPath(request.getContextPath());
            response.addCookie(gone);
            response.sendRedirect(request.getContextPath() + "/session");
            return;
        }

        HttpSession session = request.getSession();  // creates one on the first visit
        Integer visits = (Integer) session.getAttribute("visits");
        visits = visits == null ? 1 : visits + 1;
        session.setAttribute("visits", visits);

        String name = readCookie(request, NAME_COOKIE);

        response.setContentType("text/html;charset=UTF-8");
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html><html><head><title>Session Tracking</title></head><body>");
            out.println("<h2>Welcome " + (name == null ? "guest" : esc(name)) + "</h2>");
            out.println("<table border='1' cellpadding='4'>");
            out.println("<tr><th align='left'>Session ID</th><td>" + session.getId() + "</td></tr>");
            out.println("<tr><th align='left'>New session?</th><td>" + session.isNew() + "</td></tr>");
            out.println("<tr><th align='left'>Created</th><td>" + new Date(session.getCreationTime()) + "</td></tr>");
            out.println("<tr><th align='left'>Last accessed</th><td>" + new Date(session.getLastAccessedTime()) + "</td></tr>");
            out.println("<tr><th align='left'>Timeout (s)</th><td>" + session.getMaxInactiveInterval() + "</td></tr>");
            out.println("<tr><th align='left'>Visits in this session</th><td>" + visits + "</td></tr>");
            out.println("<tr><th align='left'>Session id came from cookie?</th><td>"
                    + request.isRequestedSessionIdFromCookie() + "</td></tr>");
            out.println("<tr><th align='left'>Session id came from URL?</th><td>"
                    + request.isRequestedSessionIdFromURL() + "</td></tr>");
            out.println("<tr><th align='left'>visitorName cookie</th><td>" + esc(name) + "</td></tr>");
            out.println("</table>");

            out.println("<form method='post'><p>Your name: <input name='name' required> "
                    + "<button type='submit'>Remember me (cookie, 7 days)</button></p></form>");
            // encodeURL appends ;jsessionid=... only when the browser refused the session cookie
            out.println("<p><a href='" + response.encodeURL("session") + "'>Reload (URL rewriting aware)</a> | "
                    + "<a href='session?action=logout'>Logout</a></p>");
            out.println("</body></html>");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        String name = request.getParameter("name");
        Cookie c = new Cookie(NAME_COOKIE, java.net.URLEncoder.encode(name, "UTF-8"));
        c.setMaxAge(7 * 24 * 60 * 60);
        c.setPath(request.getContextPath());
        c.setHttpOnly(true);
        response.addCookie(c);
        request.getSession().setAttribute("name", name);
        response.sendRedirect(request.getContextPath() + "/session");
    }

    private static String readCookie(HttpServletRequest request, String key) throws IOException {
        Cookie[] cookies = request.getCookies();
        if (cookies == null) return null;
        for (Cookie c : cookies) {
            if (key.equals(c.getName())) return java.net.URLDecoder.decode(c.getValue(), "UTF-8");
        }
        return null;
    }

    private static String esc(String s) {
        if (s == null) return "";
        return s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;").replace("\"", "&quot;");
    }
}
