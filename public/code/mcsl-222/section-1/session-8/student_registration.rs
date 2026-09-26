// student_registration.rs -- MCSL-222 Session 8, Q19
// Figure 1.15 (Student Registration) in Rust 2021, standard library only.
// Ownership: every object is an Rc<RefCell<T>>; an association end is an Rc clone (Weak for the School back link inside Programme, so the 1..* to 1..* link is not an Rc cycle).
// Build: rustc -O --edition 2021 student_registration.rs && ./student_registration
//
// Mapping used throughout:
//   class            -> struct + impl
//   attribute        -> pub field (same name as the figure)
//   operation        -> method or associated function (same name as the figure)
//   association end  -> Option<Rc<..>> for 1 / 0..1, Vec<Rc<..>> for * / 1..*
#![allow(non_snake_case)] // attribute and operation names are kept exactly as in the figure
#![allow(dead_code)] // Course.programmes is an association end main fills but never reads

use std::cell::RefCell;
use std::rc::{Rc, Weak};

type Ref<T> = Rc<RefCell<T>>;

fn new_ref<T>(x: T) -> Ref<T> {
    Rc::new(RefCell::new(x))
}

// Removes one link from an association vector. Every remove* operation uses it.
fn unlink<T>(v: &mut Vec<Ref<T>>, p: &Ref<T>) {
    v.retain(|x| !Rc::ptr_eq(x, p));
}

// ---------------------------------------------------------------- Course
struct Course {
    courseCode: String,
    courseName: String,
    programmes: Vec<Ref<Programme>>, // Course (1) <>-- (*) Programme, as drawn
}

thread_local! {
    // The four operations in the figure manage the list of courses, so they
    // work on one shared catalogue: the C++ static member is a thread-local static here.
    static CATALOGUE: RefCell<Vec<Ref<Course>>> = RefCell::new(Vec::new());
}

impl Course {
    fn new(code: &str, name: &str) -> Ref<Course> {
        new_ref(Course { courseCode: code.into(), courseName: name.into(), programmes: Vec::new() })
    }
    fn addCourse(c: &Ref<Course>) {
        CATALOGUE.with(|cat| cat.borrow_mut().push(Rc::clone(c)));
    }
    fn removeCourse(c: &Ref<Course>) {
        CATALOGUE.with(|cat| unlink(&mut cat.borrow_mut(), c));
    }
    fn getCoursebyName(name: &str) -> Option<Ref<Course>> {
        CATALOGUE.with(|cat| cat.borrow().iter().find(|c| c.borrow().courseName == name).cloned())
    }
    fn getCoursebyCode(code: &str) -> Option<Ref<Course>> {
        CATALOGUE.with(|cat| cat.borrow().iter().find(|c| c.borrow().courseCode == code).cloned())
    }
    fn catalogueSize() -> usize {
        CATALOGUE.with(|cat| cat.borrow().len())
    }
}

// ------------------------------------------------------------- Programme
struct Programme {
    programID: String,
    ProgramName: String,
    schools: Vec<Weak<RefCell<School>>>, // School (1..*) --- (1..*) Programme, back end
}

impl Programme {
    fn new(id: &str, name: &str) -> Ref<Programme> {
        new_ref(Programme { programID: id.into(), ProgramName: name.into(), schools: Vec::new() })
    }
}

// --------------------------------------------------------------- Faculty
struct Faculty {
    facultyID: String,
    facultyName: String,
    schoolName: String,
    hod: Option<Ref<Faculty>>, // HOD 0..1 (reflexive association)
    courses: Vec<Ref<Course>>, // Teaches: Faculty (1..*) --> Course
}

impl Faculty {
    fn new(id: &str, name: &str) -> Ref<Faculty> {
        new_ref(Faculty {
            facultyID: id.into(),
            facultyName: name.into(),
            schoolName: String::new(),
            hod: None,
            courses: Vec::new(),
        })
    }
    fn teaches(&mut self, c: &Ref<Course>) {
        self.courses.push(Rc::clone(c));
    }
}

// ---------------------------------------------------------------- School
struct School {
    name: String,
    faculties: Vec<Ref<Faculty>>,    // AssignTo: School (1) <>-- (1..*) Faculty
    programmes: Vec<Ref<Programme>>, // School (1..*) --- (1..*) Programme
}

