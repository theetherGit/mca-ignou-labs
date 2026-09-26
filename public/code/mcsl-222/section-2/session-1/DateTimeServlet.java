package ignou;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Date;

/** Q1: current date, time and timestamp. URL: /datetime */
@WebServlet("/datetime")
public class DateTimeServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        long millis = System.currentTimeMillis();
        LocalDateTime now = LocalDateTime.now();
        DateTimeFormatter dateFmt = DateTimeFormatter.ofPattern("dd-MM-yyyy");
        DateTimeFormatter timeFmt = DateTimeFormatter.ofPattern("HH:mm:ss");

        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html><html><head><title>Date and Time</title></head><body>");
            out.println("<h2>Current Date and Time</h2>");
            out.println("<p>Date: " + now.format(dateFmt) + "</p>");
            out.println("<p>Time: " + now.format(timeFmt) + "</p>");
            out.println("<p>Full (java.util.Date): " + new Date(millis) + "</p>");
            out.println("<p>Timestamp (milliseconds since 1 Jan 1970 UTC): " + millis + "</p>");
            out.println("<p>SQL Timestamp: " + new Timestamp(millis) + "</p>");
            out.println("</body></html>");
        }
    }
}
