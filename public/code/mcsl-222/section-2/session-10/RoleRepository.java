// src/main/java/in/ignou/admission/repository/RoleRepository.java   (Session 10, Q42)
package in.ignou.admission.repository;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import in.ignou.admission.entity.Role;

public interface RoleRepository extends JpaRepository<Role, Long> {

    Optional<Role> findByName(String name);
}
