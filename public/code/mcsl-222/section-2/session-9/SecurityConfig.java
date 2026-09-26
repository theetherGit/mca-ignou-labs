// src/main/java/in/ignou/admission/security/SecurityConfig.java   (Session 9: Q37 encoder, Q38 login page, Q39 logout)
package in.ignou.admission.security;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.config.Customizer;
import org.springframework.security.config.annotation.authentication.configuration.AuthenticationConfiguration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;

@Configuration
@EnableWebSecurity
public class SecurityConfig {

    /** Q37: BCrypt with a random salt per password; strength 10 (default) = 2^10 rounds. */
    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    /** Q40 uses this to log the new user in programmatically. */
    @Bean
    public AuthenticationManager authenticationManager(AuthenticationConfiguration config) throws Exception {
        return config.getAuthenticationManager();
    }

    @Bean
    public SecurityFilterChain filterChain(HttpSecurity http) throws Exception {
        http
            .authorizeHttpRequests(auth -> auth
                .requestMatchers("/login", "/register", "/css/**", "/actuator/health").permitAll()
                .anyRequest().authenticated())
            // Q38: our own page at GET /login; the POST /login handler is still Spring's
            .formLogin(form -> form
                .loginPage("/login")
                .defaultSuccessUrl("/dashboard", true)
                .permitAll())
            // Q39: POST /logout ends the session and returns to the login page
            .logout(logout -> logout
                .logoutUrl("/logout")
                .logoutSuccessUrl("/login?logout")
                .invalidateHttpSession(true)
                .deleteCookies("JSESSIONID")
                .permitAll())
            // lets curl -u user:pass call /api/** (browser still uses the form)
            .httpBasic(Customizer.withDefaults())
            // the JSON API is called by curl/Postman, not from a browser session: no CSRF token there
            .csrf(csrf -> csrf.ignoringRequestMatchers("/api/**", "/xml/**", "/actuator/**"));
        return http.build();
    }
}
