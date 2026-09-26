// student_registration.ts -- MCSL-222 Session 8, Q19
// Figure 1.15 (Student Registration) in TypeScript, no dependencies.
// Run: node student_registration.ts   (Node 22.18 or later strips the types itself)
//
// Mapping used throughout:
//   class            -> class
//   attribute        -> typed field (same name as the figure), readonly when it never changes
//   operation        -> method or static method (same name as the figure)
//   association end  -> `T | null` for 1 / 0..1, `T[]` for * / 1..*
"use strict";

// Removes one link from an association array. Every remove* operation uses it.
function unlink<T>(arr: T[], p: T): void {
  const i = arr.indexOf(p);
  if (i >= 0) arr.splice(i, 1);
}

// Student and University both carry a name and a postal address.
interface Addressed {
  readonly name: string;
  readonly address: string;
}

// ---------------------------------------------------------------- Course
class Course {
  // The four operations in the figure manage the list of courses, so they
  // work on one shared catalogue: a static field plus static methods.
  static readonly catalogue: Course[] = [];

  readonly courseCode: string;
  readonly courseName: string;
  readonly programmes: Programme[] = []; // Course (1) <>-- (*) Programme, as drawn

  constructor(code: string, name: string) {
    this.courseCode = code;
    this.courseName = name;
  }

  static addCourse(c: Course): void { Course.catalogue.push(c); }
  static removeCourse(c: Course): void { unlink(Course.catalogue, c); }
  static getCoursebyName(name: string): Course | null { return Course.catalogue.find((c) => c.courseName === name) ?? null; }
  static getCoursebyCode(code: string): Course | null { return Course.catalogue.find((c) => c.courseCode === code) ?? null; }
}

// ------------------------------------------------------------- Programme
class Programme {
  readonly programID: string;
  readonly ProgramName: string;
  readonly schools: School[] = []; // School (1..*) --- (1..*) Programme

  constructor(id: string, name: string) {
    this.programID = id;
    this.ProgramName = name;
  }
}

// --------------------------------------------------------------- Faculty
class Faculty {
  readonly facultyID: string;
  readonly facultyName: string;
  schoolName: string = "";
  hod: Faculty | null = null;      // HOD 0..1 (reflexive association)
  readonly courses: Course[] = []; // Teaches: Faculty (1..*) --> Course

  constructor(id: string, name: string) {
    this.facultyID = id;
    this.facultyName = name;
  }

  teaches(c: Course): void { this.courses.push(c); }
}

// ---------------------------------------------------------------- School
class School {
  readonly name: string;
  readonly faculties: Faculty[] = [];  // AssignTo: School (1) <>-- (1..*) Faculty
  readonly programmes: Programme[] = []; // School (1..*) --- (1..*) Programme

  constructor(n: string) {
    this.name = n;
  }

  addFaculty(f: Faculty): void {
    this.faculties.push(f);
    f.schoolName = this.name; // the figure keeps the school name inside Faculty
  }
  removeFaculty(f: Faculty): void {
    unlink(this.faculties, f);
    f.schoolName = "";
  }
  addProgramme(p: Programme): void { // both ends are 1..*, so update both
    this.programmes.push(p);
    p.schools.push(this);
  }
  removeProgramme(p: Programme): void {
    unlink(this.programmes, p);
    unlink(p.schools, this);
  }
}

// --------------------------------------------------------------- Student
class Student implements Addressed {
  readonly stuID: number;
  readonly name: string;
  readonly address: string;
  programme: Programme | null = null; // enrol: Student --> Programme

  constructor(id: number, n: string, addr: string) {
    this.stuID = id;
    this.name = n;
    this.address = addr;
  }

  // Constraint {one student per programme}: a registration binds a student
  // to exactly one programme, so a second enrol() is refused.
  enrol(p: Programme): boolean {
    if (this.programme !== null) {
      console.log(`  refused: ${this.name} is already enrolled in ${this.programme.ProgramName} (one student per programme)`);
      return false;
    }
    this.programme = p;
    return true;
  }
}

// ------------------------------------------------------------ University
class University implements Addressed {
  readonly name: string;
  readonly address: string;
  readonly phone: number;
  readonly schools: School[] = [];   // has: University (1) <>-- (1..*) School
  readonly students: Student[] = []; // registration: University (1) <>-- (*) Student

  constructor(n: string, addr: string, ph: number) {
    this.name = n;
    this.address = addr;
    this.phone = ph;
  }

