package Lab2.beans;


import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;
import java.time.Instant;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;


public class DateTimeBean
{
//    private Instant dateTime = Instant.ofEpochSecond(0);

    public String getDateTime() {
        return Instant.now().atZone(ZoneId.of("Europe/Moscow")).format(DateTimeFormatter.ofPattern("HH:mm:ss"));
    }
}