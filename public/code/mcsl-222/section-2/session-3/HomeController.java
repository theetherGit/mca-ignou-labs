package com.ignou.lab.admission.web;

import java.time.LocalDateTime;
import org.springframework.core.SpringVersion;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class HomeController {

    @GetMapping("/")
    public String home(Model model) {
        model.addAttribute("springVersion", SpringVersion.getVersion());
        model.addAttribute("now", LocalDateTime.now());
        return "home";
    }
}
