package lab2.mathematics.logarithmic;

public class LnFunc extends LogExecutable{

    @Override
    public double execute(final double digit, final double base) {

        if(base != Math.E){
            return 0;
//            throw new Error("Class Ln can count only E base");
        }


        double sum = 0;

        if (digit >= 0 && digit <= 2)
        {
            final double num = digit - 1;

            for (int i = 1; i < 1_000_000; i += 2)
            {
                sum += Math.pow(num, i)/(double)i - Math.pow(num, i+1)/(double)(i+1);
            }
        }
        else if (digit > 2)
        {

            final double num = digit / (digit - 1);

            for ( int i = 1; i < 500_000; i++ )
            {
                sum += 1.0 / (i * Math.pow(num, i));
            }
        }


        final double out = sum; // Сделать out человеком

        tryWriteToFile(new String[] {String.valueOf(digit), String.valueOf(out), this.getClass().getSimpleName()});

        return out;
    }
}
