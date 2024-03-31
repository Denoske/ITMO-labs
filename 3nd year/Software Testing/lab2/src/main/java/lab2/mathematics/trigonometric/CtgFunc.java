package lab2.mathematics.trigonometric;

public class CtgFunc extends TrigExecutable{

    private final TrigExecutable sin;
    private final TrigExecutable cos;

    public CtgFunc(final TrigExecutable sin, final TrigExecutable cos){
        super();
        this.sin = sin;
        this.cos = cos;
    }

    @Override
    public double execute(final double digit) {

        final double out = cos.execute(digit) / sin.execute(digit);

        tryWriteToFile(new String[] {String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName()});

        return out;
    }
}
