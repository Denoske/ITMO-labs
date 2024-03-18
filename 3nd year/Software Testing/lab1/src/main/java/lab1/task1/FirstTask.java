package lab1.task1;

public class FirstTask {
    public static double tg(double x){
        double sin_x = t_sin(x);
        double cos_x = t_cos(x);
        double tan_x;
        if( x == 0.0 ){
            return 0.0;
        } else if (x % Math.PI/2 == 0){
            return Double.NaN;
        } else{
            tan_x = sin_x/cos_x;
        }
        return tan_x;
    }
    private static double t_sin(double x){
        int n=0;
        double  s = x;
        double a = x;

        while (n<1000 && Math.abs(a) > 0.0001){
            n++;
            a *= -x*x/(2.0*n)/(2.0*n+1.0);
            s +=a;
        }

        return s;
    }
    private static double t_cos(double x){
        int n = 0;
        double s = 1;
        double a = 1;

        while (n<1000 && Math.abs(a) > 0.0001){
            n++;
            a *= -x*x/(2.0*n-1.0)/(2.0*n);
            s += a;
        }

        return s;
    }
}
