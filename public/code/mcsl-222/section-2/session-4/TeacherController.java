package com.ignou.lab.admission.web;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import com.ignou.lab.admission.ioc.Teacher;

@Controller
public class TeacherController {

    private final Teacher teacher; // JavaTeacher, found by the component scan

    public TeacherController(Teacher teacher) {
        this.teacher = teacher;
    }

    @GetMapping("/teacher")
    public String show(Model model) {
        model.addAttribute("teacherName", teacher.getName());
        model.addAttribute("course", teacher.getFavouriteCourse());
        return "teacher";
    }
}