impl School {
    fn new(n: &str) -> Ref<School> {
        new_ref(School { name: n.into(), faculties: Vec::new(), programmes: Vec::new() })
    }
    fn addFaculty(&mut self, f: &Ref<Faculty>) {
        self.faculties.push(Rc::clone(f));
        f.borrow_mut().schoolName = self.name.clone(); // the figure keeps the school name inside Faculty
    }
    fn removeFaculty(&mut self, f: &Ref<Faculty>) {
        unlink(&mut self.faculties, f);
        f.borrow_mut().schoolName.clear();
    }
    // Both ends are 1..*, so update both. The back link needs this school's Rc,
    // which a &self method cannot reach, so these two take it as a parameter.
    fn addProgramme(this: &Ref<School>, p: &Ref<Programme>) {
        this.borrow_mut().programmes.push(Rc::clone(p));
        p.borrow_mut().schools.push(Rc::downgrade(this));
    }
    fn removeProgramme(this: &Ref<School>, p: &Ref<Programme>) {
        unlink(&mut this.borrow_mut().programmes, p);
        let me = Rc::downgrade(this);
        p.borrow_mut().schools.retain(|w| !Weak::ptr_eq(w, &me));
    }
}

// --------------------------------------------------------------- Student
struct Student {
    stuID: i32,
    name: String,
    address: String,
    programme: Option<Ref<Programme>>, // enrol: Student --> Programme
}

impl Student {
    fn new(id: i32, n: &str, addr: &str) -> Ref<Student> {
        new_ref(Student { stuID: id, name: n.into(), address: addr.into(), programme: None })
    }
    // Constraint {one student per programme}: a registration binds a student
    // to exactly one programme, so a second enrol() is refused.
    fn enrol(&mut self, p: &Ref<Programme>) -> bool {
        if let Some(cur) = &self.programme {
            println!(
                "  refused: {} is already enrolled in {} (one student per programme)",
                self.name,
                cur.borrow().ProgramName
            );
            return false;
        }
        self.programme = Some(Rc::clone(p));
        true
    }
}

// ------------------------------------------------------------ University
struct University {
    name: String,
    address: String,
    phone: i32,
    schools: Vec<Ref<School>>,   // has: University (1) <>-- (1..*) School
    students: Vec<Ref<Student>>, // registration: University (1) <>-- (*) Student
}

impl University {
    fn new(n: &str, addr: &str, ph: i32) -> University {
        University { name: n.into(), address: addr.into(), phone: ph, schools: Vec::new(), students: Vec::new() }
    }
    fn addSchool(&mut self, s: &Ref<School>) {
        self.schools.push(Rc::clone(s));
    }
    fn removeSchool(&mut self, s: &Ref<School>) {
        unlink(&mut self.schools, s);
    }
    fn addStudent(&mut self, s: &Ref<Student>) {
        self.students.push(Rc::clone(s));
    }
    fn removeStudent(&mut self, s: &Ref<Student>) {
        unlink(&mut self.students, s);
    }
    fn getSchool(&self, n: &str) -> Option<Ref<School>> {
        self.schools.iter().find(|s| s.borrow().name == n).cloned()
    }
    fn getAllSchool(&self) -> &Vec<Ref<School>> {
        &self.schools
    }
    fn getStudent(&self, id: i32) -> Option<Ref<Student>> {
        self.students.iter().find(|s| s.borrow().stuID == id).cloned()
    }
}

// ------------------------------------------------------------------ main
fn print_university(u: &University) {
    println!("{}, {}, phone {}", u.name, u.address, u.phone);
    for s in u.getAllSchool() {
        let s = s.borrow();
        println!("  School: {}", s.name);
        for f in &s.faculties {
            let f = f.borrow();
            let hod = match &f.hod {
                Some(h) => format!(", HOD {}", h.borrow().facultyName),
                None => String::new(),
            };
            let mut line = format!(
                "    Faculty {} {} (school {}){} teaches",
                f.facultyID, f.facultyName, f.schoolName, hod
            );
            for c in &f.courses {
                line.push(' ');
                line.push_str(&c.borrow().courseCode);
            }
            println!("{}", line);
        }
        for p in &s.programmes {
            let p = p.borrow();
            println!("    Programme {} {}", p.programID, p.ProgramName);
        }
    }
    for st in &u.students {
        let st = st.borrow();
        let prog = match &st.programme {
            Some(p) => p.borrow().ProgramName.clone(),
            None => "not enrolled".to_string(),
        };
        println!("  Student {} {}, {} -> {}", st.stuID, st.name, st.address, prog);
    }
}

