package com.ignou.lab.admission;

import java.util.List;
import java.util.stream.Collectors;
import jakarta.persistence.EntityManagerFactory;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import com.ignou.lab.admission.entity.Student;

/**
 * Q26: read students with the Hibernate Session API and print them on the console.
 * Run: mvn -q compile exec:java -Dexec.mainClass=com.ignou.lab.admission.ConsoleApp
 */
public class ConsoleApp {

    public static void main(String[] args) {
        try (var ctx = new AnnotationConfigApplicationContext(JpaConfig.class)) {
            SessionFactory sessionFactory = ctx.getBean(EntityManagerFactory.class).unwrap(SessionFactory.class);
            try (Session session = sessionFactory.openSession()) {
                List<Student> students = session.createQuery(
                        "select distinct s from Student s join fetch s.programme"
                        + " left join fetch s.courses sc left join fetch sc.course order by s.id",
                        Student.class).getResultList();

                System.out.printf("%-4s %-11s %-18s %-5s %-9s %s%n",
                        "ID", "ENROLMENT", "NAME", "PROG", "STATUS", "COURSES");
                for (Student s : students) {
                    String courses = s.getCourses().stream()
                            .map(sc -> sc.getCourse().getCode())
                            .collect(Collectors.joining(","));
                    System.out.printf("%-4d %-11s %-18s %-5s %-9s %s%n",
                            s.getId(), s.getEnrolmentNo() == null ? "-" : s.getEnrolmentNo(),
                            s.getName(), s.getProgramme().getCode(), s.getStatus(), courses);
                }
                System.out.println(students.size() + " student(s)");
            }
        }
    }
}
