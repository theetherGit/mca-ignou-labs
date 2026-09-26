package ignou;

/** One row of the Student table. Plain data holder used by the DAO, servlets and JSPs. */
public class Student {
    private String enrolmentNo;
    private String name;
    private String dob;          // yyyy-MM-dd, the format <input type="date"> and MySQL both use
    private String gender;
    private String email;
    private String mobile;
    private String address;
    private String city;
    private String state;
    private String pincode;
    private String programme;
    private int semester;
    private int admissionYear;
    private String studyCentre;
    private String courses;      // comma-separated course codes

    public String getEnrolmentNo() { return enrolmentNo; }
    public void setEnrolmentNo(String enrolmentNo) { this.enrolmentNo = enrolmentNo; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getDob() { return dob; }
    public void setDob(String dob) { this.dob = dob; }
    public String getGender() { return gender; }
    public void setGender(String gender) { this.gender = gender; }
    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }
    public String getMobile() { return mobile; }
    public void setMobile(String mobile) { this.mobile = mobile; }
    public String getAddress() { return address; }
    public void setAddress(String address) { this.address = address; }
    public String getCity() { return city; }
    public void setCity(String city) { this.city = city; }
    public String getState() { return state; }
    public void setState(String state) { this.state = state; }
    public String getPincode() { return pincode; }
    public void setPincode(String pincode) { this.pincode = pincode; }
    public String getProgramme() { return programme; }
    public void setProgramme(String programme) { this.programme = programme; }
    public int getSemester() { return semester; }
    public void setSemester(int semester) { this.semester = semester; }
    public int getAdmissionYear() { return admissionYear; }
    public void setAdmissionYear(int admissionYear) { this.admissionYear = admissionYear; }
    public String getStudyCentre() { return studyCentre; }
    public void setStudyCentre(String studyCentre) { this.studyCentre = studyCentre; }
    public String getCourses() { return courses; }
    public void setCourses(String courses) { this.courses = courses; }
}
