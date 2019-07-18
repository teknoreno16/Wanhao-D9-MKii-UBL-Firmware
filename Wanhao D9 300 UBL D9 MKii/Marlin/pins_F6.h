#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops!  Make sure you have 'Arduino Mega' selected from the 'Tools -> Boards' menu."
#endif
#ifndef BOARD_NAME
  #define BOARD_NAME "F6"
#endif
#define LARGE_FLASH true
#define X_STEP_PIN         54   
#define X_DIR_PIN          55   
#define X_ENABLE_PIN       38
#define X_MIN_PIN          63   
#define Y_STEP_PIN         60   
#define Y_DIR_PIN          61   
#define Y_ENABLE_PIN       56   
#define Y_MIN_PIN          14
#define Z_STEP_PIN         48
#define Z_DIR_PIN          62   
#define Z_ENABLE_PIN       43
#define Z_MIN_PIN          18
#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24
#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
#define E2_STEP_PIN        59   
#define E2_DIR_PIN         65   
#define E2_ENABLE_PIN      40
#define FAN_PIN            2
#define KILL_PIN           -1
#define HEATER_0_PIN       7
#define HEATER_1_PIN       8
#define HEATER_2_PIN       9
#define HEATER_BED_PIN     10
#define TEMP_0_PIN         PIN_A14  
#define TEMP_1_PIN         PIN_A15  
#define TEMP_2_PIN         PIN_A14
#define TEMP_BED_PIN       PIN_A15
#define SD_DETECT_PIN       49
#define SERVO0_PIN         -1
#define SDSS               53
#define LED_PIN            13
#ifndef FILWIDTH_PIN
#define FILWIDTH_PIN       12
#endif
#if ENABLED(ULTRA_LCD)
#define LCD_PINS_RS         37
#define LCD_PINS_ENABLE     36
#define LCD_PINS_D4         34
#define LCD_PINS_D5         35
#define LCD_PINS_D6         32
#define LCD_PINS_D7         33
#define BEEPER_PIN        27
#define BTN_EN2           28
#define BTN_EN1           29
#define BTN_ENC           30
#endif
#define POW_BREAK_CHECK_PIN         19  
