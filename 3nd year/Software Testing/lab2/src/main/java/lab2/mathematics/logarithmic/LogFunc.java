package lab2.mathematics.logarithmic;

public class LogFunc extends LogExecutable{

    private final LogExecutable ln;

    public LogFunc(final LogExecutable ln){
        super();
        this.ln = ln;
    }

    @Override
    public double execute(final double digit, final double base) {

        double out;

        if(base == Math.E){
            out = ln.execute(digit, Math.E);
        }
        else {
            out = ln.execute(digit, Math.E) / ln.execute(base, Math.E);
        }

        tryWriteToFile(String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName() + base);

        return out;
    }
}
