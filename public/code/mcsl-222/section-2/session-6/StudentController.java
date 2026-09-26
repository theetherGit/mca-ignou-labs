package com.ignou.lab.admission.web;

import java.time.LocalDate;
import java.util.List;
import jakarta.validation.Valid;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import com.ignou.lab.admission.entity.Course;
import com.ignou.lab.admission.entity.Programme;
import com.ignou.lab.admission.entity.Student;
import com.ignou.lab.admission.repo.StudentRepository;

/** Replaces Session 5's AdmissionController: create, read, update, delete and batch approve. */
@Controller
@RequestMapping("/students")
public class StudentController {

    private final StudentRepository repo;

    public StudentController(StudentRepository repo) {
        this.repo = repo;
    }

    @ModelAttribute("programmes")
    public List<Programme> programmes() {
        return repo.programmes();
    }

    @ModelAttribute("courseList")
    public List<Course> courseList() {
        return repo.courses();
    }

    @ModelAttribute("today")
    public LocalDate today() {
        return LocalDate.now();
    }

    // Read
    @GetMapping
    public String list(Model model) {
        model.addAttribute("students", repo.findAll());
        return "students";
    }

    // Create (form)
    @GetMapping("/new")
    public String createForm(Model model) {
        model.addAttribute("admission", new AdmissionForm());
        return "student-form";
    }

    // Update (form)
    @GetMapping("/{id}/edit")
    public String editForm(@PathVariable Long id, Model model) {
        model.addAttribute("admission", repo.formFor(id));
        return "student-form";
    }

    // Create or Update (submit)
    @PostMapping("/save")
    public String save(@Valid @ModelAttribute("admission") AdmissionForm form,
                       BindingResult result, RedirectAttributes redirect) {
        if (result.hasErrors()) {
            return "student-form";
        }
        Student saved = repo.save(form);
        redirect.addFlashAttribute("message", "Saved " + saved.getName() + " (id " + saved.getId() + ")");
        return "redirect:/students"; // POST-redirect-GET: refresh does not resubmit
    }

    // Delete
    @PostMapping("/{id}/delete")
    public String delete(@PathVariable Long id, RedirectAttributes redirect) {
        repo.delete(id);
        redirect.addFlashAttribute("message", "Deleted student " + id);
        return "redirect:/students";
    }

    // Q28: batch approval of the ticked rows
    @PostMapping("/approve")
    public String approve(@RequestParam(name = "ids", required = false) List<Long> ids,
                          RedirectAttributes redirect) {
        int n = ids == null ? 0 : repo.approve(ids);
        redirect.addFlashAttribute("message", n + " application(s) approved in one transaction");
        return "redirect:/students";
    }
}
