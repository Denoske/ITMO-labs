package lab1.task3;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class ModelTest {
    private final ByteArrayOutputStream outputStreamCaptor = new ByteArrayOutputStream();

    @BeforeEach
    public void setUp() {
        System.setOut(new PrintStream(outputStreamCaptor));
    }


    @Test
    void ArturInTheRoom(){
        Artur artur = new Artur("Артур");
        artur.setNervous();
        artur.enterTheRoom();
        artur.setShocked();
        artur.see("Человек");
        assertEquals("Артур, нервничая," + System.lineSeparator() +
                "вошел в комнату" + System.lineSeparator() +
                "Артур был ошеламлен" + System.lineSeparator() +
                "увидел разалившегося в кресле человека", outputStreamCaptor.toString().trim());
    }

    @Test
    void PersonInTheRoom(){
        PersonInChair person = new PersonInChair("Человек в кресле");
        person.setLegsOnControlPanel();
        person.setLeftHead();
        assertEquals("Человек в кресле положил ноги на пульт управления" + System.lineSeparator() +
                    "ковыряет левой рукой в зубах правой головы", outputStreamCaptor.toString().trim());
    }

    @Test
    void HeadsDeal(){
        RightHead right = new RightHead("Правая голова");
        LeftHead left = new LeftHead("Левая голова");
        right.busy();
        left.smile();
        assertEquals("Правая голова была всецело занята этим" + System.lineSeparator() +
                "Левая голова улыбалась широко и непринужденно", outputStreamCaptor.toString().trim());
    }

    @Test
    void ThirdPart(){
        Artur artur = new Artur("Артур");
        artur.see("Вещи");
        artur.dontTrust();
        artur.jaw();
        assertEquals("Количество вещей, видя которые, все росло" + System.lineSeparator() +
                        "Артур не верил своим глазам" + System.lineSeparator() +
                        "Его челюсть отвисла", outputStreamCaptor.toString().trim());
    }

    @Test
    void WholeStoryTail(){
        Artur artur = new Artur("Артур");
        PersonInChair person = new PersonInChair("Человек в кресле");
        RightHead right = new RightHead("Правая голова");
        LeftHead left = new LeftHead("Левая голова");
        artur.setNervous();
        artur.enterTheRoom();
        artur.setShocked();
        artur.see("Человек");
        person.setLegsOnControlPanel();
        person.setLeftHead();
        right.busy();
        left.smile();
        artur.see("Вещи");
        artur.dontTrust();
        artur.jaw();
        assertEquals("Артур, нервничая," + System.lineSeparator() +
                "вошел в комнату" + System.lineSeparator() +
                "Артур был ошеламлен" + System.lineSeparator() +
                "увидел разалившегося в кресле человека" + System.lineSeparator() +
                "Человек в кресле положил ноги на пульт управления" + System.lineSeparator() +
                "ковыряет левой рукой в зубах правой головы" + System.lineSeparator() +
                "Правая голова была всецело занята этим" + System.lineSeparator() +
                "Левая голова улыбалась широко и непринужденно" + System.lineSeparator() +
                "Количество вещей, видя которые, все росло" + System.lineSeparator() +
                "Артур не верил своим глазам" + System.lineSeparator() +
                "Его челюсть отвисла", outputStreamCaptor.toString().trim());

    }

}

//Цель
//Обоснование выбора тестир. знач
//Ссылка на код
//Доменная модель
//Вывод
//телега в личку
