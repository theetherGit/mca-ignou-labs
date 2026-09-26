package com.ignou.lab.admission.web;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import org.springframework.format.annotation.DateTimeFormat;

/** Form-backing object for the Student Admission form. */
public class AdmissionForm {

    private String name;                       // form:input
    private String email;                      // form:input type="email"
    private String mobile;                     // form:input
    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE)
    private LocalDate dob;                     // form:input type="date" (browser date picker)
    private String address;                    // form:textarea
    private String programme;                  // form:select
    private Boolean hostelRequired;            // form:radiobutton true / false
    private List<String> courses = new ArrayList<>(); // form:checkboxes

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }
    public String getMobile() { return mobile; }
    public void setMobile(String mobile) { this.mobile = mobile; }
    public LocalDate getDob() { return dob; }
    public void setDob(LocalDate dob) { this.dob = dob; }
    public String getAddress() { return address; }
    public void setAddress(String address) { this.address = address; }
    public String getProgramme() { return programme; }
    public void setProgramme(String programme) { this.programme = programme; }
    public Boolean getHostelRequired() { return hostelRequired; }
    public void setHostelRequired(Boolean hostelRequired) { this.hostelRequired = hostelRequired; }
    public List<String> getCourses() { return courses; }
    public void setCourses(List<String> courses) { this.courses = courses; }
}
