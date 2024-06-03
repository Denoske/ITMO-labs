package integration.pages;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

// page_url = https://www.jetbrains.com/
public class MainPage {

    WebDriver driver;

    @FindBy(xpath = "//div[@class='TextInput__input TextInput__input_r8 SearchLineSuggest__inputControl']/span[@class='TextInput__box']/div[@class='TextInput__inputWrap']/input[@class='TextInput__control']")
    public WebElement searchInput;

    @FindBy(xpath = "//div[@class='IndexMarks__col'][1]/a[@class='IndexMarks__item'][2]/div[@class='IndexMarks__item-name']")
    public WebElement audiFilterButton;

    public String searchable(){
        final String search = "LADA";

        try{
            final WebElement adCloser = new WebDriverWait(driver, Duration.ofSeconds(2))
                    .pollingEvery(Duration.ofMillis(500))
                    .until(ExpectedConditions.presenceOfElementLocated(
                            By.xpath("//div[@class='Modal Modal_visible Modal_has-animation']/div[@class='Modal__container']/div[@class='Modal__closer']")));
            adCloser.click();
        }catch (Exception ignored){}

        searchInput.sendKeys(search);

        final WebElement ladaSearchLabel = new WebDriverWait(driver, Duration.ofSeconds(3))
                .pollingEvery(Duration.ofMillis(500))
                .until(ExpectedConditions.presenceOfElementLocated(
                        By.xpath("(//div[@class='SearchLineSuggestItem'])[1]"))
                );

        ladaSearchLabel.click();

        return search;
    }

//    @FindBy(xpath = "")
//    public WebElement a;

    public MainPage(final WebDriver driver) {
        this.driver = driver;
        PageFactory.initElements(driver, this);
    }
}
