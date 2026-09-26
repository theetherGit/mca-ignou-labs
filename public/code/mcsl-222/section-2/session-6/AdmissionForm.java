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
import com.ignou.lab.admission.entity.StudentCourse;

/** Session 6 version: programme and courses are database ids; id is set when editing. */
public class AdmissionForm {

    private Long id;

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

    @NotNull(message = "choose a programme")
    private Long programmeId;

    @NotNull(message = "choose Yes or No")
    private Boolean hostelRequired;

    @NotEmpty(message = "pick at least one course")
    private List<Long> courseIds = new ArrayList<>();

    /** entity -> form, for the edit page */
    public static AdmissionForm from(Student s) {
        AdmissionForm f = new AdmissionForm();
        f.id = s.getId();
        f.name = s.getName();
        f.email = s.getEmail();
        f.mobile = s.getMobile();
        f.dob = s.getDob();
        f.address = s.getAddress();
        f.programmeId = s.getProgramme().getId();
        f.hostelRequired = s.isHostelRequired();
        for (StudentCourse sc : s.getCourses()) {
            f.courseIds.add(sc.getCourse().getId());
        }
        return f;
    }

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }
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
    public Long getProgrammeId() { return programmeId; }
    public void setProgrammeId(Long programmeId) { this.programmeId = programmeId; }
    public Boolean getHostelRequired() { return hostelRequired; }
    public void setHostelRequired(Boolean hostelRequired) { this.hostelRequired = hostelRequired; }
    public List<Long> getCourseIds() { return courseIds; }
    public void setCourseIds(List<Long> courseIds) { this.courseIds = courseIds; }
}
