package Lab2.beans;


public class DataBean {
    private double x, y, y_for_slider;
    private int r;
    private boolean inside;

    public DataBean(double x, double y, int r, boolean inside)
    {
        this.x = x;
        this.y = y;
        this.r = r;
        this.inside = inside;
    }

    public DataBean(DataBean data)
    {
        this.x = data.getX();
        this.y = data.y;
        this.r = data.getR();
        this.inside = data.isInside();
    }

    public DataBean() {};

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getY_for_slider() {
        return y_for_slider;
    }

    public int getR() {
        return r;
    }

    public boolean isInside() {
        return inside;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
        this.y_for_slider = y * 100;
    }

    public void setY_for_slider(double y_for_slider) {
        this.y = y_for_slider / 100.;
        this.y_for_slider = y_for_slider;
    }



    public void setR(int r) {
        this.r = r;
    }

    public void setInside(boolean inside) {
        this.inside = inside;
    }

    @Override
    public String toString() {
        String sx = Double.toString(this.x).replace(",", ".");
        String sy = Double.toString(this.y).replace(",", ".");
        return String.format("[%f,%f,%d,%b]", x, y, r, inside);
    }
}