<%-- Q12: src/main/webapp/WEB-INF/views/student-form.jsp
     One page for both Add and Edit. The controller sets 'student' and 'editing'. --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="fn" uri="jakarta.tags.functions" %>
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8"><title>${editing ? 'Edit' : 'Add'} Student</title></head>
<body>
    <h2>${editing ? 'Edit' : 'Add'} Student</h2>
    <form method="post" action="students">
        <input type="hidden" name="action" value="${editing ? 'update' : 'insert'}">
        <p><label>Enrolment No:
            <input name="enrolmentNo" value="<c:out value='${student.enrolmentNo}' />"
                   pattern="[0-9]{9,12}" required ${editing ? 'readonly' : ''}></label></p>
        <p><label>Name: <input name="name" value="<c:out value='${student.name}' />" required></label></p>
        <p><label>Date of Birth: <input type="date" name="dob" value="${student.dob}" required></label></p>
        <p>Gender:
            <label><input type="radio" name="gender" value="M" ${student.gender != 'F' && student.gender != 'O' ? 'checked' : ''}> Male</label>
            <label><input type="radio" name="gender" value="F" ${student.gender == 'F' ? 'checked' : ''}> Female</label>
            <label><input type="radio" name="gender" value="O" ${student.gender == 'O' ? 'checked' : ''}> Other</label>
        </p>
        <p><label>Email: <input type="email" name="email" value="<c:out value='${student.email}' />" required></label></p>
        <p><label>Mobile: <input name="mobile" value="<c:out value='${student.mobile}' />" pattern="[0-9]{10}" required></label></p>
        <p><label>Address: <input name="address" value="<c:out value='${student.address}' />"></label></p>
        <p><label>City: <input name="city" value="<c:out value='${student.city}' />"></label></p>
        <p><label>State: <input name="state" value="<c:out value='${student.state}' />"></label></p>
        <p><label>Pincode: <input name="pincode" value="<c:out value='${student.pincode}' />" pattern="[0-9]{6}"></label></p>
        <p><label>Programme:
            <select name="programme">
                <c:forEach var="p" items="${['MCA', 'BCA', 'MSc', 'PGDCA']}">
                    <option ${student.programme == p ? 'selected' : ''}>${p}</option>
                </c:forEach>
            </select></label></p>
        <p><label>Semester: <input type="number" name="semester" min="1" max="6"
                  value="${student.semester == 0 ? 1 : student.semester}"></label></p>
        <p><label>Admission Year: <input type="number" name="admissionYear" min="2000" max="2099"
                  value="${student.admissionYear == 0 ? 2024 : student.admissionYear}"></label></p>
        <p><label>Study Centre: <input name="studyCentre" value="<c:out value='${student.studyCentre}' />"></label></p>
        <p>Courses:
            <c:set var="chosen" value=",${student.courses},"/>
            <c:forEach var="code" items="${['MCS-218', 'MCS-219', 'MCS-220', 'MCS-221', 'MCSL-222', 'MCSL-223']}">
                <c:set var="key" value=",${code}," />
                <label><input type="checkbox" name="courses" value="${code}"
                       ${fn:contains(chosen, key) ? 'checked' : ''}> ${code}</label>
            </c:forEach>
        </p>
        <p><button type="submit">Save</button> <a href="students">Cancel</a></p>
    </form>
</body>
</html>
