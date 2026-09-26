// src/main/java/in/ignou/xmlapi/CourseService.java   (Session 8, Q35)
// NOTE the package: in.ignou.xmlapi is OUTSIDE in.ignou.admission, so component scanning
// never sees these classes. Only beans.xml creates them.
package in.ignou.xmlapi;

import java.util.List;
import java.util.Optional;

import in.ignou.admission.entity.Course;
import in.ignou.admission.repository.CourseRepository;

/** Plain class: no @Service, no @Autowired. beans.xml supplies the repository through the constructor. */
public class CourseService {

    private final CourseRepository courses;

    public CourseService(CourseRepository courses) {
        this.courses = courses;
    }

    public Course create(Course c) {
        c.setId(null);
        return courses.save(c);
    }

    public List<Course> all() {
        return courses.findAll();
    }

    public Optional<Course> find(Long id) {
        return courses.findById(id);
    }

    public Optional<Course> update(Long id, Course in) {
        return courses.findById(id).map(c -> {
            c.setCode(in.getCode());
            c.setTitle(in.getTitle());
            c.setCredits(in.getCredits());
            c.setProgramme(in.getProgramme());
            return courses.save(c);
        });
    }

    public boolean delete(Long id) {
        if (!courses.existsById(id)) {
            return false;
        }
        courses.deleteById(id);
        return true;
    }
}
