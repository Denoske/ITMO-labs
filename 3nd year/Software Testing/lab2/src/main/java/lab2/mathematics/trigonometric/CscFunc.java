package lab2.mathematics.trigonometric;

public class CscFunc extends TrigExecutable{

    private final TrigExecutable sin;

    public CscFunc(final TrigExecutable sin){
        super();
        this.sin = sin;
    }

    @Override
    public double execute(final double digit) {

        final double out = 1 / sin.execute(digit);

        tryWriteToFile(new String[] {String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName()});

        return out;
    }
}
