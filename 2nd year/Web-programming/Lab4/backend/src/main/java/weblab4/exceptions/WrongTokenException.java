package weblab4.exceptions;

import lombok.Getter;
import org.springframework.http.HttpStatus;

public class WrongTokenException extends RuntimeException{
    @Getter
    private final HttpStatus status;
    public WrongTokenException(HttpStatus status){
        super("Expired or invalid JWT token");
        this.status = status;
    }
}
