// src/main/java/in/ignou/admission/web/StudentRestController.java   (Session 7, Q32: read only)
package in.ignou.admission.web;

import java.util.List;

import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import in.ignou.admission.entity.Student;
import in.ignou.admission.repository.StudentRepository;

/**
 * @RestController = @Controller + @ResponseBody: every return value is written
 * to the HTTP body as JSON by Jackson instead of being resolved as a view name.
 */
@RestController
@RequestMapping("/api/students")
public class StudentRestController {

    private final StudentRepository students;

    // one constructor: Spring injects the repository, no @Autowired needed
    public StudentRestController(StudentRepository students) {
        this.students = students;
    }

    /** GET /api/students  or  GET /api/students?city=Jaipur */
    @GetMapping
    public List<Student> all(@RequestParam(required = false) String city) {
        return city == null ? students.findAll() : students.findByCityIgnoreCase(city);
    }

    /** GET /api/students/1 -> 200 with the student, or 404 with an empty body */
    @GetMapping("/{id}")
    public ResponseEntity<Student> one(@PathVariable Long id) {
        return students.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }
}
