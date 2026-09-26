<%-- Q10: src/main/webapp/header.jsp  (pulled in with jsp:include at request time) --%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<div style="background:#eee;padding:8px;border-bottom:1px solid #999">
    <b>IGNOU Web Technologies Lab</b> |
    Page title: <%= request.getParameter("title") %> |
    Served at <%= new java.util.Date() %>
</div>
