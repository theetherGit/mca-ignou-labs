// src/main/java/in/ignou/admission/web/PageController.java   (Session 10: Q44 dashboard details, Q43 admin page)
package in.ignou.admission.web;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.stream.Collectors;

import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import in.ignou.admission.repository.UserRepository;
import jakarta.servlet.http.HttpServletRequest;

@Controller
public class PageController {

    private static final DateTimeFormatter FMT = DateTimeFormatter.ofPattern("dd-MM-yyyy HH:mm:ss");

    private final UserRepository users;

    public PageController(UserRepository users) {
        this.users = users;
    }

    @GetMapping("/login")
    public String login() {
        return "login";
    }

    /** Q44: Spring injects the current Authentication as a handler-method argument. */
    @GetMapping({"/", "/dashboard"})
    public String dashboard(Authentication auth, HttpServletRequest request, Model model) {
        model.addAttribute("username", auth.getName());
        model.addAttribute("roles", auth.getAuthorities().stream()
                .map(GrantedAuthority::getAuthority)
                .collect(Collectors.joining(", ")));
        // ponytail: behind a proxy read the X-Forwarded-For header instead
        model.addAttribute("clientIp", request.getRemoteAddr());
        model.addAttribute("serverTime", LocalDateTime.now().format(FMT));
        model.addAttribute("sessionId", request.getSession().getId());
        return "dashboard";
    }

    /** Q43: reachable only with ROLE_ADMIN (rule in SecurityConfig). */
    @GetMapping("/admin/users")
    public String adminUsers(Model model) {
        model.addAttribute("users", users.findAll());
        return "admin";
    }
}
