package com.ignou.lab.admission.ioc;

import org.springframework.stereotype.Component;

/** Session 4 version: the favourite course now comes from an injected CourseService. */
@Component
public class JavaTeacher implements Teacher {

    private final CourseService courseService;

    public JavaTeacher(CourseService courseService) { // constructor injection
        this.courseService = courseService;
    }

    @Override
    public String getName() {
        return "Dr. Rao";
    }

    @Override
    public String getFavouriteCourse() {
        return courseService.getRandom();
    }
}
