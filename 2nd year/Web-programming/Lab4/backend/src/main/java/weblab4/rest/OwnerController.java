package weblab4.rest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import weblab4.entities.Owner;
import weblab4.services.OwnerService;

import java.util.List;

@RestController
public class OwnerController {

    private final OwnerService service;

    @Autowired
    public OwnerController(OwnerService service) {
        this.service = service;
    }

    @GetMapping("/users")
    List<Owner> all() {
        return service.allOwners();
    }

    @PostMapping("/users")
    Owner addOwner(@RequestBody Owner newOwner) {
        return service.addOwner(newOwner);
    }

    // Single item
    @GetMapping("/users/{login}")
    Owner getOwner(@PathVariable String login) {
        return service.getOwner(login);
    }

    @PutMapping("/users/{login}")
    Owner replaceOwner(@RequestBody Owner newOwner, @PathVariable String login) {
        return service.replaceOwner(newOwner, login);

    }

    @DeleteMapping("/users/{login}")
    void deleteAttempt(@PathVariable String login) {
        service.deleteOwner(login);
    }
}