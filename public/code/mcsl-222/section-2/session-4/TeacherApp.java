package com.ignou.lab.admission.ioc;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class TeacherApp {

    public static void main(String[] args) {
        try (var ctx = new AnnotationConfigApplicationContext(JavaTeacher.class, RandomCourseService.class)) {
            Teacher teacher = ctx.getBean(Teacher.class);
            for (int i = 1; i <= 5; i++) {
                System.out.println(i + ". " + teacher.getName() + " prefers " + teacher.getFavouriteCourse());
            }
        }
    }
}
