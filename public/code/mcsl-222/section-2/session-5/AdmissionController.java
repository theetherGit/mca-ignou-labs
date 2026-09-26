package com.ignou.lab.admission.web;

import java.time.LocalDate;
import java.util.List;
import jakarta.validation.Valid;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import com.ignou.lab.admission.entity.Student;
import com.ignou.lab.admission.repo.StudentRepository;

@Controller
public class AdmissionController {

    private static final List<String> PROGRAMMES = List.of("MCA", "BCA", "PGDCA");
    private static final List<String> COURSES = List.of(
            "MCS-218 Data Communication and Computer Networks",
            "MCS-219 Object Oriented Analysis and Design",
            "MCS-220 Web Technologies",
            "MCS-221 Data Warehousing and Data Mining");

    private final StudentRepository repo;

    public AdmissionController(StudentRepository repo) {
        this.repo = repo;
    }

    @ModelAttribute("programmes")
    public List<String> programmes() {
        return PROGRAMMES;
    }

    @ModelAttribute("courseList")
    public List<String> courseList() {
        return COURSES;
    }

    /** used by the date picker's max attribute (client-side @Past) */
    @ModelAttribute("today")
    public LocalDate today() {
        return LocalDate.now();
    }

    @GetMapping("/admission")
    public String showForm(Model model) {
        model.addAttribute("admission", new AdmissionForm());
        return "admission-form";
    }

    @PostMapping("/admission")
    public String submit(@Valid @ModelAttribute("admission") AdmissionForm form,
                         BindingResult result, Model model) {
        if (result.hasErrors()) {
            return "admission-form"; // re-render with form:errors filled in; user input is kept
        }
        Student saved = repo.save(form.toStudent()); // Q22: form object -> entity bean -> database
        model.addAttribute("student", saved);
        return "admission-result";
    }
}
