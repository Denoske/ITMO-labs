package weblab4.entitiesDTO;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class OwnerDTO {
    private String login;
    private String password;


    @Override
    public String toString() {
        return "OwnerDTO{" +
                "login=" + login +
                ", password=" + password +
                '}';
    }
}
