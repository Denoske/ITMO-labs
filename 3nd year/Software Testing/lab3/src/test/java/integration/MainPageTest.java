package integration;

import integration.pages.MainPage;
import integration.pages.SalePage;
import integration.pages.SearchPage;
import org.junit.jupiter.api.*;
import org.junit.jupiter.api.extension.ExtendWith;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeOptions;

import org.openqa.selenium.edge.EdgeOptions;
import org.openqa.selenium.firefox.FirefoxOptions;
import org.openqa.selenium.ie.InternetExplorerOptions;
import org.openqa.selenium.remote.AbstractDriverOptions;
import org.openqa.selenium.remote.RemoteWebDriver;
import org.openqa.selenium.safari.SafariOptions;

import java.net.MalformedURLException;
import java.net.URL;
import java.time.Duration;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

@ExtendWith(DriverExtension.class)
@TestInstance(TestInstance.Lifecycle.PER_CLASS)
public class MainPageTest{

    private final String browser;
    private WebDriver driver;

    public MainPageTest(final String browserConst){
        browser = browserConst;
    }

    @BeforeAll
    void initDriver() throws MalformedURLException {

        AbstractDriverOptions options = new ChromeOptions();

        if ("Chrome".equalsIgnoreCase(browser)) {
            options = new ChromeOptions();
        }
        else if ("Firefox".equalsIgnoreCase(browser)) {
            options = new FirefoxOptions();
        }
        else if ("Edge".equalsIgnoreCase(browser)) {
            options = new EdgeOptions();
        }
        else if ("Safari".equalsIgnoreCase(browser)) {
            options = new SafariOptions();
        }
        else if ("internet explorer".equalsIgnoreCase(browser)) {
            options = new InternetExplorerOptions();
        }

        final Map<String, Object> capabilityMap = new HashMap<>();
        capabilityMap.put("sessionTimeout", "0.5m");
        capabilityMap.put("enableVNC", true);
        capabilityMap.put("enableVideo", true);
        capabilityMap.put("videoName", "last test");

        options.setCapability("selenoid:options", capabilityMap);



        driver = new RemoteWebDriver(new URL("http://localhost:4444/wd/hub"), options);
        driver.manage().window().maximize();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

    }

    @Nested
    class Filter{

        private SearchPage searchPage;

        @BeforeEach
        void goFilterPage(){
            driver.get(SearchPage.URL);
            searchPage = new SearchPage(driver);
        }

        @Test
        void filterByBodyType(){
            Assertions.assertEquals(searchPage.filterByCarType(), new SalePage(driver).bodyType.getText().toLowerCase(Locale.ROOT));
        }

        @Test
        void filterByEngine(){

            final String choice = searchPage.filterByEngine();

            final String[] dataSplit = new SalePage(driver).engine.getText().toLowerCase(Locale.ROOT).split("/");

            Assertions.assertEquals(choice, dataSplit[2].trim());
        }

        @Test
        void filterByDriveUnit(){
            Assertions.assertEquals(searchPage.filterByDriveUnit().toLowerCase(Locale.ROOT), new SalePage(driver).drive.getText().toLowerCase(Locale.ROOT));
        }

        @Test
        void filterByTransmission(){
            Assertions.assertTrue(List.of(new String[]{"автоматическая", "автомат", "робот", "вариатор"}).contains(searchPage.filterByTransmission()));
        }

        @Test
        void filterByYearFrom(){
            Assertions.assertTrue(searchPage.filterByYearFrom() <= Integer.parseInt(new SalePage(driver).yearOfManufacture.getText()));
        }

        @Test
        void filterByMileageFrom(){

            final int mileage = 200_000;

            Assertions.assertTrue(mileage <= searchPage.filterByMileageFrom(String.valueOf(mileage)));
        }

        @Test
        void filterByPriceFrom(){

            final int price = 2_000_000;

            Assertions.assertTrue(price <= searchPage.filterByPriceFrom(String.valueOf(price)));
        }

    }

    @Nested
    class Search{

        private MainPage mainPage;

        @BeforeEach
        void goSearchPage(){
            driver.get("https://auto.ru/");

            mainPage = new MainPage(driver);
        }

        @Test
        void searchAble(){

            final String searchTitle = mainPage.searchable();

            Assertions.assertTrue(new SearchPage(driver).firstSearchCar.getText().contains(searchTitle));
        }

        @Test
        void filterAbleAudi(){
            mainPage.audiFilterButton.click();

            final SearchPage searchPage = new SearchPage(driver);

            Assertions.assertTrue(searchPage.firstSearchCar.getText().contains("Audi"));
        }
    }



    @Nested
    @TestInstance(TestInstance.Lifecycle.PER_CLASS)
    class SalePost{

        private SalePage salePage;

        @BeforeAll
        public void goSalePage(){
            driver.get("https://auto.ru/cars/used/sale/lamborghini/urus/1118748585-aac44f12/");

            salePage = new SalePage(driver);
        }

        @Test
        void title(){
            Assertions.assertEquals(salePage.title.getText(), salePage.testTitle);
        }

//        @Test
//        void sellerName(){
//            Assertions.assertEquals(salePage.sellerName.getText(), salePage.testSellerName);
//        }

        @Test
        void price(){
            Assertions.assertEquals(salePage.price.getText(), salePage.testPrice);
        }

        @Test
        void availability(){
            Assertions.assertEquals(salePage.availability.getText(), salePage.testAvailability);
        }

        @Test
        void yearOfManufacture(){
            Assertions.assertEquals(salePage.yearOfManufacture.getText(), salePage.testYearOfManufacture);
        }

        @Test
        void kmAge(){
            Assertions.assertEquals(salePage.kmAge.getText(), salePage.testKmAge);
        }

        @Test
        void bodyType(){
            Assertions.assertEquals(salePage.bodyType.getText(), salePage.testBodyType);
        }

        @Test
        void color(){
            Assertions.assertEquals(salePage.color.getText(), salePage.testColor);
        }

        @Test
        void engine(){
            Assertions.assertEquals(salePage.engine.getText(), salePage.testEngine);
        }

        @Test
        void transportTax(){
            Assertions.assertEquals(salePage.transportTax.getText(), salePage.testTransportTax);
        }

        @Test
        void transmission(){
            Assertions.assertEquals(salePage.transmission.getText(), salePage.testTransmission);
        }

        @Test
        void wheel(){
            Assertions.assertEquals(salePage.wheel.getText(), salePage.testWheel);
        }

        @Test
        void state(){
            Assertions.assertEquals(salePage.state.getText(), salePage.testState);
        }

        @Test
        void ownersCount(){
            Assertions.assertEquals(salePage.ownersCount.getText(), salePage.testOwnersCount);
        }

        @Test
        void pts(){
            Assertions.assertEquals(salePage.pts.getText(), salePage.testPts);
        }

        @Test
        void customs(){
            Assertions.assertEquals(salePage.customs.getText(), salePage.testCustoms);
        }

//        @Test
//        void exchange(){
//            Assertions.assertEquals(salePage.exchange.getText(), salePage.testExchange);
//        }

//        @Test
//        void description(){
//            Assertions.assertEquals(salePage.description.getText(), salePage.testDescription);
//        }

        @Test
        void drive(){
            Assertions.assertEquals(salePage.drive.getText(), salePage.testDrive);
        }

        @Test
        void id(){
            Assertions.assertEquals(salePage.id.getText(), salePage.testID);
        }
    }


}
