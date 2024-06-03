package integration.pages;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

// page_url = https://auto.ru/cars/used/sale/lamborghini/urus/1118748585-aac44f12/
public class SalePage {

    public String testAvailability = "На заказ";
    public String testYearOfManufacture = "2019";
    public String testKmAge = "82 000 км";
    public String testBodyType = "внедорожник 5 дв.";
    public String testColor = "серый";
    public String testEngine = "4.0 л / 650 л.с. / Бензин";
    public String testTransportTax = "219 375 ₽ / год";
    public String testTransmission = "автоматическая";
    public String testDrive = "полный";
    public String testWheel = "Левый";
    public String testState = "Не требует ремонта";
    public String testOwnersCount = "1 владелец";
    public String testPts = "Оригинал";
    public String testCustoms = "Растаможен";
//    public String testExchange = "Рассмотрю варианты";
    public String testTitle = "Lamborghini Urus, 2019";
    public String testID = "№ 1118748585";
    public String testPrice = "18 000 000 ₽";
    public String testSellerName = "legocar125";
    public String testDescription = "Автомобили под заказ из Южной Кореи. Выбор огромный, различных авто.\n" +
            "Возможны разные варианты по комплектации.\n" +
            "Доставка по всей России!\n" +
            "\n" +
            "Внимание! Цена указана с учетом текущего курса и может варьироваться, как в большую, так и в меньшую сторону.\n" +
            "\n" +
            "Расчет принимаем в любой валюте.\n" +
            "\n" +
            "Ввоз подержанных автомобилей из Японии, США, Китая и Кореи не ограничен. Предоставим";


    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_availability']/span[@class='CardInfoRow__cell'][2]")
    public WebElement availability;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_year']/span[@class='CardInfoRow__cell'][2]")
    public WebElement yearOfManufacture;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_kmAge']/span[@class='CardInfoRow__cell'][2]")
    public WebElement kmAge;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_bodytype']/span[@class='CardInfoRow__cell'][2]")
    public WebElement bodyType;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_color']/span[@class='CardInfoRow__cell'][2]")
    public WebElement color;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_engine']/span[@class='CardInfoRow__cell'][2]/div")
    public WebElement engine;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_transportTax']/span[@class='CardInfoRow__cell'][2]")
    public WebElement transportTax;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_transmission']/span[@class='CardInfoRow__cell'][2]")
    public WebElement transmission;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_drive']/span[@class='CardInfoRow__cell'][2]")
    public WebElement drive;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_wheel']/span[@class='CardInfoRow__cell'][2]")
    public WebElement wheel;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_state']/span[@class='CardInfoRow__cell'][2]")
    public WebElement state;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_ownersCount']/span[@class='CardInfoRow__cell'][2]")
    public WebElement ownersCount;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_pts']/span[@class='CardInfoRow__cell'][2]")
    public WebElement pts;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_customs']/span[@class='CardInfoRow__cell'][2]")
    public WebElement customs;

    @FindBy(xpath = "//li[@class='CardInfoRow CardInfoRow_exchange']/span[@class='CardInfoRow__cell'][2]")
    public WebElement exchange;

    @FindBy(xpath = "//h1[@class='CardHead__title']")
    public WebElement title;

    @FindBy(xpath = "//div[@class='CardHead__infoItem CardHead__id']")
    public WebElement id;

    @FindBy(xpath = "//span[@class='OfferPriceCaption__price']")
    public WebElement price;

    @FindBy(xpath = "//div[@class='CardSellerNamePlace__name']")
    public WebElement sellerName;

    @FindBy(xpath = "//div[@class='CardDescriptionHTML']/span")
    public WebElement description;

    public SalePage(final WebDriver driver) {
        PageFactory.initElements(driver, this);
    }
}
