// src/main/java/in/ignou/admission/repository/CourseRepository.java
package in.ignou.admission.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;

import in.ignou.admission.entity.Course;

public interface CourseRepository extends JpaRepository<Course, Long> {

    /** Walks the association: course.programme.code = ?1 */
    List<Course> findByProgrammeCode(String programmeCode);
}
