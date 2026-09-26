<%-- Q6: src/main/webapp/datetime.jsp
     Prints date, time and timestamp; the page reloads itself every 5 seconds. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.Date, java.text.SimpleDateFormat, java.sql.Timestamp" %>
<%
    // HTTP Refresh header: the browser requests this URL again after 5 seconds.
    response.setHeader("Refresh", "5");
    long millis = System.currentTimeMillis();
    Date now = new Date(millis);
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <%-- Second way: meta refresh. Either one alone is enough. --%>
    <meta http-equiv="refresh" content="5">
    <title>Date and Time (auto refresh)</title>
</head>
<body>
    <h2>Current Date and Time</h2>
    <p>Date: <%= new SimpleDateFormat("dd-MM-yyyy").format(now) %></p>
    <p>Time: <%= new SimpleDateFormat("HH:mm:ss").format(now) %></p>
    <p>Full: <%= now %></p>
    <p>Timestamp (ms since epoch): <%= millis %></p>
    <p>SQL Timestamp: <%= new Timestamp(millis) %></p>
    <p><i>This page refreshes every 5 seconds. Watch the seconds change.</i></p>
</body>
</html>
