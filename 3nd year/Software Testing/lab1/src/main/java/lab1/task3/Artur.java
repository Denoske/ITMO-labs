package lab1.task3;

public class Artur {
    private String name;

    public Artur(String name) {
        this.name = name;
    }

    // Getters and Setters
    public String getName() {
        return name;
    }

    public void setNervous() {
        System.out.println(getName() + ", нервничая,");
    }

    public void setShocked() {
        System.out.println(getName() + " был ошеламлен");
    }
    public void enterTheRoom(){
        System.out.println("вошел в комнату");
    }

    public void see(String some){
        if(some.equals("Человек")) {
            System.out.println("увидел разалившегося в кресле человека" );
        }
        if(some.equals("Вещи")){
            System.out.println("Количество вещей, видя которые, все росло");
        }

    }
    public void dontTrust(){
        System.out.println( getName() + " не верил своим глазам");
    }
    public void jaw(){
        System.out.println("Его челюсть отвисла");
    }


}