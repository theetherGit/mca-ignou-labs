package com.ignou.lab.admission.ioc;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class TeacherApp {

    public static void main(String[] args) {
        try (var ctx = new AnnotationConfigApplicationContext(JavaTeacher.class)) {
            Teacher teacher = ctx.getBean(Teacher.class); // asked for by interface, not by class
            System.out.println("Bean class : " + teacher.getClass().getSimpleName());
            System.out.println(teacher.getName() + " prefers " + teacher.getFavouriteCourse());
        }
    }
}
