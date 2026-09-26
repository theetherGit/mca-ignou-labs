package ignou;

import java.io.Serializable;

/**
 * Q10: JavaBean for jsp:useBean. Rules a bean must follow: public class,
 * public no-argument constructor, private fields, public getters and setters
 * named after the fields. jsp:setProperty property="*" matches request
 * parameter names to these setter names.
 */
public class StudentBean implements Serializable {
    private String name;
    private String programme;
    private int semester;

    public StudentBean() { }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public String getProgramme() { return programme; }
    public void setProgramme(String programme) { this.programme = programme; }
    public int getSemester() { return semester; }
    public void setSemester(int semester) { this.semester = semester; }
}
