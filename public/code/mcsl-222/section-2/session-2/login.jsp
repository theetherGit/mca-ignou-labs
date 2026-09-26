<%-- Q12: src/main/webapp/login.jsp  (welcome page of the project) --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%-- already logged in? go straight to the list --%>
<c:if test="${not empty sessionScope.user}">
    <c:redirect url="/students" />
</c:if>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Login - IGNOU Student App</title></head>
<body>
    <h2>IGNOU Student App - Login</h2>
    <c:if test="${not empty param.error}">
        <p style="color:red"><c:out value="${param.error}" /></p>
    </c:if>
    <c:if test="${param.out == '1'}">
        <p style="color:green">You have been logged out.</p>
    </c:if>
    <form action="login" method="post">
        <p><label>Username: <input name="username" required autofocus></label></p>
        <p><label>Password: <input name="password" type="password" required></label></p>
        <p><button type="submit">Login</button></p>
    </form>
    <p><small>Demo account: admin / ignou123</small></p>
</body>
</html>
