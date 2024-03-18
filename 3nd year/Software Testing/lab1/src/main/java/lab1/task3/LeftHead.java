package lab1.task3;

public class LeftHead {
    private String name;

    public LeftHead(String name) {
        this.name = name;
    }
    public String getName() {
        return name;
    }

    public void smile(){
        System.out.println( getName() +  " улыбалась широко и непринужденно");
    }
}
