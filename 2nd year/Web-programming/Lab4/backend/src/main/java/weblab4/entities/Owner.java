package weblab4.entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.util.ArrayList;
import java.util.List;

@NoArgsConstructor
@AllArgsConstructor
@Entity
@Getter
@Setter
public class Owner {
    @Id
    @Column(name = "login", nullable = false)
    private String login;

    @Column(name = "password", nullable = false)
    private String password;

    @JsonIgnore
    //if we want to drop all attempts after owner death
    @OneToMany(mappedBy = "owner", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<Attempt> attemptList = new ArrayList<>();

    public static Owner initOwner(){
        Owner owner = new Owner();
        owner.setAttemptList(new ArrayList<>());
        return owner;
    }

    public Owner(String login, String password){
        this.login = login;
        this.password = password;

    }

    @Override
    public String toString() {
        return "Owner{" +
                "login=" + login +
                ", password=" + password +
                ", attemptsIds=" + attemptList.stream().map(attempt -> attempt.getId().toString() + ", ") +
                '}';
    }
}
