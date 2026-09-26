// src/main/java/in/ignou/admission/web/PageController.java   (Session 9, Q38)
package in.ignou.admission.web;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

/** Plain @Controller: return values are Thymeleaf template names under src/main/resources/templates. */
@Controller
public class PageController {

    @GetMapping("/login")
    public String login() {
        return "login";        // templates/login.html
    }

    @GetMapping({"/", "/dashboard"})
    public String dashboard() {
        return "dashboard";    // templates/dashboard.html
    }
}
