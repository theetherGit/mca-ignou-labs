package com.ignou.lab.admission.entity;

import java.time.LocalDateTime;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.EnumType;
import jakarta.persistence.Enumerated;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;

/** One row per status change: the life cycle of an application. */
@Entity
@Table(name = "admission_status")
public class AdmissionStatus {

    public enum Status { PENDING, APPROVED, REJECTED }

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(optional = false)
    @JoinColumn(name = "student_id")
    private Student student;

    @Enumerated(EnumType.STRING)
    @Column(nullable = false, length = 10)
    private Status status;

    @Column(name = "changed_on", nullable = false)
    private LocalDateTime changedOn = LocalDateTime.now();

    @Column(length = 255)
    private String remark;

    protected AdmissionStatus() { } // JPA needs a no-arg constructor

    public AdmissionStatus(Student student, Status status, String remark) {
        this.student = student;
        this.status = status;
        this.remark = remark;
    }

    public Long getId() { return id; }
    public Student getStudent() { return student; }
    public Status getStatus() { return status; }
    public LocalDateTime getChangedOn() { return changedOn; }
    public String getRemark() { return remark; }
}
