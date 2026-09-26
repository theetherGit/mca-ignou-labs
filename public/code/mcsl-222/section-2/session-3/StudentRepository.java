package com.ignou.lab.admission.repo;

import java.util.List;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;
import com.ignou.lab.admission.entity.Student;

@Repository
@Transactional
public class StudentRepository {

    @PersistenceContext
    private EntityManager em;

    @Transactional(readOnly = true)
    public List<Student> findAll() {
        return em.createQuery("from Student s order by s.id", Student.class).getResultList();
    }
}
