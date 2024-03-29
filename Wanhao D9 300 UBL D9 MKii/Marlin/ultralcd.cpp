#include "ultralcd.h"
#if ENABLED(ULTRA_LCD)
#include "Marlin.h"
#include "language.h"
#include "cardreader.h"
#include "temperature.h"
#include "planner.h"
#include "stepper.h"
#include "configuration_store.h"
#include "utility.h"
#if HAS_BUZZER && DISABLED(LCD_USE_I2C_BUZZER)
  #include "buzzer.h"
#endif
#if ENABLED(PRINTCOUNTER)
  #include "printcounter.h"
  #include "duration_t.h"
#endif
#if ENABLED(BLTOUCH)
  #include "endstops.h"
#endif
#if ENABLED(AUTO_BED_LEVELING_UBL)
  #include "ubl.h"
  bool ubl_lcd_map_control = false;
#endif
int16_t lcd_preheat_hotend_temp[2], lcd_preheat_bed_temp[2], lcd_preheat_fan_speed[2];
#if ENABLED(FILAMENT_LCD_DISPLAY) && ENABLED(SDSUPPORT)
  millis_t previous_lcd_status_ms = 0;
#endif
#if ENABLED(BABYSTEPPING)
  long babysteps_done = 0; 
  #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
    static void lcd_babystep_zoffset();
  #else
    static void lcd_babystep_z();
  #endif
#endif
uint8_t lcd_status_message_level;
char lcd_status_message[3 * (LCD_WIDTH) + 1] = WELCOME_MSG; 
#if ENABLED(STATUS_MESSAGE_SCROLLING)
  uint8_t status_scroll_pos = 0;
#endif
#if ENABLED(DOGLCD)
  #include "ultralcd_impl_DOGM.h"
  #include <U8glib.h>
#else
  #include "ultralcd_impl_HD44780.h"
#endif
void lcd_status_screen();
millis_t next_lcd_update_ms;
uint8_t lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW; 
uint16_t max_display_update_time = 0;
#if ENABLED(DOGLCD)
  bool drawing_screen = false;
#endif
#if ENABLED(DAC_STEPPER_CURRENT)
  #include "stepper_dac.h" 
  uint8_t driverPercent[XYZE];
#endif
#if PIN_EXISTS(SD_DETECT)
  uint8_t lcd_sd_status;
