package weblab4.exceptions;

public class EmptyCoordinateException extends RuntimeException{
    public EmptyCoordinateException(String coordinateName){
        super("Coordinate " + coordinateName + " is empty!");
    }
}
