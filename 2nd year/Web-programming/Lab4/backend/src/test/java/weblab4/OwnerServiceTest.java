package weblab4;

import org.junit.jupiter.api.Test;
import weblab4.entities.Owner;
import weblab4.services.OwnerService;

public class OwnerServiceTest {

    private final OwnerService service;

    public OwnerServiceTest(OwnerService service) {
        this.service = service;
    }

//    @Test
    public void gettingUserTest(){
        //insert into OWNER(LOGIN, PASSWORD) values('Test', 'User');
        Owner owner = service.getOwner("Test");
        System.out.println(owner);
    }

//    @Test
    public void addingUserTest(){
        Owner owner = new Owner("Masha", "Senina");
        service.addOwner(owner);
        Owner bdOwner = service.getOwner("Test");
        System.out.println(bdOwner);
    }
}
