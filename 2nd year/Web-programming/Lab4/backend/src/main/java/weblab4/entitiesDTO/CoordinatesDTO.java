package weblab4.entitiesDTO;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class CoordinatesDTO {
    private double x = 0.0;
    private double y = 0.0;
    private double r = 0.0;

    @Override
    public String toString() {
        return "Coordinates{" +
                "x=" + x +
                "; y=" + y +
                "; r=" + r +
                "}";
    }
}
