<%-- Q11 and Q12: src/main/webapp/error.jsp
     isErrorPage="true" makes the 'exception' implicit object available.
     Reached two ways: errorPage="error.jsp" in a JSP page directive, or the
     error-page entries in web.xml (uncaught exception or HTTP 404). --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" isErrorPage="true" %>
<%
    Integer status = (Integer) request.getAttribute("jakarta.servlet.error.status_code");
    String uri = (String) request.getAttribute("jakarta.servlet.error.request_uri");
%>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Error</title></head>
<body>
    <h2>Something went wrong</h2>
    <% if (exception != null) { %>
        <p>Exception type: <b><%= exception.getClass().getName() %></b></p>
        <p>Message: <%= exception.getMessage() %></p>
        <p>Thrown from: <%= exception.getStackTrace().length > 0 ? exception.getStackTrace()[0] : "unknown" %></p>
    <% } else { %>
        <p>HTTP status <%= status %> for <%= uri %></p>
    <% } %>
    <p><a href="<%= request.getContextPath() %>/">Home</a></p>
</body>
</html>
