package lab1.task1;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

public class TanTest {
    double delta = 0.01;

    @ParameterizedTest
    @ValueSource(doubles = {1.1, 5, 10})
    void positiveBig(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {0.9, 0.99, 0.8})
    void positiveCloseToOne(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {1, -1})
    void positivOneNegativeOne(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {0.6, 0.5, 0.4})
    void positiveMiddle(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {0.1, 0.05, 0.001})
    void positiveCloseToZero(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {0.0, 0.001, -0.001})
    void zero(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-0.1, -0.05, -0.001})
    void negativeCloseToZero(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-0.6, -0.5, -0.4})
    void negativeMiddle(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-0.9, -0.99, -0.8})
    void negativeCloseToOne(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }

    @ParameterizedTest
    @ValueSource(doubles = {-1.1, -5, -10})
    void negativeBig(double x)
    {
        assertEquals(FirstTask.tg(x), Math.tan(x), delta);
    }
}
