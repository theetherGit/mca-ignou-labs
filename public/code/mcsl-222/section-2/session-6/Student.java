package com.ignou.lab.admission.entity;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import jakarta.persistence.CascadeType;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.EnumType;
import jakarta.persistence.Enumerated;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.OneToMany;
import jakarta.persistence.OrderBy;
import jakarta.persistence.Table;
import com.ignou.lab.admission.entity.AdmissionStatus.Status;

@Entity
@Table(name = "student")
public class Student {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    /** assigned on approval (Q28); null while the application is pending */
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

    @Column(nullable = false, length = 255)
    private String address;

    @Column(name = "hostel_required", nullable = false)
    private boolean hostelRequired;

    @ManyToOne(optional = false)
    @JoinColumn(name = "programme_id")
    private Programme programme;

    /** current stage; the full history is in AdmissionStatus rows */
    @Enumerated(EnumType.STRING)
    @Column(nullable = false, length = 10)
    private Status status = Status.PENDING;

    @Column(name = "applied_on", nullable = false)
    private LocalDate appliedOn = LocalDate.now();

    /** cascade + orphanRemoval: saving/deleting the student saves/deletes its rows */
    @OneToMany(mappedBy = "student", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<StudentCourse> courses = new ArrayList<>();

    @OneToMany(mappedBy = "student", cascade = CascadeType.ALL, orphanRemoval = true)
    @OrderBy("changedOn")
    private List<AdmissionStatus> history = new ArrayList<>();

    /** the only way to change the status: keeps the current column and the history in step */
    public void changeStatus(Status newStatus, String remark) {
        this.status = newStatus;
        history.add(new AdmissionStatus(this, newStatus, remark));
    }

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
    public boolean isHostelRequired() { return hostelRequired; }
    public void setHostelRequired(boolean hostelRequired) { this.hostelRequired = hostelRequired; }
    public Programme getProgramme() { return programme; }
    public void setProgramme(Programme programme) { this.programme = programme; }
    public Status getStatus() { return status; }
    public LocalDate getAppliedOn() { return appliedOn; }
    public List<StudentCourse> getCourses() { return courses; }
    public List<AdmissionStatus> getHistory() { return history; }
}
