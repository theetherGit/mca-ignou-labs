// src/main/java/in/ignou/admission/web/RegistrationController.java   (Session 9, Q40)
package in.ignou.admission.web;

import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContext;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.context.HttpSessionSecurityContextRepository;
import org.springframework.security.web.context.SecurityContextRepository;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

import in.ignou.admission.entity.User;
import in.ignou.admission.repository.UserRepository;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.validation.Valid;

@Controller
public class RegistrationController {

    private final UserRepository users;
    private final PasswordEncoder encoder;
    private final AuthenticationManager authenticationManager;
    // saves the SecurityContext into the HTTP session so the next request is still logged in
    private final SecurityContextRepository contextRepository = new HttpSessionSecurityContextRepository();

    public RegistrationController(UserRepository users, PasswordEncoder encoder,
                                  AuthenticationManager authenticationManager) {
        this.users = users;
        this.encoder = encoder;
        this.authenticationManager = authenticationManager;
    }

    @GetMapping("/register")
    public String form(@ModelAttribute("form") RegistrationForm form) {
        return "register";
    }

    /**
     * @Valid runs the annotations on RegistrationForm; BindingResult must be the very next
     * parameter, otherwise Spring throws instead of letting us re-show the form.
     */
    @PostMapping("/register")
    public String register(@Valid @ModelAttribute("form") RegistrationForm form, BindingResult result,
                           HttpServletRequest request, HttpServletResponse response) {
        if (!result.hasFieldErrors("confirmPassword") && !form.getPassword().equals(form.getConfirmPassword())) {
            result.rejectValue("confirmPassword", "mismatch", "Passwords do not match");
        }
        if (!result.hasFieldErrors("username") && users.existsByUsername(form.getUsername())) {
            result.rejectValue("username", "taken", "Username is already taken");
        }
        if (result.hasErrors()) {
            return "register";                       // re-render with th:errors messages
        }

        User user = new User();
        user.setUsername(form.getUsername());
        user.setPassword(encoder.encode(form.getPassword()));
        users.save(user);

        // --- auto-login: the same path the login form takes, done in code ---
        Authentication auth = authenticationManager.authenticate(
                UsernamePasswordAuthenticationToken.unauthenticated(form.getUsername(), form.getPassword()));
        SecurityContext context = SecurityContextHolder.createEmptyContext();
        context.setAuthentication(auth);
        SecurityContextHolder.setContext(context);            // current thread
        contextRepository.saveContext(context, request, response);   // HTTP session

        return "redirect:/dashboard";
    }
}
