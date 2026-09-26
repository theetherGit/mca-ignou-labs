package com.ignou.lab.admission.ioc;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.stereotype.Component;

// ponytail: three small classes in one file so the whole DI example is one listing

/** What AdmissionDesk depends on. It never knows which implementation it gets. */
interface FeeCalculator {
    int feeFor(String programme);
}

@Component
class FlatFeeCalculator implements FeeCalculator {
    @Override
    public int feeFor(String programme) {
        return programme.equals("MCA") ? 12000 : 8000;
    }
}

/** Constructor injection: Spring passes the FeeCalculator in; the field is final. */
@Component
class AdmissionDesk {
    private final FeeCalculator fees;

    AdmissionDesk(FeeCalculator fees) {
        this.fees = fees;
    }

    String quote(String programme) {
        return programme + " fee per semester: Rs " + fees.feeFor(programme);
    }
}

public class DiApp {
    public static void main(String[] args) {
        try (var ctx = new AnnotationConfigApplicationContext(FlatFeeCalculator.class, AdmissionDesk.class)) {
            AdmissionDesk desk = ctx.getBean(AdmissionDesk.class);
            System.out.println(desk.quote("MCA"));
            System.out.println(desk.quote("BCA"));
        }
    }
}
