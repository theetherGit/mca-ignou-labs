<%-- Q11: src/main/webapp/implicit.jsp
     out, request, response, session, pageContext; exception is shown by error.jsp.
     Open /implicit.jsp?fail=1 to trigger the exception path. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" errorPage="error.jsp" %>
<%
    // response: set a header and a cookie before any output is flushed
    response.setHeader("X-Lab", "MCSL-222");
    response.addCookie(new jakarta.servlet.http.Cookie("lastPage", "implicit"));

    // session: count visits for this browser
    Integer visits = (Integer) session.getAttribute("visits");
    visits = visits == null ? 1 : visits + 1;
    session.setAttribute("visits", visits);

    // pageContext: attribute in page scope, and a shortcut to the other scopes
    pageContext.setAttribute("pageNote", "only visible on this page");
    pageContext.setAttribute("appNote", "visible to every page", jakarta.servlet.jsp.PageContext.APPLICATION_SCOPE);
%>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Implicit Objects</title></head>
<body>
    <h2>JSP Implicit Objects</h2>

    <h3>1. out</h3>
    <% out.println("<p>Written with out.println(). Buffer size: " + out.getBufferSize()
                   + " bytes, remaining: " + out.getRemaining() + "</p>"); %>

    <h3>2. request</h3>
    <p>Method: <%= request.getMethod() %>, URI: <%= request.getRequestURI() %>,
       client IP: <%= request.getRemoteAddr() %>, name parameter: <%= request.getParameter("name") %></p>

    <h3>3. response</h3>
    <p>Content type set to <%= response.getContentType() %>; header X-Lab and cookie lastPage added (see browser dev tools).</p>

    <h3>4. session</h3>
    <p>Session id: <%= session.getId() %>, visits: <%= visits %>, new: <%= session.isNew() %></p>

    <h3>5. pageContext</h3>
    <p>page scope: <%= pageContext.getAttribute("pageNote") %></p>
    <p>application scope via pageContext: <%= pageContext.findAttribute("appNote") %></p>
    <p>session via pageContext: <%= pageContext.getSession().getId().equals(session.getId()) %> (same object as session)</p>

    <h3>6. exception</h3>
    <p><a href="implicit.jsp?fail=1">Click to divide by zero</a>; error.jsp shows the exception object.</p>
    <%
        if ("1".equals(request.getParameter("fail"))) {
            int zero = 0;
            out.println(10 / zero);   // ArithmeticException goes to errorPage
        }
    %>
</body>
</html>
