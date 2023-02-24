
package weblab4.entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.util.Objects;

@Entity
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class Coordinates{
    private double x = 0.0;
    private double y = 0.0;
    private double r = 0.0;

    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "coordinates_id")
    private Long id;

    @JsonIgnore
    @OneToOne(mappedBy = "coordinates", cascade = CascadeType.ALL)
    @JoinColumn(name = "coordinates_id")
    private Attempt attempt;

    public Coordinates(double x, double y, double r) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.id = null;
        this.attempt = null;
    }

    @Override
    public String toString() {
        return "Coordinates{" +
                "(x=" + x +
                "; y=" + y +
                "; r=" + r +
                "), id=" + id +
                ", attempts isn't null=" + (Objects.nonNull(attempt)) +
                '}';
    }
}