  addSchool(s: School): void { this.schools.push(s); }
  removeSchool(s: School): void { unlink(this.schools, s); }
  addStudent(s: Student): void { this.students.push(s); }
  removeStudent(s: Student): void { unlink(this.students, s); }
  getSchool(n: string): School | null { return this.schools.find((s) => s.name === n) ?? null; }
  getAllSchool(): School[] { return this.schools; }
  getStudent(id: number): Student | null { return this.students.find((s) => s.stuID === id) ?? null; }
}

// ------------------------------------------------------------------ main
function where(x: Addressed): string { return `${x.name}, ${x.address}`; }

function printUniversity(u: University): void {
  console.log(`${where(u)}, phone ${u.phone}`);
  for (const s of u.getAllSchool()) {
    console.log(`  School: ${s.name}`);
    for (const f of s.faculties) {
      const hod = f.hod ? `, HOD ${f.hod.facultyName}` : "";
      const codes = f.courses.map((c) => ` ${c.courseCode}`).join("");
      console.log(`    Faculty ${f.facultyID} ${f.facultyName} (school ${f.schoolName})${hod} teaches${codes}`);
    }
    for (const p of s.programmes) console.log(`    Programme ${p.programID} ${p.ProgramName}`);
  }
  for (const st of u.students) {
    const prog = st.programme ? st.programme.ProgramName : "not enrolled";
    console.log(`  Student ${st.stuID} ${where(st)} -> ${prog}`);
  }
}

function main(): void {
  const ignou = new University("IGNOU", "Maidan Garhi, New Delhi", 29572514);

  // Two schools
  const socis = new School("SOCIS");
  const soms = new School("SOMS");
  ignou.addSchool(socis);
  ignou.addSchool(soms);

  // Faculties, with a HOD link inside SOCIS
  const f1 = new Faculty("F01", "Dr. Sharma");
  const f2 = new Faculty("F02", "Dr. Verma");
  const f3 = new Faculty("F03", "Dr. Iyer");
  socis.addFaculty(f1);
  socis.addFaculty(f2);
  soms.addFaculty(f3);
  f2.hod = f1; // HOD 0..1

  // Programmes
  const mca = new Programme("MCA", "Master of Computer Applications");
  const mba = new Programme("MBA", "Master of Business Administration");
  socis.addProgramme(mca);
  soms.addProgramme(mba);

  // Courses and the catalogue operations
  const c1 = new Course("MCS-217", "Software Engineering");
  const c2 = new Course("MCSL-222", "OOAD and Web Technologies Lab");
  const c3 = new Course("MMPC-001", "Management Concepts");
  Course.addCourse(c1);
  Course.addCourse(c2);
  Course.addCourse(c3);
  c1.programmes.push(mca); // Course (1) <>-- (*) Programme
  c2.programmes.push(mca);
  c3.programmes.push(mba);
  f1.teaches(c1);
  f2.teaches(c2);
  f3.teaches(c3);

  // Students and registration
  const s1 = new Student(2401, "Asha", "Jaipur");
  const s2 = new Student(2402, "Ravi", "Pune");
  ignou.addStudent(s1);
  ignou.addStudent(s2);
  s1.enrol(mca);
  s2.enrol(mba);

  console.log("--- after setup ---");
  printUniversity(ignou);

  console.log("--- constraint check ---");
  s1.enrol(mba); // refused: already in MCA

  console.log("--- lookups ---");
  // The lookups return `T | null`; `!` tells the checker these hits exist.
  console.log(`getSchool("SOMS") -> ${ignou.getSchool("SOMS")!.name}`);
  // "nullptr" is printed for a miss so the output matches the C++ version.
  console.log(`getSchool("SOL") -> ${ignou.getSchool("SOL") ? "found" : "nullptr"}`);
  console.log(`getStudent(2402) -> ${ignou.getStudent(2402)!.name}`);
  console.log(`getCoursebyCode("MCSL-222") -> ${Course.getCoursebyCode("MCSL-222")!.courseName}`);
  console.log(`getCoursebyName("Management Concepts") -> ${Course.getCoursebyName("Management Concepts")!.courseCode}`);
  console.log(`catalogue size: ${Course.catalogue.length}`);

  console.log("--- removals ---");
  Course.removeCourse(c3);
  socis.removeFaculty(f2);
  soms.removeProgramme(mba);
  ignou.removeStudent(s2);
  ignou.removeSchool(soms);
  console.log(`catalogue size: ${Course.catalogue.length}, f2.schoolName is "${f2.schoolName}", mba.schools.size() = ${mba.schools.length}`);
  printUniversity(ignou);
}

main();
