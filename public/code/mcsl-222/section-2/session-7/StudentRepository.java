// src/main/java/in/ignou/admission/repository/StudentRepository.java
package in.ignou.admission.repository;

import java.util.List;
import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import in.ignou.admission.entity.Student;

/** No implementation needed: Spring Data generates it at start-up from the method names. */
public interface StudentRepository extends JpaRepository<Student, Long> {

    Optional<Student> findByEmail(String email);

    List<Student> findByCityIgnoreCase(String city);
}
