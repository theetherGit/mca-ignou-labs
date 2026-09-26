<%-- Q10: src/main/webapp/action-demo.jsp
     Entry page: jsp:include for the header, a form that posts to bean-view.jsp,
     and a message slot that bean-view.jsp fills when it jsp:forwards back here. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>JSP Action Elements</title></head>
<body>
    <%-- 2. jsp:include runs header.jsp now and pastes its output here --%>
    <jsp:include page="header.jsp">
        <jsp:param name="title" value="Action Elements" />
    </jsp:include>

    <h2>Student Bean Form</h2>
    <% if (request.getParameter("msg") != null) { %>
        <p style="color:red"><%= request.getParameter("msg") %></p>
    <% } %>

    <%-- field names match the StudentBean property names on purpose --%>
    <form action="bean-view.jsp" method="post">
        <p><label>Name: <input name="name"></label></p>
        <p><label>Programme: <input name="programme" value="MCA"></label></p>
        <p><label>Semester: <input name="semester" type="number" value="2" min="1" max="6"></label></p>
        <p><button type="submit">Show bean</button></p>
    </form>
</body>
</html>
