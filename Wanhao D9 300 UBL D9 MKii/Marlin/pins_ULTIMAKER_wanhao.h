#if !defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)
  #error "Oops!  Make sure you have 'Arduino Mega' selected from the 'Tools -> Boards' menu."
#endif
#define DEFAULT_MACHINE_NAME    "Ultimaker"
#define DEFAULT_SOURCE_CODE_URL "https://github.com/Ultimaker/Marlin"
#define BOARD_NAME              "Ultimaker <1.5.4"
#define LARGE_FLASH true
//
// Z Probe (when not Z_MIN_PIN)
//
#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN  18
#endif
//
// Steppers
//
#define X_STEP_PIN 25
#define X_DIR_PIN 23
#define X_MIN_PIN  22
#define X_MAX_PIN -1
#define X_ENABLE_PIN 27
#define Y_STEP_PIN 32
#define Y_DIR_PIN 33
#define Y_MIN_PIN 26
#define Y_MAX_PIN -1
#define Y_ENABLE_PIN 31
#define Z_STEP_PIN 35
#define Z_DIR_PIN 36
#define Z_MIN_PIN 29
#define Z_MAX_PIN -1
#define Z_ENABLE_PIN 34
#define E0_STEP_PIN         42
#define E0_DIR_PIN          43
#define E0_ENABLE_PIN       37
#define E1_STEP_PIN         49
#define E1_DIR_PIN          47
#define E1_ENABLE_PIN       48
//
// Limit Switches
#if 0
#define X_MIN_PIN          15
#define X_MAX_PIN          14
#define Y_MIN_PIN          17
#define Y_MAX_PIN          16
#define Z_MIN_PIN          19
#define Z_MAX_PIN          18
#endif
//
// Temperature
//
#define HEATER_BED_PIN 4
#define TEMP_BED_PIN 10
#define HEATER_0_PIN  2
#define TEMP_0_PIN 8
#define HEATER_1_PIN 3
#define TEMP_1_PIN 9
#define HEATER_2_PIN -1
#define TEMP_2_PIN -1
//
// LCD / Controller
//
#define LCD_PINS_RS 20
#define LCD_PINS_ENABLE 15
#define LCD_PINS_D4 14
#define LCD_PINS_D5 21
#define LCD_PINS_D6 5
#define LCD_PINS_D7 6
#define BEEPER_PIN 18
//buttons are directly attached
#define BTN_EN1 40
#define BTN_EN2 41
#define BTN_ENC 19  //the click
#define BLEN_C 2
#define BLEN_B 1
#define BLEN_A 0
#define SD_DETECT_PIN 39
//encoder rotation values
#define encrot0 0
#define encrot1 1
#define encrot2 3
#define encrot3 2
#define SDPOWER            -1
#define SDSS               53
#define MAX6675_SS         13
#define LED_PIN            8
#define SERVO0_PIN         9
#define FAN_PIN            7
#define PS_ON_PIN          24
#define KILL_PIN           -1
#define SUICIDE_PIN        -1  //PIN that has to be turned on right after start, to keep power flowing.
#define SAFETY_TRIGGERED_PIN     28 //PIN to detect the safety circuit has triggered
#define MAIN_VOLTAGE_MEASURE_PIN 14 //Analogue PIN to measure the main voltage, with a 100k - 4k7 resitor divider.
#undef MOTOR_CURRENT_PWM_XY_PIN
#undef MOTOR_CURRENT_PWM_Z_PIN
#undef MOTOR_CURRENT_PWM_E_PIN
#define MOTOR_CURRENT_PWM_XY_PIN 44
#define MOTOR_CURRENT_PWM_Z_PIN 45
#define MOTOR_CURRENT_PWM_E_PIN 46
#define DEFAULT_PWM_MOTOR_CURRENT {1200, 1000, 1000}
//Motor current PWM conversion, PWM value = MotorCurrentSetting * 255 / range
#define MOTOR_CURRENT_PWM_RANGE 2782
#define   POW_BREAK_CHECK_PIN         63//断电检测脚,不要与其它功能引脚冲突 在Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h中定义
//#define   PS_ON_PIN                   11
