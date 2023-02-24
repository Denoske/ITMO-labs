package Lab2.beans;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "POINTS")
public class Data implements Serializable
{
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Double x;
    private Double y;
    private Integer r;
    private Boolean inside;

    @Override
    public String toString() {
        String sx = this.x.toString().replace(",", ".");
        String sy = this.y.toString().replace(",", ".");
        return "Data{" +
                "id=" + id +
                ", x=" + sx +
                ", y=" + sy +
                ", r=" + r +
                ", inside=" + inside +
                '}';
    }

    public Data(Double x, Double y, Integer r, Boolean inside) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.inside = inside;
    }

    public Data() {
    }

    public void setX(Double x) {
        this.x = x;
    }

    public void setY(Double y) {
        this.y = y;
    }

    public void setR(Integer r) {
        this.r = r;
    }

    public void setInside(Boolean inside) {
        this.inside = inside;
    }

    public Double getX() {
        return x;
    }

    public Double getY() {
        return y;
    }

    public Integer getR() {
        return r;
    }

    public Boolean getInside() {
        return inside;
    }

    public void addRow(DataBean data)
    {

    }
}