// src/main/java/in/ignou/xmlapi/CourseRestController.java   (Session 8, Q35)
package in.ignou.xmlapi;

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
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;

import in.ignou.admission.entity.Course;

/**
 * The bean is declared in beans.xml, not found by scanning. @RestController stays,
 * because Spring MVC 6 only treats @Controller-annotated beans as request handlers.
 */
@RestController
@RequestMapping("/xml/courses")
public class CourseRestController {

    private final CourseService service;

    public CourseRestController(CourseService service) {
        this.service = service;
    }

    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public Course create(@RequestBody Course course) {
        return service.create(course);
    }

    @GetMapping
    public List<Course> all() {
        return service.all();
    }

    @GetMapping("/{id}")
    public ResponseEntity<Course> one(@PathVariable Long id) {
        return service.find(id).map(ResponseEntity::ok).orElse(ResponseEntity.notFound().build());
    }

    @PutMapping("/{id}")
    public ResponseEntity<Course> update(@PathVariable Long id, @RequestBody Course course) {
        return service.update(id, course).map(ResponseEntity::ok).orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        return service.delete(id) ? ResponseEntity.noContent().build() : ResponseEntity.notFound().build();
    }
}