#endif
#if ENABLED(ULTIPANEL)
  #ifndef TALL_FONT_CORRECTION
    #define TALL_FONT_CORRECTION 0
  #endif
  typedef void (*screenFunc_t)();
  #if HAS_POWER_SWITCH
    extern bool powersupply_on;
  #endif
  void lcd_main_menu();
  void lcd_tune_menu();
  void lcd_prepare_menu();
  void lcd_move_menu();
  void lcd_control_menu();
  void lcd_control_temperature_menu();
  void lcd_control_temperature_preheat_material1_settings_menu();
  void lcd_control_temperature_preheat_material2_settings_menu();
  void lcd_control_motion_menu();
  void lcd_control_filament_menu();
  #if ENABLED(LCD_INFO_MENU)
    #if ENABLED(PRINTCOUNTER)
      void lcd_info_stats_menu();
    #endif
    void lcd_info_thermistors_menu();
    void lcd_info_board_menu();
    void lcd_info_menu();
  #endif 
  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    void lcd_advanced_pause_toocold_menu();
    void lcd_advanced_pause_option_menu();
    void lcd_advanced_pause_init_message();
    void lcd_advanced_pause_unload_message();
    void lcd_advanced_pause_insert_message();
    void lcd_advanced_pause_load_message();
    void lcd_advanced_pause_heat_nozzle();
    void lcd_advanced_pause_extrude_message();
    void lcd_advanced_pause_resume_message();
  #endif
  #if ENABLED(DAC_STEPPER_CURRENT)
    void dac_driver_commit();
    void dac_driver_getValues();
    void lcd_dac_menu();
    void lcd_dac_write_eeprom();
  #endif
  #if ENABLED(FWRETRACT)
    void lcd_control_retract_menu();
  #endif
  #if ENABLED(DELTA_CALIBRATION_MENU)
    void lcd_delta_calibrate_menu();
  #endif
  #if ENABLED(MESH_BED_LEVELING) && ENABLED(LCD_BED_LEVELING)
    #include "mesh_bed_leveling.h"
    extern void mesh_probing_done();
  #endif
  #define menu_action_back(dummy) _menu_action_back()
  void _menu_action_back();
  void menu_action_submenu(screenFunc_t data);
  void menu_action_gcode(const char* pgcode);
  void menu_action_function(screenFunc_t data);
  #define DECLARE_MENU_EDIT_TYPE(_type, _name) \
    bool _menu_edit_ ## _name(); \
    void menu_edit_ ## _name(); \
    void menu_edit_callback_ ## _name(); \
    void _menu_action_setting_edit_ ## _name(const char * const pstr, _type* const ptr, const _type minValue, const _type maxValue); \
    void menu_action_setting_edit_ ## _name(const char * const pstr, _type * const ptr, const _type minValue, const _type maxValue); \
    void menu_action_setting_edit_callback_ ## _name(const char * const pstr, _type * const ptr, const _type minValue, const _type maxValue, const screenFunc_t callback, const bool live=false); \
    typedef void _name##_void
  DECLARE_MENU_EDIT_TYPE(int16_t, int3);
  DECLARE_MENU_EDIT_TYPE(uint8_t, int8);
  DECLARE_MENU_EDIT_TYPE(float, float3);
  DECLARE_MENU_EDIT_TYPE(float, float32);
  DECLARE_MENU_EDIT_TYPE(float, float43);
  DECLARE_MENU_EDIT_TYPE(float, float5);
  DECLARE_MENU_EDIT_TYPE(float, float51);
  DECLARE_MENU_EDIT_TYPE(float, float52);
  DECLARE_MENU_EDIT_TYPE(float, float62);
  DECLARE_MENU_EDIT_TYPE(uint32_t, long5);
  void menu_action_setting_edit_bool(const char* pstr, bool* ptr);
  void menu_action_setting_edit_callback_bool(const char* pstr, bool* ptr, screenFunc_t callbackFunc);
  #if ENABLED(SDSUPPORT)
    void lcd_sdcard_menu();
    void menu_action_sdfile(const char* filename, char* longFilename);
    void menu_action_sddirectory(const char* filename, char* longFilename);
  #endif
  #ifndef ENCODER_FEEDRATE_DEADZONE
    #define ENCODER_FEEDRATE_DEADZONE 10
  #endif
  #ifndef ENCODER_STEPS_PER_MENU_ITEM
    #define ENCODER_STEPS_PER_MENU_ITEM 5
  #endif
  #ifndef ENCODER_PULSES_PER_STEP
    #define ENCODER_PULSES_PER_STEP 1
  #endif
  #define _MENU_ITEM_PART_1(TYPE, ...) \
    if (_menuLineNr == _thisItemNr) { \
      if (lcd_clicked && encoderLine == _thisItemNr) {
  #define _MENU_ITEM_PART_2(TYPE, LABEL, ...) \
        menu_action_ ## TYPE(__VA_ARGS__); \
        if (screen_changed) return; \
      } \
      if (lcdDrawUpdate) \
        lcd_implementation_drawmenu_ ## TYPE(encoderLine == _thisItemNr, _lcdLineNr, PSTR(LABEL), ## __VA_ARGS__); \
    } \
    ++_thisItemNr
  #define MENU_ITEM(TYPE, LABEL, ...) do { \
      _skipStatic = false; \
      _MENU_ITEM_PART_1(TYPE, ## __VA_ARGS__); \
      _MENU_ITEM_PART_2(TYPE, LABEL, ## __VA_ARGS__); \
    }while(0)
  #define MENU_BACK(LABEL) MENU_ITEM(back, LABEL, 0)
  #define STATIC_ITEM(LABEL, ...) \
    if (_menuLineNr == _thisItemNr) { \
      if (_skipStatic && encoderLine <= _thisItemNr) { \
        encoderPosition += ENCODER_STEPS_PER_MENU_ITEM; \
        ++encoderLine; \
      } \
      if (lcdDrawUpdate) \
        lcd_implementation_drawmenu_static(_lcdLineNr, PSTR(LABEL), ## __VA_ARGS__); \
    } \
    ++_thisItemNr
  #if ENABLED(ENCODER_RATE_MULTIPLIER)
    bool encoderRateMultiplierEnabled;
    #define ENCODER_RATE_MULTIPLY(F) (encoderRateMultiplierEnabled = F)
    #define MENU_MULTIPLIER_ITEM(type, label, ...) do { \
        _MENU_ITEM_PART_1(type, ## __VA_ARGS__); \
        encoderRateMultiplierEnabled = true; \
        lastEncoderMovementMillis = 0; \
        _MENU_ITEM_PART_2(type, label, ## __VA_ARGS__); \
      }while(0)
  #else 
    #define ENCODER_RATE_MULTIPLY(F) NOOP
  #endif 
  #define MENU_ITEM_DUMMY() do { _thisItemNr++; }while(0)
  #define MENU_ITEM_EDIT(type, label, ...) MENU_ITEM(setting_edit_ ## type, label, PSTR(label), ## __VA_ARGS__)
  #define MENU_ITEM_EDIT_CALLBACK(type, label, ...) MENU_ITEM(setting_edit_callback_ ## type, label, PSTR(label), ## __VA_ARGS__)
  #if ENABLED(ENCODER_RATE_MULTIPLIER)
    #define MENU_MULTIPLIER_ITEM_EDIT(type, label, ...) MENU_MULTIPLIER_ITEM(setting_edit_ ## type, label, PSTR(label), ## __VA_ARGS__)
    #define MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(type, label, ...) MENU_MULTIPLIER_ITEM(setting_edit_callback_ ## type, label, PSTR(label), ## __VA_ARGS__)
  #else 
    #define MENU_MULTIPLIER_ITEM_EDIT(type, label, ...) MENU_ITEM(setting_edit_ ## type, label, PSTR(label), ## __VA_ARGS__)
    #define MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(type, label, ...) MENU_ITEM(setting_edit_callback_ ## type, label, PSTR(label), ## __VA_ARGS__)
  #endif 
  #define START_SCREEN_OR_MENU(LIMIT) \
    ENCODER_DIRECTION_MENUS(); \
    ENCODER_RATE_MULTIPLY(false); \
    if (encoderPosition > 0x8000) encoderPosition = 0; \
    static int8_t _countedItems = 0; \
    int8_t encoderLine = encoderPosition / (ENCODER_STEPS_PER_MENU_ITEM); \
    if (_countedItems > 0 && encoderLine >= _countedItems - (LIMIT)) { \
      encoderLine = max(0, _countedItems - (LIMIT)); \
      encoderPosition = encoderLine * (ENCODER_STEPS_PER_MENU_ITEM); \
    }
  #define SCREEN_OR_MENU_LOOP() \
    int8_t _menuLineNr = encoderTopLine, _thisItemNr; \
    for (int8_t _lcdLineNr = 0; _lcdLineNr < LCD_HEIGHT - (TALL_FONT_CORRECTION); _lcdLineNr++, _menuLineNr++) { \
      _thisItemNr = 0
  #define START_SCREEN() \
    START_SCREEN_OR_MENU(LCD_HEIGHT - (TALL_FONT_CORRECTION)); \
    encoderTopLine = encoderLine; \
    bool _skipStatic = false; \
    SCREEN_OR_MENU_LOOP()
  #define START_MENU() \
    START_SCREEN_OR_MENU(1); \
    screen_changed = false; \
    NOMORE(encoderTopLine, encoderLine); \
    if (encoderLine >= encoderTopLine + LCD_HEIGHT - (TALL_FONT_CORRECTION)) { \
      encoderTopLine = encoderLine - (LCD_HEIGHT - (TALL_FONT_CORRECTION) - 1); \
    } \
    bool _skipStatic = true; \
    SCREEN_OR_MENU_LOOP()
  #define END_SCREEN() \
    } \
    _countedItems = _thisItemNr
  #define END_MENU() \
    } \
    _countedItems = _thisItemNr; \
    UNUSED(_skipStatic)
  #if ENABLED(REVERSE_MENU_DIRECTION)
    int8_t encoderDirection = 1;
    #define ENCODER_DIRECTION_NORMAL() (encoderDirection = 1)
    #define ENCODER_DIRECTION_MENUS() (encoderDirection = -1)
  #else
    #define ENCODER_DIRECTION_NORMAL() ;
    #define ENCODER_DIRECTION_MENUS() ;
  #endif
  volatile int8_t encoderDiff; 
  uint32_t encoderPosition;
  millis_t lastEncoderMovementMillis = 0;
  bool lcd_clicked, wait_for_unclick;
  volatile uint8_t buttons;
  millis_t next_button_update_ms;
  #if ENABLED(REPRAPWORLD_KEYPAD)
    volatile uint8_t buttons_reprapworld_keypad;
  #endif
  #if ENABLED(LCD_HAS_SLOW_BUTTONS)
    volatile uint8_t slow_buttons;
  #endif
  screenFunc_t currentScreen = lcd_status_screen;
  int8_t encoderTopLine;
  typedef struct {
    screenFunc_t menu_function;
    uint32_t encoder_position;
  } menuPosition;
  menuPosition screen_history[6];
  uint8_t screen_history_depth = 0;
  bool screen_changed, defer_return_to_status;
  const char *editLabel;
  void *editValue;
  int32_t minEditValue, maxEditValue;
  screenFunc_t callbackFunc;
  bool liveEdit;
  const float manual_feedrate_mm_m[] = MANUAL_FEEDRATE;
  millis_t manual_move_start_time = 0;
  int8_t manual_move_axis = (int8_t)NO_AXIS;
  #if EXTRUDERS > 1
    int8_t manual_move_e_index = 0;
  #else
    #define manual_move_e_index 0
  #endif
  #if ENABLED(PIDTEMP)
    float raw_Ki, raw_Kd; 
  #endif
  void lcd_goto_screen(screenFunc_t screen, const uint32_t encoder = 0) {
    if (currentScreen != screen) {
      #if ENABLED(DOUBLECLICK_FOR_Z_BABYSTEPPING) && ENABLED(BABYSTEPPING)
        static millis_t doubleclick_expire_ms = 0;
        if (screen == lcd_main_menu) {
          if (currentScreen == lcd_status_screen)
            doubleclick_expire_ms = millis() + DOUBLECLICK_MAX_INTERVAL;
        }
        else if (screen == lcd_status_screen && currentScreen == lcd_main_menu && PENDING(millis(), doubleclick_expire_ms))
          screen =
            #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
              lcd_babystep_zoffset
            #else
              lcd_babystep_z
            #endif
          ;
      #endif
      currentScreen = screen;
      encoderPosition = encoder;
      if (screen == lcd_status_screen) {
        defer_return_to_status = false;
        screen_history_depth = 0;
      }
      lcd_implementation_clear();
      #if DISABLED(DOGLCD) && ENABLED(AUTO_BED_LEVELING_UBL)
        if (!ubl_lcd_map_control) lcd_set_custom_characters(
          #if ENABLED(LCD_PROGRESS_BAR)
            screen == lcd_status_screen
          #endif
        );
      #elif ENABLED(LCD_PROGRESS_BAR)
        lcd_set_custom_characters(screen == lcd_status_screen);
      #endif
      lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
      screen_changed = true;
      #if ENABLED(DOGLCD)
        drawing_screen = false;
      #endif
    }
  }
  static const char moving[] PROGMEM = MSG_MOVING;
  static const char *sync_message = moving;
  void _lcd_synchronize() {
    static bool no_reentry = false;
    if (lcdDrawUpdate) lcd_implementation_drawmenu_static(LCD_HEIGHT >= 4 ? 1 : 0, sync_message);
    if (no_reentry) return;
    no_reentry = true;
    screenFunc_t old_screen = currentScreen;
    lcd_goto_screen(_lcd_synchronize);
    stepper.synchronize();
    no_reentry = false;
    lcd_goto_screen(old_screen);
  }
  void lcd_synchronize(const char * const msg=NULL) {
    sync_message = msg ? msg : moving;
    _lcd_synchronize();
  }
  void lcd_return_to_status() { lcd_goto_screen(lcd_status_screen); }
  void lcd_save_previous_screen() {
    if (screen_history_depth < COUNT(screen_history)) {
      screen_history[screen_history_depth].menu_function = currentScreen;
      screen_history[screen_history_depth].encoder_position = encoderPosition;
      ++screen_history_depth;
    }
  }
  void lcd_goto_previous_menu() {
    if (screen_history_depth > 0) {
      --screen_history_depth;
      lcd_goto_screen(
        screen_history[screen_history_depth].menu_function,
        screen_history[screen_history_depth].encoder_position
      );
    }
    else
      lcd_return_to_status();
  }
#endif 
void lcd_status_screen() {
  #if ENABLED(ULTIPANEL)
    ENCODER_DIRECTION_NORMAL();
    ENCODER_RATE_MULTIPLY(false);
  #endif
  #if ENABLED(LCD_PROGRESS_BAR)
    millis_t ms = millis();
    #if DISABLED(PROGRESS_MSG_ONCE)
      if (ELAPSED(ms, progress_bar_ms + PROGRESS_BAR_MSG_TIME + PROGRESS_BAR_BAR_TIME)) {
        progress_bar_ms = ms;
      }
    #endif
    #if PROGRESS_MSG_EXPIRE > 0
      if (expire_status_ms > 0) {
        #if ENABLED(SDSUPPORT)
          if (card.isFileOpen()) {
            if (IS_SD_PRINTING) {
              if (ELAPSED(ms, expire_status_ms)) {
                lcd_status_message[0] = '\0';
                expire_status_ms = 0;
              }
            }
            else {
              expire_status_ms += LCD_UPDATE_INTERVAL;
            }
          }
          else {
            expire_status_ms = 0;
          }
        #else
          expire_status_ms = 0;
        #endif 
      }
    #endif
  #endif 
  #if ENABLED(ULTIPANEL)
    if (lcd_clicked) {
      #if ENABLED(FILAMENT_LCD_DISPLAY) && ENABLED(SDSUPPORT)
        previous_lcd_status_ms = millis();  
      #endif
      lcd_implementation_init( 
        #if ENABLED(LCD_PROGRESS_BAR)
          false
        #endif
      );
      lcd_goto_screen(lcd_main_menu);
      return;
    }
    #if ENABLED(ULTIPANEL_FEEDMULTIPLY)
      const int16_t new_frm = feedrate_percentage + (int32_t)encoderPosition;
      if ((feedrate_percentage < 100 && new_frm > 100) || (feedrate_percentage > 100 && new_frm < 100)) {
        feedrate_percentage = 100;
        encoderPosition = 0;
      }
      else if (feedrate_percentage == 100) {
        if ((int32_t)encoderPosition > ENCODER_FEEDRATE_DEADZONE) {
          feedrate_percentage += (int32_t)encoderPosition - (ENCODER_FEEDRATE_DEADZONE);
          encoderPosition = 0;
        }
        else if ((int32_t)encoderPosition < -(ENCODER_FEEDRATE_DEADZONE)) {
          feedrate_percentage += (int32_t)encoderPosition + ENCODER_FEEDRATE_DEADZONE;
          encoderPosition = 0;
        }
      }
      else {
        feedrate_percentage = new_frm;
        encoderPosition = 0;
      }
    #endif 
    feedrate_percentage = constrain(feedrate_percentage, 10, 999);
  #endif 
  lcd_implementation_status_screen();
}
void lcd_reset_status() { lcd_setstatusPGM(PSTR(""), -1); }
void kill_screen(const char* lcd_msg) {
  lcd_init();
  lcd_setalertstatusPGM(lcd_msg);
  #if ENABLED(DOGLCD)
    u8g.firstPage();
    do {
      lcd_kill_screen();
    } while (u8g.nextPage());
  #else
    lcd_kill_screen();
  #endif
}
#if ENABLED(ULTIPANEL)
  void lcd_buzz(long duration, uint16_t freq) {
    #if ENABLED(LCD_USE_I2C_BUZZER)
      lcd.buzz(duration, freq);
    #elif PIN_EXISTS(BEEPER)
      buzzer.tone(duration, freq);
    #else
      UNUSED(duration); UNUSED(freq);
    #endif
  }
  void lcd_quick_feedback() {
    lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW;
    buttons = 0;
    next_button_update_ms = millis() + 500;
    lcd_buzz(LCD_FEEDBACK_FREQUENCY_DURATION_MS, LCD_FEEDBACK_FREQUENCY_HZ);
    #if ENABLED(LCD_USE_I2C_BUZZER)
      delay(10);
    #elif PIN_EXISTS(BEEPER)
      for (int8_t i = 5; i--;) { buzzer.tick(); delay(2); }
    #endif
  }
  void lcd_completion_feedback(const bool good) {
    if (good) {
      lcd_buzz(100, 659);
      lcd_buzz(100, 698);
    }
    else lcd_buzz(20, 440);
  }
  inline void line_to_current_z() {
    planner.buffer_line_kinematic(current_position, MMM_TO_MMS(manual_feedrate_mm_m[Z_AXIS]), active_extruder);
  }
  inline void line_to_z(const float &z) {
    current_position[Z_AXIS] = z;
    line_to_current_z();
  }
  #if ENABLED(SDSUPPORT)
    void lcd_sdcard_pause() {
      card.pauseSDPrint();
      print_job_timer.pause();
      #if ENABLED(PARK_HEAD_ON_PAUSE)
        enqueue_and_echo_commands_P(PSTR("M125"));
      #endif
      lcd_setstatusPGM(PSTR(MSG_PRINT_PAUSED), -1);
    }
#if PIN_EXISTS(PS_ON)
    inline void lcd_ifShutdownComplete()
    {
        GLOBAL_var_V005=!GLOBAL_var_V005;
    }
#endif
#ifdef DEFAULT_ENERGY_CONSERVE_HEIGHT
    inline void lcd_ifEnergyConserve()
    {
        ifEnergyConserve = !ifEnergyConserve;
    }
#endif
    void lcd_sdcard_resume() {
      #if ENABLED(PARK_HEAD_ON_PAUSE)
        enqueue_and_echo_commands_P(PSTR("M24"));
      #else
        card.startFileprint();
        print_job_timer.start();
      #endif
      lcd_reset_status();
    }
    void lcd_sdcard_stop() {
      card.stopSDPrint();
      clear_command_queue();
      quickstop_stepper();
      print_job_timer.stop();
      thermalManager.disable_all_heaters();
      #if FAN_COUNT > 0
        for (uint8_t i = 0; i < FAN_COUNT; i++) fanSpeeds[i] = 0;
      #endif
      wait_for_heatup = false;
      lcd_setstatusPGM(PSTR(MSG_PRINT_ABORTED), -1);
      lcd_return_to_status();
    }
  #endif 
  #if ENABLED(MENU_ITEM_CASE_LIGHT)
    extern int case_light_brightness;
    extern bool case_light_on;
    extern void update_case_light();
    void case_light_menu() {
      START_MENU();
      MENU_BACK(MSG_MAIN);
      MENU_ITEM_EDIT_CALLBACK(int3, MSG_CASE_LIGHT_BRIGHTNESS, &case_light_brightness, 0, 255, update_case_light, true);
      MENU_ITEM_EDIT_CALLBACK(bool, MSG_CASE_LIGHT, (bool*)&case_light_on, update_case_light);
      END_MENU();
    }
  #endif 
  #if ENABLED(BLTOUCH)
    static void bltouch_menu() {
      START_MENU();
      MENU_BACK(MSG_MAIN);
      MENU_ITEM(gcode, MSG_BLTOUCH_RESET, PSTR("M280 P" STRINGIFY(Z_ENDSTOP_SERVO_NR) " S" STRINGIFY(BLTOUCH_RESET)));
      MENU_ITEM(gcode, MSG_BLTOUCH_SELFTEST, PSTR("M280 P" STRINGIFY(Z_ENDSTOP_SERVO_NR) " S" STRINGIFY(BLTOUCH_SELFTEST)));
      MENU_ITEM(gcode, MSG_BLTOUCH_DEPLOY, PSTR("M280 P" STRINGIFY(Z_ENDSTOP_SERVO_NR) " S" STRINGIFY(BLTOUCH_DEPLOY)));
      MENU_ITEM(gcode, MSG_BLTOUCH_STOW, PSTR("M280 P" STRINGIFY(Z_ENDSTOP_SERVO_NR) " S" STRINGIFY(BLTOUCH_STOW)));
      END_MENU();
    }
  #endif 
  #if ENABLED(LCD_PROGRESS_BAR_TEST)
    static void progress_bar_test() {
      static int8_t bar_percent = 0;
      if (lcd_clicked) {
        lcd_goto_previous_menu();
        lcd_set_custom_characters(false);
        return;
      }
      bar_percent += (int8_t)encoderPosition;
      bar_percent = constrain(bar_percent, 0, 100);
      encoderPosition = 0;
      lcd_implementation_drawmenu_static(0, PSTR(MSG_PROGRESS_BAR_TEST), true, true);
      lcd.setCursor((LCD_WIDTH) / 2 - 2, LCD_HEIGHT - 2);
      lcd.print(itostr3(bar_percent)); lcd.write('%');
      lcd.setCursor(0, LCD_HEIGHT - 1); lcd_draw_progress_bar(bar_percent);
    }
    void _progress_bar_test() {
      lcd_goto_screen(progress_bar_test);
      lcd_set_custom_characters();
    }
  #endif 
  #if HAS_DEBUG_MENU
    void lcd_debug_menu() {
      START_MENU();
      MENU_BACK(MSG_MAIN); 
      #if ENABLED(LCD_PROGRESS_BAR_TEST)
        MENU_ITEM(submenu, MSG_PROGRESS_BAR_TEST, _progress_bar_test);
      #endif
      END_MENU();
    }
  #endif 
  #if ENABLED(CUSTOM_USER_MENUS)
    #ifdef USER_SCRIPT_DONE
      #define _DONE_SCRIPT "\n" USER_SCRIPT_DONE
    #else
      #define _DONE_SCRIPT ""
    #endif
    void _lcd_user_gcode(const char * const cmd) {
      lcd_return_to_status();
      enqueue_and_echo_commands_P(cmd);
    }
    #if defined(USER_DESC_1) && defined(USER_GCODE_1)
      void lcd_user_gcode_1() { _lcd_user_gcode(PSTR(USER_GCODE_1 _DONE_SCRIPT)); }
    #endif
    #if defined(USER_DESC_2) && defined(USER_GCODE_2)
      void lcd_user_gcode_2() { _lcd_user_gcode(PSTR(USER_GCODE_2 _DONE_SCRIPT)); }
    #endif
    #if defined(USER_DESC_3) && defined(USER_GCODE_3)
      void lcd_user_gcode_3() { _lcd_user_gcode(PSTR(USER_GCODE_3 _DONE_SCRIPT)); }
    #endif
    #if defined(USER_DESC_4) && defined(USER_GCODE_4)
      void lcd_user_gcode_4() { _lcd_user_gcode(PSTR(USER_GCODE_4 _DONE_SCRIPT)); }
    #endif
    #if defined(USER_DESC_5) && defined(USER_GCODE_5)
      void lcd_user_gcode_5() { _lcd_user_gcode(PSTR(USER_GCODE_5 _DONE_SCRIPT)); }
    #endif
    void _lcd_user_menu() {
      START_MENU();
      MENU_BACK(MSG_MAIN);
      #if defined(USER_DESC_1) && defined(USER_GCODE_1)
        MENU_ITEM(function, USER_DESC_1, lcd_user_gcode_1);
      #endif
      #if defined(USER_DESC_2) && defined(USER_GCODE_2)
        MENU_ITEM(function, USER_DESC_2, lcd_user_gcode_2);
      #endif
      #if defined(USER_DESC_3) && defined(USER_GCODE_3)
        MENU_ITEM(function, USER_DESC_3, lcd_user_gcode_3);
      #endif
      #if defined(USER_DESC_4) && defined(USER_GCODE_4)
        MENU_ITEM(function, USER_DESC_4, lcd_user_gcode_4);
      #endif
      #if defined(USER_DESC_5) && defined(USER_GCODE_5)
        MENU_ITEM(function, USER_DESC_5, lcd_user_gcode_5);
      #endif
      END_MENU();
    }
  #endif
    static bool ifPause = false;
    static inline void myLcdPausePrint()
    {
        GLOBAL_var_V00E=MACRO_var_V020;
        ifPause = true;
    }
    static inline void myLcdResumePrint()
    {
        GLOBAL_var_V00E=MACRO_var_V021;
        ifPause = false;
        lcd_return_to_status();
    }
    static inline void myLcdStopPrint()
    {
        GLOBAL_var_V00E=MACRO_var_V022;
        ifPause = false;
    }
  void lcd_main_menu() {
    START_MENU();
    MENU_BACK(MSG_WATCH);
    #if ENABLED(CUSTOM_USER_MENUS)
      MENU_ITEM(submenu, MSG_USER_MENU, _lcd_user_menu);
    #endif
    #if HAS_DEBUG_MENU
      MENU_ITEM(submenu, MSG_DEBUG_MENU, lcd_debug_menu);
    #endif
    #if ENABLED(MENU_ITEM_CASE_LIGHT)
      if (USEABLE_HARDWARE_PWM(CASE_LIGHT_PIN)) {
        MENU_ITEM(submenu, MSG_CASE_LIGHT, case_light_menu);
      }
      else
        MENU_ITEM_EDIT_CALLBACK(bool, MSG_CASE_LIGHT, (bool*)&case_light_on, update_case_light);
    #endif
    if (planner.movesplanned() || IS_SD_PRINTING) {
      MENU_ITEM(submenu, MSG_TUNE, lcd_tune_menu);
    }
    else {
      MENU_ITEM(submenu, MSG_PREPARE, lcd_prepare_menu);
      #if ENABLED(DELTA_CALIBRATION_MENU)
        MENU_ITEM(submenu, MSG_DELTA_CALIBRATE, lcd_delta_calibrate_menu);
      #endif
    }
    MENU_ITEM(submenu, MSG_CONTROL, lcd_control_menu);
    const char* str;
#if PIN_EXISTS(PS_ON)
    if(GLOBAL_var_V005)
    {
        MENU_ITEM(function, "Finish to turn off", lcd_ifShutdownComplete); 
    }
    else
    {
        MENU_ITEM(function, "Finish to turn on", lcd_ifShutdownComplete);
    }
#endif
#ifdef DEFAULT_ENERGY_CONSERVE_HEIGHT
    if (ifEnergyConserve)
    {
        MENU_ITEM(function, "Energy conserve", lcd_ifEnergyConserve);
    }
    else
    {
        MENU_ITEM(function, "Normal print", lcd_ifEnergyConserve);
    }
#endif
    #if ENABLED(SDSUPPORT)
      if (card.cardOK) {
          if (card.isFileOpen()
              || ifPause
              ) 
          {
            if (card.sdprinting)
              MENU_ITEM(function, MSG_PAUSE_PRINT, myLcdPausePrint);
          else
              MENU_ITEM(function, MSG_RESUME_PRINT, myLcdResumePrint);
          MENU_ITEM(function, MSG_STOP_PRINT, myLcdStopPrint);
        }
        else{
          MENU_ITEM(submenu, MSG_CARD_MENU, lcd_sdcard_menu);
          #if !PIN_EXISTS(SD_DETECT)
            MENU_ITEM(gcode, MSG_CNG_SDCARD, PSTR("M21"));  
          #endif
        }
      }
      else {
        MENU_ITEM(submenu, MSG_NO_CARD, lcd_sdcard_menu);
        #if !PIN_EXISTS(SD_DETECT)
          MENU_ITEM(gcode, MSG_INIT_SDCARD, PSTR("M21")); 
        #endif
      }
    #endif 
    #if ENABLED(LCD_INFO_MENU)
      MENU_ITEM(submenu, MSG_INFO_MENU, lcd_info_menu);
    #endif
    END_MENU();
  }
#define MY_MENU_ITEM_PART_1(TYPE, LABEL,offset, ...) \
    if (_menuLineNr == _thisItemNr) {\
    if (lcdDrawUpdate) \
    lcd_implementation_drawmenu_ ## TYPE(encoderLine == _thisItemNr, offset, PSTR(LABEL), ## __VA_ARGS__); \
    if (lcd_clicked && encoderLine == _thisItemNr) {
#define MY_MENU_ITEM_PART_2(TYPE, ...) \
    menu_action_ ## TYPE(__VA_ARGS__); \
    if (screen_changed) return;}}\
    ++_thisItemNr
#define MY_MENU_ITEM(TYPE, LABEL, offset,...) do { \
    _skipStatic = false; \
    MY_MENU_ITEM_PART_1(TYPE, LABEL,offset, ## __VA_ARGS__); \
    MY_MENU_ITEM_PART_2(TYPE,  ## __VA_ARGS__); \
    } while (0)
  void lcdContinuPrint()
  {
      defer_return_to_status = false;
      enqueue_and_echo_commands_P(PSTR("M1101"));
      lcd_goto_screen(lcd_status_screen);
  }
  void lcdAbortContinuePrint()
  {
      defer_return_to_status = false;
      enqueue_and_echo_commands_P(PSTR("M1103"));
      lcd_goto_screen(lcd_status_screen);
  }
  void askForReprint() {
      defer_return_to_status = true;
      START_MENU();
      MY_MENU_ITEM(function, "Yes", 3, lcdContinuPrint);
      MY_MENU_ITEM(function, "No", 4, lcdAbortContinuePrint);
      END_MENU();
      if (lcdDrawUpdate)
      {
      #if ENABLED(DOGLCD)
          u8g.setColorIndex(1);
          u8g.setPrintPos(0, 12 * 1);
          lcd_print("Last print task is");
          u8g.setPrintPos(0, 12 * 2);
          lcd_print("uncompleted,do you");
          u8g.setPrintPos(0, 12 * 3);
          lcd_print("want to continue?");
      #else 
          lcd.setCursor(0, 0); 
          lcd.setCursor(3, 0);
          lcd_print("Print the");
          #if LCD_HEIGHT > 2
          lcd.setCursor(0, 1); 
          lcd.setCursor(3, 0);
          lcd_print("unfinished task?");
          #endif 
      #endif
      }
  }
  #if HAS_M206_COMMAND
    void lcd_set_home_offsets() {
      enqueue_and_echo_commands_P(PSTR("M428"));
      lcd_return_to_status();
    }
  #endif
  #if ENABLED(BABYSTEPPING)
    void _lcd_babystep(const AxisEnum axis, const char* msg) {
      if (lcd_clicked) { defer_return_to_status = false; return lcd_goto_previous_menu(); }
      ENCODER_DIRECTION_NORMAL();
      if (encoderPosition) {
        const int16_t babystep_increment = (int32_t)encoderPosition * (BABYSTEP_MULTIPLICATOR);
        encoderPosition = 0;
        lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
        thermalManager.babystep_axis(axis, babystep_increment);
        babysteps_done += babystep_increment;
      }
      if (lcdDrawUpdate)
        lcd_implementation_drawedit(msg, ftostr43sign(planner.steps_to_mm[axis] * babysteps_done));
    }
    #if ENABLED(BABYSTEP_XY)
      void _lcd_babystep_x() { _lcd_babystep(X_AXIS, PSTR(MSG_BABYSTEPPING_X)); }
      void _lcd_babystep_y() { _lcd_babystep(Y_AXIS, PSTR(MSG_BABYSTEPPING_Y)); }
      void lcd_babystep_x() { lcd_goto_screen(_lcd_babystep_x); babysteps_done = 0; defer_return_to_status = true; }
      void lcd_babystep_y() { lcd_goto_screen(_lcd_babystep_y); babysteps_done = 0; defer_return_to_status = true; }
    #endif
    #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
      void lcd_babystep_zoffset() {
        if (lcd_clicked) { defer_return_to_status = false; return lcd_goto_previous_menu(); }
        defer_return_to_status = true;
        ENCODER_DIRECTION_NORMAL();
        if (encoderPosition) {
          const int16_t babystep_increment = (int32_t)encoderPosition * (BABYSTEP_MULTIPLICATOR);
          encoderPosition = 0;
          const float new_zoffset = zprobe_zoffset + planner.steps_to_mm[Z_AXIS] * babystep_increment;
          if (WITHIN(new_zoffset, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX)) {
            if (planner.abl_enabled)
              thermalManager.babystep_axis(Z_AXIS, babystep_increment);
            zprobe_zoffset = new_zoffset;
            refresh_zprobe_zoffset(true);
            lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
          }
        }
        if (lcdDrawUpdate)
          lcd_implementation_drawedit(PSTR(MSG_ZPROBE_ZOFFSET), ftostr43sign(zprobe_zoffset));
      }
    #else 
      void _lcd_babystep_z() { _lcd_babystep(Z_AXIS, PSTR(MSG_BABYSTEPPING_Z)); }
      void lcd_babystep_z() { lcd_goto_screen(_lcd_babystep_z); babysteps_done = 0; defer_return_to_status = true; }
    #endif 
  #endif 
  #if ENABLED(AUTO_BED_LEVELING_UBL)
    float mesh_edit_value, mesh_edit_accumulator; 
    static int16_t ubl_encoderPosition = 0;
    static void _lcd_mesh_fine_tune(const char* msg) {
      defer_return_to_status = true;
      if (ubl.encoder_diff) {
        ubl_encoderPosition = (ubl.encoder_diff > 0) ? 1 : -1;
        ubl.encoder_diff = 0;
        mesh_edit_accumulator += float(ubl_encoderPosition) * 0.005 / 2.0;
        mesh_edit_value = mesh_edit_accumulator;
        encoderPosition = 0;
        lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
        const int32_t rounded = (int32_t)(mesh_edit_value * 1000.0);
        mesh_edit_value = float(rounded - (rounded % 5L)) / 1000.0;
      }
      if (lcdDrawUpdate)
        lcd_implementation_drawedit(msg, ftostr43sign(mesh_edit_value));
    }
    void _lcd_mesh_edit_NOP() {
      defer_return_to_status = true;
    }
    float lcd_mesh_edit() {
      lcd_goto_screen(_lcd_mesh_edit_NOP);
      lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
      _lcd_mesh_fine_tune(PSTR("Mesh Editor"));
      return mesh_edit_value;
    }
    void lcd_mesh_edit_setup(float initial) {
      mesh_edit_value = mesh_edit_accumulator = initial;
      lcd_goto_screen(_lcd_mesh_edit_NOP);
    }
    void _lcd_z_offset_edit() {
      _lcd_mesh_fine_tune(PSTR("Z-Offset: "));
    }
    float lcd_z_offset_edit() {
      lcd_goto_screen(_lcd_z_offset_edit);
      return mesh_edit_value;
    }
    void lcd_z_offset_edit_setup(float initial) {
      mesh_edit_value = mesh_edit_accumulator = initial;
      lcd_goto_screen(_lcd_z_offset_edit);
    }
  #endif 
  #if HAS_TEMP_HOTEND
    #if WATCH_HOTENDS
      #define _WATCH_FUNC(N) thermalManager.start_watching_heater(N)
    #else
      #define _WATCH_FUNC(N) NOOP
    #endif
    void watch_temp_callback_E0() { _WATCH_FUNC(0); }
    #if HOTENDS > 1
      void watch_temp_callback_E1() { _WATCH_FUNC(1); }
      #if HOTENDS > 2
        void watch_temp_callback_E2() { _WATCH_FUNC(2); }
        #if HOTENDS > 3
          void watch_temp_callback_E3() { _WATCH_FUNC(3); }
          #if HOTENDS > 4
            void watch_temp_callback_E4() { _WATCH_FUNC(4); }
          #endif 
        #endif 
      #endif 
    #endif 
  #endif 
  void watch_temp_callback_bed() {
    #if WATCH_THE_BED
      thermalManager.start_watching_bed();
    #endif
  }
  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    void lcd_enqueue_filament_change() {
      #if ENABLED(PREVENT_COLD_EXTRUSION)
        if (!DEBUGGING(DRYRUN) && !thermalManager.allow_cold_extrude &&
            thermalManager.degTargetHotend(active_extruder) < thermalManager.extrude_min_temp) {
          lcd_save_previous_screen();
          lcd_goto_screen(lcd_advanced_pause_toocold_menu);
          return;
        }
      #endif
      lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_INIT);
      enqueue_and_echo_commands_P(PSTR("M600 B0"));
    }
  #endif 
  void lcd_tune_menu() {
    START_MENU();
    MENU_BACK(MSG_MAIN);
    MENU_ITEM_EDIT(int3, MSG_SPEED, &feedrate_percentage, 10, 999);
    #if ENABLED(MESH_BED_LEVELING) && ENABLED(LCD_BED_LEVELING)
      MENU_ITEM_EDIT(float43, MSG_BED_Z, &mbl.z_offset, -1, 1);
    #endif
    #if HOTENDS == 1
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE, &thermalManager.target_temperature[0], 0, HEATER_0_MAXTEMP - 15, watch_temp_callback_E0);
    #else 
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N1, &thermalManager.target_temperature[0], 0, HEATER_0_MAXTEMP - 15, watch_temp_callback_E0);
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N2, &thermalManager.target_temperature[1], 0, HEATER_1_MAXTEMP - 15, watch_temp_callback_E1);
      #if HOTENDS > 2
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N3, &thermalManager.target_temperature[2], 0, HEATER_2_MAXTEMP - 15, watch_temp_callback_E2);
        #if HOTENDS > 3
          MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N4, &thermalManager.target_temperature[3], 0, HEATER_3_MAXTEMP - 15, watch_temp_callback_E3);
          #if HOTENDS > 4
            MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N5, &thermalManager.target_temperature[4], 0, HEATER_4_MAXTEMP - 15, watch_temp_callback_E4);
          #endif 
        #endif 
      #endif 
    #endif 
    #if HAS_TEMP_BED
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_BED, &thermalManager.target_temperature_bed, 0, BED_MAXTEMP - 15, watch_temp_callback_bed);
    #endif
    #if FAN_COUNT > 0
      #if HAS_FAN0
        #if FAN_COUNT > 1
          #define MSG_1ST_FAN_SPEED MSG_FAN_SPEED " 1"
        #else
          #define MSG_1ST_FAN_SPEED MSG_FAN_SPEED
        #endif
        MENU_MULTIPLIER_ITEM_EDIT(int3, MSG_1ST_FAN_SPEED, &fanSpeeds[0], 0, 255);
      #endif
      #if HAS_FAN1
        MENU_MULTIPLIER_ITEM_EDIT(int3, MSG_FAN_SPEED " 2", &fanSpeeds[1], 0, 255);
      #endif
      #if HAS_FAN2
        MENU_MULTIPLIER_ITEM_EDIT(int3, MSG_FAN_SPEED " 3", &fanSpeeds[2], 0, 255);
      #endif
    #endif 
    #if EXTRUDERS == 1
      MENU_ITEM_EDIT(int3, MSG_FLOW, &flow_percentage[0], 10, 999);
    #else 
      MENU_ITEM_EDIT(int3, MSG_FLOW, &flow_percentage[active_extruder], 10, 999);
      MENU_ITEM_EDIT(int3, MSG_FLOW MSG_N1, &flow_percentage[0], 10, 999);
      MENU_ITEM_EDIT(int3, MSG_FLOW MSG_N2, &flow_percentage[1], 10, 999);
      #if EXTRUDERS > 2
        MENU_ITEM_EDIT(int3, MSG_FLOW MSG_N3, &flow_percentage[2], 10, 999);
        #if EXTRUDERS > 3
          MENU_ITEM_EDIT(int3, MSG_FLOW MSG_N4, &flow_percentage[3], 10, 999);
          #if EXTRUDERS > 4
            MENU_ITEM_EDIT(int3, MSG_FLOW MSG_N5, &flow_percentage[4], 10, 999);
          #endif 
        #endif 
      #endif 
    #endif 
    #if ENABLED(BABYSTEPPING)
      #if ENABLED(BABYSTEP_XY)
        MENU_ITEM(submenu, MSG_BABYSTEP_X, lcd_babystep_x);
        MENU_ITEM(submenu, MSG_BABYSTEP_Y, lcd_babystep_y);
      #endif
      #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
        MENU_ITEM(submenu, MSG_ZPROBE_ZOFFSET, lcd_babystep_zoffset);
      #else
        MENU_ITEM(submenu, MSG_BABYSTEP_Z, lcd_babystep_z);
      #endif
    #endif
    #if ENABLED(ADVANCED_PAUSE_FEATURE)
      if (!thermalManager.tooColdToExtrude(active_extruder))
        MENU_ITEM(function, MSG_FILAMENTCHANGE, lcd_enqueue_filament_change);
    #endif
    END_MENU();
  }
  #if ENABLED(DAC_STEPPER_CURRENT)
    void dac_driver_getValues() { LOOP_XYZE(i) driverPercent[i] = dac_current_get_percent((AxisEnum)i); }
    void dac_driver_commit() { dac_current_set_percents(driverPercent); }
    void dac_driver_eeprom_write() { dac_commit_eeprom(); }
    void lcd_dac_menu() {
      dac_driver_getValues();
      START_MENU();
      MENU_BACK(MSG_CONTROL);
      MENU_ITEM_EDIT_CALLBACK(int8, MSG_X " " MSG_DAC_PERCENT, &driverPercent[X_AXIS], 0, 100, dac_driver_commit);
      MENU_ITEM_EDIT_CALLBACK(int8, MSG_Y " " MSG_DAC_PERCENT, &driverPercent[Y_AXIS], 0, 100, dac_driver_commit);
      MENU_ITEM_EDIT_CALLBACK(int8, MSG_Z " " MSG_DAC_PERCENT, &driverPercent[Z_AXIS], 0, 100, dac_driver_commit);
      MENU_ITEM_EDIT_CALLBACK(int8, MSG_E " " MSG_DAC_PERCENT, &driverPercent[E_AXIS], 0, 100, dac_driver_commit);
      MENU_ITEM(function, MSG_DAC_EEPROM_WRITE, dac_driver_eeprom_write);
      END_MENU();
    }
  #endif 
  #if HAS_MOTOR_CURRENT_PWM
    void lcd_pwm_menu() {
      START_MENU();
      MENU_BACK(MSG_CONTROL);
      #if PIN_EXISTS(MOTOR_CURRENT_PWM_XY)
        MENU_ITEM_EDIT_CALLBACK(long5, MSG_X MSG_Y, &stepper.motor_current_setting[0], 100, 2000, Stepper::refresh_motor_power);
      #endif
      #if PIN_EXISTS(MOTOR_CURRENT_PWM_Z)
        MENU_ITEM_EDIT_CALLBACK(long5, MSG_Z, &stepper.motor_current_setting[1], 100, 2000, Stepper::refresh_motor_power);
      #endif
      #if PIN_EXISTS(MOTOR_CURRENT_PWM_E)
        MENU_ITEM_EDIT_CALLBACK(long5, MSG_E, &stepper.motor_current_setting[2], 100, 2000, Stepper::refresh_motor_power);
      #endif
      END_MENU();
    }
  #endif 
  constexpr int16_t heater_maxtemp[HOTENDS] = ARRAY_BY_HOTENDS(HEATER_0_MAXTEMP, HEATER_1_MAXTEMP, HEATER_2_MAXTEMP, HEATER_3_MAXTEMP, HEATER_4_MAXTEMP);
  void _lcd_preheat(const int16_t endnum, const int16_t temph, const int16_t tempb, const int16_t fan) {
    if (temph > 0) thermalManager.setTargetHotend(min(heater_maxtemp[endnum], temph), endnum);
    #if TEMP_SENSOR_BED != 0
      if (tempb >= 0) thermalManager.setTargetBed(tempb);
    #else
      UNUSED(tempb);
    #endif
    #if FAN_COUNT > 0
      #if FAN_COUNT > 1
        fanSpeeds[active_extruder < FAN_COUNT ? active_extruder : 0] = fan;
      #else
        fanSpeeds[0] = fan;
      #endif
    #else
      UNUSED(fan);
    #endif
    lcd_return_to_status();
  }
  #if TEMP_SENSOR_0 != 0
    void lcd_preheat_m1_e0_only() { _lcd_preheat(0, lcd_preheat_hotend_temp[0], -1, lcd_preheat_fan_speed[0]); }
    void lcd_preheat_m2_e0_only() { _lcd_preheat(0, lcd_preheat_hotend_temp[1], -1, lcd_preheat_fan_speed[1]); }
    #if TEMP_SENSOR_BED != 0
      void lcd_preheat_m1_e0() { _lcd_preheat(0, lcd_preheat_hotend_temp[0], lcd_preheat_bed_temp[0], lcd_preheat_fan_speed[0]); }
      void lcd_preheat_m2_e0() { _lcd_preheat(0, lcd_preheat_hotend_temp[1], lcd_preheat_bed_temp[1], lcd_preheat_fan_speed[1]); }
    #endif
  #endif
  #if HOTENDS > 1
    void lcd_preheat_m1_e1_only() { _lcd_preheat(1, lcd_preheat_hotend_temp[0], -1, lcd_preheat_fan_speed[0]); }
    void lcd_preheat_m2_e1_only() { _lcd_preheat(1, lcd_preheat_hotend_temp[1], -1, lcd_preheat_fan_speed[1]); }
    #if TEMP_SENSOR_BED != 0
      void lcd_preheat_m1_e1() { _lcd_preheat(1, lcd_preheat_hotend_temp[0], lcd_preheat_bed_temp[0], lcd_preheat_fan_speed[0]); }
      void lcd_preheat_m2_e1() { _lcd_preheat(1, lcd_preheat_hotend_temp[1], lcd_preheat_bed_temp[1], lcd_preheat_fan_speed[1]); }
    #endif
    #if HOTENDS > 2
      void lcd_preheat_m1_e2_only() { _lcd_preheat(2, lcd_preheat_hotend_temp[0], -1, lcd_preheat_fan_speed[0]); }
      void lcd_preheat_m2_e2_only() { _lcd_preheat(2, lcd_preheat_hotend_temp[1], -1, lcd_preheat_fan_speed[1]); }
      #if TEMP_SENSOR_BED != 0
        void lcd_preheat_m1_e2() { _lcd_preheat(2, lcd_preheat_hotend_temp[0], lcd_preheat_bed_temp[0], lcd_preheat_fan_speed[0]); }
        void lcd_preheat_m2_e2() { _lcd_preheat(2, lcd_preheat_hotend_temp[1], lcd_preheat_bed_temp[1], lcd_preheat_fan_speed[1]); }
      #endif
      #if HOTENDS > 3
        void lcd_preheat_m1_e3_only() { _lcd_preheat(3, lcd_preheat_hotend_temp[0], -1, lcd_preheat_fan_speed[0]); }
        void lcd_preheat_m2_e3_only() { _lcd_preheat(3, lcd_preheat_hotend_temp[1], -1, lcd_preheat_fan_speed[1]); }
        #if TEMP_SENSOR_BED != 0
          void lcd_preheat_m1_e3() { _lcd_preheat(3, lcd_preheat_hotend_temp[0], lcd_preheat_bed_temp[0], lcd_preheat_fan_speed[0]); }
          void lcd_preheat_m2_e3() { _lcd_preheat(3, lcd_preheat_hotend_temp[1], lcd_preheat_bed_temp[1], lcd_preheat_fan_speed[1]); }
        #endif
        #if HOTENDS > 4
          void lcd_preheat_m1_e4_only() { _lcd_preheat(4, lcd_preheat_hotend_temp[0], -1, lcd_preheat_fan_speed[0]); }
          void lcd_preheat_m2_e4_only() { _lcd_preheat(4, lcd_preheat_hotend_temp[1], -1, lcd_preheat_fan_speed[1]); }
          #if TEMP_SENSOR_BED != 0
            void lcd_preheat_m1_e4() { _lcd_preheat(4, lcd_preheat_hotend_temp[0], lcd_preheat_bed_temp[0], lcd_preheat_fan_speed[0]); }
            void lcd_preheat_m2_e4() { _lcd_preheat(4, lcd_preheat_hotend_temp[1], lcd_preheat_bed_temp[1], lcd_preheat_fan_speed[1]); }
          #endif
        #endif 
      #endif 
    #endif 
    void lcd_preheat_m1_all() {
      #if HOTENDS > 1
        thermalManager.setTargetHotend(lcd_preheat_hotend_temp[0], 1);
        #if HOTENDS > 2
          thermalManager.setTargetHotend(lcd_preheat_hotend_temp[0], 2);
          #if HOTENDS > 3
            thermalManager.setTargetHotend(lcd_preheat_hotend_temp[0], 3);
            #if HOTENDS > 4
              thermalManager.setTargetHotend(lcd_preheat_hotend_temp[0], 4);
            #endif 
          #endif 
        #endif 
      #endif 
      #if TEMP_SENSOR_BED != 0
        lcd_preheat_m1_e0();
      #else
        lcd_preheat_m1_e0_only();
      #endif
    }
    void lcd_preheat_m2_all() {
      #if HOTENDS > 1
        thermalManager.setTargetHotend(lcd_preheat_hotend_temp[1], 1);
        #if HOTENDS > 2
          thermalManager.setTargetHotend(lcd_preheat_hotend_temp[1], 2);
          #if HOTENDS > 3
            thermalManager.setTargetHotend(lcd_preheat_hotend_temp[1], 3);
            #if HOTENDS > 4
              thermalManager.setTargetHotend(lcd_preheat_hotend_temp[1], 4);
            #endif 
          #endif 
        #endif 
      #endif 
      #if TEMP_SENSOR_BED != 0
        lcd_preheat_m2_e0();
      #else
        lcd_preheat_m2_e0_only();
      #endif
    }
  #endif 
  #if TEMP_SENSOR_BED != 0
    void lcd_preheat_m1_bedonly() { _lcd_preheat(0, 0, lcd_preheat_bed_temp[0], lcd_preheat_fan_speed[0]); }
    void lcd_preheat_m2_bedonly() { _lcd_preheat(0, 0, lcd_preheat_bed_temp[1], lcd_preheat_fan_speed[1]); }
  #endif
  #if TEMP_SENSOR_0 != 0 && (TEMP_SENSOR_1 != 0 || TEMP_SENSOR_2 != 0 || TEMP_SENSOR_3 != 0 || TEMP_SENSOR_4 != 0 || TEMP_SENSOR_BED != 0)
    void lcd_preheat_m1_menu() {
      START_MENU();
      MENU_BACK(MSG_PREPARE);
      #if HOTENDS == 1
        #if TEMP_SENSOR_BED != 0
          MENU_ITEM(function, MSG_PREHEAT_1, lcd_preheat_m1_e0);
          MENU_ITEM(function, MSG_PREHEAT_1_END, lcd_preheat_m1_e0_only);
        #else
          MENU_ITEM(function, MSG_PREHEAT_1, lcd_preheat_m1_e0_only);
        #endif
      #else
        #if TEMP_SENSOR_BED != 0
          MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H1, lcd_preheat_m1_e0);
          MENU_ITEM(function, MSG_PREHEAT_1_END " " MSG_E1, lcd_preheat_m1_e0_only);
          MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H2, lcd_preheat_m1_e1);
          MENU_ITEM(function, MSG_PREHEAT_1_END " " MSG_E2, lcd_preheat_m1_e1_only);
        #else
          MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H1, lcd_preheat_m1_e0_only);
          MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H2, lcd_preheat_m1_e1_only);
        #endif
        #if HOTENDS > 2
          #if TEMP_SENSOR_BED != 0
            MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H3, lcd_preheat_m1_e2);
            MENU_ITEM(function, MSG_PREHEAT_1_END " " MSG_E3, lcd_preheat_m1_e2_only);
          #else
            MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H3, lcd_preheat_m1_e2_only);
          #endif
          #if HOTENDS > 3
            #if TEMP_SENSOR_BED != 0
              MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H4, lcd_preheat_m1_e3);
              MENU_ITEM(function, MSG_PREHEAT_1_END " " MSG_E4, lcd_preheat_m1_e3_only);
            #else
              MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H4, lcd_preheat_m1_e3_only);
            #endif
            #if HOTENDS > 4
              #if TEMP_SENSOR_BED != 0
                MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H5, lcd_preheat_m1_e4);
                MENU_ITEM(function, MSG_PREHEAT_1_END " " MSG_E5, lcd_preheat_m1_e4_only);
              #else
                MENU_ITEM(function, MSG_PREHEAT_1_N MSG_H5, lcd_preheat_m1_e4_only);
              #endif
            #endif 
          #endif 
        #endif 
        MENU_ITEM(function, MSG_PREHEAT_1_ALL, lcd_preheat_m1_all);
      #endif 
      #if TEMP_SENSOR_BED != 0
        MENU_ITEM(function, MSG_PREHEAT_1_BEDONLY, lcd_preheat_m1_bedonly);
      #endif
      END_MENU();
    }
    void lcd_preheat_m2_menu() {
      START_MENU();
      MENU_BACK(MSG_PREPARE);
      #if HOTENDS == 1
        #if TEMP_SENSOR_BED != 0
          MENU_ITEM(function, MSG_PREHEAT_2, lcd_preheat_m2_e0);
          MENU_ITEM(function, MSG_PREHEAT_2_END, lcd_preheat_m2_e0_only);
        #else
          MENU_ITEM(function, MSG_PREHEAT_2, lcd_preheat_m2_e0_only);
        #endif
      #else
        #if TEMP_SENSOR_BED != 0
          MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H1, lcd_preheat_m2_e0);
          MENU_ITEM(function, MSG_PREHEAT_2_END " " MSG_E1, lcd_preheat_m2_e0_only);
          MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H2, lcd_preheat_m2_e1);
          MENU_ITEM(function, MSG_PREHEAT_2_END " " MSG_E2, lcd_preheat_m2_e1_only);
        #else
          MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H1, lcd_preheat_m2_e0_only);
          MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H2, lcd_preheat_m2_e1_only);
        #endif
        #if HOTENDS > 2
          #if TEMP_SENSOR_BED != 0
            MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H3, lcd_preheat_m2_e2);
            MENU_ITEM(function, MSG_PREHEAT_2_END " " MSG_E3, lcd_preheat_m2_e2_only);
          #else
            MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H3, lcd_preheat_m2_e2_only);
          #endif
          #if HOTENDS > 3
            #if TEMP_SENSOR_BED != 0
              MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H4, lcd_preheat_m2_e3);
              MENU_ITEM(function, MSG_PREHEAT_2_END " " MSG_E4, lcd_preheat_m2_e3_only);
            #else
              MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H4, lcd_preheat_m2_e3_only);
            #endif
            #if HOTENDS > 4
              #if TEMP_SENSOR_BED != 0
                MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H5, lcd_preheat_m2_e4);
                MENU_ITEM(function, MSG_PREHEAT_2_END " " MSG_E5, lcd_preheat_m2_e4_only);
              #else
                MENU_ITEM(function, MSG_PREHEAT_2_N MSG_H5, lcd_preheat_m2_e4_only);
              #endif
            #endif 
          #endif 
        #endif 
        MENU_ITEM(function, MSG_PREHEAT_2_ALL, lcd_preheat_m2_all);
      #endif 
      #if TEMP_SENSOR_BED != 0
        MENU_ITEM(function, MSG_PREHEAT_2_BEDONLY, lcd_preheat_m2_bedonly);
      #endif
      END_MENU();
    }
  #endif 
  void lcd_cooldown() {
    #if FAN_COUNT > 0
      for (uint8_t i = 0; i < FAN_COUNT; i++) fanSpeeds[i] = 0;
    #endif
    thermalManager.disable_all_heaters();
    lcd_return_to_status();
  }
  #if ENABLED(SDSUPPORT) && ENABLED(MENU_ADDAUTOSTART)
    void lcd_autostart_sd() {
      card.autostart_index = 0;
      card.setroot();
      card.checkautostart(true);
    }
  #endif
  #if ENABLED(EEPROM_SETTINGS)
    static void lcd_store_settings()   { lcd_completion_feedback(settings.save()); }
    static void lcd_load_settings()    { lcd_completion_feedback(settings.load()); }
  #endif
  #if HAS_BED_PROBE && DISABLED(BABYSTEP_ZPROBE_OFFSET)
    static void lcd_refresh_zprobe_zoffset() { refresh_zprobe_zoffset(); }
  #endif
