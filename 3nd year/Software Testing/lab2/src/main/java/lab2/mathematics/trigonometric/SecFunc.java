package lab2.mathematics.trigonometric;

public class SecFunc extends TrigExecutable{

    private final TrigExecutable cos;

    public SecFunc(final TrigExecutable cos) {
        super();
        this.cos = cos;
    }

    @Override
    public double execute(final double digit) {

        final double out = 1 / cos.execute(digit);

        tryWriteToFile(new String[] {String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName()});

        return out;
    }
}
