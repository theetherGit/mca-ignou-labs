// src/main/java/in/ignou/admission/AdmissionApiApplication.java   (Session 8: + @ImportResource)
package in.ignou.admission;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ImportResource;

@SpringBootApplication
@ImportResource("classpath:beans.xml")   // Q35: load the XML-defined beans into the same context
public class AdmissionApiApplication {

    public static void main(String[] args) {
        SpringApplication.run(AdmissionApiApplication.class, args);
    }
}