#if ENABLED(LCD_BED_LEVELING)
    static uint8_t manual_probe_index;
    constexpr uint8_t total_probe_points = (
      #if ENABLED(AUTO_BED_LEVELING_3POINT)
        3
      #elif ABL_GRID || ENABLED(MESH_BED_LEVELING)
        GRID_MAX_POINTS
      #endif
    );
    void _lcd_after_probing() {
      #if MANUAL_PROBE_HEIGHT > 0
        line_to_z(LOGICAL_Z_POSITION(Z_MIN_POS) + MANUAL_PROBE_HEIGHT);
      #endif
      #if MANUAL_PROBE_HEIGHT > 0 || ENABLED(MESH_BED_LEVELING)
        lcd_synchronize(PSTR(MSG_LEVEL_BED_DONE));
      #endif
      lcd_goto_previous_menu();
      lcd_completion_feedback();
      defer_return_to_status = false;
    }
    #if ENABLED(MESH_BED_LEVELING)
      inline void _manual_probe_goto_xy(float x, float y) {
        #if MANUAL_PROBE_HEIGHT > 0
          line_to_z(LOGICAL_Z_POSITION(Z_MIN_POS) + MANUAL_PROBE_HEIGHT);
        #endif
        current_position[X_AXIS] = LOGICAL_X_POSITION(x);
        current_position[Y_AXIS] = LOGICAL_Y_POSITION(y);
        planner.buffer_line_kinematic(current_position, MMM_TO_MMS(XY_PROBE_SPEED), active_extruder);
        #if MANUAL_PROBE_HEIGHT > 0
          line_to_z(LOGICAL_Z_POSITION(Z_MIN_POS));
        #endif
        lcd_synchronize();
      }
    #elif ENABLED(PROBE_MANUALLY)
      bool lcd_wait_for_move;
      void _lcd_level_bed_done() {
        if (!lcd_wait_for_move) _lcd_after_probing();
        if (lcdDrawUpdate) lcd_implementation_drawedit(PSTR(MSG_LEVEL_BED_DONE));
        lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
      }
    #endif
    void _lcd_level_goto_next_point();
    void _lcd_level_bed_get_z() {
      ENCODER_DIRECTION_NORMAL();
      if (lcd_clicked) {
        #if ENABLED(MESH_BED_LEVELING)
          mbl.set_zigzag_z(manual_probe_index, current_position[Z_AXIS]);
        #endif
        if (++manual_probe_index >= total_probe_points) {
          #if ENABLED(PROBE_MANUALLY)
            lcd_wait_for_move = true;
            enqueue_and_echo_commands_P(PSTR("G29 V1"));
            lcd_goto_screen(_lcd_level_bed_done);
          #elif ENABLED(MESH_BED_LEVELING)
            _lcd_after_probing();
            mbl.set_has_mesh(true);
            mesh_probing_done();
          #endif
        }
        else {
          _lcd_level_goto_next_point();
        }
        return;
      }
      if (encoderPosition) {
        refresh_cmd_timeout();
        const float z = current_position[Z_AXIS] + float((int32_t)encoderPosition) * (MBL_Z_STEP);
        line_to_z(constrain(z, -(LCD_PROBE_Z_RANGE) * 0.5, (LCD_PROBE_Z_RANGE) * 0.5));
        lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
        encoderPosition = 0;
      }
      if (lcdDrawUpdate) {
        const float v = current_position[Z_AXIS];
        lcd_implementation_drawedit(PSTR(MSG_MOVE_Z), ftostr43sign(v + (v < 0 ? -0.0001 : 0.0001), '+'));
      }
    }
    void _lcd_level_bed_moving() {
      if (lcdDrawUpdate) {
        char msg[10];
        sprintf_P(msg, PSTR("%i / %u"), (int)(manual_probe_index + 1), total_probe_points);
        lcd_implementation_drawedit(PSTR(MSG_LEVEL_BED_NEXT_POINT), msg);
      }
      lcdDrawUpdate = LCDVIEW_CALL_NO_REDRAW;
      #if ENABLED(PROBE_MANUALLY)
        if (!lcd_wait_for_move) lcd_goto_screen(_lcd_level_bed_get_z);
      #endif
    }
    void _lcd_level_goto_next_point() {
      lcd_goto_screen(_lcd_level_bed_moving);
      #if ENABLED(MESH_BED_LEVELING)
        int8_t px, py;
        mbl.zigzag(manual_probe_index, px, py);
        _manual_probe_goto_xy(
          LOGICAL_X_POSITION(mbl.index_to_xpos[px]),
          LOGICAL_Y_POSITION(mbl.index_to_ypos[py])
        );
        lcd_goto_screen(_lcd_level_bed_get_z);
      #elif ENABLED(PROBE_MANUALLY)
        lcd_wait_for_move = true;
        enqueue_and_echo_commands_P(PSTR("G29 V1"));
      #endif
    }
    void _lcd_level_bed_homing_done() {
      if (lcdDrawUpdate) lcd_implementation_drawedit(PSTR(MSG_LEVEL_BED_WAITING));
      if (lcd_clicked) {
        manual_probe_index = 0;
        _lcd_level_goto_next_point();
      }
    }
    void _lcd_level_bed_homing() {
      if (lcdDrawUpdate) lcd_implementation_drawedit(PSTR(MSG_LEVEL_BED_HOMING), NULL);
      lcdDrawUpdate = LCDVIEW_CALL_NO_REDRAW;
      if (axis_homed[X_AXIS] && axis_homed[Y_AXIS] && axis_homed[Z_AXIS])
        lcd_goto_screen(_lcd_level_bed_homing_done);
    }
    #if ENABLED(PROBE_MANUALLY)
      extern bool g29_in_progress;
    #endif
    void _lcd_level_bed_continue() {
      defer_return_to_status = true;
      axis_homed[X_AXIS] = axis_homed[Y_AXIS] = axis_homed[Z_AXIS] = false;
      lcd_goto_screen(_lcd_level_bed_homing);
      enqueue_and_echo_commands_P(PSTR("G28"));
    }
    static bool _level_state;
    void _lcd_toggle_bed_leveling() { set_bed_leveling_enabled(_level_state); }
    #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
      void _lcd_set_z_fade_height() { set_z_fade_height(planner.z_fade_height); }
    #endif
    void lcd_bed_leveling() {
      START_MENU();
      MENU_BACK(MSG_PREPARE);
      if (!(axis_known_position[X_AXIS] && axis_known_position[Y_AXIS] && axis_known_position[Z_AXIS]))
        MENU_ITEM(gcode, MSG_AUTO_HOME, PSTR("G28"));
      else if (leveling_is_valid()) {
        _level_state = leveling_is_active();
        MENU_ITEM_EDIT_CALLBACK(bool, MSG_BED_LEVELING, &_level_state, _lcd_toggle_bed_leveling);
      }
      #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
        set_z_fade_height(planner.z_fade_height);
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_Z_FADE_HEIGHT, &planner.z_fade_height, 0.0, 100.0, _lcd_set_z_fade_height);
      #endif
      #if ENABLED(MESH_BED_LEVELING)
        MENU_ITEM_EDIT(float43, MSG_BED_Z, &mbl.z_offset, -1, 1);
      #endif
      #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
        MENU_ITEM(submenu, MSG_ZPROBE_ZOFFSET, lcd_babystep_zoffset);
      #elif HAS_BED_PROBE
        MENU_ITEM_EDIT_CALLBACK(float32, MSG_ZPROBE_ZOFFSET, &zprobe_zoffset, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX, lcd_refresh_zprobe_zoffset);
      #endif
      MENU_ITEM(submenu, MSG_LEVEL_BED, _lcd_level_bed_continue);
      #if ENABLED(EEPROM_SETTINGS)
        MENU_ITEM(function, MSG_LOAD_EEPROM, lcd_load_settings);
        MENU_ITEM(function, MSG_STORE_EEPROM, lcd_store_settings);
      #endif
      END_MENU();
    }
  #elif ENABLED(AUTO_BED_LEVELING_UBL)
    void _lcd_ubl_level_bed();
    static int16_t ubl_storage_slot = 0,
               custom_bed_temp = 50,
               custom_hotend_temp = 190,
               side_points = 3,
               ubl_fillin_amount = 5,
               ubl_height_amount = 1,
               n_edit_pts = 1,
               x_plot = 0,
               y_plot = 0;
    void _lcd_ubl_build_custom_mesh() {
      char UBL_LCD_GCODE[20];
      enqueue_and_echo_commands_P(PSTR("G28"));
      #if HAS_TEMP_BED
        sprintf_P(UBL_LCD_GCODE, PSTR("M190 S%i"), custom_bed_temp);
        enqueue_and_echo_command(UBL_LCD_GCODE);
      #endif
      sprintf_P(UBL_LCD_GCODE, PSTR("M109 S%i"), custom_hotend_temp);
      enqueue_and_echo_command(UBL_LCD_GCODE);
      enqueue_and_echo_commands_P(PSTR("G29 P1"));
    }
    void _lcd_ubl_custom_mesh() {
      START_MENU();
      MENU_BACK(MSG_UBL_BUILD_MESH_MENU);
      MENU_ITEM_EDIT(int3, MSG_UBL_CUSTOM_HOTEND_TEMP, &custom_hotend_temp, EXTRUDE_MINTEMP, (HEATER_0_MAXTEMP - 10));
      #if HAS_TEMP_BED
        MENU_ITEM_EDIT(int3, MSG_UBL_CUSTOM_BED_TEMP, &custom_bed_temp, BED_MINTEMP, (BED_MAXTEMP - 5));
      #endif
      MENU_ITEM(function, MSG_UBL_BUILD_CUSTOM_MESH, _lcd_ubl_build_custom_mesh);
      END_MENU();
    }
    void _lcd_ubl_adjust_height_cmd() {
      char UBL_LCD_GCODE[16];
      const int ind = ubl_height_amount < 0 ? 6 : 7;
      strcpy_P(UBL_LCD_GCODE, PSTR("G29 P6-"));
      sprintf_P(&UBL_LCD_GCODE[ind], PSTR(".%i"), abs(ubl_height_amount));
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_height_adjust_menu() {
      START_MENU();
      MENU_BACK(MSG_UBL_EDIT_MESH_MENU);
      MENU_ITEM_EDIT(int3, MSG_UBL_MESH_HEIGHT_AMOUNT, &ubl_height_amount, -9, 9);
      MENU_ITEM(function, MSG_UBL_MESH_HEIGHT_ADJUST, _lcd_ubl_adjust_height_cmd);
      MENU_ITEM(function, MSG_WATCH, lcd_return_to_status);
      END_MENU();
    }
    void _lcd_ubl_edit_mesh() {
      START_MENU();
      MENU_BACK(MSG_UBL_TOOLS);
      MENU_ITEM(gcode, MSG_UBL_FINE_TUNE_ALL, PSTR("G29 P4 R999 T"));
      MENU_ITEM(gcode, MSG_UBL_FINE_TUNE_CLOSEST, PSTR("G29 P4 T"));
      MENU_ITEM(submenu, MSG_UBL_MESH_HEIGHT_ADJUST, _lcd_ubl_height_adjust_menu);
      MENU_ITEM(function, MSG_WATCH, lcd_return_to_status);
      END_MENU();
    }
    void _lcd_ubl_validate_custom_mesh() {
      char UBL_LCD_GCODE[24];
      const int temp =
        #if HAS_TEMP_BED
          custom_bed_temp
        #else
          0
        #endif
      ;
      sprintf_P(UBL_LCD_GCODE, PSTR("G28\nG26 C B%i H%i P"), temp, custom_hotend_temp);
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_validate_mesh() {
      START_MENU();
      MENU_BACK(MSG_UBL_TOOLS);
      #if HAS_TEMP_BED
        MENU_ITEM(gcode, MSG_UBL_VALIDATE_PLA_MESH, PSTR("G28\nG26 C B" STRINGIFY(PREHEAT_1_TEMP_BED) " H" STRINGIFY(PREHEAT_1_TEMP_HOTEND) " P"));
        MENU_ITEM(gcode, MSG_UBL_VALIDATE_ABS_MESH, PSTR("G28\nG26 C B" STRINGIFY(PREHEAT_2_TEMP_BED) " H" STRINGIFY(PREHEAT_2_TEMP_HOTEND) " P"));
      #else
        MENU_ITEM(gcode, MSG_UBL_VALIDATE_PLA_MESH, PSTR("G28\nG26 C B0 H" STRINGIFY(PREHEAT_1_TEMP_HOTEND) " P"));
        MENU_ITEM(gcode, MSG_UBL_VALIDATE_ABS_MESH, PSTR("G28\nG26 C B0 H" STRINGIFY(PREHEAT_2_TEMP_HOTEND) " P"));
      #endif
      MENU_ITEM(function, MSG_UBL_VALIDATE_CUSTOM_MESH, _lcd_ubl_validate_custom_mesh);
      MENU_ITEM(function, MSG_WATCH, lcd_return_to_status);
      END_MENU();
    }
    void _lcd_ubl_grid_level_cmd() {
      char UBL_LCD_GCODE[10];
      sprintf_P(UBL_LCD_GCODE, PSTR("G29 J%i"), side_points);
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_grid_level() {
      START_MENU();
      MENU_BACK(MSG_UBL_TOOLS);
      MENU_ITEM_EDIT(int3, MSG_UBL_SIDE_POINTS, &side_points, 2, 6);
      MENU_ITEM(function, MSG_UBL_MESH_LEVEL, _lcd_ubl_grid_level_cmd);
      END_MENU();
    }
    void _lcd_ubl_mesh_leveling() {
      START_MENU();
      MENU_BACK(MSG_UBL_TOOLS);
      MENU_ITEM(gcode, MSG_UBL_3POINT_MESH_LEVELING, PSTR("G29 J0"));
      MENU_ITEM(submenu, MSG_UBL_GRID_MESH_LEVELING, _lcd_ubl_grid_level);
      MENU_ITEM(function, MSG_WATCH, lcd_return_to_status);
      END_MENU();
    }
    void _lcd_ubl_fillin_amount_cmd() {
      char UBL_LCD_GCODE[16];
      sprintf_P(UBL_LCD_GCODE, PSTR("G29 P3 R C.%i"), ubl_fillin_amount);
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_smart_fillin_cmd() {
      char UBL_LCD_GCODE[12];
      sprintf_P(UBL_LCD_GCODE, PSTR("G29 P3 T0"));
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_fillin_menu() {
      START_MENU();
      MENU_BACK(MSG_UBL_BUILD_MESH_MENU);
      MENU_ITEM_EDIT(int3, MSG_UBL_FILLIN_AMOUNT, &ubl_fillin_amount, 0, 9);
      MENU_ITEM(function, MSG_UBL_FILLIN_MESH, _lcd_ubl_fillin_amount_cmd);
      MENU_ITEM(function, MSG_UBL_SMART_FILLIN, _lcd_ubl_smart_fillin_cmd);
      MENU_ITEM(gcode, MSG_UBL_MANUAL_FILLIN, PSTR("G29 P2 B T0"));
      MENU_ITEM(function, MSG_WATCH, lcd_return_to_status);
      END_MENU();
    }
    void _lcd_ubl_invalidate() {
      ubl.invalidate();
      SERIAL_PROTOCOLLNPGM("Mesh invalidated.");
    }
    void _lcd_ubl_build_mesh() {
      START_MENU();
      MENU_BACK(MSG_UBL_TOOLS);
      #if HAS_TEMP_BED
        MENU_ITEM(gcode, MSG_UBL_BUILD_PLA_MESH, PSTR(
          "G28\n"
          "M190 S" STRINGIFY(PREHEAT_1_TEMP_BED) "\n"
          "M109 S" STRINGIFY(PREHEAT_1_TEMP_HOTEND) "\n"
          "G29 P1\n"
          "M104 S0\n"
          "M140 S0"
        ));
        MENU_ITEM(gcode, MSG_UBL_BUILD_ABS_MESH, PSTR(
          "G28\n"
          "M190 S" STRINGIFY(PREHEAT_2_TEMP_BED) "\n"
          "M109 S" STRINGIFY(PREHEAT_2_TEMP_HOTEND) "\n"
          "G29 P1\n"
          "M104 S0\n"
          "M140 S0"
        ));
      #else
        MENU_ITEM(gcode, MSG_UBL_BUILD_PLA_MESH, PSTR(
          "G28\n"
          "M109 S" STRINGIFY(PREHEAT_1_TEMP_HOTEND) "\n"
          "G29 P1\n"
          "M104 S0"
        ));
        MENU_ITEM(gcode, MSG_UBL_BUILD_ABS_MESH, PSTR(
          "G28\n"
          "M109 S" STRINGIFY(PREHEAT_2_TEMP_HOTEND) "\n"
          "G29 P1\n"
          "M104 S0"
        ));
      #endif
      MENU_ITEM(submenu, MSG_UBL_BUILD_CUSTOM_MESH, _lcd_ubl_custom_mesh);
      MENU_ITEM(gcode, MSG_UBL_BUILD_COLD_MESH, PSTR("G28\nG29 P1"));
      MENU_ITEM(submenu, MSG_UBL_FILLIN_MESH, _lcd_ubl_fillin_menu);
      MENU_ITEM(gcode, MSG_UBL_CONTINUE_MESH, PSTR("G29 P1 C"));
      MENU_ITEM(function, MSG_UBL_INVALIDATE_ALL, _lcd_ubl_invalidate);
      MENU_ITEM(gcode, MSG_UBL_INVALIDATE_CLOSEST, PSTR("G29 I"));
      MENU_ITEM(function, MSG_WATCH, lcd_return_to_status);
      END_MENU();
    }
    void _lcd_ubl_load_mesh_cmd() {
      char UBL_LCD_GCODE[8];
      sprintf_P(UBL_LCD_GCODE, PSTR("G29 L%i"), ubl_storage_slot);
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_save_mesh_cmd() {
      char UBL_LCD_GCODE[8];
      sprintf_P(UBL_LCD_GCODE, PSTR("G29 S%i"), ubl_storage_slot);
      enqueue_and_echo_command(UBL_LCD_GCODE);
    }
    void _lcd_ubl_storage_mesh() {
      START_MENU();
      MENU_BACK(MSG_UBL_LEVEL_BED);
      MENU_ITEM_EDIT(int3, MSG_UBL_STORAGE_SLOT, &ubl_storage_slot, 0, 9);
      MENU_ITEM(function, MSG_UBL_LOAD_MESH, _lcd_ubl_load_mesh_cmd);
      MENU_ITEM(function, MSG_UBL_SAVE_MESH, _lcd_ubl_save_mesh_cmd);
      END_MENU();
    }
    void _lcd_ubl_output_map_lcd();
    void _lcd_ubl_map_homing() {
      defer_return_to_status = true;
      if (lcdDrawUpdate) lcd_implementation_drawedit(PSTR(MSG_LEVEL_BED_HOMING), NULL);
      lcdDrawUpdate = LCDVIEW_CALL_NO_REDRAW;
      if (axis_homed[X_AXIS] && axis_homed[Y_AXIS] && axis_homed[Z_AXIS]) {
        #if DISABLED(DOGLCD)
          lcd_set_ubl_map_plot_chars();
        #endif
        lcd_goto_screen(_lcd_ubl_output_map_lcd);
      }
    }
    void _lcd_ubl_map_lcd_edit_cmd() {
      char ubl_lcd_gcode [50], str[10], str2[10];
      dtostrf(pgm_read_float(&ubl._mesh_index_to_xpos[x_plot]), 0, 2, str);
      dtostrf(pgm_read_float(&ubl._mesh_index_to_ypos[y_plot]), 0, 2, str2);
      snprintf_P(ubl_lcd_gcode, sizeof(ubl_lcd_gcode), PSTR("G29 P4 X%s Y%s R%i"), str, str2, n_edit_pts);
      enqueue_and_echo_command(ubl_lcd_gcode);
    }
    void ubl_map_move_to_xy() {
      current_position[X_AXIS] = LOGICAL_X_POSITION(pgm_read_float(&ubl._mesh_index_to_xpos[x_plot]));
      current_position[Y_AXIS] = LOGICAL_Y_POSITION(pgm_read_float(&ubl._mesh_index_to_ypos[y_plot]));
      planner.buffer_line_kinematic(current_position, MMM_TO_MMS(XY_PROBE_SPEED), active_extruder);
    }
    void set_current_from_steppers_for_axis(const AxisEnum axis);
    void sync_plan_position();
    void _lcd_ubl_output_map_lcd() {
      static int16_t step_scaler = 0;
      if (!(axis_known_position[X_AXIS] && axis_known_position[Y_AXIS] && axis_known_position[Z_AXIS]))
        return lcd_goto_screen(_lcd_ubl_map_homing);
      if (lcd_clicked) return _lcd_ubl_map_lcd_edit_cmd();
      ENCODER_DIRECTION_NORMAL();
      if (encoderPosition) {
        step_scaler += (int32_t)encoderPosition;
        x_plot += step_scaler / (ENCODER_STEPS_PER_MENU_ITEM);
        if (abs(step_scaler) >= ENCODER_STEPS_PER_MENU_ITEM)
          step_scaler = 0;
        refresh_cmd_timeout();
        encoderPosition = 0;
        lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
      }
      if (x_plot >= GRID_MAX_POINTS_X) { x_plot = 0; y_plot++; }
      if (y_plot >= GRID_MAX_POINTS_Y) y_plot = 0;
      if (x_plot <= GRID_MAX_POINTS_X - (GRID_MAX_POINTS_X + 1)) { x_plot = GRID_MAX_POINTS_X - 1; y_plot--; }
      if (y_plot <= GRID_MAX_POINTS_Y - (GRID_MAX_POINTS_Y + 1)) y_plot = GRID_MAX_POINTS_Y - 1;
      x_plot = constrain(x_plot, GRID_MAX_POINTS_X - (GRID_MAX_POINTS_X + 1), GRID_MAX_POINTS_X + 1);
      y_plot = constrain(y_plot, GRID_MAX_POINTS_Y - (GRID_MAX_POINTS_Y + 1), GRID_MAX_POINTS_Y + 1);
      #if IS_KINEMATIC
        n_edit_pts = 9; 
      #else
        const bool xc = WITHIN(x_plot, 1, GRID_MAX_POINTS_X - 2),
                   yc = WITHIN(y_plot, 1, GRID_MAX_POINTS_Y - 2);
        n_edit_pts = yc ? (xc ? 9 : 6) : (xc ? 6 : 4); 
      #endif
      if (lcdDrawUpdate) {
        lcd_implementation_ubl_plot(x_plot, y_plot);
        ubl_map_move_to_xy(); 
        if (planner.movesplanned() > 1) { 
          quickstop_stepper();
          ubl_map_move_to_xy(); 
        }
      }
    }
    void _lcd_ubl_output_map_lcd_cmd() {
      ubl_lcd_map_control = true; 
      if (!(axis_known_position[X_AXIS] && axis_known_position[Y_AXIS] && axis_known_position[Z_AXIS]))
        enqueue_and_echo_commands_P(PSTR("G28"));
      lcd_goto_screen(_lcd_ubl_map_homing);
    }
    void _lcd_ubl_output_map() {
      START_MENU();
      MENU_BACK(MSG_UBL_LEVEL_BED);
      MENU_ITEM(gcode, MSG_UBL_OUTPUT_MAP_HOST, PSTR("G29 T0"));
      MENU_ITEM(gcode, MSG_UBL_OUTPUT_MAP_CSV, PSTR("G29 T1"));
      MENU_ITEM(gcode, MSG_UBL_OUTPUT_MAP_BACKUP, PSTR("G29 S-1"));
      MENU_ITEM(function, MSG_UBL_OUTPUT_MAP, _lcd_ubl_output_map_lcd_cmd);
      END_MENU();
    }
    void _lcd_ubl_tools_menu() {
      START_MENU();
      MENU_BACK(MSG_UBL_LEVEL_BED);
      MENU_ITEM(submenu, MSG_UBL_BUILD_MESH_MENU, _lcd_ubl_build_mesh);
      MENU_ITEM(submenu, MSG_UBL_VALIDATE_MESH_MENU, _lcd_ubl_validate_mesh);
      MENU_ITEM(submenu, MSG_UBL_EDIT_MESH_MENU, _lcd_ubl_edit_mesh);
      MENU_ITEM(submenu, MSG_UBL_MESH_LEVELING, _lcd_ubl_mesh_leveling);
      END_MENU();
    }
    void _lcd_ubl_step_by_step() {
      START_MENU();
      MENU_BACK(MSG_UBL_LEVEL_BED);
      MENU_ITEM(gcode, "1 " MSG_UBL_BUILD_COLD_MESH, PSTR("G28\nG29 P1"));
      MENU_ITEM(function, "2 " MSG_UBL_SMART_FILLIN, _lcd_ubl_smart_fillin_cmd);
      MENU_ITEM(submenu, "3 " MSG_UBL_VALIDATE_MESH_MENU, _lcd_ubl_validate_mesh);
      MENU_ITEM(gcode, "4 " MSG_UBL_FINE_TUNE_ALL, PSTR("G29 P4 R999 T"));
      MENU_ITEM(submenu, "5 " MSG_UBL_VALIDATE_MESH_MENU, _lcd_ubl_validate_mesh);
      MENU_ITEM(gcode, "6 " MSG_UBL_FINE_TUNE_ALL, PSTR("G29 P4 R999 T"));
      MENU_ITEM(function, "7 " MSG_UBL_SAVE_MESH, _lcd_ubl_save_mesh_cmd);
      END_MENU();
    }
    void _lcd_ubl_level_bed() {
      START_MENU();
      MENU_BACK(MSG_PREPARE);
      MENU_ITEM(gcode, MSG_UBL_MANUAL_MESH, PSTR("G29 I999\nG29 P2 B T0"));
      MENU_ITEM(gcode, MSG_UBL_ACTIVATE_MESH, PSTR("G29 A"));
      MENU_ITEM(gcode, MSG_UBL_DEACTIVATE_MESH, PSTR("G29 D"));
      MENU_ITEM(submenu, MSG_UBL_STEP_BY_STEP_MENU, _lcd_ubl_step_by_step);
      MENU_ITEM(submenu, MSG_UBL_STORAGE_MESH_MENU, _lcd_ubl_storage_mesh);
      MENU_ITEM(submenu, MSG_UBL_OUTPUT_MAP, _lcd_ubl_output_map);
      MENU_ITEM(submenu, MSG_UBL_TOOLS, _lcd_ubl_tools_menu);
      MENU_ITEM(gcode, MSG_UBL_INFO_UBL, PSTR("G29 W"));
      END_MENU();
    }
  #endif 
  void lcd_prepare_menu() {
    START_MENU();
    MENU_BACK(MSG_MAIN);
    #if ENABLED(DELTA)
      if (axis_homed[Z_AXIS])
    #endif
        MENU_ITEM(submenu, MSG_MOVE_AXIS, lcd_move_menu);
    MENU_ITEM(gcode, MSG_AUTO_HOME, PSTR("G28"));
    #if ENABLED(INDIVIDUAL_AXIS_HOMING_MENU)
      MENU_ITEM(gcode, MSG_AUTO_HOME_X, PSTR("G28 X"));
      MENU_ITEM(gcode, MSG_AUTO_HOME_Y, PSTR("G28 Y"));
      MENU_ITEM(gcode, MSG_AUTO_HOME_Z, PSTR("G28 Z"));
    #endif
    #if ENABLED(AUTO_BED_LEVELING_UBL)
      MENU_ITEM(submenu, MSG_UBL_LEVEL_BED, _lcd_ubl_level_bed);
    #elif ENABLED(LCD_BED_LEVELING)
      #if ENABLED(PROBE_MANUALLY)
        if (!g29_in_progress)
      #endif
      MENU_ITEM(submenu, MSG_BED_LEVELING, lcd_bed_leveling);
    #elif PLANNER_LEVELING
      MENU_ITEM(gcode, MSG_BED_LEVELING, PSTR("G28\nG29"));
    #endif
    #if HAS_M206_COMMAND
      MENU_ITEM(function, MSG_SET_HOME_OFFSETS, lcd_set_home_offsets);
    #endif
    MENU_ITEM(gcode, MSG_DISABLE_STEPPERS, PSTR("M84"));
    #if ENABLED(ADVANCED_PAUSE_FEATURE)
      if (!thermalManager.tooColdToExtrude(active_extruder))
        MENU_ITEM(function, MSG_FILAMENTCHANGE, lcd_enqueue_filament_change);
    #endif
    #if TEMP_SENSOR_0 != 0
      bool has_heat = false;
      HOTEND_LOOP() if (thermalManager.target_temperature[HOTEND_INDEX]) { has_heat = true; break; }
      #if HAS_TEMP_BED
        if (thermalManager.target_temperature_bed) has_heat = true;
      #endif
      if (has_heat) MENU_ITEM(function, MSG_COOLDOWN, lcd_cooldown);
      #if TEMP_SENSOR_1 != 0 || TEMP_SENSOR_2 != 0 || TEMP_SENSOR_3 != 0 || TEMP_SENSOR_4 != 0 || TEMP_SENSOR_BED != 0
        MENU_ITEM(submenu, MSG_PREHEAT_1, lcd_preheat_m1_menu);
        MENU_ITEM(submenu, MSG_PREHEAT_2, lcd_preheat_m2_menu);
      #else
        MENU_ITEM(function, MSG_PREHEAT_1, lcd_preheat_m1_e0_only);
        MENU_ITEM(function, MSG_PREHEAT_2, lcd_preheat_m2_e0_only);
      #endif
    #endif 
    #if ENABLED(BLTOUCH)
      MENU_ITEM(gcode, MSG_BLTOUCH_SELFTEST, PSTR("M280 P" STRINGIFY(Z_ENDSTOP_SERVO_NR) " S" STRINGIFY(BLTOUCH_SELFTEST)));
      if (!endstops.z_probe_enabled && TEST_BLTOUCH())
        MENU_ITEM(gcode, MSG_BLTOUCH_RESET, PSTR("M280 P" STRINGIFY(Z_ENDSTOP_SERVO_NR) " S" STRINGIFY(BLTOUCH_RESET)));
    #endif
    #if HAS_POWER_SWITCH
      if (powersupply_on)
        MENU_ITEM(gcode, MSG_SWITCH_PS_OFF, PSTR("M81"));
      else
        MENU_ITEM(gcode, MSG_SWITCH_PS_ON, PSTR("M80"));
    #endif
    #if ENABLED(SDSUPPORT) && ENABLED(MENU_ADDAUTOSTART)
      MENU_ITEM(function, MSG_AUTOSTART, lcd_autostart_sd);
    #endif
    END_MENU();
  }
  float move_menu_scale;
  #if ENABLED(DELTA_CALIBRATION_MENU)
    void lcd_move_z();
    void lcd_delta_calibrate_menu();
    void _lcd_calibrate_homing() {
      if (lcdDrawUpdate) lcd_implementation_drawmenu_static(LCD_HEIGHT >= 4 ? 1 : 0, PSTR(MSG_LEVEL_BED_HOMING));
      lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT;
      if (axis_homed[X_AXIS] && axis_homed[Y_AXIS] && axis_homed[Z_AXIS])
        lcd_goto_previous_menu();
    }
    void _lcd_delta_calibrate_home() {
      #if HAS_LEVELING
        reset_bed_level(); 
      #endif
      enqueue_and_echo_commands_P(PSTR("G28"));
      lcd_goto_screen(_lcd_calibrate_homing);
    }
    void _man_probe_pt(const float &lx, const float &ly) {
      #if HAS_LEVELING
        reset_bed_level(); 
      #endif
      float z_dest = LOGICAL_Z_POSITION((Z_CLEARANCE_BETWEEN_PROBES) + (DELTA_PRINTABLE_RADIUS) / 5);
      line_to_z(z_dest);
      current_position[X_AXIS] = LOGICAL_X_POSITION(lx);
      current_position[Y_AXIS] = LOGICAL_Y_POSITION(ly);
      line_to_current_z();
      z_dest = LOGICAL_Z_POSITION(Z_CLEARANCE_BETWEEN_PROBES);
      line_to_z(z_dest);
      lcd_synchronize();
      move_menu_scale = 0.1;
      lcd_goto_screen(lcd_move_z);
    }
    float lcd_probe_pt(const float &lx, const float &ly) {
      _man_probe_pt(lx, ly);
      KEEPALIVE_STATE(PAUSED_FOR_USER);
      wait_for_user = true;
      while (wait_for_user) idle();
      KEEPALIVE_STATE(IN_HANDLER);
      return current_position[Z_AXIS];
    }
    void _goto_tower_x() { _man_probe_pt(cos(RADIANS(210)) * delta_calibration_radius, sin(RADIANS(210)) * delta_calibration_radius); }
    void _goto_tower_y() { _man_probe_pt(cos(RADIANS(330)) * delta_calibration_radius, sin(RADIANS(330)) * delta_calibration_radius); }
    void _goto_tower_z() { _man_probe_pt(cos(RADIANS( 90)) * delta_calibration_radius, sin(RADIANS( 90)) * delta_calibration_radius); }
    void _goto_center()  { _man_probe_pt(0,0); }
    void lcd_delta_calibrate_menu() {
      START_MENU();
      MENU_BACK(MSG_MAIN);
      #if ENABLED(DELTA_AUTO_CALIBRATION)
        MENU_ITEM(gcode, MSG_DELTA_AUTO_CALIBRATE, PSTR("G33"));
        MENU_ITEM(gcode, MSG_DELTA_HEIGHT_CALIBRATE, PSTR("G33 P1"));
      #endif
      MENU_ITEM(submenu, MSG_AUTO_HOME, _lcd_delta_calibrate_home);
      if (axis_homed[Z_AXIS]) {
        MENU_ITEM(submenu, MSG_DELTA_CALIBRATE_X, _goto_tower_x);
        MENU_ITEM(submenu, MSG_DELTA_CALIBRATE_Y, _goto_tower_y);
        MENU_ITEM(submenu, MSG_DELTA_CALIBRATE_Z, _goto_tower_z);
        MENU_ITEM(submenu, MSG_DELTA_CALIBRATE_CENTER, _goto_center);
      }
      END_MENU();
    }
  #endif 
  inline void manage_manual_move() {
    if (manual_move_axis != (int8_t)NO_AXIS && ELAPSED(millis(), manual_move_start_time) && !planner.is_full()) {
      planner.buffer_line_kinematic(current_position, MMM_TO_MMS(manual_feedrate_mm_m[manual_move_axis]), manual_move_e_index);
      manual_move_axis = (int8_t)NO_AXIS;
    }
  }
  inline void manual_move_to_current(AxisEnum axis
    #if E_MANUAL > 1
      , int8_t eindex=-1
    #endif
  ) {
    #if E_MANUAL > 1
      if (axis == E_AXIS) manual_move_e_index = eindex >= 0 ? eindex : active_extruder;
    #endif
    manual_move_start_time = millis() + (move_menu_scale < 0.99 ? 0UL : 250UL); 
    manual_move_axis = (int8_t)axis;
  }
  void _lcd_move_xyz(const char* name, AxisEnum axis) {
    if (lcd_clicked) { return lcd_goto_previous_menu(); }
    ENCODER_DIRECTION_NORMAL();
    if (encoderPosition) {
      refresh_cmd_timeout();
      float min = current_position[axis] - 1000,
            max = current_position[axis] + 1000;
      #if HAS_SOFTWARE_ENDSTOPS
        if (soft_endstops_enabled) {
          #if ENABLED(MIN_SOFTWARE_ENDSTOPS)
            min = soft_endstop_min[axis];
          #endif
          #if ENABLED(MAX_SOFTWARE_ENDSTOPS)
            max = soft_endstop_max[axis];
          #endif
        }
      #endif
      current_position[axis] += float((int32_t)encoderPosition) * move_menu_scale;
      #if ENABLED(DELTA)
        if (axis != Z_AXIS) {
          max = SQRT(sq((float)(DELTA_PRINTABLE_RADIUS)) - sq(current_position[Y_AXIS - axis]));
          min = -max;
        }
      #endif
      if ((int32_t)encoderPosition < 0) NOLESS(current_position[axis], min);
      if ((int32_t)encoderPosition > 0) NOMORE(current_position[axis], max);
      manual_move_to_current(axis);
      encoderPosition = 0;
      lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
    }
    if (lcdDrawUpdate) lcd_implementation_drawedit(name, ftostr41sign(current_position[axis]));
  }
  void lcd_move_x() { _lcd_move_xyz(PSTR(MSG_MOVE_X), X_AXIS); }
  void lcd_move_y() { _lcd_move_xyz(PSTR(MSG_MOVE_Y), Y_AXIS); }
  void lcd_move_z() { _lcd_move_xyz(PSTR(MSG_MOVE_Z), Z_AXIS); }
  void _lcd_move_e(
    #if E_MANUAL > 1
      int8_t eindex=-1
    #endif
  ) {
    if (lcd_clicked) { return lcd_goto_previous_menu(); }
    ENCODER_DIRECTION_NORMAL();
    if (encoderPosition) {
      current_position[E_AXIS] += float((int32_t)encoderPosition) * move_menu_scale;
      encoderPosition = 0;
      manual_move_to_current(E_AXIS
        #if E_MANUAL > 1
          , eindex
        #endif
      );
      lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
    }
    if (lcdDrawUpdate) {
      PGM_P pos_label;
      #if E_MANUAL == 1
        pos_label = PSTR(MSG_MOVE_E);
      #else
        switch (eindex) {
          default: pos_label = PSTR(MSG_MOVE_E MSG_MOVE_E1); break;
          case 1: pos_label = PSTR(MSG_MOVE_E MSG_MOVE_E2); break;
          #if E_MANUAL > 2
            case 2: pos_label = PSTR(MSG_MOVE_E MSG_MOVE_E3); break;
            #if E_MANUAL > 3
              case 3: pos_label = PSTR(MSG_MOVE_E MSG_MOVE_E4); break;
              #if E_MANUAL > 4
                case 4: pos_label = PSTR(MSG_MOVE_E MSG_MOVE_E5); break;
              #endif 
            #endif 
          #endif 
        }
      #endif 
      lcd_implementation_drawedit(pos_label, ftostr41sign(current_position[E_AXIS]));
    }
  }
  void lcd_move_e() { _lcd_move_e(); }
  #if E_MANUAL > 1
    void lcd_move_e0() { _lcd_move_e(0); }
    void lcd_move_e1() { _lcd_move_e(1); }
    #if E_MANUAL > 2
      void lcd_move_e2() { _lcd_move_e(2); }
      #if E_MANUAL > 3
        void lcd_move_e3() { _lcd_move_e(3); }
        #if E_MANUAL > 4
          void lcd_move_e4() { _lcd_move_e(4); }
        #endif 
      #endif 
    #endif 
  #endif 
  screenFunc_t _manual_move_func_ptr;
  void lcd_move_menu_10mm() { move_menu_scale = 10.0; lcd_goto_screen(_manual_move_func_ptr); }
  void lcd_move_menu_1mm()  { move_menu_scale =  1.0; lcd_goto_screen(_manual_move_func_ptr); }
  void lcd_move_menu_01mm() { move_menu_scale =  0.1; lcd_goto_screen(_manual_move_func_ptr); }
  void _lcd_move_distance_menu(AxisEnum axis, screenFunc_t func) {
    _manual_move_func_ptr = func;
    START_MENU();
    if (LCD_HEIGHT >= 4) {
      switch(axis) {
        case X_AXIS:
          STATIC_ITEM(MSG_MOVE_X, true, true); break;
        case Y_AXIS:
          STATIC_ITEM(MSG_MOVE_Y, true, true); break;
        case Z_AXIS:
          STATIC_ITEM(MSG_MOVE_Z, true, true); break;
        default:
          STATIC_ITEM(MSG_MOVE_E, true, true); break;
      }
    }
    MENU_BACK(MSG_MOVE_AXIS);
    MENU_ITEM(submenu, MSG_MOVE_10MM, lcd_move_menu_10mm);
    MENU_ITEM(submenu, MSG_MOVE_1MM, lcd_move_menu_1mm);
    MENU_ITEM(submenu, MSG_MOVE_01MM, lcd_move_menu_01mm);
    END_MENU();
  }
  void lcd_move_get_x_amount()        { _lcd_move_distance_menu(X_AXIS, lcd_move_x); }
  void lcd_move_get_y_amount()        { _lcd_move_distance_menu(Y_AXIS, lcd_move_y); }
  void lcd_move_get_z_amount()        { _lcd_move_distance_menu(Z_AXIS, lcd_move_z); }
  void lcd_move_get_e_amount()        { _lcd_move_distance_menu(E_AXIS, lcd_move_e); }
  #if E_MANUAL > 1
    void lcd_move_get_e0_amount()     { _lcd_move_distance_menu(E_AXIS, lcd_move_e0); }
    void lcd_move_get_e1_amount()     { _lcd_move_distance_menu(E_AXIS, lcd_move_e1); }
    #if E_MANUAL > 2
      void lcd_move_get_e2_amount()   { _lcd_move_distance_menu(E_AXIS, lcd_move_e2); }
      #if E_MANUAL > 3
        void lcd_move_get_e3_amount() { _lcd_move_distance_menu(E_AXIS, lcd_move_e3); }
        #if E_MANUAL > 4
          void lcd_move_get_e4_amount() { _lcd_move_distance_menu(E_AXIS, lcd_move_e4); }
        #endif 
      #endif 
    #endif 
  #endif 
  #if IS_KINEMATIC
    #define _MOVE_XYZ_ALLOWED (axis_homed[X_AXIS] && axis_homed[Y_AXIS] && axis_homed[Z_AXIS])
    #if ENABLED(DELTA)
      #define _MOVE_XY_ALLOWED (current_position[Z_AXIS] <= delta_clip_start_height)
      void lcd_lower_z_to_clip_height() {
        line_to_z(delta_clip_start_height);
        lcd_synchronize();
      }
    #else
      #define _MOVE_XY_ALLOWED true
    #endif
  #else
    #define _MOVE_XYZ_ALLOWED true
    #define _MOVE_XY_ALLOWED true
  #endif
  void lcd_move_menu() {
    START_MENU();
    MENU_BACK(MSG_PREPARE);
    if (_MOVE_XYZ_ALLOWED) {
      if (_MOVE_XY_ALLOWED) {
        MENU_ITEM(submenu, MSG_MOVE_X, lcd_move_get_x_amount);
        MENU_ITEM(submenu, MSG_MOVE_Y, lcd_move_get_y_amount);
      }
      #if ENABLED(DELTA)
        else
          MENU_ITEM(function, MSG_FREE_XY, lcd_lower_z_to_clip_height);
      #endif
      MENU_ITEM(submenu, MSG_MOVE_Z, lcd_move_get_z_amount);
    }
    else
      MENU_ITEM(gcode, MSG_AUTO_HOME, PSTR("G28"));
    #if ENABLED(SWITCHING_EXTRUDER)
      if (active_extruder)
        MENU_ITEM(gcode, MSG_SELECT " " MSG_E1, PSTR("T0"));
      else
        MENU_ITEM(gcode, MSG_SELECT " " MSG_E2, PSTR("T1"));
    #endif
    MENU_ITEM(submenu, MSG_MOVE_E, lcd_move_get_e_amount);
    #if E_MANUAL > 1
      MENU_ITEM(submenu, MSG_MOVE_E MSG_MOVE_E1, lcd_move_get_e0_amount);
      MENU_ITEM(submenu, MSG_MOVE_E MSG_MOVE_E2, lcd_move_get_e1_amount);
      #if E_MANUAL > 2
        MENU_ITEM(submenu, MSG_MOVE_E MSG_MOVE_E3, lcd_move_get_e2_amount);
        #if E_MANUAL > 3
          MENU_ITEM(submenu, MSG_MOVE_E MSG_MOVE_E4, lcd_move_get_e3_amount);
          #if E_MANUAL > 4
            MENU_ITEM(submenu, MSG_MOVE_E MSG_MOVE_E5, lcd_move_get_e4_amount);
          #endif 
        #endif 
      #endif 
    #endif 
    END_MENU();
  }
  #if HAS_LCD_CONTRAST
    void lcd_callback_set_contrast() { set_lcd_contrast(lcd_contrast); }
  #endif
  static void lcd_factory_settings() {
    settings.reset();
    lcd_completion_feedback();
  }
  void lcd_control_menu() {
    START_MENU();
    MENU_BACK(MSG_MAIN);
    MENU_ITEM(submenu, MSG_TEMPERATURE, lcd_control_temperature_menu);
    MENU_ITEM(submenu, MSG_MOTION, lcd_control_motion_menu);
    MENU_ITEM(submenu, MSG_FILAMENT, lcd_control_filament_menu);
    #if HAS_LCD_CONTRAST
      MENU_ITEM_EDIT_CALLBACK(int3, MSG_CONTRAST, (int*)&lcd_contrast, LCD_CONTRAST_MIN, LCD_CONTRAST_MAX, lcd_callback_set_contrast, true);
    #endif
    #if ENABLED(FWRETRACT)
      MENU_ITEM(submenu, MSG_RETRACT, lcd_control_retract_menu);
    #endif
    #if ENABLED(DAC_STEPPER_CURRENT)
      MENU_ITEM(submenu, MSG_DRIVE_STRENGTH, lcd_dac_menu);
    #endif
    #if HAS_MOTOR_CURRENT_PWM
      MENU_ITEM(submenu, MSG_DRIVE_STRENGTH, lcd_pwm_menu);
    #endif
    #if ENABLED(BLTOUCH)
      MENU_ITEM(submenu, MSG_BLTOUCH, bltouch_menu);
    #endif
    #if ENABLED(EEPROM_SETTINGS)
      MENU_ITEM(function, MSG_STORE_EEPROM, lcd_store_settings);
      MENU_ITEM(function, MSG_LOAD_EEPROM, lcd_load_settings);
    #endif
    MENU_ITEM(function, MSG_RESTORE_FAILSAFE, lcd_factory_settings);
    #if ENABLED(EEPROM_SETTINGS)
      MENU_ITEM(gcode, MSG_INIT_EEPROM, PSTR("M502\nM500")); 
    #endif
    END_MENU();
  }
  #if ENABLED(PID_AUTOTUNE_MENU)
    #if ENABLED(PIDTEMP)
      int16_t autotune_temp[HOTENDS] = ARRAY_BY_HOTENDS1(150);
    #endif
    #if ENABLED(PIDTEMPBED)
      int16_t autotune_temp_bed = 70;
    #endif
    void _lcd_autotune(int16_t e) {
      char cmd[30];
      sprintf_P(cmd, PSTR("M303 U1 E%i S%i"), e,
        #if HAS_PID_FOR_BOTH
          e < 0 ? autotune_temp_bed : autotune_temp[e]
        #elif ENABLED(PIDTEMPBED)
          autotune_temp_bed
        #else
          autotune_temp[e]
        #endif
      );
      enqueue_and_echo_command(cmd);
    }
  #endif 
  #if ENABLED(PIDTEMP)
    void copy_and_scalePID_i(int16_t e) {
      #if DISABLED(PID_PARAMS_PER_HOTEND) || HOTENDS == 1
        UNUSED(e);
      #endif
      PID_PARAM(Ki, e) = scalePID_i(raw_Ki);
      thermalManager.updatePID();
    }
    void copy_and_scalePID_d(int16_t e) {
      #if DISABLED(PID_PARAMS_PER_HOTEND) || HOTENDS == 1
        UNUSED(e);
      #endif
      PID_PARAM(Kd, e) = scalePID_d(raw_Kd);
      thermalManager.updatePID();
    }
    #define _DEFINE_PIDTEMP_BASE_FUNCS(N) \
      void copy_and_scalePID_i_E ## N() { copy_and_scalePID_i(N); } \
      void copy_and_scalePID_d_E ## N() { copy_and_scalePID_d(N); }
    #if ENABLED(PID_AUTOTUNE_MENU)
      #define DEFINE_PIDTEMP_FUNCS(N) \
        _DEFINE_PIDTEMP_BASE_FUNCS(N); \
        void lcd_autotune_callback_E ## N() { _lcd_autotune(N); } typedef void _pid_##N##_void
    #else
      #define DEFINE_PIDTEMP_FUNCS(N) _DEFINE_PIDTEMP_BASE_FUNCS(N) typedef void _pid_##N##_void
    #endif
    DEFINE_PIDTEMP_FUNCS(0);
    #if ENABLED(PID_PARAMS_PER_HOTEND)
      #if HOTENDS > 1
        DEFINE_PIDTEMP_FUNCS(1);
        #if HOTENDS > 2
          DEFINE_PIDTEMP_FUNCS(2);
          #if HOTENDS > 3
            DEFINE_PIDTEMP_FUNCS(3);
            #if HOTENDS > 4
              DEFINE_PIDTEMP_FUNCS(4);
            #endif 
          #endif 
        #endif 
      #endif 
    #endif 
  #endif 
  void lcd_control_temperature_menu() {
    START_MENU();
    MENU_BACK(MSG_CONTROL);
    #if HOTENDS == 1
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE, &thermalManager.target_temperature[0], 0, HEATER_0_MAXTEMP - 15, watch_temp_callback_E0);
    #else 
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N1, &thermalManager.target_temperature[0], 0, HEATER_0_MAXTEMP - 15, watch_temp_callback_E0);
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N2, &thermalManager.target_temperature[1], 0, HEATER_1_MAXTEMP - 15, watch_temp_callback_E1);
      #if HOTENDS > 2
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N3, &thermalManager.target_temperature[2], 0, HEATER_2_MAXTEMP - 15, watch_temp_callback_E2);
        #if HOTENDS > 3
          MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N4, &thermalManager.target_temperature[3], 0, HEATER_3_MAXTEMP - 15, watch_temp_callback_E3);
          #if HOTENDS > 4
            MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_NOZZLE MSG_N5, &thermalManager.target_temperature[4], 0, HEATER_4_MAXTEMP - 15, watch_temp_callback_E4);
          #endif 
        #endif 
      #endif 
    #endif 
    #if HAS_TEMP_BED
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_BED, &thermalManager.target_temperature_bed, 0, BED_MAXTEMP - 15, watch_temp_callback_bed);
    #endif
    #if FAN_COUNT > 0
      #if HAS_FAN0
        #if FAN_COUNT > 1
          #define MSG_1ST_FAN_SPEED MSG_FAN_SPEED " 1"
        #else
          #define MSG_1ST_FAN_SPEED MSG_FAN_SPEED
        #endif
        MENU_MULTIPLIER_ITEM_EDIT(int3, MSG_1ST_FAN_SPEED, &fanSpeeds[0], 0, 255);
      #endif
      #if HAS_FAN1
        MENU_MULTIPLIER_ITEM_EDIT(int3, MSG_FAN_SPEED " 2", &fanSpeeds[1], 0, 255);
      #endif
      #if HAS_FAN2
        MENU_MULTIPLIER_ITEM_EDIT(int3, MSG_FAN_SPEED " 3", &fanSpeeds[2], 0, 255);
      #endif
    #endif 
    #if ENABLED(AUTOTEMP) && (TEMP_SENSOR_0 != 0)
      MENU_ITEM_EDIT(bool, MSG_AUTOTEMP, &planner.autotemp_enabled);
      MENU_ITEM_EDIT(float3, MSG_MIN, &planner.autotemp_min, 0, HEATER_0_MAXTEMP - 15);
      MENU_ITEM_EDIT(float3, MSG_MAX, &planner.autotemp_max, 0, HEATER_0_MAXTEMP - 15);
      MENU_ITEM_EDIT(float32, MSG_FACTOR, &planner.autotemp_factor, 0.0, 1.0);
    #endif
    #if ENABLED(PIDTEMP)
      #define _PID_BASE_MENU_ITEMS(ELABEL, eindex) \
        raw_Ki = unscalePID_i(PID_PARAM(Ki, eindex)); \
        raw_Kd = unscalePID_d(PID_PARAM(Kd, eindex)); \
        MENU_ITEM_EDIT(float52, MSG_PID_P ELABEL, &PID_PARAM(Kp, eindex), 1, 9990); \
        MENU_ITEM_EDIT_CALLBACK(float52, MSG_PID_I ELABEL, &raw_Ki, 0.01, 9990, copy_and_scalePID_i_E ## eindex); \
        MENU_ITEM_EDIT_CALLBACK(float52, MSG_PID_D ELABEL, &raw_Kd, 1, 9990, copy_and_scalePID_d_E ## eindex)
      #if ENABLED(PID_EXTRUSION_SCALING)
        #define _PID_MENU_ITEMS(ELABEL, eindex) \
          _PID_BASE_MENU_ITEMS(ELABEL, eindex); \
          MENU_ITEM_EDIT(float3, MSG_PID_C ELABEL, &PID_PARAM(Kc, eindex), 1, 9990)
      #else
        #define _PID_MENU_ITEMS(ELABEL, eindex) _PID_BASE_MENU_ITEMS(ELABEL, eindex)
      #endif
      #if ENABLED(PID_AUTOTUNE_MENU)
        #define PID_MENU_ITEMS(ELABEL, eindex) \
          _PID_MENU_ITEMS(ELABEL, eindex); \
          MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(int3, MSG_PID_AUTOTUNE ELABEL, &autotune_temp[eindex], 150, heater_maxtemp[eindex] - 15, lcd_autotune_callback_E ## eindex)
      #else
        #define PID_MENU_ITEMS(ELABEL, eindex) _PID_MENU_ITEMS(ELABEL, eindex)
      #endif
      #if ENABLED(PID_PARAMS_PER_HOTEND) && HOTENDS > 1
        PID_MENU_ITEMS(" " MSG_E1, 0);
        PID_MENU_ITEMS(" " MSG_E2, 1);
        #if HOTENDS > 2
          PID_MENU_ITEMS(" " MSG_E3, 2);
          #if HOTENDS > 3
            PID_MENU_ITEMS(" " MSG_E4, 3);
            #if HOTENDS > 4
              PID_MENU_ITEMS(" " MSG_E5, 4);
            #endif 
          #endif 
        #endif 
      #else 
        PID_MENU_ITEMS("", 0);
      #endif 
    #endif 
    MENU_ITEM(submenu, MSG_PREHEAT_1_SETTINGS, lcd_control_temperature_preheat_material1_settings_menu);
    MENU_ITEM(submenu, MSG_PREHEAT_2_SETTINGS, lcd_control_temperature_preheat_material2_settings_menu);
    END_MENU();
  }
  void _lcd_control_temperature_preheat_settings_menu(uint8_t material) {
    #if HOTENDS > 4
      #define MINTEMP_ALL MIN5(HEATER_0_MINTEMP, HEATER_1_MINTEMP, HEATER_2_MINTEMP, HEATER_3_MINTEMP, HEATER_4_MINTEMP)
      #define MAXTEMP_ALL MAX5(HEATER_0_MAXTEMP, HEATER_1_MAXTEMP, HEATER_2_MAXTEMP, HEATER_3_MAXTEMP, HEATER_4_MAXTEMP)
    #elif HOTENDS > 3
      #define MINTEMP_ALL MIN4(HEATER_0_MINTEMP, HEATER_1_MINTEMP, HEATER_2_MINTEMP, HEATER_3_MINTEMP)
      #define MAXTEMP_ALL MAX4(HEATER_0_MAXTEMP, HEATER_1_MAXTEMP, HEATER_2_MAXTEMP, HEATER_3_MAXTEMP)
    #elif HOTENDS > 2
      #define MINTEMP_ALL MIN3(HEATER_0_MINTEMP, HEATER_1_MINTEMP, HEATER_2_MINTEMP)
      #define MAXTEMP_ALL MAX3(HEATER_0_MAXTEMP, HEATER_1_MAXTEMP, HEATER_2_MAXTEMP)
    #elif HOTENDS > 1
      #define MINTEMP_ALL min(HEATER_0_MINTEMP, HEATER_1_MINTEMP)
      #define MAXTEMP_ALL max(HEATER_0_MAXTEMP, HEATER_1_MAXTEMP)
    #else
      #define MINTEMP_ALL HEATER_0_MINTEMP
      #define MAXTEMP_ALL HEATER_0_MAXTEMP
    #endif
    START_MENU();
    MENU_BACK(MSG_TEMPERATURE);
    MENU_ITEM_EDIT(int3, MSG_FAN_SPEED, &lcd_preheat_fan_speed[material], 0, 255);
    #if TEMP_SENSOR_0 != 0
      MENU_ITEM_EDIT(int3, MSG_NOZZLE, &lcd_preheat_hotend_temp[material], MINTEMP_ALL, MAXTEMP_ALL - 15);
    #endif
    #if TEMP_SENSOR_BED != 0
      MENU_ITEM_EDIT(int3, MSG_BED, &lcd_preheat_bed_temp[material], BED_MINTEMP, BED_MAXTEMP - 15);
    #endif
    #if ENABLED(EEPROM_SETTINGS)
      MENU_ITEM(function, MSG_STORE_EEPROM, lcd_store_settings);
    #endif
    END_MENU();
  }
  void lcd_control_temperature_preheat_material1_settings_menu() { _lcd_control_temperature_preheat_settings_menu(0); }
  void lcd_control_temperature_preheat_material2_settings_menu() { _lcd_control_temperature_preheat_settings_menu(1); }
  void _reset_acceleration_rates() { planner.reset_acceleration_rates(); }
  #if ENABLED(DISTINCT_E_FACTORS)
    void _reset_e_acceleration_rate(const uint8_t e) { if (e == active_extruder) _reset_acceleration_rates(); }
    void _reset_e0_acceleration_rate() { _reset_e_acceleration_rate(0); }
    void _reset_e1_acceleration_rate() { _reset_e_acceleration_rate(1); }
    #if E_STEPPERS > 2
      void _reset_e2_acceleration_rate() { _reset_e_acceleration_rate(2); }
      #if E_STEPPERS > 3
        void _reset_e3_acceleration_rate() { _reset_e_acceleration_rate(3); }
        #if E_STEPPERS > 4
          void _reset_e4_acceleration_rate() { _reset_e_acceleration_rate(4); }
        #endif 
      #endif 
    #endif 
  #endif
  void _planner_refresh_positioning() { planner.refresh_positioning(); }
  #if ENABLED(DISTINCT_E_FACTORS)
    void _planner_refresh_e_positioning(const uint8_t e) {
      if (e == active_extruder)
        _planner_refresh_positioning();
      else
        planner.steps_to_mm[E_AXIS + e] = 1.0 / planner.axis_steps_per_mm[E_AXIS + e];
    }
    void _planner_refresh_e0_positioning() { _planner_refresh_e_positioning(0); }
    void _planner_refresh_e1_positioning() { _planner_refresh_e_positioning(1); }
    #if E_STEPPERS > 2
      void _planner_refresh_e2_positioning() { _planner_refresh_e_positioning(2); }
      #if E_STEPPERS > 3
        void _planner_refresh_e3_positioning() { _planner_refresh_e_positioning(3); }
        #if E_STEPPERS > 4
          void _planner_refresh_e4_positioning() { _planner_refresh_e_positioning(4); }
        #endif 
      #endif 
    #endif 
  #endif
  void lcd_control_motion_velocity_menu() {
    START_MENU();
    MENU_BACK(MSG_MOTION);
    MENU_ITEM_EDIT(float3, MSG_VMAX MSG_X, &planner.max_feedrate_mm_s[X_AXIS], 1, 999);
    MENU_ITEM_EDIT(float3, MSG_VMAX MSG_Y, &planner.max_feedrate_mm_s[Y_AXIS], 1, 999);
    MENU_ITEM_EDIT(float3, MSG_VMAX MSG_Z, &planner.max_feedrate_mm_s[Z_AXIS], 1, 999);
    #if ENABLED(DISTINCT_E_FACTORS)
      MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E, &planner.max_feedrate_mm_s[E_AXIS + active_extruder], 1, 999);
      MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E1, &planner.max_feedrate_mm_s[E_AXIS], 1, 999);
      MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E2, &planner.max_feedrate_mm_s[E_AXIS + 1], 1, 999);
      #if E_STEPPERS > 2
        MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E3, &planner.max_feedrate_mm_s[E_AXIS + 2], 1, 999);
        #if E_STEPPERS > 3
          MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E4, &planner.max_feedrate_mm_s[E_AXIS + 3], 1, 999);
          #if E_STEPPERS > 4
            MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E5, &planner.max_feedrate_mm_s[E_AXIS + 4], 1, 999);
          #endif 
        #endif 
      #endif 
    #else
      MENU_ITEM_EDIT(float3, MSG_VMAX MSG_E, &planner.max_feedrate_mm_s[E_AXIS], 1, 999);
    #endif
    MENU_ITEM_EDIT(float3, MSG_VMIN, &planner.min_feedrate_mm_s, 0, 999);
    MENU_ITEM_EDIT(float3, MSG_VTRAV_MIN, &planner.min_travel_feedrate_mm_s, 0, 999);
    END_MENU();
  }
  void lcd_control_motion_acceleration_menu() {
    START_MENU();
    MENU_BACK(MSG_MOTION);
    MENU_ITEM_EDIT(float5, MSG_ACC, &planner.acceleration, 10, 99000);
    MENU_ITEM_EDIT(float5, MSG_A_RETRACT, &planner.retract_acceleration, 100, 99000);
    MENU_ITEM_EDIT(float5, MSG_A_TRAVEL, &planner.travel_acceleration, 100, 99000);
    MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_X, &planner.max_acceleration_mm_per_s2[X_AXIS], 100, 99000, _reset_acceleration_rates);
    MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_Y, &planner.max_acceleration_mm_per_s2[Y_AXIS], 100, 99000, _reset_acceleration_rates);
    MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_Z, &planner.max_acceleration_mm_per_s2[Z_AXIS], 10, 99000, _reset_acceleration_rates);
    #if ENABLED(DISTINCT_E_FACTORS)
      MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E, &planner.max_acceleration_mm_per_s2[E_AXIS + active_extruder], 100, 99000, _reset_acceleration_rates);
      MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E1, &planner.max_acceleration_mm_per_s2[E_AXIS], 100, 99000, _reset_e0_acceleration_rate);
      MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E2, &planner.max_acceleration_mm_per_s2[E_AXIS + 1], 100, 99000, _reset_e1_acceleration_rate);
      #if E_STEPPERS > 2
        MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E3, &planner.max_acceleration_mm_per_s2[E_AXIS + 2], 100, 99000, _reset_e2_acceleration_rate);
        #if E_STEPPERS > 3
          MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E4, &planner.max_acceleration_mm_per_s2[E_AXIS + 3], 100, 99000, _reset_e3_acceleration_rate);
          #if E_STEPPERS > 4
            MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E5, &planner.max_acceleration_mm_per_s2[E_AXIS + 4], 100, 99000, _reset_e4_acceleration_rate);
          #endif 
        #endif 
      #endif 
    #else
      MENU_ITEM_EDIT_CALLBACK(long5, MSG_AMAX MSG_E, &planner.max_acceleration_mm_per_s2[E_AXIS], 100, 99000, _reset_acceleration_rates);
    #endif
    END_MENU();
  }
  void lcd_control_motion_jerk_menu() {
    START_MENU();
    MENU_BACK(MSG_MOTION);
    MENU_ITEM_EDIT(float3, MSG_VX_JERK, &planner.max_jerk[X_AXIS], 1, 990);
    MENU_ITEM_EDIT(float3, MSG_VY_JERK, &planner.max_jerk[Y_AXIS], 1, 990);
    #if ENABLED(DELTA)
      MENU_ITEM_EDIT(float3, MSG_VZ_JERK, &planner.max_jerk[Z_AXIS], 1, 990);
    #else
      MENU_ITEM_EDIT(float52, MSG_VZ_JERK, &planner.max_jerk[Z_AXIS], 0.1, 990);
    #endif
    MENU_ITEM_EDIT(float3, MSG_VE_JERK, &planner.max_jerk[E_AXIS], 1, 990);
    END_MENU();
  }
  void lcd_control_motion_steps_per_mm_menu() {
    START_MENU();
    MENU_BACK(MSG_MOTION);
    MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_XSTEPS, &planner.axis_steps_per_mm[X_AXIS], 5, 9999, _planner_refresh_positioning);
    MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_YSTEPS, &planner.axis_steps_per_mm[Y_AXIS], 5, 9999, _planner_refresh_positioning);
    MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_ZSTEPS, &planner.axis_steps_per_mm[Z_AXIS], 5, 9999, _planner_refresh_positioning);
    #if ENABLED(DISTINCT_E_FACTORS)
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_ESTEPS, &planner.axis_steps_per_mm[E_AXIS + active_extruder], 5, 9999, _planner_refresh_positioning);
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_E1STEPS, &planner.axis_steps_per_mm[E_AXIS], 5, 9999, _planner_refresh_e0_positioning);
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_E2STEPS, &planner.axis_steps_per_mm[E_AXIS + 1], 5, 9999, _planner_refresh_e1_positioning);
      #if E_STEPPERS > 2
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_E3STEPS, &planner.axis_steps_per_mm[E_AXIS + 2], 5, 9999, _planner_refresh_e2_positioning);
        #if E_STEPPERS > 3
          MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_E4STEPS, &planner.axis_steps_per_mm[E_AXIS + 3], 5, 9999, _planner_refresh_e3_positioning);
          #if E_STEPPERS > 4
            MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_E5STEPS, &planner.axis_steps_per_mm[E_AXIS + 4], 5, 9999, _planner_refresh_e4_positioning);
          #endif 
        #endif 
      #endif 
    #else
      MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float62, MSG_ESTEPS, &planner.axis_steps_per_mm[E_AXIS], 5, 9999, _planner_refresh_positioning);
    #endif
    END_MENU();
  }
  void lcd_control_motion_menu() {
    START_MENU();
    MENU_BACK(MSG_CONTROL);
    #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
      MENU_ITEM(submenu, MSG_ZPROBE_ZOFFSET, lcd_babystep_zoffset);
    #elif HAS_BED_PROBE
      MENU_ITEM_EDIT_CALLBACK(float32, MSG_ZPROBE_ZOFFSET, &zprobe_zoffset, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX, lcd_refresh_zprobe_zoffset);
    #endif
    MENU_ITEM(submenu, MSG_VELOCITY, lcd_control_motion_velocity_menu);
    MENU_ITEM(submenu, MSG_ACCELERATION, lcd_control_motion_acceleration_menu);
    MENU_ITEM(submenu, MSG_JERK, lcd_control_motion_jerk_menu);
    MENU_ITEM(submenu, MSG_STEPS_PER_MM, lcd_control_motion_steps_per_mm_menu);
    #if ENABLED(ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED)
      MENU_ITEM_EDIT(bool, MSG_ENDSTOP_ABORT, &stepper.abort_on_endstop_hit);
    #endif
    END_MENU();
  }
  void lcd_control_filament_menu() {
    START_MENU();
    MENU_BACK(MSG_CONTROL);
    #if ENABLED(LIN_ADVANCE)
      MENU_ITEM_EDIT(float3, MSG_ADVANCE_K, &planner.extruder_advance_k, 0, 999);
    #endif
    MENU_ITEM_EDIT_CALLBACK(bool, MSG_VOLUMETRIC_ENABLED, &volumetric_enabled, calculate_volumetric_multipliers);
    if (volumetric_enabled) {
      #if EXTRUDERS == 1
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float43, MSG_FILAMENT_DIAM, &filament_size[0], 1.5, 3.25, calculate_volumetric_multipliers);
      #else 
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float43, MSG_FILAMENT_DIAM MSG_DIAM_E1, &filament_size[0], 1.5, 3.25, calculate_volumetric_multipliers);
        MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float43, MSG_FILAMENT_DIAM MSG_DIAM_E2, &filament_size[1], 1.5, 3.25, calculate_volumetric_multipliers);
        #if EXTRUDERS > 2
          MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float43, MSG_FILAMENT_DIAM MSG_DIAM_E3, &filament_size[2], 1.5, 3.25, calculate_volumetric_multipliers);
          #if EXTRUDERS > 3
            MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float43, MSG_FILAMENT_DIAM MSG_DIAM_E4, &filament_size[3], 1.5, 3.25, calculate_volumetric_multipliers);
            #if EXTRUDERS > 4
              MENU_MULTIPLIER_ITEM_EDIT_CALLBACK(float43, MSG_FILAMENT_DIAM MSG_DIAM_E5, &filament_size[4], 1.5, 3.25, calculate_volumetric_multipliers);
            #endif 
          #endif 
        #endif 
      #endif 
    }
    END_MENU();
  }
  #if ENABLED(FWRETRACT)
    void lcd_control_retract_menu() {
      START_MENU();
      MENU_BACK(MSG_CONTROL);
      MENU_ITEM_EDIT(bool, MSG_AUTORETRACT, &autoretract_enabled);
      MENU_ITEM_EDIT(float52, MSG_CONTROL_RETRACT, &retract_length, 0, 100);
      #if EXTRUDERS > 1
        MENU_ITEM_EDIT(float52, MSG_CONTROL_RETRACT_SWAP, &retract_length_swap, 0, 100);
      #endif
      MENU_ITEM_EDIT(float3, MSG_CONTROL_RETRACTF, &retract_feedrate_mm_s, 1, 999);
      MENU_ITEM_EDIT(float52, MSG_CONTROL_RETRACT_ZLIFT, &retract_zlift, 0, 999);
      MENU_ITEM_EDIT(float52, MSG_CONTROL_RETRACT_RECOVER, &retract_recover_length, -100, 100);
      #if EXTRUDERS > 1
        MENU_ITEM_EDIT(float52, MSG_CONTROL_RETRACT_RECOVER_SWAP, &retract_recover_length_swap, -100, 100);
      #endif
      MENU_ITEM_EDIT(float3, MSG_CONTROL_RETRACT_RECOVERF, &retract_recover_feedrate_mm_s, 1, 999);
      END_MENU();
    }
  #endif 
  #if ENABLED(SDSUPPORT)
    #if !PIN_EXISTS(SD_DETECT)
      void lcd_sd_refresh() {
        card.initsd();
        encoderTopLine = 0;
      }
    #endif
    void lcd_sd_updir() {
      card.updir();
      encoderTopLine = 0;
      screen_changed = true;
      lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW;
    }
    void lcd_sdcard_menu() {
      ENCODER_DIRECTION_MENUS();
      if (!lcdDrawUpdate && !lcd_clicked) return; 
      const uint16_t fileCnt = card.getnrfilenames();
      START_MENU();
      MENU_BACK(MSG_MAIN);
      card.getWorkDirName();
      if (card.filename[0] == '/') {
        #if !PIN_EXISTS(SD_DETECT)
          MENU_ITEM(function, LCD_STR_REFRESH MSG_REFRESH, lcd_sd_refresh);
        #endif
      }
      else {
        MENU_ITEM(function, LCD_STR_FOLDER "..", lcd_sd_updir);
      }
      for (uint16_t i = 0; i < fileCnt; i++) {
        if (_menuLineNr == _thisItemNr) {
          const uint16_t nr =
            #if ENABLED(SDCARD_RATHERRECENTFIRST) && DISABLED(SDCARD_SORT_ALPHA)
              fileCnt - 1 -
            #endif
          i;
          #if ENABLED(SDCARD_SORT_ALPHA)
            card.getfilename_sorted(nr);
          #else
            card.getfilename(nr);
          #endif
          if (card.filenameIsDir)
            MENU_ITEM(sddirectory, MSG_CARD_MENU, card.filename, card.longFilename);
          else
            MENU_ITEM(sdfile, MSG_CARD_MENU, card.filename, card.longFilename);
        }
        else {
          MENU_ITEM_DUMMY();
        }
      }
      END_MENU();
    }
  #endif 
  #if ENABLED(LCD_INFO_MENU)
    #if ENABLED(PRINTCOUNTER)
      void lcd_info_stats_menu() {
        if (lcd_clicked) { return lcd_goto_previous_menu(); }
        char buffer[21];
        printStatistics stats = print_job_timer.getStats();
        START_SCREEN();                                                                                
        STATIC_ITEM(MSG_INFO_PRINT_COUNT ": ", false, false, itostr3left(stats.totalPrints));          
        STATIC_ITEM(MSG_INFO_COMPLETED_PRINTS": ", false, false, itostr3left(stats.finishedPrints));   
        duration_t elapsed = stats.printTime;
        elapsed.toString(buffer);
        STATIC_ITEM(MSG_INFO_PRINT_TIME ": ", false, false);                                           
        STATIC_ITEM("", false, false, buffer);                                                         
        elapsed = stats.longestPrint;
        elapsed.toString(buffer);
        STATIC_ITEM(MSG_INFO_PRINT_LONGEST ": ", false, false);                                        
        STATIC_ITEM("", false, false, buffer);                                                         
        sprintf_P(buffer, PSTR("%ld.%im"), long(stats.filamentUsed / 1000), int16_t(stats.filamentUsed / 100) % 10);
        STATIC_ITEM(MSG_INFO_PRINT_FILAMENT ": ", false, false);                                       
        STATIC_ITEM("", false, false, buffer);                                                         
        END_SCREEN();
      }
    #endif 
    void lcd_info_thermistors_menu() {
      if (lcd_clicked) { return lcd_goto_previous_menu(); }
      START_SCREEN();
      #define THERMISTOR_ID TEMP_SENSOR_0
      #include "thermistornames.h"
      STATIC_ITEM("T0: " THERMISTOR_NAME, false, true);
      STATIC_ITEM(MSG_INFO_MIN_TEMP ": " STRINGIFY(HEATER_0_MINTEMP), false);
      STATIC_ITEM(MSG_INFO_MAX_TEMP ": " STRINGIFY(HEATER_0_MAXTEMP), false);
      #if TEMP_SENSOR_1 != 0
        #undef THERMISTOR_ID
        #define THERMISTOR_ID TEMP_SENSOR_1
        #include "thermistornames.h"
        STATIC_ITEM("T1: " THERMISTOR_NAME, false, true);
        STATIC_ITEM(MSG_INFO_MIN_TEMP ": " STRINGIFY(HEATER_1_MINTEMP), false);
        STATIC_ITEM(MSG_INFO_MAX_TEMP ": " STRINGIFY(HEATER_1_MAXTEMP), false);
      #endif
      #if TEMP_SENSOR_2 != 0
        #undef THERMISTOR_ID
        #define THERMISTOR_ID TEMP_SENSOR_2
        #include "thermistornames.h"
        STATIC_ITEM("T2: " THERMISTOR_NAME, false, true);
        STATIC_ITEM(MSG_INFO_MIN_TEMP ": " STRINGIFY(HEATER_2_MINTEMP), false);
        STATIC_ITEM(MSG_INFO_MAX_TEMP ": " STRINGIFY(HEATER_2_MAXTEMP), false);
      #endif
      #if TEMP_SENSOR_3 != 0
        #undef THERMISTOR_ID
        #define THERMISTOR_ID TEMP_SENSOR_3
        #include "thermistornames.h"
        STATIC_ITEM("T3: " THERMISTOR_NAME, false, true);
        STATIC_ITEM(MSG_INFO_MIN_TEMP ": " STRINGIFY(HEATER_3_MINTEMP), false);
        STATIC_ITEM(MSG_INFO_MAX_TEMP ": " STRINGIFY(HEATER_3_MAXTEMP), false);
      #endif
      #if TEMP_SENSOR_4 != 0
        #undef THERMISTOR_ID
        #define THERMISTOR_ID TEMP_SENSOR_4
        #include "thermistornames.h"
        STATIC_ITEM("T4: " THERMISTOR_NAME, false, true);
        STATIC_ITEM(MSG_INFO_MIN_TEMP ": " STRINGIFY(HEATER_4_MINTEMP), false);
        STATIC_ITEM(MSG_INFO_MAX_TEMP ": " STRINGIFY(HEATER_4_MAXTEMP), false);
      #endif
      #if TEMP_SENSOR_BED != 0
        #undef THERMISTOR_ID
        #define THERMISTOR_ID TEMP_SENSOR_BED
        #include "thermistornames.h"
        STATIC_ITEM("TBed:" THERMISTOR_NAME, false, true);
        STATIC_ITEM(MSG_INFO_MIN_TEMP ": " STRINGIFY(BED_MINTEMP), false);
        STATIC_ITEM(MSG_INFO_MAX_TEMP ": " STRINGIFY(BED_MAXTEMP), false);
      #endif
      END_SCREEN();
    }
    void lcd_info_board_menu() {
      if (lcd_clicked) { return lcd_goto_previous_menu(); }
      START_SCREEN();
      STATIC_ITEM(BOARD_NAME, true, true);                           
      STATIC_ITEM(MSG_INFO_BAUDRATE ": " STRINGIFY(BAUDRATE), true); 
      STATIC_ITEM(MSG_INFO_PROTOCOL ": " PROTOCOL_VERSION, true);    
      #if POWER_SUPPLY == 0
        STATIC_ITEM(MSG_INFO_PSU ": Generic", true);
      #elif POWER_SUPPLY == 1
        STATIC_ITEM(MSG_INFO_PSU ": ATX", true);  
      #elif POWER_SUPPLY == 2
        STATIC_ITEM(MSG_INFO_PSU ": XBox", true); 
      #endif
      END_SCREEN();
    }
    void lcd_info_printer_menu() {
      if (lcd_clicked) { return lcd_goto_previous_menu(); }
      START_SCREEN();
      STATIC_ITEM(MSG_MARLIN, true, true);                             
      STATIC_ITEM(SHORT_BUILD_VERSION, true);                          
      STATIC_ITEM(STRING_DISTRIBUTION_DATE, true);                     
      STATIC_ITEM(MACHINE_NAME, true);                                 
      STATIC_ITEM(WEBSITE_URL, true);                                  
      STATIC_ITEM(MSG_INFO_EXTRUDERS ": " STRINGIFY(EXTRUDERS), true); 
      #if ENABLED(AUTO_BED_LEVELING_3POINT)
        STATIC_ITEM(MSG_3POINT_LEVELING, true);                        
      #elif ENABLED(AUTO_BED_LEVELING_LINEAR)
        STATIC_ITEM(MSG_LINEAR_LEVELING, true);                        
      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
        STATIC_ITEM(MSG_BILINEAR_LEVELING, true);                      
      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        STATIC_ITEM(MSG_UBL_LEVELING, true);                           
      #elif ENABLED(MESH_BED_LEVELING)
        STATIC_ITEM(MSG_MESH_LEVELING, true);                          
      #endif
      END_SCREEN();
    }
    void lcd_info_menu() {
      START_MENU();
      MENU_BACK(MSG_MAIN);
      MENU_ITEM(submenu, MSG_INFO_PRINTER_MENU, lcd_info_printer_menu);        
      MENU_ITEM(submenu, MSG_INFO_BOARD_MENU, lcd_info_board_menu);            
      MENU_ITEM(submenu, MSG_INFO_THERMISTOR_MENU, lcd_info_thermistors_menu); 
      #if ENABLED(PRINTCOUNTER)
        MENU_ITEM(submenu, MSG_INFO_STATS_MENU, lcd_info_stats_menu);          
      #endif
      END_MENU();
    }
  #endif 
  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    #define HOTEND_STATUS_ITEM() do { \
      if (_menuLineNr == _thisItemNr) { \
        if (lcdDrawUpdate) { \
          lcd_implementation_drawmenu_static(_lcdLineNr, PSTR(MSG_FILAMENT_CHANGE_NOZZLE), false, true); \
          lcd_implementation_hotend_status(_lcdLineNr); \
        } \
        if (_skipStatic && encoderLine <= _thisItemNr) { \
          encoderPosition += ENCODER_STEPS_PER_MENU_ITEM; \
          ++encoderLine; \
        } \
        lcdDrawUpdate = LCDVIEW_CALL_REDRAW_NEXT; \
      } \
      ++_thisItemNr; \
    }while(0)
    void lcd_advanced_pause_toocold_menu() {
      START_MENU();
      STATIC_ITEM(MSG_HEATING_FAILED_LCD, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_MINTEMP STRINGIFY(EXTRUDE_MINTEMP) ".", false, false);
      MENU_BACK(MSG_BACK);
      #if LCD_HEIGHT > 4
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_MENU();
    }
    void lcd_advanced_pause_resume_print() {
      advanced_pause_menu_response = ADVANCED_PAUSE_RESPONSE_RESUME_PRINT;
    }
    void lcd_advanced_pause_extrude_more() {
      advanced_pause_menu_response = ADVANCED_PAUSE_RESPONSE_EXTRUDE_MORE;
    }
    void lcd_advanced_pause_option_menu() {
      START_MENU();
      #if LCD_HEIGHT > 2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_OPTION_HEADER, true, false);
      #endif
      MENU_ITEM(function, MSG_FILAMENT_CHANGE_OPTION_RESUME, lcd_advanced_pause_resume_print);
      MENU_ITEM(function, MSG_FILAMENT_CHANGE_OPTION_EXTRUDE, lcd_advanced_pause_extrude_more);
      END_MENU();
    }
    void lcd_advanced_pause_init_message() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_INIT_1);
      #ifdef MSG_FILAMENT_CHANGE_INIT_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_INIT_2);
        #define __FC_LINES_A 3
      #else
        #define __FC_LINES_A 2
      #endif
      #ifdef MSG_FILAMENT_CHANGE_INIT_3
        STATIC_ITEM(MSG_FILAMENT_CHANGE_INIT_3);
        #define _FC_LINES_A (__FC_LINES_A + 1)
      #else
        #define _FC_LINES_A __FC_LINES_A
      #endif
      #if LCD_HEIGHT > _FC_LINES_A + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_unload_message() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_UNLOAD_1);
      #ifdef MSG_FILAMENT_CHANGE_UNLOAD_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_UNLOAD_2);
        #define __FC_LINES_B 3
      #else
        #define __FC_LINES_B 2
      #endif
      #ifdef MSG_FILAMENT_CHANGE_UNLOAD_3
        STATIC_ITEM(MSG_FILAMENT_CHANGE_UNLOAD_3);
        #define _FC_LINES_B (__FC_LINES_B + 1)
      #else
        #define _FC_LINES_B __FC_LINES_B
      #endif
      #if LCD_HEIGHT > _FC_LINES_B + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_wait_for_nozzles_to_heat() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEATING_1);
      #ifdef MSG_FILAMENT_CHANGE_HEATING_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_HEATING_2);
        #define _FC_LINES_C 3
      #else
        #define _FC_LINES_C 2
      #endif
      #if LCD_HEIGHT > _FC_LINES_C + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_heat_nozzle() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEAT_1);
      #ifdef MSG_FILAMENT_CHANGE_INSERT_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_HEAT_2);
        #define _FC_LINES_D 3
      #else
        #define _FC_LINES_D 2
      #endif
      #if LCD_HEIGHT > _FC_LINES_D + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_insert_message() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_INSERT_1);
      #ifdef MSG_FILAMENT_CHANGE_INSERT_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_INSERT_2);
        #define __FC_LINES_E 3
      #else
        #define __FC_LINES_E 2
      #endif
      #ifdef MSG_FILAMENT_CHANGE_INSERT_3
        STATIC_ITEM(MSG_FILAMENT_CHANGE_INSERT_3);
        #define _FC_LINES_E (__FC_LINES_E + 1)
      #else
        #define _FC_LINES_E __FC_LINES_E
      #endif
      #if LCD_HEIGHT > _FC_LINES_E + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_load_message() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_LOAD_1);
      #ifdef MSG_FILAMENT_CHANGE_LOAD_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_LOAD_2);
        #define __FC_LINES_F 3
      #else
        #define __FC_LINES_F 2
      #endif
      #ifdef MSG_FILAMENT_CHANGE_LOAD_3
        STATIC_ITEM(MSG_FILAMENT_CHANGE_LOAD_3);
        #define _FC_LINES_F (__FC_LINES_F + 1)
      #else
        #define _FC_LINES_F __FC_LINES_F
      #endif
      #if LCD_HEIGHT > _FC_LINES_F + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_extrude_message() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_EXTRUDE_1);
      #ifdef MSG_FILAMENT_CHANGE_EXTRUDE_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_EXTRUDE_2);
        #define __FC_LINES_G 3
      #else
        #define __FC_LINES_G 2
      #endif
      #ifdef MSG_FILAMENT_CHANGE_EXTRUDE_3
        STATIC_ITEM(MSG_FILAMENT_CHANGE_EXTRUDE_3);
        #define _FC_LINES_G (__FC_LINES_G + 1)
      #else
        #define _FC_LINES_G __FC_LINES_G
      #endif
      #if LCD_HEIGHT > _FC_LINES_G + 1
        STATIC_ITEM(" ");
      #endif
      HOTEND_STATUS_ITEM();
      END_SCREEN();
    }
    void lcd_advanced_pause_resume_message() {
      START_SCREEN();
      STATIC_ITEM(MSG_FILAMENT_CHANGE_HEADER, true, true);
      STATIC_ITEM(MSG_FILAMENT_CHANGE_RESUME_1);
      #ifdef MSG_FILAMENT_CHANGE_RESUME_2
        STATIC_ITEM(MSG_FILAMENT_CHANGE_RESUME_2);
      #endif
      #ifdef MSG_FILAMENT_CHANGE_RESUME_3
        STATIC_ITEM(MSG_FILAMENT_CHANGE_RESUME_3);
      #endif
      END_SCREEN();
    }
    void lcd_advanced_pause_show_message(const AdvancedPauseMessage message) {
      switch (message) {
        case ADVANCED_PAUSE_MESSAGE_INIT:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_init_message);
          break;
        case ADVANCED_PAUSE_MESSAGE_UNLOAD:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_unload_message);
          break;
        case ADVANCED_PAUSE_MESSAGE_INSERT:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_insert_message);
          break;
        case ADVANCED_PAUSE_MESSAGE_LOAD:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_load_message);
          break;
        case ADVANCED_PAUSE_MESSAGE_EXTRUDE:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_extrude_message);
          break;
        case ADVANCED_PAUSE_MESSAGE_CLICK_TO_HEAT_NOZZLE:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_heat_nozzle);
          break;
        case ADVANCED_PAUSE_MESSAGE_WAIT_FOR_NOZZLES_TO_HEAT:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_wait_for_nozzles_to_heat);
          break;
        case ADVANCED_PAUSE_MESSAGE_OPTION:
          defer_return_to_status = true;
          advanced_pause_menu_response = ADVANCED_PAUSE_RESPONSE_WAIT_FOR;
          lcd_goto_screen(lcd_advanced_pause_option_menu);
          break;
        case ADVANCED_PAUSE_MESSAGE_RESUME:
          defer_return_to_status = true;
          lcd_goto_screen(lcd_advanced_pause_resume_message);
          break;
        case ADVANCED_PAUSE_MESSAGE_STATUS:
          lcd_return_to_status();
          break;
      }
    }
  #endif 
  #define DEFINE_MENU_EDIT_TYPE(_type, _name, _strFunc, _scale) \
    bool _menu_edit_ ## _name() { \
      ENCODER_DIRECTION_NORMAL(); \
      if ((int32_t)encoderPosition < 0) encoderPosition = 0; \
      if ((int32_t)encoderPosition > maxEditValue) encoderPosition = maxEditValue; \
      if (lcdDrawUpdate) \
        lcd_implementation_drawedit(editLabel, _strFunc(((_type)((int32_t)encoderPosition + minEditValue)) * (1.0 / _scale))); \
      if (lcd_clicked || (liveEdit && lcdDrawUpdate)) { \
        _type value = ((_type)((int32_t)encoderPosition + minEditValue)) * (1.0 / _scale); \
        if (editValue != NULL) *((_type*)editValue) = value; \
        if (liveEdit) (*callbackFunc)(); \
        if (lcd_clicked) lcd_goto_previous_menu(); \
      } \
      return lcd_clicked; \
    } \
    void menu_edit_ ## _name() { _menu_edit_ ## _name(); } \
    void menu_edit_callback_ ## _name() { if (_menu_edit_ ## _name()) (*callbackFunc)(); } \
    void _menu_action_setting_edit_ ## _name(const char * const pstr, _type* const ptr, const _type minValue, const _type maxValue) { \
      lcd_save_previous_screen(); \
      \
      lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW; \
      \
      editLabel = pstr; \
      editValue = ptr; \
      minEditValue = minValue * _scale; \
      maxEditValue = maxValue * _scale - minEditValue; \
      encoderPosition = (*ptr) * _scale - minEditValue; \
    } \
    void menu_action_setting_edit_ ## _name(const char * const pstr, _type * const ptr, const _type minValue, const _type maxValue) { \
      _menu_action_setting_edit_ ## _name(pstr, ptr, minValue, maxValue); \
      currentScreen = menu_edit_ ## _name; \
    } \
    void menu_action_setting_edit_callback_ ## _name(const char * const pstr, _type * const ptr, const _type minValue, const _type maxValue, const screenFunc_t callback, const bool live) { \
      _menu_action_setting_edit_ ## _name(pstr, ptr, minValue, maxValue); \
      currentScreen = menu_edit_callback_ ## _name; \
      callbackFunc = callback; \
      liveEdit = live; \
    } \
    typedef void _name
  DEFINE_MENU_EDIT_TYPE(int16_t, int3, itostr3, 1);
  DEFINE_MENU_EDIT_TYPE(uint8_t, int8, i8tostr3, 1);
  DEFINE_MENU_EDIT_TYPE(float, float3, ftostr3, 1.0);
  DEFINE_MENU_EDIT_TYPE(float, float32, ftostr32, 100.0);
  DEFINE_MENU_EDIT_TYPE(float, float43, ftostr43sign, 1000.0);
  DEFINE_MENU_EDIT_TYPE(float, float5, ftostr5rj, 0.01);
  DEFINE_MENU_EDIT_TYPE(float, float51, ftostr51sign, 10.0);
  DEFINE_MENU_EDIT_TYPE(float, float52, ftostr52sign, 100.0);
  DEFINE_MENU_EDIT_TYPE(float, float62, ftostr62rj, 100.0);
  DEFINE_MENU_EDIT_TYPE(uint32_t, long5, ftostr5rj, 0.01);
  #if ENABLED(ADC_KEYPAD)
    inline bool handle_adc_keypad() {
      static uint8_t adc_steps = 0;
      if (buttons_reprapworld_keypad) {
        if (adc_steps < 20) ++adc_steps;
        lcd_quick_feedback();
        lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
        if (encoderDirection == -1) { 
          if      (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_DOWN)  encoderPosition -= ENCODER_STEPS_PER_MENU_ITEM;
          else if (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_UP)    encoderPosition += ENCODER_STEPS_PER_MENU_ITEM;
          else if (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_LEFT)  menu_action_back();
          else if (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_RIGHT) lcd_return_to_status();
        }
        else {
          const int8_t step = adc_steps > 19 ? 100 : adc_steps > 10 ? 10 : 1;
               if (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_DOWN)  encoderPosition += ENCODER_PULSES_PER_STEP * step;
          else if (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_UP)    encoderPosition -= ENCODER_PULSES_PER_STEP * step;
          else if (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_RIGHT) encoderPosition = 0;
        }
        #if ENABLED(ADC_KEYPAD_DEBUG)
          SERIAL_PROTOCOLLNPAIR("buttons_reprapworld_keypad = ", (uint32_t)buttons_reprapworld_keypad);
          SERIAL_PROTOCOLLNPAIR("encoderPosition = ", (uint32_t)encoderPosition);
        #endif
        return true;
      }
      else if (!thermalManager.current_ADCKey_raw)
        adc_steps = 0; 
      return false;
    }
  #elif ENABLED(REPRAPWORLD_KEYPAD)
    void _reprapworld_keypad_move(const AxisEnum axis, const int16_t dir) {
      move_menu_scale = REPRAPWORLD_KEYPAD_MOVE_STEP;
      encoderPosition = dir;
      switch (axis) {
        case X_AXIS: lcd_move_x(); break;
        case Y_AXIS: lcd_move_y(); break;
        case Z_AXIS: lcd_move_z();
        default: break;
      }
    }
    void reprapworld_keypad_move_z_up()    { _reprapworld_keypad_move(Z_AXIS,  1); }
    void reprapworld_keypad_move_z_down()  { _reprapworld_keypad_move(Z_AXIS, -1); }
    void reprapworld_keypad_move_x_left()  { _reprapworld_keypad_move(X_AXIS, -1); }
    void reprapworld_keypad_move_x_right() { _reprapworld_keypad_move(X_AXIS,  1); }
    void reprapworld_keypad_move_y_up()    { _reprapworld_keypad_move(Y_AXIS, -1); }
    void reprapworld_keypad_move_y_down()  { _reprapworld_keypad_move(Y_AXIS,  1); }
    void reprapworld_keypad_move_home()    { enqueue_and_echo_commands_P(PSTR("G28")); } 
    void reprapworld_keypad_move_menu()    { lcd_goto_screen(lcd_move_menu); }
    inline void handle_reprapworld_keypad() {
      static uint8_t keypad_debounce = 0;
      if (!REPRAPWORLD_KEYPAD_PRESSED) {
        if (keypad_debounce > 0) keypad_debounce--;
      }
      else if (!keypad_debounce) {
        keypad_debounce = 2;
        if (REPRAPWORLD_KEYPAD_MOVE_MENU)       reprapworld_keypad_move_menu();
        #if DISABLED(DELTA) && Z_HOME_DIR == -1
          if (REPRAPWORLD_KEYPAD_MOVE_Z_UP)     reprapworld_keypad_move_z_up();
        #endif
        if (axis_homed[X_AXIS] && axis_homed[Y_AXIS] && axis_homed[Z_AXIS]) {
          #if ENABLED(DELTA) || Z_HOME_DIR != -1
            if (REPRAPWORLD_KEYPAD_MOVE_Z_UP)   reprapworld_keypad_move_z_up();
          #endif
          if (REPRAPWORLD_KEYPAD_MOVE_Z_DOWN)   reprapworld_keypad_move_z_down();
          if (REPRAPWORLD_KEYPAD_MOVE_X_LEFT)   reprapworld_keypad_move_x_left();
          if (REPRAPWORLD_KEYPAD_MOVE_X_RIGHT)  reprapworld_keypad_move_x_right();
          if (REPRAPWORLD_KEYPAD_MOVE_Y_DOWN)   reprapworld_keypad_move_y_down();
          if (REPRAPWORLD_KEYPAD_MOVE_Y_UP)     reprapworld_keypad_move_y_up();
        }
        else {
          if (REPRAPWORLD_KEYPAD_MOVE_HOME)     reprapworld_keypad_move_home();
        }
      }
    }
  #endif 
  void _menu_action_back() { lcd_goto_previous_menu(); }
  void menu_action_submenu(screenFunc_t func) { lcd_save_previous_screen(); lcd_goto_screen(func); }
  void menu_action_gcode(const char* pgcode) { enqueue_and_echo_commands_P(pgcode); }
  void menu_action_function(screenFunc_t func) { (*func)(); }
  #if ENABLED(SDSUPPORT)
    void menu_action_sdfile(const char* filename, char* longFilename) {
      UNUSED(longFilename);
      card.openAndPrintFile(filename);
      lcd_return_to_status();
    }
    void menu_action_sddirectory(const char* filename, char* longFilename) {
      UNUSED(longFilename);
      card.chdir(filename);
      encoderPosition = 0;
      screen_changed = true;
      lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW;
    }
  #endif 
  void menu_action_setting_edit_bool(const char* pstr, bool* ptr) { UNUSED(pstr); *ptr ^= true; lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW; }
  void menu_action_setting_edit_callback_bool(const char* pstr, bool* ptr, screenFunc_t callback) {
    menu_action_setting_edit_bool(pstr, ptr);
    (*callback)();
  }
