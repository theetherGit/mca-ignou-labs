<%-- Q12: src/main/webapp/WEB-INF/views/students.jsp
     Under WEB-INF so it cannot be opened directly; only the controller forwards here. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="fn" uri="jakarta.tags.functions" %>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>Students</title></head>
<body>
    <p style="float:right">Logged in as <b><c:out value="${sessionScope.user}" /></b> |
       <a href="logout">Logout</a></p>
    <h2>IGNOU Students (${fn:length(students)})</h2>
    <c:if test="${not empty param.msg}">
        <p style="color:green"><c:out value="${param.msg}" /></p>
    </c:if>
    <p><a href="students?action=new">Add new student</a></p>
    <table border="1" cellpadding="4">
        <tr><th>Enrolment</th><th>Name</th><th>DOB</th><th>Email</th><th>Mobile</th>
            <th>Programme</th><th>Sem</th><th>Courses</th><th>Actions</th></tr>
        <c:forEach var="s" items="${students}">
            <tr>
                <td><c:out value="${s.enrolmentNo}" /></td>
                <td><c:out value="${s.name}" /></td>
                <td>${s.dob}</td>
                <td><c:out value="${s.email}" /></td>
                <td><c:out value="${s.mobile}" /></td>
                <td><c:out value="${s.programme}" /></td>
                <td>${s.semester}</td>
                <td><c:out value="${s.courses}" /></td>
                <td>
                    <c:url var="editUrl" value="/students">
                        <c:param name="action" value="edit" />
                        <c:param name="id" value="${s.enrolmentNo}" />
                    </c:url>
                    <a href="${editUrl}">Edit</a>
                    <form method="post" action="students" style="display:inline"
                          onsubmit="return confirm('Delete ${s.enrolmentNo}?')">
                        <input type="hidden" name="action" value="delete">
                        <input type="hidden" name="id" value="<c:out value='${s.enrolmentNo}' />">
                        <button type="submit">Delete</button>
                    </form>
                </td>
            </tr>
        </c:forEach>
        <c:if test="${empty students}">
            <tr><td colspan="9">No students yet. Add one.</td></tr>
        </c:if>
    </table>
</body>
</html>
