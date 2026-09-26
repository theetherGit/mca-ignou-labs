<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <%@ include file="head.jspf" %>
  <title>Application saved</title>
</head>
<body>
<nav class="navbar navbar-dark"><div class="container"><span class="navbar-brand">IGNOU Student Admission</span></div></nav>
<div class="container">
  <div class="card card-form">
    <div class="card-body">
      <div class="alert alert-success">Application saved. Database id: <b>${student.id}</b></div>
      <table class="table table-striped">
        <tbody>
          <tr><th scope="row">Name</th><td><c:out value="${student.name}"/></td></tr>
          <tr><th scope="row">Email</th><td><c:out value="${student.email}"/></td></tr>
          <tr><th scope="row">Mobile</th><td><c:out value="${student.mobile}"/></td></tr>
          <tr><th scope="row">Date of birth</th><td>${student.dob}</td></tr>
          <tr><th scope="row">Address</th><td><c:out value="${student.address}"/></td></tr>
          <tr><th scope="row">Programme</th><td><c:out value="${student.programme}"/></td></tr>
          <tr><th scope="row">Hostel required</th><td>${student.hostelRequired ? 'Yes' : 'No'}</td></tr>
          <tr><th scope="row">Courses</th><td><c:out value="${student.courses}"/></td></tr>
          <tr><th scope="row">Enrolment no</th><td>${empty student.enrolmentNo ? 'pending approval' : student.enrolmentNo}</td></tr>
        </tbody>
      </table>
      <a class="btn btn-primary" href="${pageContext.request.contextPath}/admission">Another application</a>
      <a class="btn btn-outline-secondary" href="${pageContext.request.contextPath}/students">All students</a>
    </div>
  </div>
</div>
</body>
</html>
