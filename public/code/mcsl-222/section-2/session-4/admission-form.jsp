<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Student Admission Form</title>
</head>
<body>
  <h1>Student Admission Form</h1>
  <form:form modelAttribute="admission" method="post">
    <p><form:label path="name">Full name</form:label><br>
       <form:input path="name" size="40"/></p>

    <p><form:label path="email">Email</form:label><br>
       <form:input path="email" type="email" size="40"/></p>

    <p><form:label path="mobile">Mobile</form:label><br>
       <form:input path="mobile" size="12"/></p>

    <p><form:label path="dob">Date of birth</form:label><br>
       <form:input path="dob" type="date"/></p>

    <p><form:label path="address">Address</form:label><br>
       <form:textarea path="address" rows="3" cols="40"/></p>

    <p><form:label path="programme">Programme</form:label><br>
       <form:select path="programme">
         <form:option value="" label="-- choose --"/>
         <form:options items="${programmes}"/>
       </form:select></p>

    <p>Hostel required?<br>
       <form:radiobutton path="hostelRequired" value="true" label="Yes"/>
       <form:radiobutton path="hostelRequired" value="false" label="No"/></p>

    <p>Courses this semester<br>
       <form:checkboxes path="courses" items="${courseList}" delimiter="<br>"/></p>

    <p><button type="submit">Submit application</button></p>
  </form:form>
</body>
</html>
