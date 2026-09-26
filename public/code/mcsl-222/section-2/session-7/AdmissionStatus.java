// src/main/java/in/ignou/admission/entity/AdmissionStatus.java
package in.ignou.admission.entity;

/** Life cycle of one application. Stored as a string column by @Enumerated(EnumType.STRING). */
public enum AdmissionStatus {
    APPLIED, VERIFIED, APPROVED, REJECTED
}
