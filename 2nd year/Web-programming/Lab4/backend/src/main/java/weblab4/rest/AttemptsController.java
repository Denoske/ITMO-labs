package weblab4.rest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import weblab4.entitiesDTO.AttemptDTO;
import weblab4.entitiesDTO.CoordinatesDTO;
import weblab4.services.AttemptsService;

import java.util.List;


@RestController
public class AttemptsController {

    private final AttemptsService service;


    @Autowired
    public AttemptsController(AttemptsService service) {
        this.service = service;
    }

    @GetMapping("/attempts")
    List<AttemptDTO> getAllAttempts() {
        return service.getAllAttempts();
    }

    @PostMapping("/attempts")
    AttemptDTO addAttempt(@RequestBody CoordinatesDTO newAttempt) {
        return service.addAttempt(newAttempt);
    }

    @DeleteMapping("/attempts")
    void deleteAllAttempt() {
        service.deleteAllAttempts();
    }
}