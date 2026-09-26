# student_registration.py -- MCSL-222 Session 8, Q19
# Figure 1.15 (Student Registration) in Python 3, standard library only.
# Run: python3 student_registration.py
#
# Mapping used throughout:
#   class            -> @dataclass
#   attribute        -> field (same name as the figure)
#   operation        -> method or @staticmethod (same name as the figure)
#   association end  -> object reference (or None) for 1 / 0..1, list for * / 1..*
# eq=False keeps identity comparison, so list.remove() unlinks that exact object
# and the two-way School/Programme links cannot recurse through a field-by-field ==.
from __future__ import annotations

from dataclasses import dataclass, field
from typing import ClassVar, Optional


# ---------------------------------------------------------------- Course
@dataclass(eq=False)
class Course:
    courseCode: str
    courseName: str
    programmes: list[Programme] = field(default_factory=list)  # Course (1) <>-- (*) Programme, as drawn

    # The four operations in the figure manage the list of courses, so they
    # work on one shared catalogue: a class attribute, the Python static member.
    catalogue: ClassVar[list[Course]] = []

    @staticmethod
    def addCourse(c: Course) -> None:
        Course.catalogue.append(c)

    @staticmethod
    def removeCourse(c: Course) -> None:
        Course.catalogue.remove(c)

    @staticmethod
    def getCoursebyName(name: str) -> Optional[Course]:
        return next((c for c in Course.catalogue if c.courseName == name), None)

    @staticmethod
    def getCoursebyCode(code: str) -> Optional[Course]:
        return next((c for c in Course.catalogue if c.courseCode == code), None)


# ------------------------------------------------------------- Programme
@dataclass(eq=False)
class Programme:
    programID: str
    ProgramName: str
    schools: list[School] = field(default_factory=list)  # School (1..*) --- (1..*) Programme


# --------------------------------------------------------------- Faculty
@dataclass(eq=False)
class Faculty:
    facultyID: str
    facultyName: str
    schoolName: str = ""
    hod: Optional[Faculty] = None                        # HOD 0..1 (reflexive association)
    courses: list[Course] = field(default_factory=list)  # Teaches: Faculty (1..*) --> Course

    def teaches(self, c: Course) -> None:
        self.courses.append(c)


# ---------------------------------------------------------------- School
@dataclass(eq=False)
class School:
    name: str
    faculties: list[Faculty] = field(default_factory=list)    # AssignTo: School (1) <>-- (1..*) Faculty
    programmes: list[Programme] = field(default_factory=list)  # School (1..*) --- (1..*) Programme

    def addFaculty(self, f: Faculty) -> None:
        self.faculties.append(f)
        f.schoolName = self.name  # the figure keeps the school name inside Faculty

    def removeFaculty(self, f: Faculty) -> None:
        self.faculties.remove(f)
        f.schoolName = ""

    def addProgramme(self, p: Programme) -> None:  # both ends are 1..*, so update both
        self.programmes.append(p)
        p.schools.append(self)

    def removeProgramme(self, p: Programme) -> None:
        self.programmes.remove(p)
        p.schools.remove(self)


# --------------------------------------------------------------- Student
@dataclass(eq=False)
class Student:
    stuID: int
    name: str
    address: str
    programme: Optional[Programme] = None  # enrol: Student --> Programme

    # Constraint {one student per programme}: a registration binds a student
    # to exactly one programme, so a second enrol() is refused.
    def enrol(self, p: Programme) -> bool:
        if self.programme is not None:
            print(f"  refused: {self.name} is already enrolled in "
                  f"{self.programme.ProgramName} (one student per programme)")
            return False
        self.programme = p
        return True


# ------------------------------------------------------------ University
@dataclass(eq=False)
class University:
    name: str
    address: str
    phone: int
    schools: list[School] = field(default_factory=list)    # has: University (1) <>-- (1..*) School
    students: list[Student] = field(default_factory=list)  # registration: University (1) <>-- (*) Student

    def addSchool(self, s: School) -> None:
        self.schools.append(s)

    def removeSchool(self, s: School) -> None:
        self.schools.remove(s)

    def addStudent(self, s: Student) -> None:
        self.students.append(s)

    def removeStudent(self, s: Student) -> None:
        self.students.remove(s)

    def getSchool(self, n: str) -> Optional[School]:
        return next((s for s in self.schools if s.name == n), None)

    def getAllSchool(self) -> list[School]:
        return self.schools

    def getStudent(self, id: int) -> Optional[Student]:
        return next((s for s in self.students if s.stuID == id), None)


