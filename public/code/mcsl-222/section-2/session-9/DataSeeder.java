// src/main/java/in/ignou/admission/security/DataSeeder.java   (Session 9, Q37: first login account)
package in.ignou.admission.security;

import org.springframework.boot.CommandLineRunner;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

import in.ignou.admission.entity.User;
import in.ignou.admission.repository.UserRepository;

/** Runs once after start-up. Hashes the password in Java, so no hash needs to be pasted into SQL. */
@Component
public class DataSeeder implements CommandLineRunner {

    private final UserRepository users;
    private final PasswordEncoder encoder;

    public DataSeeder(UserRepository users, PasswordEncoder encoder) {
        this.users = users;
        this.encoder = encoder;
    }

    @Override
    public void run(String... args) {
        if (users.existsByUsername("admin")) {
            return;
        }
        User admin = new User();
        admin.setUsername("admin");
        admin.setPassword(encoder.encode("admin123"));
        users.save(admin);
        System.out.println("Seeded user admin / admin123");
    }
}