#endif 
void lcd_init() {
  lcd_implementation_init(
    #if ENABLED(LCD_PROGRESS_BAR)
      true
    #endif
  );
  #if ENABLED(NEWPANEL)
    #if BUTTON_EXISTS(EN1)
      SET_INPUT_PULLUP(BTN_EN1);
    #endif
    #if BUTTON_EXISTS(EN2)
      SET_INPUT_PULLUP(BTN_EN2);
    #endif
    #if BUTTON_EXISTS(ENC)
      SET_INPUT_PULLUP(BTN_ENC);
    #endif
    #if ENABLED(REPRAPWORLD_KEYPAD) && DISABLED(ADC_KEYPAD)
      SET_OUTPUT(SHIFT_CLK);
      OUT_WRITE(SHIFT_LD, HIGH);
      SET_INPUT_PULLUP(SHIFT_OUT);
    #endif
    #if BUTTON_EXISTS(UP)
      SET_INPUT(BTN_UP);
    #endif
    #if BUTTON_EXISTS(DWN)
      SET_INPUT(BTN_DWN);
    #endif
    #if BUTTON_EXISTS(LFT)
      SET_INPUT(BTN_LFT);
    #endif
    #if BUTTON_EXISTS(RT)
      SET_INPUT(BTN_RT);
    #endif
  #else 
    #if ENABLED(SR_LCD_2W_NL) 
      SET_OUTPUT(SR_DATA_PIN);
      SET_OUTPUT(SR_CLK_PIN);
    #elif defined(SHIFT_CLK)
      SET_OUTPUT(SHIFT_CLK);
      OUT_WRITE(SHIFT_LD, HIGH);
      OUT_WRITE(SHIFT_EN, LOW);
      SET_INPUT_PULLUP(SHIFT_OUT);
    #endif 
  #endif 
  #if ENABLED(SDSUPPORT) && PIN_EXISTS(SD_DETECT)
    SET_INPUT_PULLUP(SD_DETECT_PIN);
    lcd_sd_status = 2; 
  #endif
  #if ENABLED(LCD_HAS_SLOW_BUTTONS)
    slow_buttons = 0;
  #endif
  lcd_buttons_update();
  #if ENABLED(ULTIPANEL)
    encoderDiff = 0;
  #endif
}
int16_t lcd_strlen(const char* s) {
  int16_t i = 0, j = 0;
  while (s[i]) {
    if (PRINTABLE(s[i])) j++;
    i++;
  }
  return j;
}
int16_t lcd_strlen_P(const char* s) {
  int16_t j = 0;
  while (pgm_read_byte(s)) {
    if (PRINTABLE(pgm_read_byte(s))) j++;
    s++;
  }
  return j;
}
bool lcd_blink() {
  static uint8_t blink = 0;
  static millis_t next_blink_ms = 0;
  millis_t ms = millis();
  if (ELAPSED(ms, next_blink_ms)) {
    blink ^= 0xFF;
    next_blink_ms = ms + 1000 - LCD_UPDATE_INTERVAL / 2;
  }
  return blink != 0;
}
static void FunV042()
{
    uint8_t n;
    for (n = 0; n < 16; n++)
    {
        if (GLOBAL_var_V001&(1 << n))
        {
            GLOBAL_var_V001 &= ~((uint16_t)0x0001 << n);
            break;
        }
    }
    switch(n)
    {
    case MACRO_var_V005:
        defer_return_to_status = true;
        lcd_goto_screen(askForReprint);
        break;
    case MACRO_var_V006:
        defer_return_to_status = false;
        lcd_return_to_status();
        break;
    }
}
void lcd_update() {
    FunV042();
  #if ENABLED(ULTIPANEL)
    static millis_t return_to_status_ms = 0;
    manage_manual_move();
    lcd_buttons_update();
    #if ENABLED(AUTO_BED_LEVELING_UBL)
      const bool UBL_CONDITION = !ubl.has_control_of_lcd_panel;
    #else
      constexpr bool UBL_CONDITION = true;
    #endif
    if (UBL_CONDITION && LCD_CLICKED) {
      if (!wait_for_unclick) {           
        wait_for_unclick = true;         
        lcd_clicked = !wait_for_user;    
        wait_for_user = false;           
        lcd_quick_feedback();            
      }
    }
    else wait_for_unclick = false;
  #endif
  #if ENABLED(SDSUPPORT) && PIN_EXISTS(SD_DETECT)
    const bool sd_status = IS_SD_INSERTED;
    if (sd_status != lcd_sd_status && lcd_detected()) {
      if (sd_status) {
        card.initsd();
        if (lcd_sd_status != 2) LCD_MESSAGEPGM(MSG_SD_INSERTED);
      }
      else {
        card.release();
        if (lcd_sd_status != 2) LCD_MESSAGEPGM(MSG_SD_REMOVED);
      }
      lcd_sd_status = sd_status;
      lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW;
      lcd_implementation_init( 
        #if ENABLED(LCD_PROGRESS_BAR)
          currentScreen == lcd_status_screen
        #endif
      );
    }
  #endif 
  const millis_t ms = millis();
  if (ELAPSED(ms, next_lcd_update_ms)
    #if ENABLED(DOGLCD)
      || drawing_screen
    #endif
    ) {
    next_lcd_update_ms = ms + LCD_UPDATE_INTERVAL;
    #if ENABLED(LCD_HAS_STATUS_INDICATORS)
      lcd_implementation_update_indicators();
    #endif
    #if ENABLED(ULTIPANEL)
      #if ENABLED(LCD_HAS_SLOW_BUTTONS)
        slow_buttons = lcd_implementation_read_slow_buttons(); 
      #endif
      #if ENABLED(ADC_KEYPAD)
        if (handle_adc_keypad())
          return_to_status_ms = ms + LCD_TIMEOUT_TO_STATUS;
      #elif ENABLED(REPRAPWORLD_KEYPAD)
        handle_reprapworld_keypad();
      #endif
      bool encoderPastThreshold = (abs(encoderDiff) >= ENCODER_PULSES_PER_STEP);
      if (encoderPastThreshold || lcd_clicked) {
        if (encoderPastThreshold) {
          int32_t encoderMultiplier = 1;
          #if ENABLED(ENCODER_RATE_MULTIPLIER)
            if (encoderRateMultiplierEnabled) {
              int32_t encoderMovementSteps = abs(encoderDiff) / ENCODER_PULSES_PER_STEP;
              if (lastEncoderMovementMillis) {
                float encoderStepRate = float(encoderMovementSteps) / float(ms - lastEncoderMovementMillis) * 1000.0;
                if (encoderStepRate >= ENCODER_100X_STEPS_PER_SEC)     encoderMultiplier = 100;
                else if (encoderStepRate >= ENCODER_10X_STEPS_PER_SEC) encoderMultiplier = 10;
                #if ENABLED(ENCODER_RATE_MULTIPLIER_DEBUG)
                  SERIAL_ECHO_START();
                  SERIAL_ECHOPAIR("Enc Step Rate: ", encoderStepRate);
                  SERIAL_ECHOPAIR("  Multiplier: ", encoderMultiplier);
                  SERIAL_ECHOPAIR("  ENCODER_10X_STEPS_PER_SEC: ", ENCODER_10X_STEPS_PER_SEC);
                  SERIAL_ECHOPAIR("  ENCODER_100X_STEPS_PER_SEC: ", ENCODER_100X_STEPS_PER_SEC);
                  SERIAL_EOL();
                #endif 
              }
              lastEncoderMovementMillis = ms;
            } 
          #endif 
          encoderPosition += (encoderDiff * encoderMultiplier) / ENCODER_PULSES_PER_STEP;
          encoderDiff = 0;
        }
        return_to_status_ms = ms + LCD_TIMEOUT_TO_STATUS;
        lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
      }
    #endif 
    static int8_t lcd_status_update_delay = 1; 
    if (
      #if ENABLED(ULTIPANEL)
        currentScreen == lcd_status_screen &&
      #endif
      !lcd_status_update_delay--
    ) {
      lcd_status_update_delay = 9
        #if ENABLED(DOGLCD)
          + 3
        #endif
      ;
      max_display_update_time--;
      lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
    }
    uint16_t bbr2 = planner.block_buffer_runtime() >> 1;
    #if ENABLED(DOGLCD)
      if ((lcdDrawUpdate || drawing_screen) && (!bbr2 || (bbr2 > max_display_update_time)))
    #else
      if (lcdDrawUpdate && (!bbr2 || (bbr2 > max_display_update_time)))
    #endif
    {
      #if ENABLED(DOGLCD)
        if (!drawing_screen)
      #endif
        {
          switch (lcdDrawUpdate) {
            case LCDVIEW_CALL_NO_REDRAW:
              lcdDrawUpdate = LCDVIEW_NONE;
              break;
            case LCDVIEW_CLEAR_CALL_REDRAW: 
            case LCDVIEW_CALL_REDRAW_NEXT:  
              lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
            case LCDVIEW_REDRAW_NOW:        
            case LCDVIEW_NONE:
              break;
          } 
        }
      #if ENABLED(ADC_KEYPAD)
        buttons_reprapworld_keypad = 0;
      #endif
      #if ENABLED(ULTIPANEL)
        #define CURRENTSCREEN() (*currentScreen)(), lcd_clicked = false
      #else
        #define CURRENTSCREEN() lcd_status_screen()
      #endif
      #if ENABLED(DOGLCD)  
        if (!drawing_screen) {
          u8g.firstPage();
          drawing_screen = 1;
        }
        lcd_setFont(FONT_MENU);
        u8g.setColorIndex(1);
        CURRENTSCREEN();
        if (drawing_screen && (drawing_screen = u8g.nextPage())) {
          NOLESS(max_display_update_time, millis() - ms);
          return;
        }
      #else
        CURRENTSCREEN();
      #endif
      NOLESS(max_display_update_time, millis() - ms);
    }
    #if ENABLED(ULTIPANEL)
      if (currentScreen == lcd_status_screen || defer_return_to_status)
        return_to_status_ms = ms + LCD_TIMEOUT_TO_STATUS;
      else if (ELAPSED(ms, return_to_status_ms))
        lcd_return_to_status();
    #endif 
    #if ENABLED(DOGLCD)
      if (!drawing_screen)
    #endif
      {
        switch (lcdDrawUpdate) {
          case LCDVIEW_CLEAR_CALL_REDRAW:
            lcd_implementation_clear();
          case LCDVIEW_CALL_REDRAW_NEXT:
            lcdDrawUpdate = LCDVIEW_REDRAW_NOW;
            break;
          case LCDVIEW_REDRAW_NOW:
            lcdDrawUpdate = LCDVIEW_NONE;
            break;
          case LCDVIEW_NONE:
            break;
        } 
      }
  } 
}
void pad_message_string() {
  uint8_t i = 0, j = 0;
  char c;
  while ((c = lcd_status_message[i]) && j < LCD_WIDTH) {
    if (PRINTABLE(c)) j++;
    i++;
  }
  if (true
    #if ENABLED(STATUS_MESSAGE_SCROLLING)
      && j < LCD_WIDTH
    #endif
  ) {
    while (j++ < LCD_WIDTH) lcd_status_message[i++] = ' ';
    lcd_status_message[i] = '\0';
  }
}
void lcd_finishstatus(const bool persist=false) {
  pad_message_string();
  #if !(ENABLED(LCD_PROGRESS_BAR) && (PROGRESS_MSG_EXPIRE > 0))
    UNUSED(persist);
  #endif
  #if ENABLED(LCD_PROGRESS_BAR)
    progress_bar_ms = millis();
    #if PROGRESS_MSG_EXPIRE > 0
      expire_status_ms = persist ? 0 : progress_bar_ms + PROGRESS_MSG_EXPIRE;
    #endif
  #endif
  lcdDrawUpdate = LCDVIEW_CLEAR_CALL_REDRAW;
  #if ENABLED(FILAMENT_LCD_DISPLAY) && ENABLED(SDSUPPORT)
    previous_lcd_status_ms = millis();  
  #endif
  #if ENABLED(STATUS_MESSAGE_SCROLLING)
    status_scroll_pos = 0;
  #endif
}
#if ENABLED(LCD_PROGRESS_BAR) && PROGRESS_MSG_EXPIRE > 0
  void dontExpireStatus() { expire_status_ms = 0; }
