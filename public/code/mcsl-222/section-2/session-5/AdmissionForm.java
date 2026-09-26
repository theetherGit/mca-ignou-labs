package com.ignou.lab.admission.web;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotEmpty;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Past;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;
import org.springframework.format.annotation.DateTimeFormat;
import com.ignou.lab.admission.entity.Student;

/** Form-backing object with server-side (Bean Validation) rules. */
public class AdmissionForm {

    @NotBlank
    @Size(min = 3, max = 80)
    private String name;

    @NotBlank
    @Email
    private String email;

    @NotBlank
    @Pattern(regexp = "[6-9][0-9]{9}", message = "must be a 10-digit Indian mobile number")
    private String mobile;

    @NotNull
    @Past
    @DateTimeFormat(iso = DateTimeFormat.ISO.DATE)
    private LocalDate dob;

    @NotBlank
    @Size(max = 255)
    private String address;

    @NotBlank
    private String programme;

    @NotNull(message = "choose Yes or No")
    private Boolean hostelRequired;

    @NotEmpty(message = "pick at least one course")
    private List<String> courses = new ArrayList<>();

    /** Q22: bind the form object to the entity bean. */
    public Student toStudent() {
        Student s = new Student();
        s.setName(name);
        s.setEmail(email);
        s.setMobile(mobile);
        s.setDob(dob);
        s.setAddress(address);
        s.setProgramme(programme);
        s.setHostelRequired(hostelRequired);
        s.setCourses(String.join(",", courses)); // entity column is one comma-separated string
        return s;                                // enrolmentNo stays null until approval (Session 6)
    }

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
