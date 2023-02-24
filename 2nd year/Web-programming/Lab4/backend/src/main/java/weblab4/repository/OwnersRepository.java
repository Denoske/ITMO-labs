package weblab4.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import weblab4.entities.Owner;

public interface OwnersRepository extends JpaRepository<Owner, String> {}
