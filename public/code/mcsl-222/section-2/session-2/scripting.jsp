<%-- Q7: src/main/webapp/scripting.jsp
     Declaration <%! %>, scriptlet <% %> and expression <%= %> in one page. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<%-- Declaration: becomes a field and a method of the generated servlet class.
     Because it is a field, hitCount survives across requests (until redeploy). --%>
<%!
    private int hitCount = 0;

    private long factorial(int n) {
        long f = 1;
        for (int i = 2; i <= n; i++) f *= i;
        return f;
    }
%>

<%-- Scriptlet: plain Java inside _jspService(); runs on every request. --%>
<%
    hitCount++;
    String name = request.getParameter("name");
    if (name == null || name.isBlank()) name = "Student";
    int n = 5;
%>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>JSP Scripting Elements</title></head>
<body>
    <h2>JSP Scripting Elements</h2>
    <%-- Expression: value is converted to String and written into the output. --%>
    <p>Hello, <%= name %>! You are visitor number <%= hitCount %>.</p>
    <p>Factorial of <%= n %> is <%= factorial(n) %>.</p>

    <h3>Multiplication table of 7 (scriptlet loop)</h3>
    <table border="1" cellpadding="4">
    <% for (int i = 1; i <= 10; i++) { %>
        <tr><td>7 x <%= i %></td><td>= <%= 7 * i %></td></tr>
    <% } %>
    </table>

    <form method="get">
        <p>Your name: <input name="name" value="<%= name %>"> <button type="submit">Greet</button></p>
    </form>
</body>
</html>
