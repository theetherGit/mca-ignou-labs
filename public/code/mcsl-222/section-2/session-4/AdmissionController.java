package com.ignou.lab.admission.web;

import java.util.List;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class AdmissionController {

    // ponytail: fixed lists; Session 6 reads programmes and courses from the database
    private static final List<String> PROGRAMMES = List.of("MCA", "BCA", "PGDCA");
    private static final List<String> COURSES = List.of(
            "MCS-218 Data Communication and Computer Networks",
            "MCS-219 Object Oriented Analysis and Design",
            "MCS-220 Web Technologies",
            "MCS-221 Data Warehousing and Data Mining");

    @ModelAttribute("programmes")
    public List<String> programmes() {
        return PROGRAMMES;
    }

    @ModelAttribute("courseList")
    public List<String> courseList() {
        return COURSES;
    }

    @GetMapping("/admission")
    public String showForm(Model model) {
        model.addAttribute("admission", new AdmissionForm()); // empty object the form tags bind to
        return "admission-form";
    }

    @PostMapping("/admission")
    public String submit(@ModelAttribute("admission") AdmissionForm form) {
        return "admission-result"; // "admission" is already in the model
    }
}
