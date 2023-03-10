package Lab2.beans;

import javax.persistence.*;
import java.io.Serializable;
import java.time.LocalTime;

/*create table RAWS (
 ID INT,
 X_VAL FLOAT,
 Y_VAL FLOAT,
 R_VAL FLOAT,
 TIME_Y CHAR(50),
 RESULT_Y BOOLEAN
)*/

@Entity
@Table(name = "raws")
public class Raw implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.SEQUENCE)
    private Long id;
    @Transient private static final long serialVersionUID = 4L;

    @Column(name="x_val")
    private double x_val;

    @Column(name="y_val")
    private double y_val;

    @Column(name="r_val")
    private double r_val;

    @Column(name="time_Y")
    private String timeP;

    @Column(name="result_Y")
    private boolean resultP;

    public Raw(){
        x_val = 0;
        y_val = 0;
        r_val = 1;
        timeP = "";
        resultP = false;
    }

    public Raw(double x, double y, double r, boolean res){
        this.x_val = x;
        this.y_val = y;
        this.r_val = r;
        this.resultP = res;
    }

    private boolean checkTriangle(){
        return x_val <= 0 && y_val >= 0 && x_val >= 2*y_val - r_val;
    }

    private boolean checkRectangle(){
        return x_val <= 0 && y_val <= 0 && x_val >= -r_val && y_val >= -r_val/2;
    }
    private boolean checkCircle(){
        return x_val >= 0 && y_val <= 0 && x_val*x_val + y_val*y_val <= (r_val/2)*(r_val/2);
    }

    public void checkResult(){
        setTime(LocalTime.now().toString());
        resultP = checkCircle() || checkRectangle() || checkTriangle();;
    }

    public double getR_val() {
        return r_val;
    }

    public void r1(){
        r_val = 1;
    }

    public void r2(){
        r_val = 2;
    }

    public void r3(){
        r_val = 3;
    }

    public void r4(){
        r_val = 4;
    }

    public void r5(){
        r_val = 5;
    }


    public double getX_val() {
        return x_val;
    }

    public double getY_val() {
        return y_val;
    }

    public String getTime() { return timeP; }

    public boolean isResult() {
        return resultP;
    }

    public void setY_val(double y_val) {
        this.y_val = y_val;
    }

    public void setTime(String time) {
        this.timeP = time;
    }

    public void setR_val(double r_val) {
        this.r_val = r_val;
    }

    public void setResult(boolean result) {
        this.resultP = result;
    }

    public void setX_val(double x_val) {
        this.x_val = x_val;
    }
}