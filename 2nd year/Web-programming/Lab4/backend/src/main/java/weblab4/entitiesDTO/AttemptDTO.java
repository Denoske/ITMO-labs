package weblab4.entitiesDTO;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.java.Log;


@Log
@Getter
@Setter
@AllArgsConstructor
public class AttemptDTO {
    private double x;
    private double y;
    private double r;
    private boolean doFitArea;

    @Override
    public String toString() {
        return "Attempt{" +
                "coordinates{" +
                "(x=" + x +
                "; y=" + y +
                "; r=" + r +
                "),doFitArea=" + doFitArea +
                '}';
    }
}
