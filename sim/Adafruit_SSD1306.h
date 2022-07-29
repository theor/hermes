//
// Created by theor on 2022-07-29.
//

#ifndef SIM_ADAFRUIT_SSD1306_H
#define SIM_ADAFRUIT_SSD1306_H


#include <Adafruit_GFX.h>

/// The following "raw" color names are kept for backwards client compatability
/// They can be disabled by predefining this macro before including the Adafruit
/// header client code will then need to be modified to use the scoped enum
/// values directly
#ifndef NO_ADAFRUIT_SSD1306_COLOR_COMPATIBILITY
#define BLACK SSD1306_BLACK     ///< Draw 'off' pixels
#define WHITE SSD1306_WHITE     ///< Draw 'on' pixels
#define INVERSE SSD1306_INVERSE ///< Invert pixels
#endif
/// fit into the SSD1306_ naming scheme
#define SSD1306_BLACK 0   ///< Draw 'off' pixels
#define SSD1306_WHITE 1   ///< Draw 'on' pixels
#define SSD1306_INVERSE 2 ///< Invert pixels

#define SSD1306_MEMORYMODE 0x20          ///< See datasheet
#define SSD1306_COLUMNADDR 0x21          ///< See datasheet
#define SSD1306_PAGEADDR 0x22            ///< See datasheet
#define SSD1306_SETCONTRAST 0x81         ///< See datasheet
#define SSD1306_CHARGEPUMP 0x8D          ///< See datasheet
#define SSD1306_SEGREMAP 0xA0            ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_DISPLAYALLON 0xA5        ///< Not currently used
#define SSD1306_NORMALDISPLAY 0xA6       ///< See datasheet
#define SSD1306_INVERTDISPLAY 0xA7       ///< See datasheet
#define SSD1306_SETMULTIPLEX 0xA8        ///< See datasheet
#define SSD1306_DISPLAYOFF 0xAE          ///< See datasheet
#define SSD1306_DISPLAYON 0xAF           ///< See datasheet
#define SSD1306_COMSCANINC 0xC0          ///< Not currently used
#define SSD1306_COMSCANDEC 0xC8          ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET 0xD3    ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5  ///< See datasheet
#define SSD1306_SETPRECHARGE 0xD9        ///< See datasheet
#define SSD1306_SETCOMPINS 0xDA          ///< See datasheet
#define SSD1306_SETVCOMDETECT 0xDB       ///< See datasheet

#define SSD1306_SETLOWCOLUMN 0x00  ///< Not currently used
#define SSD1306_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SSD1306_SETSTARTLINE 0x40  ///< See datasheet

#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26              ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27               ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL 0x2E                    ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL 0x2F                      ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3             ///< Set scroll range

/*!
    @brief  Class that stores state and functions for interacting with
            SSD1306 OLED displays.
*/
class Adafruit_SSD1306 : public Adafruit_GFX {
public:
    // NEW CONSTRUCTORS -- recommended for new projects
//    Adafruit_SSD1306(uint8_t w, uint8_t h, TwoWire *twi = &Wire,
//                     int8_t rst_pin = -1, uint32_t clkDuring = 400000UL,
//                     uint32_t clkAfter = 100000UL);
//    Adafruit_SSD1306(uint8_t w, uint8_t h, int8_t mosi_pin, int8_t sclk_pin,
//                     int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
//    Adafruit_SSD1306(uint8_t w, uint8_t h, SPIClass *spi, int8_t dc_pin,
//                     int8_t rst_pin, int8_t cs_pin, uint32_t bitrate = 8000000UL);
//
//    // DEPRECATED CONSTRUCTORS - for back compatibility, avoid in new projects
//    Adafruit_SSD1306(int8_t mosi_pin, int8_t sclk_pin, int8_t dc_pin,
//                     int8_t rst_pin, int8_t cs_pin);
//    Adafruit_SSD1306(int8_t dc_pin, int8_t rst_pin, int8_t cs_pin);
//    Adafruit_SSD1306(int8_t rst_pin = -1);
    Adafruit_SSD1306(uint8_t w, uint8_t h);

    ~Adafruit_SSD1306(void);

    bool begin();
    void display(void);
    void clearDisplay(void);
    void invertDisplay(bool i);
    void dim(bool dim);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void startscrollright(uint8_t start, uint8_t stop);
    void startscrollleft(uint8_t start, uint8_t stop);
    void startscrolldiagright(uint8_t start, uint8_t stop);
    void startscrolldiagleft(uint8_t start, uint8_t stop);
    void stopscroll(void);
    void ssd1306_command(uint8_t c);
    bool getPixel(int16_t x, int16_t y);
    uint8_t *getBuffer(void);
    bool inverted;

protected:
    void drawFastHLineInternal(int16_t x, int16_t y, int16_t w, uint16_t color);
    void drawFastVLineInternal(int16_t x, int16_t y, int16_t h, uint16_t color);


    uint8_t *buffer; ///< Buffer data used for display buffer. Allocated when
    ///< begin method is called.
    int8_t i2caddr;  ///< I2C address initialized when begin method is called.
    int8_t vccstate; ///< VCC selection, set by begin method.
    int8_t page_end; ///< not used


    uint8_t contrast; ///< normal contrast setting for this device
};


#endif //SIM_ADAFRUIT_SSD1306_H
