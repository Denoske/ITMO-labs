package lab2.mathematics.trigonometric;

public class SinFunc extends TrigExecutable{


    @Override
    public double execute(final double digit) {
        double x = digit;

        if (x >= 0)
        {
            while (x > Math.PI * 2)
            {
                x -= Math.PI * 2;
            }
        }
        else if (x < 0)
        {
            while (x < Math.PI * 2)
            {
                x += Math.PI * 2;
            }
        }

        double summ = 0;
        double fact = 1;
        double sign = 1;
        for (int i = 1; i < 200; i += 2)
        {
            summ += sign * Math.pow(x, i)/fact;
            sign *= -1;
            fact *= (i + 1) * (i + 2);
        }
        final double out = summ; // сделать аут человеком

        tryWriteToFile(new String[] {String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName()});

        return out;
    }
}
