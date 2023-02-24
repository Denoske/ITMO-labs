package weblab4.services;

import lombok.extern.java.Log;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;
import weblab4.entities.Owner;
import weblab4.entitiesDTO.OwnerDTO;
import weblab4.exceptions.OwnerAlreadyExistsException;
import weblab4.exceptions.OwnerNotFoundException;
import weblab4.repository.OwnersRepository;

import javax.persistence.EntityNotFoundException;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;

@Log
@Service
public class OwnerService implements UserDetailsService {
    private final OwnersRepository repository;
    private final BCryptPasswordEncoder passwordEncoder; //FIXME this field needed only for tests

    @Autowired
    public OwnerService(OwnersRepository repository, BCryptPasswordEncoder passwordEncoder) {
        this.repository = repository;
        this.passwordEncoder = passwordEncoder;
        //addUserTest(); //todo: remove test
    }

    public List<Owner> allOwners() {
        return repository.findAll();
    }

    public Owner addOwner(Owner newOwner) {
        if(checkOwner(newOwner.getLogin())) throw  new OwnerAlreadyExistsException(newOwner.getLogin());
        return repository.save(newOwner);
    }

    public void updateOwner(Owner newOwner) {
        repository.save(newOwner);
    }

    public Owner getOwner(String ownerLogin) {
        try {
            return repository.findById(ownerLogin).orElseThrow(() -> new OwnerNotFoundException(ownerLogin));
        }catch (EntityNotFoundException e){
            throw new OwnerNotFoundException(ownerLogin);
        }
    }

    public Owner replaceOwner(Owner newOwner, String ownerLogin) {

        return repository.findById(ownerLogin)
                .map(owner -> {
                    owner.setPassword(newOwner.getPassword());
                    owner.setAttemptList(newOwner.getAttemptList()); //todo:check that here we put the whole object and check if it is authorized
                    return repository.save(owner);
                })
                .orElseGet(() -> {
                    newOwner.setLogin(ownerLogin);
                    return repository.save(newOwner);
                });
    }

    public void deleteOwner(String login) {
        repository.deleteById(login);
    }

    @Override
    public UserDetails loadUserByUsername(String login) throws UsernameNotFoundException {
        Owner owner = getOwner(login);
        if (Objects.isNull(owner)) {
            throw new OwnerNotFoundException(login);
        }
        return new User(owner.getLogin(), owner.getPassword(), true, true, true, true, new HashSet<>());
    }

    public Owner getOwnerFromDTO(OwnerDTO ownerDTO){
        return new Owner(ownerDTO.getLogin(), ownerDTO.getPassword());
    }

    public  boolean checkOwner(String login){
        return repository.findById(login).isPresent();
    }
    private void addUserTest() { //todo: remove test
//        Coordinates testCoordinates = new Coordinates(7, 7, 7);
//        Attempt testAttempt = new Attempt(testCoordinates, true);
//        Owner testOwner = new Owner("liv", "marsen");
//        testOwner.getAttemptList().add(testAttempt);
//        testAttempt.setOwner(testOwner);
//        testCoordinates.setAttempt(testAttempt);
//        repository.save(testOwner);
        Owner owner = new Owner("Masha", passwordEncoder.encode("Senina"));
        addOwner(owner);
        try {
            log.info("Trying to find user with id:\"" + owner.getLogin() +"\".");
            Owner bdOwner = getOwner(owner.getLogin());
            log.info(bdOwner.toString());
        }catch (OwnerNotFoundException e){
            log.warning(e.getLocalizedMessage());
        }
    }
}
