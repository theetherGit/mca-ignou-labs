// src/main/java/in/ignou/admission/AdmissionApiApplication.java
package in.ignou.admission;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * Entry point. @SpringBootApplication = @Configuration + @EnableAutoConfiguration
 * + @ComponentScan of the package in.ignou.admission and everything below it.
 */
@SpringBootApplication
public class AdmissionApiApplication {

    public static void main(String[] args) {
        SpringApplication.run(AdmissionApiApplication.class, args);
    }
}
