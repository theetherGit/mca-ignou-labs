package com.ignou.lab.admission.ioc;

import org.springframework.stereotype.Component;

/** New implementation of Teacher. The container creates it; nobody calls new. */
@Component
public class JavaTeacher implements Teacher {

    @Override
    public String getName() {
        return "Dr. Rao";
    }

    @Override
    public String getFavouriteCourse() {
        return "MCS-220 Web Technologies";
    }
}
