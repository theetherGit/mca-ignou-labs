package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;

/** Q3: shows the client's IP address and related request details. URL: /clientIp */
@WebServlet("/clientIp")
public class ClientIpServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        // Behind a proxy or load balancer the real client IP arrives in this header;
        // on a direct localhost connection it is null.
        String forwarded = request.getHeader("X-Forwarded-For");
        String clientIp = forwarded != null ? forwarded.split(",")[0].trim() : request.getRemoteAddr();

        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html><html><head><title>Client IP</title></head><body>");
            out.println("<h2>Client Information</h2>");
            out.println("<p>Client IP address: <b>" + clientIp + "</b></p>");
            out.println("<p>request.getRemoteAddr(): " + request.getRemoteAddr() + "</p>");
            out.println("<p>request.getRemoteHost(): " + request.getRemoteHost() + "</p>");
            out.println("<p>request.getRemotePort(): " + request.getRemotePort() + "</p>");
            out.println("<p>X-Forwarded-For header: " + forwarded + "</p>");
            out.println("<p>Server name and port: " + request.getServerName() + ":" + request.getServerPort() + "</p>");
            out.println("<p>User-Agent: " + request.getHeader("User-Agent") + "</p>");
            out.println("</body></html>");
        }
    }
}