fn main() {
    let mut ignou = University::new("IGNOU", "Maidan Garhi, New Delhi", 29572514);

    // Two schools
    let socis = School::new("SOCIS");
    let soms = School::new("SOMS");
    ignou.addSchool(&socis);
    ignou.addSchool(&soms);

    // Faculties, with a HOD link inside SOCIS
    let f1 = Faculty::new("F01", "Dr. Sharma");
    let f2 = Faculty::new("F02", "Dr. Verma");
    let f3 = Faculty::new("F03", "Dr. Iyer");
    socis.borrow_mut().addFaculty(&f1);
    socis.borrow_mut().addFaculty(&f2);
    soms.borrow_mut().addFaculty(&f3);
    f2.borrow_mut().hod = Some(Rc::clone(&f1)); // HOD 0..1

    // Programmes
    let mca = Programme::new("MCA", "Master of Computer Applications");
    let mba = Programme::new("MBA", "Master of Business Administration");
    School::addProgramme(&socis, &mca);
    School::addProgramme(&soms, &mba);

    // Courses and the catalogue operations
    let c1 = Course::new("MCS-217", "Software Engineering");
    let c2 = Course::new("MCSL-222", "OOAD and Web Technologies Lab");
    let c3 = Course::new("MMPC-001", "Management Concepts");
    Course::addCourse(&c1);
    Course::addCourse(&c2);
    Course::addCourse(&c3);
    c1.borrow_mut().programmes.push(Rc::clone(&mca)); // Course (1) <>-- (*) Programme
    c2.borrow_mut().programmes.push(Rc::clone(&mca));
    c3.borrow_mut().programmes.push(Rc::clone(&mba));
    f1.borrow_mut().teaches(&c1);
    f2.borrow_mut().teaches(&c2);
    f3.borrow_mut().teaches(&c3);

    // Students and registration
    let s1 = Student::new(2401, "Asha", "Jaipur");
    let s2 = Student::new(2402, "Ravi", "Pune");
    ignou.addStudent(&s1);
    ignou.addStudent(&s2);
    s1.borrow_mut().enrol(&mca);
    s2.borrow_mut().enrol(&mba);

    println!("--- after setup ---");
    print_university(&ignou);

    println!("--- constraint check ---");
    s1.borrow_mut().enrol(&mba); // refused: already in MCA

    println!("--- lookups ---");
    let soms_found = ignou.getSchool("SOMS").unwrap();
    println!("getSchool(\"SOMS\") -> {}", soms_found.borrow().name);
    // "nullptr" is printed for a miss so the output matches the C++ version.
    println!("getSchool(\"SOL\") -> {}", if ignou.getSchool("SOL").is_some() { "found" } else { "nullptr" });
    let ravi = ignou.getStudent(2402).unwrap();
    println!("getStudent(2402) -> {}", ravi.borrow().name);
    let by_code = Course::getCoursebyCode("MCSL-222").unwrap();
    println!("getCoursebyCode(\"MCSL-222\") -> {}", by_code.borrow().courseName);
    let by_name = Course::getCoursebyName("Management Concepts").unwrap();
    println!("getCoursebyName(\"Management Concepts\") -> {}", by_name.borrow().courseCode);
    println!("catalogue size: {}", Course::catalogueSize());

    println!("--- removals ---");
    Course::removeCourse(&c3);
    socis.borrow_mut().removeFaculty(&f2);
    School::removeProgramme(&soms, &mba);
    ignou.removeStudent(&s2);
    ignou.removeSchool(&soms);
    println!(
        "catalogue size: {}, f2.schoolName is \"{}\", mba.schools.size() = {}",
        Course::catalogueSize(),
        f2.borrow().schoolName,
        mba.borrow().schools.len()
    );
    print_university(&ignou);
}
