// student_registration.cpp -- MCSL-222 Session 8, Q19
// Figure 1.15 (Student Registration) implemented in C++17.
// Build: clang++ -std=c++17 -Wall -Wextra -o student_registration student_registration.cpp
//
// Mapping used throughout:
//   class            -> class
//   attribute        -> public data member (same name as the figure)
//   operation        -> member function (same name as the figure)
//   association end  -> pointer for 1 / 0..1, std::vector of pointers for * / 1..*
// Objects are created in main and never deleted here; the pointers are links only.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class School;
class Faculty;
class Programme;
class Course;
class Student;

// Removes one link from an association vector. Every remove* operation uses it.
template <class T>
static void unlink(std::vector<T*>& v, T* p) {
    v.erase(std::remove(v.begin(), v.end(), p), v.end());
}

// ---------------------------------------------------------------- Course
class Course {
public:
    std::string courseCode;
    std::string courseName;
    std::vector<Programme*> programmes;  // Course (1) <>-- (*) Programme, as drawn

    Course(std::string code, std::string name)
        : courseCode(std::move(code)), courseName(std::move(name)) {}

    // The four operations in the figure manage the list of courses, so they
    // work on one shared catalogue rather than on a single Course object.
    inline static std::vector<Course*> catalogue;

    static void addCourse(Course& c) { catalogue.push_back(&c); }
    static void removeCourse(Course& c) { unlink(catalogue, &c); }
    static Course* getCoursebyName(const std::string& name) {
        for (Course* c : catalogue)
            if (c->courseName == name) return c;
        return nullptr;
    }
    static Course* getCoursebyCode(const std::string& code) {
        for (Course* c : catalogue)
            if (c->courseCode == code) return c;
        return nullptr;
    }
};

// ------------------------------------------------------------- Programme
class Programme {
public:
    std::string programID;
    std::string ProgramName;
    std::vector<School*> schools;  // School (1..*) --- (1..*) Programme

    Programme(std::string id, std::string name)
        : programID(std::move(id)), ProgramName(std::move(name)) {}
};

// --------------------------------------------------------------- Faculty
class Faculty {
public:
    std::string facultyID;
    std::string facultyName;
    std::string schoolName;
    Faculty* hod = nullptr;         // HOD 0..1 (reflexive association)
    std::vector<Course*> courses;   // Teaches: Faculty (1..*) --> Course

    Faculty(std::string id, std::string name)
        : facultyID(std::move(id)), facultyName(std::move(name)) {}

    void teaches(Course& c) { courses.push_back(&c); }
};

// ---------------------------------------------------------------- School
class School {
public:
    std::string name;
    std::vector<Faculty*> faculties;     // AssignTo: School (1) <>-- (1..*) Faculty
    std::vector<Programme*> programmes;  // School (1..*) --- (1..*) Programme

    explicit School(std::string n) : name(std::move(n)) {}

    void addFaculty(Faculty& f) {
        faculties.push_back(&f);
        f.schoolName = name;  // the figure keeps the school name inside Faculty
    }
    void removeFaculty(Faculty& f) {
        unlink(faculties, &f);
        f.schoolName.clear();
    }
    void addProgramme(Programme& p) {  // both ends are 1..*, so update both
        programmes.push_back(&p);
        p.schools.push_back(this);
    }
    void removeProgramme(Programme& p) {
        unlink(programmes, &p);
        unlink(p.schools, this);
    }
};

// --------------------------------------------------------------- Student
class Student {
public:
    int stuID;
    std::string name;
    std::string address;
    Programme* programme = nullptr;  // enrol: Student --> Programme

    Student(int id, std::string n, std::string addr)
        : stuID(id), name(std::move(n)), address(std::move(addr)) {}

    // Constraint {one student per programme}: a registration binds a student
    // to exactly one programme, so a second enrol() is refused.
    bool enrol(Programme& p) {
        if (programme != nullptr) {
            std::cout << "  refused: " << name << " is already enrolled in "
                      << programme->ProgramName << " (one student per programme)\n";
            return false;
        }
        programme = &p;
        return true;
    }
};

// ------------------------------------------------------------ University
class University {
public:
    std::string name;
    std::string address;
    int phone;
    std::vector<School*> schools;    // has: University (1) <>-- (1..*) School
    std::vector<Student*> students;  // registration: University (1) <>-- (*) Student

    University(std::string n, std::string addr, int ph)
        : name(std::move(n)), address(std::move(addr)), phone(ph) {}

