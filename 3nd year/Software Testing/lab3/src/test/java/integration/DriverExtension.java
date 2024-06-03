package integration;

import org.junit.jupiter.api.extension.*;

public class DriverExtension implements ParameterResolver {

    // проверить настчет работает ли без эксепленов
    @Override
    public boolean supportsParameter(final ParameterContext parameterContext, final ExtensionContext extensionContext){
        return parameterContext.getParameter().getType().equals(String.class);
    }

    @Override
    public Object resolveParameter(final ParameterContext parameterContext, final ExtensionContext extensionContext){
        return extensionContext.getConfigurationParameter("browser").orElse(null);
    }
}
