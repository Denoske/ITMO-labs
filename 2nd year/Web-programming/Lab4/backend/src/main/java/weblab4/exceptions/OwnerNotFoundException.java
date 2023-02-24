package weblab4.exceptions;

import org.springframework.security.core.userdetails.UsernameNotFoundException;

public class OwnerNotFoundException extends UsernameNotFoundException {
    public OwnerNotFoundException(String login) {
        super("Owner with login: \"" + login + "\" wasn't found!");
    }
}
