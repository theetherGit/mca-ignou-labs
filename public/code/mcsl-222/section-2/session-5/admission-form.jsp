<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <%@ include file="head.jspf" %>
  <title>Student Admission Form</title>
</head>
<body>
<nav class="navbar navbar-dark"><div class="container"><span class="navbar-brand">IGNOU Student Admission</span></div></nav>
<div class="container">
  <div class="card card-form">
    <div class="card-body">
      <h1 class="h3 card-title">Student Admission Form</h1>

      <form:form modelAttribute="admission" method="post" cssClass="row g-3">
        <div class="col-12">
          <form:label path="name" cssClass="form-label required">Full name</form:label>
          <form:input path="name" cssClass="form-control" cssErrorClass="form-control is-invalid"
                      required="required" minlength="3" maxlength="80"/>
          <form:errors path="name" cssClass="invalid-feedback"/>
        </div>

        <div class="col-md-6">
          <form:label path="email" cssClass="form-label required">Email</form:label>
          <form:input path="email" type="email" cssClass="form-control" cssErrorClass="form-control is-invalid"
                      required="required"/>
          <form:errors path="email" cssClass="invalid-feedback"/>
        </div>

        <div class="col-md-6">
          <form:label path="mobile" cssClass="form-label required">Mobile</form:label>
          <form:input path="mobile" cssClass="form-control" cssErrorClass="form-control is-invalid"
                      required="required" pattern="[6-9][0-9]{9}" title="10 digits, starting 6 to 9"/>
          <form:errors path="mobile" cssClass="invalid-feedback"/>
        </div>

        <div class="col-md-6">
          <form:label path="dob" cssClass="form-label required">Date of birth</form:label>
          <form:input path="dob" type="date" cssClass="form-control" cssErrorClass="form-control is-invalid"
                      required="required" max="${today}"/>
          <form:errors path="dob" cssClass="invalid-feedback"/>
        </div>

        <div class="col-md-6">
          <form:label path="programme" cssClass="form-label required">Programme</form:label>
          <form:select path="programme" cssClass="form-select" cssErrorClass="form-select is-invalid" required="required">
            <form:option value="" label="-- choose --"/>
            <form:options items="${programmes}"/>
          </form:select>
          <form:errors path="programme" cssClass="invalid-feedback"/>
        </div>

        <div class="col-12">
          <form:label path="address" cssClass="form-label required">Address</form:label>
          <form:textarea path="address" rows="3" cssClass="form-control" cssErrorClass="form-control is-invalid"
                         required="required" maxlength="255"/>
          <form:errors path="address" cssClass="invalid-feedback"/>
        </div>

        <div class="col-md-6">
          <label class="form-label required">Hostel required?</label>
          <div class="form-check form-check-inline">
            <form:radiobutton path="hostelRequired" value="true" cssClass="form-check-input" label=" Yes" required="required"/>
          </div>
          <div class="form-check form-check-inline">
            <form:radiobutton path="hostelRequired" value="false" cssClass="form-check-input" label=" No"/>
          </div>
          <form:errors path="hostelRequired" cssClass="text-danger small d-block"/>
        </div>

        <div class="col-md-6">
          <label class="form-label required">Courses this semester</label>
          <c:forEach items="${courseList}" var="course">
            <div class="form-check">
              <form:checkbox path="courses" value="${course}" cssClass="form-check-input" label=" ${course}"/>
            </div>
          </c:forEach>
          <form:errors path="courses" cssClass="text-danger small d-block"/>
        </div>

        <div class="col-12 text-end">
          <a class="btn btn-outline-secondary" href="${pageContext.request.contextPath}/">Cancel</a>
          <button type="submit" class="btn btn-primary">Submit application</button>
        </div>
      </form:form>
    </div>
  </div>
</div>
</body>
</html>