#endif
bool lcd_hasstatus() { return (lcd_status_message[0] != '\0'); }
void lcd_setstatus(const char * const message, const bool persist) {
  if (lcd_status_message_level > 0) return;
  strncpy(lcd_status_message, message, 3 * (LCD_WIDTH));
  lcd_finishstatus(persist);
}
void lcd_setstatusPGM(const char * const message, int8_t level) {
  if (level < 0) level = lcd_status_message_level = 0;
  if (level < lcd_status_message_level) return;
  lcd_status_message_level = level;
  strncpy_P(lcd_status_message, message, 3 * (LCD_WIDTH));
  lcd_finishstatus(level > 0);
}
void lcd_status_printf_P(const uint8_t level, const char * const fmt, ...) {
  if (level < lcd_status_message_level) return;
  lcd_status_message_level = level;
  va_list args;
  va_start(args, fmt);
  vsnprintf_P(lcd_status_message, 3 * (LCD_WIDTH), fmt, args);
  va_end(args);
  lcd_finishstatus(level > 0);
}
void lcd_setalertstatusPGM(const char * const message) {
  lcd_setstatusPGM(message, 1);
  #if ENABLED(ULTIPANEL)
    lcd_return_to_status();
  #endif
}
void lcd_reset_alert_level() { lcd_status_message_level = 0; }
#if HAS_LCD_CONTRAST
  void set_lcd_contrast(const uint16_t value) {
    lcd_contrast = constrain(value, LCD_CONTRAST_MIN, LCD_CONTRAST_MAX);
    u8g.setContrast(lcd_contrast);
  }
