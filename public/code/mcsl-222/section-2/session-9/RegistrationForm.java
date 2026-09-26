// src/main/java/in/ignou/admission/web/RegistrationForm.java   (Session 9, Q40)
package in.ignou.admission.web;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;

/** Form-backing object. Not an entity: it carries confirmPassword, which is never stored. */
public class RegistrationForm {

    @NotBlank(message = "Username is required")
    @Size(min = 4, max = 50, message = "Username must be 4 to 50 characters")
    @Pattern(regexp = "[a-zA-Z0-9_]+", message = "Letters, digits and underscore only")
    private String username;

    @NotBlank(message = "Password is required")
    @Size(min = 6, max = 40, message = "Password must be 6 to 40 characters")
    private String password;

    @NotBlank(message = "Confirm the password")
    private String confirmPassword;

    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }
    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }
    public String getConfirmPassword() { return confirmPassword; }
    public void setConfirmPassword(String confirmPassword) { this.confirmPassword = confirmPassword; }
}
