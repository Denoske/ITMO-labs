package lab2.mathematics.trigonometric;

public class TgFunc extends TrigExecutable{

    private final TrigExecutable sin;
    private final TrigExecutable cos;

    public TgFunc(final TrigExecutable sin, final TrigExecutable cos){
        super();
        this.sin = sin;
        this.cos = cos;
    }

    @Override
    public double execute(final double digit) {

        final double out = sin.execute(digit) / cos.execute(digit);

        tryWriteToFile(new String[] {String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName()});

        return out;
    }
}