#endif
#if ENABLED(ULTIPANEL)
  #if defined(EN_A) && defined(EN_B)
    #define encrot0 0
    #define encrot1 2
    #define encrot2 3
    #define encrot3 1
  #endif
  #define GET_BUTTON_STATES(DST) \
    uint8_t new_##DST = 0; \
    WRITE(SHIFT_LD, LOW); \
    WRITE(SHIFT_LD, HIGH); \
    for (int8_t i = 0; i < 8; i++) { \
      new_##DST >>= 1; \
      if (READ(SHIFT_OUT)) SBI(new_##DST, 7); \
      WRITE(SHIFT_CLK, HIGH); \
      WRITE(SHIFT_CLK, LOW); \
    } \
    DST = ~new_##DST; 
  void lcd_buttons_update() {
    static uint8_t lastEncoderBits;
    millis_t now = millis();
    if (ELAPSED(now, next_button_update_ms)) {
      #if ENABLED(NEWPANEL)
        uint8_t newbutton = 0;
        #if BUTTON_EXISTS(EN1)
          if (BUTTON_PRESSED(EN1)) newbutton |= EN_A;
        #endif
        #if BUTTON_EXISTS(EN2)
          if (BUTTON_PRESSED(EN2)) newbutton |= EN_B;
        #endif
        #if BUTTON_EXISTS(ENC)
          if (BUTTON_PRESSED(ENC)) newbutton |= EN_C;
        #endif
        #if LCD_HAS_DIRECTIONAL_BUTTONS
          #if ENABLED(REVERSE_MENU_DIRECTION)
            #define _ENCODER_UD_STEPS (ENCODER_STEPS_PER_MENU_ITEM * encoderDirection)
          #else
            #define _ENCODER_UD_STEPS ENCODER_STEPS_PER_MENU_ITEM
          #endif
          #if ENABLED(REVERSE_ENCODER_DIRECTION)
            #define ENCODER_UD_STEPS _ENCODER_UD_STEPS
            #define ENCODER_LR_PULSES ENCODER_PULSES_PER_STEP
          #else
            #define ENCODER_UD_STEPS -(_ENCODER_UD_STEPS)
            #define ENCODER_LR_PULSES -(ENCODER_PULSES_PER_STEP)
          #endif
          if (false) {
          }
          #if BUTTON_EXISTS(UP)
            else if (BUTTON_PRESSED(UP)) {
              encoderDiff = -(ENCODER_UD_STEPS);
              next_button_update_ms = now + 300;
            }
          #endif
          #if BUTTON_EXISTS(DWN)
            else if (BUTTON_PRESSED(DWN)) {
              encoderDiff = ENCODER_UD_STEPS;
              next_button_update_ms = now + 300;
            }
          #endif
          #if BUTTON_EXISTS(LFT)
            else if (BUTTON_PRESSED(LFT)) {
              encoderDiff = -(ENCODER_LR_PULSES);
              next_button_update_ms = now + 300;
            }
          #endif
          #if BUTTON_EXISTS(RT)
            else if (BUTTON_PRESSED(RT)) {
              encoderDiff = ENCODER_LR_PULSES;
              next_button_update_ms = now + 300;
            }
          #endif
        #endif 
        buttons = newbutton;
        #if ENABLED(LCD_HAS_SLOW_BUTTONS)
          buttons |= slow_buttons;
        #endif
        #if ENABLED(ADC_KEYPAD)
          uint8_t newbutton_reprapworld_keypad = 0;
          buttons = 0;
          if (buttons_reprapworld_keypad == 0) {
            newbutton_reprapworld_keypad = get_ADC_keyValue();
            if (WITHIN(newbutton_reprapworld_keypad, 1, 8))
              buttons_reprapworld_keypad = _BV(newbutton_reprapworld_keypad - 1);
          }
        #elif ENABLED(REPRAPWORLD_KEYPAD)
          GET_BUTTON_STATES(buttons_reprapworld_keypad);
        #endif
      #else
        GET_BUTTON_STATES(buttons);
      #endif 
    } 
    #if ENABLED(REVERSE_MENU_DIRECTION) && ENABLED(REVERSE_ENCODER_DIRECTION)
      #define ENCODER_DIFF_CW  (encoderDiff -= encoderDirection)
      #define ENCODER_DIFF_CCW (encoderDiff += encoderDirection)
    #elif ENABLED(REVERSE_MENU_DIRECTION)
      #define ENCODER_DIFF_CW  (encoderDiff += encoderDirection)
      #define ENCODER_DIFF_CCW (encoderDiff -= encoderDirection)
    #elif ENABLED(REVERSE_ENCODER_DIRECTION)
      #define ENCODER_DIFF_CW  (encoderDiff--)
      #define ENCODER_DIFF_CCW (encoderDiff++)
    #else
      #define ENCODER_DIFF_CW  (encoderDiff++)
      #define ENCODER_DIFF_CCW (encoderDiff--)
    #endif
    #define ENCODER_SPIN(_E1, _E2) switch (lastEncoderBits) { case _E1: ENCODER_DIFF_CW; break; case _E2: ENCODER_DIFF_CCW; }
    uint8_t enc = 0;
    if (buttons & EN_A) enc |= B01;
    if (buttons & EN_B) enc |= B10;
    if (enc != lastEncoderBits) {
      switch (enc) {
        case encrot0: ENCODER_SPIN(encrot3, encrot1); break;
        case encrot1: ENCODER_SPIN(encrot0, encrot2); break;
        case encrot2: ENCODER_SPIN(encrot1, encrot3); break;
        case encrot3: ENCODER_SPIN(encrot2, encrot0); break;
      }
      #if ENABLED(AUTO_BED_LEVELING_UBL)
        if (ubl.has_control_of_lcd_panel) {
          ubl.encoder_diff = encoderDiff;   
          encoderDiff = 0;                  
        }
      #endif
      lastEncoderBits = enc;
    }
  }
  #if (ENABLED(LCD_I2C_TYPE_MCP23017) || ENABLED(LCD_I2C_TYPE_MCP23008)) && ENABLED(DETECT_DEVICE)
    bool lcd_detected() { return lcd.LcdDetected() == 1; }
  #else
    bool lcd_detected() { return true; }
  #endif
  #if ENABLED(AUTO_BED_LEVELING_UBL)
    void chirp_at_user() {
      #if ENABLED(LCD_USE_I2C_BUZZER)
        lcd.buzz(LCD_FEEDBACK_FREQUENCY_DURATION_MS, LCD_FEEDBACK_FREQUENCY_HZ);
      #elif PIN_EXISTS(BEEPER)
        buzzer.tone(LCD_FEEDBACK_FREQUENCY_DURATION_MS, LCD_FEEDBACK_FREQUENCY_HZ);
      #endif
    }
    bool ubl_lcd_clicked() { return LCD_CLICKED; }
  #endif
#endif 
#if ENABLED(ADC_KEYPAD)
  typedef struct {
    uint16_t ADCKeyValueMin, ADCKeyValueMax;
    uint8_t  ADCKeyNo;
  } _stADCKeypadTable_;
  static const _stADCKeypadTable_ stADCKeyTable[] PROGMEM = {
    { 4000, 4096, BLEN_REPRAPWORLD_KEYPAD_F1 + 1 },     
    { 4000, 4096, BLEN_REPRAPWORLD_KEYPAD_F2 + 1 },     
    { 4000, 4096, BLEN_REPRAPWORLD_KEYPAD_F3 + 1 },     
    {  300,  500, BLEN_REPRAPWORLD_KEYPAD_LEFT + 1 },   
    { 1900, 2200, BLEN_REPRAPWORLD_KEYPAD_RIGHT + 1 },  
    {  570,  870, BLEN_REPRAPWORLD_KEYPAD_UP + 1 },     
    { 2670, 2870, BLEN_REPRAPWORLD_KEYPAD_DOWN + 1 },   
    { 1150, 1450, BLEN_REPRAPWORLD_KEYPAD_MIDDLE + 1 }, 
  };
  uint8_t get_ADC_keyValue(void) {
    if (thermalManager.ADCKey_count >= 16) {
      const uint16_t currentkpADCValue = thermalManager.current_ADCKey_raw >> 2;
      #if ENABLED(ADC_KEYPAD_DEBUG)
        SERIAL_PROTOCOLLN(currentkpADCValue);
      #endif
      thermalManager.current_ADCKey_raw = 0;
      thermalManager.ADCKey_count = 0;
      if (currentkpADCValue < 4000)
        for (uint8_t i = 0; i < ADC_KEY_NUM; i++) {
          const uint16_t lo = pgm_read_word(&stADCKeyTable[i].ADCKeyValueMin),
                         hi = pgm_read_word(&stADCKeyTable[i].ADCKeyValueMax);
          if (WITHIN(currentkpADCValue, lo, hi)) return pgm_read_byte(&stADCKeyTable[i].ADCKeyNo);
        }
    }
    return 0;
  }
#endif
#endif 
