package lab1.task3;

public class PersonInChair {
    private String name;

    public PersonInChair(String name) {
        this.name = name;
    }

    // Getters and Setters
    public String getName() {
        return name;
    }
    public void setLeftHead() {
        System.out.println("ковыряет левой рукой в зубах правой головы");
    }
    public void setLegsOnControlPanel() {
        System.out.println( getName() + " положил ноги на пульт управления");
    }

}
