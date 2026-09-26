// src/main/java/in/ignou/admission/repository/UserRepository.java   (Session 9, Q37)
package in.ignou.admission.repository;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import in.ignou.admission.entity.User;

public interface UserRepository extends JpaRepository<User, Long> {

    Optional<User> findByUsername(String username);

    boolean existsByUsername(String username);
}
