<%-- Q8: src/main/webapp/jstl-demo.jsp
     JSTL 3.0 core tags on Tomcat 10.1: the taglib URI is jakarta.tags.core --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>

<%-- 5. c:redirect: /jstl-demo.jsp?go=clock sends the browser to datetime.jsp --%>
<c:if test="${param.go == 'clock'}">
    <c:redirect url="/datetime.jsp" />
</c:if>

<%-- test data: a list of marks in page scope --%>
<c:set var="student" value="Asha Verma" />
<c:set var="marks" value="${[78, 92, 45, 66, 88]}" />
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>JSTL Core Tags</title></head>
<body>
    <h2>JSTL Core Tag Demo</h2>

    <h3>1. c:out</h3>
    <%-- escapeXml is true by default, so a value like <b>x</b> is printed literally --%>
    <p>Student: <c:out value="${student}" /></p>
    <p>Unknown parameter with default: <c:out value="${param.city}" default="not given" /></p>
    <p>Escaped: <c:out value="<b>bold?</b>" /></p>

    <h3>2. c:if</h3>
    <c:if test="${not empty param.name}">
        <p>Hello, <c:out value="${param.name}" /></p>
    </c:if>
    <c:if test="${empty param.name}">
        <p>Add ?name=YourName to the URL to see c:if fire.</p>
    </c:if>

    <h3>3. c:forEach</h3>
    <table border="1" cellpadding="4">
        <tr><th>#</th><th>Marks</th><th>Result</th></tr>
        <c:forEach var="m" items="${marks}" varStatus="st">
            <tr>
                <td>${st.count}</td>
                <td>${m}</td>
                <td>
                    <%-- 4. c:choose / c:when / c:otherwise --%>
                    <c:choose>
                        <c:when test="${m >= 75}">Distinction</c:when>
                        <c:when test="${m >= 50}">Pass</c:when>
                        <c:otherwise>Fail</c:otherwise>
                    </c:choose>
                </td>
            </tr>
        </c:forEach>
    </table>
    <p>Counting with begin/end/step:
        <c:forEach var="i" begin="1" end="10" step="3">${i} </c:forEach>
    </p>

    <h3>5. c:url and c:redirect</h3>
    <%-- c:url prefixes the context path and adds the session id if cookies are off --%>
    <c:url var="selfLink" value="/jstl-demo.jsp">
        <c:param name="name" value="Rahul Singh" />
        <c:param name="city" value="Kolkata" />
    </c:url>
    <p><a href="${selfLink}">Reload with name and city (built by c:url)</a></p>
    <p>Rendered link: <c:out value="${selfLink}" /></p>
    <c:url var="clockLink" value="/jstl-demo.jsp"><c:param name="go" value="clock" /></c:url>
    <p><a href="${clockLink}">Go to the clock page (c:redirect)</a></p>
</body>
</html>
