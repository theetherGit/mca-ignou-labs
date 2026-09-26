<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <%@ include file="head.jspf" %>
  <title>Students</title>
</head>
<body>
<nav class="navbar navbar-dark"><div class="container"><span class="navbar-brand">IGNOU Student Admission</span></div></nav>
<div class="container mt-4">
  <c:if test="${not empty message}">
    <div class="alert alert-success">${message}</div>
  </c:if>

  <div class="d-flex justify-content-between align-items-center mb-3">
    <h1 class="h3 m-0">Applications</h1>
    <a class="btn btn-primary" href="${pageContext.request.contextPath}/students/new">New application</a>
  </div>

  <%-- one form around the table: the ticked ids go to /students/approve --%>
  <form method="post" action="${pageContext.request.contextPath}/students/approve">
    <table class="table table-striped align-middle">
      <thead>
        <tr><th></th><th>Id</th><th>Enrolment</th><th>Name</th><th>Programme</th><th>Courses</th><th>Status</th><th>Applied</th><th></th></tr>
      </thead>
      <tbody>
        <c:forEach items="${students}" var="s">
          <tr>
            <td><c:if test="${s.status == 'PENDING'}"><input class="form-check-input" type="checkbox" name="ids" value="${s.id}"></c:if></td>
            <td>${s.id}</td>
            <td>${empty s.enrolmentNo ? '-' : s.enrolmentNo}</td>
            <td><c:out value="${s.name}"/></td>
            <td>${s.programme.code}</td>
            <td><c:forEach items="${s.courses}" var="sc" varStatus="st">${sc.course.code}<c:if test="${!st.last}">, </c:if></c:forEach></td>
            <td><span class="badge ${s.status == 'APPROVED' ? 'text-bg-success' : s.status == 'REJECTED' ? 'text-bg-danger' : 'text-bg-warning'}">${s.status}</span></td>
            <td>${s.appliedOn}</td>
            <td class="text-nowrap">
              <a class="btn btn-sm btn-outline-secondary" href="${pageContext.request.contextPath}/students/${s.id}/edit">Edit</a>
              <%-- the form attribute links this button to a form outside the approve form (forms cannot nest) --%>
              <button class="btn btn-sm btn-outline-danger" type="submit" form="delete-${s.id}"
                      onclick="return confirm('Delete student ${s.id}?')">Delete</button>
            </td>
          </tr>
        </c:forEach>
      </tbody>
    </table>
    <button type="submit" class="btn btn-success">Approve selected</button>
  </form>

  <c:forEach items="${students}" var="s">
    <form id="delete-${s.id}" method="post" action="${pageContext.request.contextPath}/students/${s.id}/delete"></form>
  </c:forEach>
</div>
</body>
</html>
