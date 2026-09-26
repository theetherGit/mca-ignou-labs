// src/main/java/in/ignou/admission/security/AppUserDetailsService.java   (Session 9, Q37)
package in.ignou.admission.security;

import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import in.ignou.admission.entity.User;
import in.ignou.admission.repository.UserRepository;

/**
 * The bridge between the users table and Spring Security. The framework calls
 * loadUserByUsername at login, then compares the submitted password with the
 * stored hash through the PasswordEncoder bean.
 */
@Service
public class AppUserDetailsService implements UserDetailsService {

    private final UserRepository users;

    public AppUserDetailsService(UserRepository users) {
        this.users = users;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        User u = users.findByUsername(username)
                .orElseThrow(() -> new UsernameNotFoundException("No user: " + username));
        // Spring's own User class (org.springframework.security.core.userdetails.User)
        return org.springframework.security.core.userdetails.User.withUsername(u.getUsername())
                .password(u.getPassword())      // already BCrypt-hashed
                .disabled(!u.isEnabled())
                .roles("USER")                  // Session 10 replaces this with roles from the DB
                .build();
    }
}
