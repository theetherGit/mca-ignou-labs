// src/main/java/in/ignou/admission/web/StudentRestController.java   (Session 8, Q34: full CRUD)
package in.ignou.admission.web;

import java.util.List;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import in.ignou.admission.entity.Student;
import in.ignou.admission.repository.StudentRepository;

/**
 * Annotation-based REST CRUD.
 *   POST   /api/students        create  -> 201 + saved student
 *   GET    /api/students        read    -> 200 + list
 *   GET    /api/students/{id}   read    -> 200 or 404
 *   PUT    /api/students/{id}   update  -> 200 or 404
 *   DELETE /api/students/{id}   delete  -> 204 or 404
 */
@RestController
@RequestMapping("/api/students")
public class StudentRestController {

    private final StudentRepository students;

    public StudentRestController(StudentRepository students) {
        this.students = students;
    }

    /** @RequestBody: Jackson turns the JSON body into a Student; id is ignored and generated. */
    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public Student create(@RequestBody Student student) {
        student.setId(null);
        return students.save(student);
    }

    @GetMapping
    public List<Student> all(@RequestParam(required = false) String city) {
        return city == null ? students.findAll() : students.findByCityIgnoreCase(city);
    }

    @GetMapping("/{id}")
    public ResponseEntity<Student> one(@PathVariable Long id) {
        return students.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    /** Copy the editable fields onto the managed entity, then save (an UPDATE, because id is set). */
    @PutMapping("/{id}")
    public ResponseEntity<Student> update(@PathVariable Long id, @RequestBody Student in) {
        return students.findById(id).map(s -> {
            s.setName(in.getName());
            s.setEmail(in.getEmail());
            s.setPhone(in.getPhone());
            s.setCity(in.getCity());
            s.setDateOfBirth(in.getDateOfBirth());
            return ResponseEntity.ok(students.save(s));
        }).orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        if (!students.existsById(id)) {
            return ResponseEntity.notFound().build();
        }
        students.deleteById(id);
        return ResponseEntity.noContent().build();
    }
}
