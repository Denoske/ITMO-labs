package lab1.task3;

public class RightHead {
    private String name;

    public RightHead(String name) {
        this.name = name;
    }
    public String getName() {
        return name;
    }

    public void busy(){
        System.out.println( getName() +  " была всецело занята этим");
    }
}
