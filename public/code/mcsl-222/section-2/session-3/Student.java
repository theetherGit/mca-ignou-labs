package com.ignou.lab.admission.entity;

import java.time.LocalDate;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

/** Maps the student table of the IGNOU database from Session 1. */
@Entity
@Table(name = "student")
public class Student {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "enrolment_no", length = 12, unique = true)
    private String enrolmentNo;

    @Column(nullable = false, length = 80)
    private String name;

    @Column(nullable = false, length = 120)
    private String email;

    @Column(nullable = false, length = 10)
    private String mobile;

    @Column(nullable = false)
    private LocalDate dob;

    @Column(length = 255)
    private String address;

    @Column(nullable = false, length = 10)
    private String programme;

    /** comma-separated course codes, as stored by the Session 1 servlet */
    @Column(length = 255)
    private String courses;

    @Column(name = "hostel_required")
    private Boolean hostelRequired;

    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }
    public String getEnrolmentNo() { return enrolmentNo; }
    public void setEnrolmentNo(String enrolmentNo) { this.enrolmentNo = enrolmentNo; }
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
    public String getCourses() { return courses; }
    public void setCourses(String courses) { this.courses = courses; }
    public Boolean getHostelRequired() { return hostelRequired; }
    public void setHostelRequired(Boolean hostelRequired) { this.hostelRequired = hostelRequired; }

    @Override
    public String toString() {
        return "Student[id=" + id + ", enrolmentNo=" + enrolmentNo + ", name=" + name
                + ", programme=" + programme + ", courses=" + courses + "]";
    }
}
