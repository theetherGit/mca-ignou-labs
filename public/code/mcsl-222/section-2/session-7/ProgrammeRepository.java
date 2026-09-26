// src/main/java/in/ignou/admission/repository/ProgrammeRepository.java
package in.ignou.admission.repository;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import in.ignou.admission.entity.Programme;

public interface ProgrammeRepository extends JpaRepository<Programme, Long> {

    Optional<Programme> findByCode(String code);
}
