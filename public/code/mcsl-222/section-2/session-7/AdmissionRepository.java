// src/main/java/in/ignou/admission/repository/AdmissionRepository.java
package in.ignou.admission.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;

import in.ignou.admission.entity.Admission;
import in.ignou.admission.entity.AdmissionStatus;

public interface AdmissionRepository extends JpaRepository<Admission, Long> {

    List<Admission> findByStatus(AdmissionStatus status);

    List<Admission> findByStudentId(Long studentId);
}