    void addSchool(School& s) { schools.push_back(&s); }
    void removeSchool(School& s) { unlink(schools, &s); }
    void addStudent(Student& s) { students.push_back(&s); }
    void removeStudent(Student& s) { unlink(students, &s); }
    School* getSchool(const std::string& n) const {
        for (School* s : schools)
            if (s->name == n) return s;
        return nullptr;
    }
    const std::vector<School*>& getAllSchool() const { return schools; }
    Student* getStudent(int id) const {
        for (Student* s : students)
            if (s->stuID == id) return s;
        return nullptr;
    }
};

// ------------------------------------------------------------------ main
static void printUniversity(const University& u) {
    std::cout << u.name << ", " << u.address << ", phone " << u.phone << "\n";
    for (const School* s : u.getAllSchool()) {
        std::cout << "  School: " << s->name << "\n";
        for (const Faculty* f : s->faculties) {
            std::cout << "    Faculty " << f->facultyID << " " << f->facultyName
                      << " (school " << f->schoolName << ")"
                      << (f->hod ? ", HOD " + f->hod->facultyName : "") << " teaches";
            for (const Course* c : f->courses) std::cout << " " << c->courseCode;
            std::cout << "\n";
        }
        for (const Programme* p : s->programmes)
            std::cout << "    Programme " << p->programID << " " << p->ProgramName << "\n";
    }
    for (const Student* st : u.students)
        std::cout << "  Student " << st->stuID << " " << st->name << ", " << st->address
                  << " -> " << (st->programme ? st->programme->ProgramName : "not enrolled")
                  << "\n";
}

int main() {
    University ignou("IGNOU", "Maidan Garhi, New Delhi", 29572514);

    // Two schools
    School socis("SOCIS");
    School soms("SOMS");
    ignou.addSchool(socis);
    ignou.addSchool(soms);

    // Faculties, with a HOD link inside SOCIS
    Faculty f1("F01", "Dr. Sharma");
    Faculty f2("F02", "Dr. Verma");
    Faculty f3("F03", "Dr. Iyer");
    socis.addFaculty(f1);
    socis.addFaculty(f2);
    soms.addFaculty(f3);
    f2.hod = &f1;  // HOD 0..1

    // Programmes
    Programme mca("MCA", "Master of Computer Applications");
    Programme mba("MBA", "Master of Business Administration");
    socis.addProgramme(mca);
    soms.addProgramme(mba);

    // Courses and the catalogue operations
    Course c1("MCS-217", "Software Engineering");
    Course c2("MCSL-222", "OOAD and Web Technologies Lab");
    Course c3("MMPC-001", "Management Concepts");
    Course::addCourse(c1);
    Course::addCourse(c2);
    Course::addCourse(c3);
    c1.programmes.push_back(&mca);  // Course (1) <>-- (*) Programme
    c2.programmes.push_back(&mca);
    c3.programmes.push_back(&mba);
    f1.teaches(c1);
    f2.teaches(c2);
    f3.teaches(c3);

    // Students and registration
    Student s1(2401, "Asha", "Jaipur");
    Student s2(2402, "Ravi", "Pune");
    ignou.addStudent(s1);
    ignou.addStudent(s2);
    s1.enrol(mca);
    s2.enrol(mba);

    std::cout << "--- after setup ---\n";
    printUniversity(ignou);

    std::cout << "--- constraint check ---\n";
    s1.enrol(mba);  // refused: already in MCA

    std::cout << "--- lookups ---\n";
    std::cout << "getSchool(\"SOMS\") -> " << ignou.getSchool("SOMS")->name << "\n";
    std::cout << "getSchool(\"SOL\") -> "
              << (ignou.getSchool("SOL") ? "found" : "nullptr") << "\n";
    std::cout << "getStudent(2402) -> " << ignou.getStudent(2402)->name << "\n";
    std::cout << "getCoursebyCode(\"MCSL-222\") -> "
              << Course::getCoursebyCode("MCSL-222")->courseName << "\n";
    std::cout << "getCoursebyName(\"Management Concepts\") -> "
              << Course::getCoursebyName("Management Concepts")->courseCode << "\n";
    std::cout << "catalogue size: " << Course::catalogue.size() << "\n";

    std::cout << "--- removals ---\n";
    Course::removeCourse(c3);
    socis.removeFaculty(f2);
    soms.removeProgramme(mba);
    ignou.removeStudent(s2);
    ignou.removeSchool(soms);
    std::cout << "catalogue size: " << Course::catalogue.size()
              << ", f2.schoolName is \"" << f2.schoolName << "\""
              << ", mba.schools.size() = " << mba.schools.size() << "\n";
    printUniversity(ignou);
    return 0;
}
