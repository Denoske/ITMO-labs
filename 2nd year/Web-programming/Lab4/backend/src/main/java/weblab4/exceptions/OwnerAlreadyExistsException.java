package weblab4.exceptions;

public class OwnerAlreadyExistsException extends RuntimeException{
    public OwnerAlreadyExistsException(String login) {
        super("Owner with such login: " + login + " already exists!");
    }
}
