package com.ignou.lab.admission.ioc;

import java.util.concurrent.ThreadLocalRandom;
import org.springframework.stereotype.Service;

@Service
public class RandomCourseService implements CourseService {

    private static final String[] COURSES = {
        "MCS-218 Data Communication and Computer Networks",
        "MCS-219 Object Oriented Analysis and Design",
        "MCS-220 Web Technologies"
    };

    @Override
    public String getRandom() {
        return COURSES[ThreadLocalRandom.current().nextInt(COURSES.length)];
    }
}
