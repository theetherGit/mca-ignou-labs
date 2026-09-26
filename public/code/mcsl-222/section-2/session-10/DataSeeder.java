// src/main/java/in/ignou/admission/security/DataSeeder.java   (Session 10, Q42: roles + one user per role)
package in.ignou.admission.security;

import java.util.Set;

import org.springframework.boot.CommandLineRunner;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

import in.ignou.admission.entity.Role;
import in.ignou.admission.entity.User;
import in.ignou.admission.repository.RoleRepository;
import in.ignou.admission.repository.UserRepository;

@Component
public class DataSeeder implements CommandLineRunner {

    private final UserRepository users;
    private final RoleRepository roles;
    private final PasswordEncoder encoder;

    public DataSeeder(UserRepository users, RoleRepository roles, PasswordEncoder encoder) {
        this.users = users;
        this.roles = roles;
        this.encoder = encoder;
    }

    @Override
    public void run(String... args) {
        Role admin = role("ROLE_ADMIN");
        Role student = role("ROLE_STUDENT");
        user("admin", "admin123", Set.of(admin, student));
        user("asha", "asha123", Set.of(student));
    }

    private Role role(String name) {
        return roles.findByName(name).orElseGet(() -> roles.save(new Role(name)));
    }

    private void user(String username, String rawPassword, Set<Role> userRoles) {
        if (users.existsByUsername(username)) {
            return;
        }
        User u = new User();
        u.setUsername(username);
        u.setPassword(encoder.encode(rawPassword));
        u.getRoles().addAll(userRoles);
        users.save(u);
        System.out.println("Seeded " + username + " with " + userRoles.size() + " role(s)");
    }
}