# ------------------------------------------------------------------ main
def printUniversity(u: University) -> None:
    print(f"{u.name}, {u.address}, phone {u.phone}")
    for s in u.getAllSchool():
        print(f"  School: {s.name}")
        for f in s.faculties:
            hod = f", HOD {f.hod.facultyName}" if f.hod else ""
            codes = "".join(f" {c.courseCode}" for c in f.courses)
            print(f"    Faculty {f.facultyID} {f.facultyName} (school {f.schoolName}){hod} teaches{codes}")
        for p in s.programmes:
            print(f"    Programme {p.programID} {p.ProgramName}")
    for st in u.students:
        prog = st.programme.ProgramName if st.programme else "not enrolled"
        print(f"  Student {st.stuID} {st.name}, {st.address} -> {prog}")


def main() -> None:
    ignou = University("IGNOU", "Maidan Garhi, New Delhi", 29572514)

    # Two schools
    socis = School("SOCIS")
    soms = School("SOMS")
    ignou.addSchool(socis)
    ignou.addSchool(soms)

    # Faculties, with a HOD link inside SOCIS
    f1 = Faculty("F01", "Dr. Sharma")
    f2 = Faculty("F02", "Dr. Verma")
    f3 = Faculty("F03", "Dr. Iyer")
    socis.addFaculty(f1)
    socis.addFaculty(f2)
    soms.addFaculty(f3)
    f2.hod = f1  # HOD 0..1

    # Programmes
    mca = Programme("MCA", "Master of Computer Applications")
    mba = Programme("MBA", "Master of Business Administration")
    socis.addProgramme(mca)
    soms.addProgramme(mba)

    # Courses and the catalogue operations
    c1 = Course("MCS-217", "Software Engineering")
    c2 = Course("MCSL-222", "OOAD and Web Technologies Lab")
    c3 = Course("MMPC-001", "Management Concepts")
    Course.addCourse(c1)
    Course.addCourse(c2)
    Course.addCourse(c3)
    c1.programmes.append(mca)  # Course (1) <>-- (*) Programme
    c2.programmes.append(mca)
    c3.programmes.append(mba)
    f1.teaches(c1)
    f2.teaches(c2)
    f3.teaches(c3)

    # Students and registration
    s1 = Student(2401, "Asha", "Jaipur")
    s2 = Student(2402, "Ravi", "Pune")
    ignou.addStudent(s1)
    ignou.addStudent(s2)
    s1.enrol(mca)
    s2.enrol(mba)

    print("--- after setup ---")
    printUniversity(ignou)

    print("--- constraint check ---")
    s1.enrol(mba)  # refused: already in MCA

    print("--- lookups ---")
    print(f'getSchool("SOMS") -> {ignou.getSchool("SOMS").name}')
    # "nullptr" is printed for a miss so the output matches the C++ version.
    print(f'getSchool("SOL") -> {"found" if ignou.getSchool("SOL") else "nullptr"}')
    print(f"getStudent(2402) -> {ignou.getStudent(2402).name}")
    print(f'getCoursebyCode("MCSL-222") -> {Course.getCoursebyCode("MCSL-222").courseName}')
    print(f'getCoursebyName("Management Concepts") -> {Course.getCoursebyName("Management Concepts").courseCode}')
    print(f"catalogue size: {len(Course.catalogue)}")

    print("--- removals ---")
    Course.removeCourse(c3)
    socis.removeFaculty(f2)
    soms.removeProgramme(mba)
    ignou.removeStudent(s2)
    ignou.removeSchool(soms)
    print(f'catalogue size: {len(Course.catalogue)}, f2.schoolName is "{f2.schoolName}", '
          f"mba.schools.size() = {len(mba.schools)}")
    printUniversity(ignou)


if __name__ == "__main__":
    main()
