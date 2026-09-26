<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <%@ include file="head.jspf" %>
  <title>Student Admission</title>
</head>
<body>
<nav class="navbar navbar-dark"><div class="container"><span class="navbar-brand">IGNOU Student Admission</span></div></nav>
<div class="container">
  <div class="card card-form text-center">
    <div class="card-body">
      <h1 class="h3 card-title">Welcome to the Lab Project for Student Admission using Spring MVC</h1>
      <p class="text-muted">Spring Framework ${springVersion} &middot; server time ${now}</p>
      <a class="btn btn-primary btn-lg" href="${pageContext.request.contextPath}/admission">Apply for admission</a>
      <a class="btn btn-outline-secondary btn-lg" href="${pageContext.request.contextPath}/students">View students</a>
    </div>
  </div>
</div>
</body>
</html>
