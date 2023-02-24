package weblab4.services.areaChecker;

import org.springframework.stereotype.Service;

import java.util.ArrayList;

@Service
public class CheckerBuilder {
    private final AreaChecker checker = new AreaChecker(new ArrayList<>());

    public CheckerBuilder initAreaChecker(){
        checker.setListOfConditions(new ArrayList<>());
        return this;
    }

    public CheckerBuilder addTriangleIn4Quoter(){
        AreaCheckCondition triangleIn4QuoterCondition = (double x, double y, double r) ->
                (x - r / 2 <= y && y <= 0 && x >= 0);
        checker.getListOfConditions().add(triangleIn4QuoterCondition);
        return this;
    }

    public CheckerBuilder addCircleIn3Quoter(){
        AreaCheckCondition circleIn3QuoterCondition = (double x, double y, double r) ->
                (x <= 0 && y <= 0 && (Math.pow(x, 2) + Math.pow(y, 2) <= Math.pow((r / 2), 2)));
        checker.getListOfConditions().add(circleIn3QuoterCondition);
        return this;
    }

    public CheckerBuilder addSquare1Quoter(){
        AreaCheckCondition squareIn1QuoterCondition = (double x, double y, double r) ->
                (x >= 0 && x <= r && y >= 0 && y <= r);
        checker.getListOfConditions().add(squareIn1QuoterCondition);
        return this;
    }

    public AreaChecker getChecker(){
        return checker;
    }
}
