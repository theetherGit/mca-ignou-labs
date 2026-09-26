<%-- Q10: src/main/webapp/bean-view.jsp
     jsp:useBean creates the bean, jsp:setProperty fills it from the request,
     jsp:getProperty prints it; jsp:forward sends bad input back to the form. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%-- 1. jsp:forward: the browser URL stays bean-view.jsp, but the form page renders --%>
<% if (request.getParameter("name") == null || request.getParameter("name").isBlank()) { %>
    <jsp:forward page="action-demo.jsp">
        <jsp:param name="msg" value="Name is required (you were forwarded back by jsp:forward)" />
    </jsp:forward>
<% } %>

<%-- 4. jsp:useBean: find a StudentBean named 'student' in request scope or create one --%>
<jsp:useBean id="student" class="ignou.StudentBean" scope="request" />
<%-- 3. jsp:setProperty with property="*" copies every matching request parameter --%>
<jsp:setProperty name="student" property="*" />

<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Bean View</title></head>
<body>
    <jsp:include page="header.jsp">
        <jsp:param name="title" value="Bean View" />
    </jsp:include>

    <h2>Values read back with jsp:getProperty</h2>
    <table border="1" cellpadding="4">
        <tr><th>Name</th><td><jsp:getProperty name="student" property="name" /></td></tr>
        <tr><th>Programme</th><td><jsp:getProperty name="student" property="programme" /></td></tr>
        <tr><th>Semester</th><td><jsp:getProperty name="student" property="semester" /></td></tr>
    </table>

    <%-- setProperty with a fixed value, then read it through EL --%>
    <jsp:setProperty name="student" property="programme" value="MCA (forced)" />
    <p>After setProperty with a literal value, programme = ${student.programme}</p>

    <p><a href="action-demo.jsp">Back</a></p>
</body>
</html>
