package com.ignou.lab.admission.web;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import com.ignou.lab.admission.repo.StudentRepository;

@Controller
public class StudentController {

    private final StudentRepository repo;

    public StudentController(StudentRepository repo) {
        this.repo = repo;
    }

    @GetMapping("/students")
    public String list(Model model) {
        model.addAttribute("students", repo.findAll());
        return "students";
    }
}
