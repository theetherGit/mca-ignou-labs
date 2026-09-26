package com.ignou.lab.admission.repo;

import java.time.Year;
import java.util.List;
import java.util.NoSuchElementException;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;
import com.ignou.lab.admission.entity.AdmissionStatus.Status;
import com.ignou.lab.admission.entity.Course;
import com.ignou.lab.admission.entity.Programme;
import com.ignou.lab.admission.entity.Student;
import com.ignou.lab.admission.entity.StudentCourse;
import com.ignou.lab.admission.web.AdmissionForm;

/** Every public method runs in one transaction; commit happens when it returns. */
@Repository
@Transactional
public class StudentRepository {

    @PersistenceContext
    private EntityManager em;

    // ---- lookups for the form ----

    public List<Programme> programmes() {
        return em.createQuery("from Programme p order by p.code", Programme.class).getResultList();
    }

    public List<Course> courses() {
        return em.createQuery("from Course c order by c.code", Course.class).getResultList();
    }

    // ---- Read ----

    @Transactional(readOnly = true)
    public List<Student> findAll() {
        // join fetch: programme and courses are loaded now, so the JSP never touches a closed session
        return em.createQuery(
                "select distinct s from Student s join fetch s.programme"
                + " left join fetch s.courses sc left join fetch sc.course order by s.id",
                Student.class).getResultList();
    }

    public Student find(Long id) {
        Student s = em.find(Student.class, id);
        if (s == null) {
            throw new NoSuchElementException("No student with id " + id); // ponytail: 500 page is fine for the lab
        }
        return s;
    }

    /** the edit page needs the form filled from a managed entity (courses are lazy) */
    @Transactional(readOnly = true)
    public AdmissionForm formFor(Long id) {
        return AdmissionForm.from(find(id));
    }

    // ---- Create / Update ----

    public Student save(AdmissionForm f) {
        Student s = f.getId() == null ? new Student() : find(f.getId());
        s.setName(f.getName());
        s.setEmail(f.getEmail());
        s.setMobile(f.getMobile());
        s.setDob(f.getDob());
        s.setAddress(f.getAddress());
        s.setHostelRequired(f.getHostelRequired());
        s.setProgramme(em.getReference(Programme.class, f.getProgrammeId())); // no SELECT, just the FK
        s.getCourses().clear();                                                // orphanRemoval deletes the old rows
        for (Long courseId : f.getCourseIds()) {
            s.getCourses().add(new StudentCourse(s, em.getReference(Course.class, courseId)));
        }
        if (s.getId() == null) {
            s.changeStatus(Status.PENDING, "Application received");
            em.persist(s);                                                    // INSERT student + student_course + admission_status
        }                                                                     // managed entity: UPDATE happens on commit
        return s;
    }

    // ---- Delete ----

    public void delete(Long id) {
        em.remove(find(id)); // cascades to student_course and admission_status
    }

    // ---- Q28: batch approval ----

    /** Approves every pending id in ONE transaction; UPDATEs go to MySQL in batches of 20. */
    public int approve(List<Long> ids) {
        int approved = 0;
        for (Long id : ids) {
            Student s = find(id);
            if (s.getStatus() != Status.PENDING) {
                continue;
            }
            s.setEnrolmentNo(String.format("%d%06d", Year.now().getValue(), id)); // e.g. 2026000007
            s.changeStatus(Status.APPROVED, "Approved in batch");
            if (++approved % 20 == 0) {
                em.flush(); // push this batch of UPDATE/INSERT statements
                em.clear(); // drop them from memory before loading the next 20
            }
        }
        return approved; // commit flushes whatever is left
    }
}
