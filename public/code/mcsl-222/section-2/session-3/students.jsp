<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Students</title>
</head>
<body>
  <h1>Students (IGNOU database, via Hibernate/JPA)</h1>
  <table border="1" cellpadding="4">
    <tr><th>Id</th><th>Enrolment No</th><th>Name</th><th>Email</th><th>DOB</th><th>Programme</th><th>Courses</th></tr>
    <c:forEach items="${students}" var="s">
      <tr>
        <td>${s.id}</td>
        <td><c:out value="${s.enrolmentNo}"/></td>
        <td><c:out value="${s.name}"/></td>
        <td><c:out value="${s.email}"/></td>
        <td>${s.dob}</td>
        <td><c:out value="${s.programme}"/></td>
        <td><c:out value="${s.courses}"/></td>
      </tr>
    </c:forEach>
  </table>
  <p><a href="${pageContext.request.contextPath}/">Home</a></p>
</body>
</html>
