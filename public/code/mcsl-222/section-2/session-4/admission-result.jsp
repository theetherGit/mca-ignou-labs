<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Application received</title>
</head>
<body>
  <h1>Application received</h1>
  <table border="1" cellpadding="4">
    <tr><th>Name</th><td><c:out value="${admission.name}"/></td></tr>
    <tr><th>Email</th><td><c:out value="${admission.email}"/></td></tr>
    <tr><th>Mobile</th><td><c:out value="${admission.mobile}"/></td></tr>
    <tr><th>Date of birth</th><td>${admission.dob}</td></tr>
    <tr><th>Address</th><td><c:out value="${admission.address}"/></td></tr>
    <tr><th>Programme</th><td><c:out value="${admission.programme}"/></td></tr>
    <tr><th>Hostel required</th><td>${admission.hostelRequired ? 'Yes' : 'No'}</td></tr>
    <tr><th>Courses</th><td>
      <c:forEach items="${admission.courses}" var="course">
        <c:out value="${course}"/><br>
      </c:forEach>
    </td></tr>
  </table>
  <p><a href="${pageContext.request.contextPath}/admission">Another application</a></p>
</body>
</html>
