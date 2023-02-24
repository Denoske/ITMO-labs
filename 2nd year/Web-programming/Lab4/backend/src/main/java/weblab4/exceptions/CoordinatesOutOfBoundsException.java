package weblab4.exceptions;

public class CoordinatesOutOfBoundsException extends RuntimeException{
    public CoordinatesOutOfBoundsException(double coordinateValue, String coordinateName) {
        super("Coordinate " + coordinateName + " is out of bounds. It's value is = " + coordinateValue + ".");
    }
}