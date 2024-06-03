package integration.pages;

import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;

public class LoginPage {

    public String login = "loginTesting@yandex.ru";
    public String pass = "oI|hvFlIAP|AqSW7VF@J";

    @FindBy(xpath = "")
    public WebElement loginField;

    @FindBy(xpath = "")
    public WebElement continueButton;
}
