package weblab4.services;

import lombok.RequiredArgsConstructor;
import lombok.extern.java.Log;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import weblab4.entities.Owner;

@Log
@Service
@RequiredArgsConstructor
public class OwnerDetails implements UserDetailsService {

    private final OwnerService service;

    @Override
    public UserDetails loadUserByUsername(String login) throws UsernameNotFoundException {
        Owner owner = service.getOwner(login);

        return User
                .withUsername(login)
                .password(owner.getPassword())
                .roles("USER")
                .accountExpired(false)
                .accountLocked(false)
                .credentialsExpired(false)
                .disabled(false)
                .build();
    }

}
