#if __cplusplus < 201103L
  #error "Marlin requires C++11 support (gcc >= 4.7, Arduino IDE >= 1.6.8). Please upgrade your toolchain."
#endif
#if ! defined(CONFIGURATION_H_VERSION) || CONFIGURATION_H_VERSION < REQUIRED_CONFIGURATION_H_VERSION
  #error "You are using an old Configuration.h file, update it before building Marlin."
#endif
#if ! defined(CONFIGURATION_ADV_H_VERSION) || CONFIGURATION_ADV_H_VERSION < REQUIRED_CONFIGURATION_ADV_H_VERSION
  #error "You are using an old Configuration_adv.h file, update it before building Marlin."
#endif
#if WATCH_TEMP_PERIOD > 500
  #error "WATCH_TEMP_PERIOD now uses seconds instead of milliseconds."
#elif DISABLED(THERMAL_PROTECTION_HOTENDS) && (defined(WATCH_TEMP_PERIOD) || defined(THERMAL_PROTECTION_PERIOD))
  #error "Thermal Runaway Protection for hotends is now enabled with THERMAL_PROTECTION_HOTENDS."
#elif DISABLED(THERMAL_PROTECTION_BED) && defined(THERMAL_PROTECTION_BED_PERIOD)
  #error "Thermal Runaway Protection for the bed is now enabled with THERMAL_PROTECTION_BED."
#elif (CORE_IS_XZ || CORE_IS_YZ) && ENABLED(Z_LATE_ENABLE)
  #error "Z_LATE_ENABLE can't be used with COREXZ, COREZX, COREYZ, or COREZY."
#elif defined(X_HOME_RETRACT_MM)
  #error "[XYZ]_HOME_RETRACT_MM settings have been renamed [XYZ]_HOME_BUMP_MM."
#elif defined(SDCARDDETECTINVERTED)
  #error "SDCARDDETECTINVERTED is now SD_DETECT_INVERTED. Please update your configuration."
#elif defined(BTENABLED)
  #error "BTENABLED is now BLUETOOTH. Please update your configuration."
#elif defined(CUSTOM_MENDEL_NAME)
  #error "CUSTOM_MENDEL_NAME is now CUSTOM_MACHINE_NAME. Please update your configuration."
#elif defined(HAS_AUTOMATIC_VERSIONING)
  #error "HAS_AUTOMATIC_VERSIONING is now USE_AUTOMATIC_VERSIONING. Please update your configuration."
#elif defined(SDSLOW)
  #error "SDSLOW deprecated. Set SPI_SPEED to SPI_HALF_SPEED instead."
#elif defined(SDEXTRASLOW)
  #error "SDEXTRASLOW deprecated. Set SPI_SPEED to SPI_QUARTER_SPEED instead."
#elif defined(FILAMENT_SENSOR)
  #error "FILAMENT_SENSOR is deprecated. Use FILAMENT_WIDTH_SENSOR instead."
#elif defined(DISABLE_MAX_ENDSTOPS) || defined(DISABLE_MIN_ENDSTOPS)
  #error "DISABLE_MAX_ENDSTOPS and DISABLE_MIN_ENDSTOPS deprecated. Use individual USE_*_PLUG options instead."
#elif ENABLED(Z_DUAL_ENDSTOPS) && !defined(Z2_USE_ENDSTOP)
  #error "Z_DUAL_ENDSTOPS settings are simplified. Just set Z2_USE_ENDSTOP to the endstop you want to repurpose for Z2."
#elif defined(LANGUAGE_INCLUDE)
  #error "LANGUAGE_INCLUDE has been replaced by LCD_LANGUAGE. Please update your configuration."
#elif defined(EXTRUDER_OFFSET_X) || defined(EXTRUDER_OFFSET_Y)
  #error "EXTRUDER_OFFSET_[XY] is deprecated. Use HOTEND_OFFSET_[XY] instead."
#elif defined(PID_PARAMS_PER_EXTRUDER)
  #error "PID_PARAMS_PER_EXTRUDER is deprecated. Use PID_PARAMS_PER_HOTEND instead."
#elif defined(EXTRUDER_WATTS) || defined(BED_WATTS)
  #error "EXTRUDER_WATTS and BED_WATTS are deprecated. Remove them from your configuration."
#elif defined(SERVO_ENDSTOP_ANGLES)
  #error "SERVO_ENDSTOP_ANGLES is deprecated. Use Z_SERVO_ANGLES instead."
#elif defined(X_ENDSTOP_SERVO_NR) || defined(Y_ENDSTOP_SERVO_NR)
  #error "X_ENDSTOP_SERVO_NR and Y_ENDSTOP_SERVO_NR are deprecated and should be removed."
#elif defined(DEFAULT_XYJERK)
  #error "DEFAULT_XYJERK is deprecated. Use DEFAULT_XJERK and DEFAULT_YJERK instead."
#elif defined(XY_TRAVEL_SPEED)
  #error "XY_TRAVEL_SPEED is deprecated. Use XY_PROBE_SPEED instead."
#elif defined(PROBE_SERVO_DEACTIVATION_DELAY)
  #error "PROBE_SERVO_DEACTIVATION_DELAY is deprecated. Use DEACTIVATE_SERVOS_AFTER_MOVE instead."
#elif defined(SERVO_DEACTIVATION_DELAY)
  #error "SERVO_DEACTIVATION_DELAY is deprecated. Use SERVO_DELAY instead."
#elif ENABLED(FILAMENTCHANGEENABLE)
  #error "FILAMENTCHANGEENABLE is now ADVANCED_PAUSE_FEATURE. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_FEATURE)
  #error "FILAMENT_CHANGE_FEATURE is now ADVANCED_PAUSE_FEATURE. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_X_POS)
  #error "FILAMENT_CHANGE_X_POS is now PAUSE_PARK_X_POS. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_Y_POS)
  #error "FILAMENT_CHANGE_Y_POS is now PAUSE_PARK_Y_POS. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_Z_ADD)
  #error "FILAMENT_CHANGE_Z_ADD is now PAUSE_PARK_Z_ADD. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_XY_FEEDRATE)
  #error "FILAMENT_CHANGE_XY_FEEDRATE is now PAUSE_PARK_XY_FEEDRATE. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_Z_FEEDRATE)
  #error "FILAMENT_CHANGE_Z_FEEDRATE is now PAUSE_PARK_Z_FEEDRATE. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_RETRACT_FEEDRATE)
  #error "FILAMENT_CHANGE_RETRACT_FEEDRATE is now PAUSE_PARK_RETRACT_FEEDRATE. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_RETRACT_LENGTH)
  #error "FILAMENT_CHANGE_RETRACT_LENGTH is now PAUSE_PARK_RETRACT_LENGTH. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_EXTRUDE_FEEDRATE)
  #error "FILAMENT_CHANGE_EXTRUDE_FEEDRATE is now ADVANCED_PAUSE_EXTRUDE_FEEDRATE. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_EXTRUDE_LENGTH)
  #error "FILAMENT_CHANGE_EXTRUDE_LENGTH is now ADVANCED_PAUSE_EXTRUDE_LENGTH. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_NOZZLE_TIMEOUT)
  #error "FILAMENT_CHANGE_NOZZLE_TIMEOUT is now PAUSE_PARK_NOZZLE_TIMEOUT. Please update your configuration."
#elif ENABLED(FILAMENT_CHANGE_NO_STEPPER_TIMEOUT)
  #error "FILAMENT_CHANGE_NO_STEPPER_TIMEOUT is now PAUSE_PARK_NO_STEPPER_TIMEOUT. Please update your configuration."
#elif defined(PLA_PREHEAT_HOTEND_TEMP)
  #error "PLA_PREHEAT_HOTEND_TEMP is now PREHEAT_1_TEMP_HOTEND. Please update your configuration."
#elif defined(PLA_PREHEAT_HPB_TEMP)
  #error "PLA_PREHEAT_HPB_TEMP is now PREHEAT_1_TEMP_BED. Please update your configuration."
#elif defined(PLA_PREHEAT_FAN_SPEED)
  #error "PLA_PREHEAT_FAN_SPEED is now PREHEAT_1_FAN_SPEED. Please update your configuration."
#elif defined(ABS_PREHEAT_HOTEND_TEMP)
  #error "ABS_PREHEAT_HOTEND_TEMP is now PREHEAT_2_TEMP_HOTEND. Please update your configuration."
#elif defined(ABS_PREHEAT_HPB_TEMP)
  #error "ABS_PREHEAT_HPB_TEMP is now PREHEAT_2_TEMP_BED. Please update your configuration."
#elif defined(ABS_PREHEAT_FAN_SPEED)
  #error "ABS_PREHEAT_FAN_SPEED is now PREHEAT_2_FAN_SPEED. Please update your configuration."
#elif defined(ENDSTOPS_ONLY_FOR_HOMING)
  #error "ENDSTOPS_ONLY_FOR_HOMING is deprecated. Use (disable) ENDSTOPS_ALWAYS_ON_DEFAULT instead."
#elif defined(HOMING_FEEDRATE)
  #error "HOMING_FEEDRATE is deprecated. Set individual rates with HOMING_FEEDRATE_(XY|Z|E) instead."
#elif defined(MANUAL_HOME_POSITIONS)
  #error "MANUAL_HOME_POSITIONS is deprecated. Set MANUAL_[XYZ]_HOME_POS as-needed instead."
#elif defined(PID_ADD_EXTRUSION_RATE)
  #error "PID_ADD_EXTRUSION_RATE is now PID_EXTRUSION_SCALING and is DISABLED by default. Are you sure you want to use this option? Please update your configuration."
#elif defined(Z_RAISE_BEFORE_HOMING)
  #error "Z_RAISE_BEFORE_HOMING is now Z_HOMING_HEIGHT. Please update your configuration."
#elif defined(MIN_Z_HEIGHT_FOR_HOMING)
  #error "MIN_Z_HEIGHT_FOR_HOMING is now Z_HOMING_HEIGHT. Please update your configuration."
#elif defined(Z_RAISE_BEFORE_PROBING) || defined(Z_RAISE_AFTER_PROBING)
  #error "Z_RAISE_(BEFORE|AFTER)_PROBING are deprecated. Use Z_CLEARANCE_DEPLOY_PROBE instead."
#elif defined(Z_RAISE_PROBE_DEPLOY_STOW) || defined(Z_RAISE_BETWEEN_PROBINGS)
  #error "Z_RAISE_PROBE_DEPLOY_STOW and Z_RAISE_BETWEEN_PROBINGS are now Z_CLEARANCE_DEPLOY_PROBE and Z_CLEARANCE_BETWEEN_PROBES. Please update your configuration."
#elif defined(Z_PROBE_DEPLOY_HEIGHT) || defined(Z_PROBE_TRAVEL_HEIGHT)
  #error "Z_PROBE_DEPLOY_HEIGHT and Z_PROBE_TRAVEL_HEIGHT are now Z_CLEARANCE_DEPLOY_PROBE and Z_CLEARANCE_BETWEEN_PROBES. Please update your configuration."
#elif defined(MANUAL_BED_LEVELING)
  #error "MANUAL_BED_LEVELING is now LCD_BED_LEVELING. Please update your configuration."
#elif defined(MESH_HOME_SEARCH_Z)
  #error "MESH_HOME_SEARCH_Z is now LCD_PROBE_Z_RANGE. Please update your configuration."
#elif defined(MANUAL_PROBE_Z_RANGE)
  #error "MANUAL_PROBE_Z_RANGE is now LCD_PROBE_Z_RANGE. Please update your configuration."
#elif !defined(MIN_STEPS_PER_SEGMENT)
  #error Please replace "const int dropsegments" with "#define MIN_STEPS_PER_SEGMENT" (and increase by 1) in Configuration_adv.h.
#elif defined(PREVENT_DANGEROUS_EXTRUDE)
  #error "PREVENT_DANGEROUS_EXTRUDE is now PREVENT_COLD_EXTRUSION. Please update your configuration."
#elif defined(SCARA)
  #error "SCARA is now MORGAN_SCARA. Please update your configuration."
#elif defined(ENABLE_AUTO_BED_LEVELING)
  #error "ENABLE_AUTO_BED_LEVELING is deprecated. Specify AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_BILINEAR, or AUTO_BED_LEVELING_3POINT."
#elif defined(AUTO_BED_LEVELING_FEATURE)
  #error "AUTO_BED_LEVELING_FEATURE is deprecated. Specify AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_BILINEAR, or AUTO_BED_LEVELING_3POINT."
#elif defined(ABL_GRID_POINTS)
  #error "ABL_GRID_POINTS is now GRID_MAX_POINTS_X and GRID_MAX_POINTS_Y. Please update your configuration."
#elif defined(ABL_GRID_POINTS_X) || defined(ABL_GRID_POINTS_Y)
  #error "ABL_GRID_POINTS_[XY] is now GRID_MAX_POINTS_[XY]. Please update your configuration."
#elif defined(ABL_GRID_MAX_POINTS_X) || defined(ABL_GRID_MAX_POINTS_Y)
  #error "ABL_GRID_MAX_POINTS_[XY] is now GRID_MAX_POINTS_[XY]. Please update your configuration."
#elif defined(MESH_NUM_X_POINTS) || defined(MESH_NUM_Y_POINTS)
  #error "MESH_NUM_[XY]_POINTS is now GRID_MAX_POINTS_[XY]. Please update your configuration."
#elif defined(UBL_MESH_NUM_X_POINTS) || defined(UBL_MESH_NUM_Y_POINTS)
  #error "UBL_MESH_NUM_[XY]_POINTS is now GRID_MAX_POINTS_[XY]. Please update your configuration."
#elif defined(UBL_MESH_EDIT_ENABLED)
  #error "UBL_MESH_EDIT_ENABLED is now UBL_G26_MESH_VALIDATION. Please update your configuration."
#elif defined(UBL_MESH_EDITING)
  #error "UBL_MESH_EDITING is now UBL_G26_MESH_VALIDATION. Please update your configuration."
#elif defined(BLTOUCH_HEATERS_OFF)
  #error "BLTOUCH_HEATERS_OFF is now PROBING_HEATERS_OFF. Please update your configuration."
#elif defined(BEEPER)
  #error "BEEPER is now BEEPER_PIN. Please update your pins definitions."
#elif defined(SDCARDDETECT)
  #error "SDCARDDETECT is now SD_DETECT_PIN. Please update your pins definitions."
#elif defined(STAT_LED_RED) || defined(STAT_LED_BLUE)
  #error "STAT_LED_RED/STAT_LED_BLUE are now STAT_LED_RED_PIN/STAT_LED_BLUE_PIN. Please update your pins definitions."
#elif defined(LCD_PIN_BL)
  #error "LCD_PIN_BL is now LCD_BACKLIGHT_PIN. Please update your pins definitions."
#elif defined(LCD_PIN_RESET)
  #error "LCD_PIN_RESET is now LCD_RESET_PIN. Please update your pins definitions."
#elif defined(EXTRUDER_0_AUTO_FAN_PIN) || defined(EXTRUDER_1_AUTO_FAN_PIN) || defined(EXTRUDER_2_AUTO_FAN_PIN) || defined(EXTRUDER_3_AUTO_FAN_PIN)
  #error "EXTRUDER_[0123]_AUTO_FAN_PIN is now E[0123]_AUTO_FAN_PIN. Please update your Configuration_adv.h."
#elif defined(min_software_endstops) || defined(max_software_endstops)
  #error "(min|max)_software_endstops are now (MIN|MAX)_SOFTWARE_ENDSTOPS. Please update your configuration."
#elif ENABLED(Z_PROBE_SLED) && defined(SLED_PIN)
  #error "Replace SLED_PIN with SOL1_PIN (applies to both Z_PROBE_SLED and SOLENOID_PROBE)."
#elif defined(CONTROLLERFAN_PIN)
  #error "CONTROLLERFAN_PIN is now CONTROLLER_FAN_PIN, enabled with USE_CONTROLLER_FAN. Please update your Configuration_adv.h."
#endif
#ifndef SHORT_BUILD_VERSION
  #error "SHORT_BUILD_VERSION must be specified."
#elif !defined(DETAILED_BUILD_VERSION)
  #error "BUILD_VERSION must be specified."
#elif !defined(STRING_DISTRIBUTION_DATE)
  #error "STRING_DISTRIBUTION_DATE must be specified."
#elif !defined(PROTOCOL_VERSION)
  #error "PROTOCOL_VERSION must be specified."
#elif !defined(MACHINE_NAME)
  #error "MACHINE_NAME must be specified."
#elif !defined(SOURCE_CODE_URL)
  #error "SOURCE_CODE_URL must be specified."
#elif !defined(DEFAULT_MACHINE_UUID)
  #error "DEFAULT_MACHINE_UUID must be specified."
#elif !defined(WEBSITE_URL)
  #error "WEBSITE_URL must be specified."
#endif
#if ENABLED(X_DUAL_STEPPER_DRIVERS) && ENABLED(DUAL_X_CARRIAGE)
  #error "DUAL_X_CARRIAGE is not compatible with X_DUAL_STEPPER_DRIVERS."
#elif ENABLED(X_DUAL_STEPPER_DRIVERS) && (!HAS_X2_ENABLE || !HAS_X2_STEP || !HAS_X2_DIR)
  #error "X_DUAL_STEPPER_DRIVERS requires X2 pins (and an extra E plug)."
#elif ENABLED(Y_DUAL_STEPPER_DRIVERS) && (!HAS_Y2_ENABLE || !HAS_Y2_STEP || !HAS_Y2_DIR)
  #error "Y_DUAL_STEPPER_DRIVERS requires Y2 pins (and an extra E plug)."
#elif ENABLED(Z_DUAL_STEPPER_DRIVERS) && (!HAS_Z2_ENABLE || !HAS_Z2_STEP || !HAS_Z2_DIR)
  #error "Z_DUAL_STEPPER_DRIVERS requires Z2 pins (and an extra E plug)."
#endif
#if ENABLED(LCD_PROGRESS_BAR)
  #if DISABLED(SDSUPPORT)
    #error "LCD_PROGRESS_BAR requires SDSUPPORT."
  #elif ENABLED(DOGLCD)
    #error "LCD_PROGRESS_BAR does not apply to graphical displays."
  #elif ENABLED(FILAMENT_LCD_DISPLAY)
    #error "LCD_PROGRESS_BAR and FILAMENT_LCD_DISPLAY are not fully compatible. Comment out this line to use both."
  #endif
#endif
#if ENABLED(SDCARD_SORT_ALPHA)
  #if SDSORT_LIMIT > 256
    #error "SDSORT_LIMIT must be 256 or smaller."
  #elif SDSORT_LIMIT < 10
    #error "SDSORT_LIMIT should be greater than 9 to be useful."
  #elif DISABLED(SDSORT_USES_RAM)
    #if ENABLED(SDSORT_DYNAMIC_RAM)
      #error "SDSORT_DYNAMIC_RAM requires SDSORT_USES_RAM (which reads the directory into RAM)."
    #elif ENABLED(SDSORT_CACHE_NAMES)
      #error "SDSORT_CACHE_NAMES requires SDSORT_USES_RAM (which reads the directory into RAM)."
    #endif
  #endif
#endif
#if ENABLED(I2C_POSITION_ENCODERS)
  #if DISABLED(BABYSTEPPING)
    #error "I2C_POSITION_ENCODERS requires BABYSTEPPING."
  #elif !WITHIN(I2CPE_ENCODER_CNT, 1, 5)
    #error "I2CPE_ENCODER_CNT must be between 1 and 5."
  #endif
#endif
#if ENABLED(BABYSTEPPING)
#endif
#if ENABLED(FILAMENT_RUNOUT_SENSOR)
  #if !HAS_FIL_RUNOUT
    #error "FILAMENT_RUNOUT_SENSOR requires FIL_RUNOUT_PIN."
  #elif DISABLED(SDSUPPORT) && DISABLED(PRINTJOB_TIMER_AUTOSTART)
    #error "FILAMENT_RUNOUT_SENSOR requires SDSUPPORT or PRINTJOB_TIMER_AUTOSTART."
  #elif DISABLED(ADVANCED_PAUSE_FEATURE)
    static_assert(NULL == strstr(FILAMENT_RUNOUT_SCRIPT, "M600"), "ADVANCED_PAUSE_FEATURE is required to use M600 with FILAMENT_RUNOUT_SENSOR.");
  #endif
#endif
#if ENABLED(ADVANCED_PAUSE_FEATURE)
#if DISABLED(NEWPANEL)&&DISABLED(ENABLE_ULTILCD2)&&DISABLED(FYSTLCD_V1) 
    #error "ADVANCED_PAUSE_FEATURE currently requires an LCD controller."
  #elif ENABLED(EXTRUDER_RUNOUT_PREVENT)
    #error "EXTRUDER_RUNOUT_PREVENT is incompatible with ADVANCED_PAUSE_FEATURE."
  #elif ENABLED(PARK_HEAD_ON_PAUSE) && DISABLED(SDSUPPORT) && DISABLED(NEWPANEL) && DISABLED(EMERGENCY_PARSER)
    #error "PARK_HEAD_ON_PAUSE requires SDSUPPORT, EMERGENCY_PARSER, or an LCD controller."
  #elif ENABLED(HOME_BEFORE_FILAMENT_CHANGE) && DISABLED(PAUSE_PARK_NO_STEPPER_TIMEOUT)
    #error "HOME_BEFORE_FILAMENT_CHANGE requires PAUSE_PARK_NO_STEPPER_TIMEOUT"
  #endif
#endif
#if ENABLED(INDIVIDUAL_AXIS_HOMING_MENU) && ENABLED(DELTA)
  #error "INDIVIDUAL_AXIS_HOMING_MENU is incompatible with DELTA kinematics."
#endif
#if EXTRUDERS > 1
  #if EXTRUDERS > 5
    #error "Marlin supports a maximum of 5 EXTRUDERS."
  #endif
  #if ENABLED(TEMP_SENSOR_1_AS_REDUNDANT)
    #error "EXTRUDERS must be 1 with TEMP_SENSOR_1_AS_REDUNDANT."
  #endif
  #if ENABLED(HEATERS_PARALLEL)
    #error "EXTRUDERS must be 1 with HEATERS_PARALLEL."
  #endif
#elif ENABLED(MK2_MULTIPLEXER)
  #error "MK2_MULTIPLEXER requires 2 or more EXTRUDERS."
#elif ENABLED(SINGLENOZZLE)
  #error "SINGLENOZZLE requires 2 or more EXTRUDERS."
#endif
#ifdef SNMM
  #error "SNMM is now MK2_MULTIPLEXER. Please update your configuration."
#elif ENABLED(MK2_MULTIPLEXER) && DISABLED(ADVANCED_PAUSE_FEATURE)
  #error "ADVANCED_PAUSE_FEATURE is required with MK2_MULTIPLEXER."
#endif
#if ENABLED(SWITCHING_NOZZLE)
  #if ENABLED(DUAL_X_CARRIAGE)
    #error "SWITCHING_NOZZLE and DUAL_X_CARRIAGE are incompatible."
  #elif ENABLED(SINGLENOZZLE)
    #error "SWITCHING_NOZZLE and SINGLENOZZLE are incompatible."
  #elif EXTRUDERS != 2
    #error "SWITCHING_NOZZLE requires exactly 2 EXTRUDERS."
  #elif NUM_SERVOS < 1
    #error "SWITCHING_NOZZLE requires NUM_SERVOS >= 1."
  #endif
#endif
#if ENABLED(SWITCHING_EXTRUDER) && NUM_SERVOS < 1
  #error "SWITCHING_EXTRUDER requires NUM_SERVOS >= 1."
#endif
#if ENABLED(MIXING_EXTRUDER)
  #if EXTRUDERS > 1
    #error "MIXING_EXTRUDER currently only supports one extruder."
  #elif MIXING_STEPPERS < 2
    #error "You must set MIXING_STEPPERS >= 2 for a mixing extruder."
  #elif ENABLED(FILAMENT_SENSOR)
    #error "MIXING_EXTRUDER is incompatible with FILAMENT_SENSOR. Comment out this line to use it anyway."
  #elif ENABLED(SWITCHING_EXTRUDER)
    #error "Please select either MIXING_EXTRUDER or SWITCHING_EXTRUDER, not both."
  #elif ENABLED(SINGLENOZZLE)
    #error "MIXING_EXTRUDER is incompatible with SINGLENOZZLE."
  #elif ENABLED(LIN_ADVANCE)
    #error "MIXING_EXTRUDER is incompatible with LIN_ADVANCE."
  #endif
#endif
#if NUM_SERVOS > 4
  #error "The maximum number of SERVOS in Marlin is 4."
#endif
#if ENABLED(DEACTIVATE_SERVOS_AFTER_MOVE) && !HAS_Z_SERVO_ENDSTOP && !defined(SWITCHING_NOZZLE_SERVO_NR)
  #error "Z_ENDSTOP_SERVO_NR or switching nozzle is required for DEACTIVATE_SERVOS_AFTER_MOVE."
#endif
#if DISABLED(DOGLCD) && ENABLED(ULTRA_LCD) && !defined(DISPLAY_CHARSET_HD44780)
  #error "You must set DISPLAY_CHARSET_HD44780 to JAPANESE, WESTERN or CYRILLIC for your LCD controller."
#endif
#if ENABLED(PIDTEMPBED) && ENABLED(BED_LIMIT_SWITCHING)
  #error "To use BED_LIMIT_SWITCHING you must disable PIDTEMPBED."
#endif
static_assert(1 >= 0
  #if ENABLED(DELTA)
    + 1
  #endif
  #if ENABLED(MORGAN_SCARA)
    + 1
  #endif
  #if ENABLED(MAKERARM_SCARA)
    + 1
  #endif
  #if ENABLED(COREXY)
    + 1
  #endif
  #if ENABLED(COREXZ)
    + 1
  #endif
  #if ENABLED(COREYZ)
    + 1
  #endif
  #if ENABLED(COREYX)
    + 1
  #endif
  #if ENABLED(COREZX)
    + 1
  #endif
  #if ENABLED(COREZY)
    + 1
  #endif
  , "Please enable only one of DELTA, MORGAN_SCARA, MAKERARM_SCARA, COREXY, COREYX, COREXZ, COREZX, COREYZ, or COREZY."
);
#if ENABLED(DELTA)
  #if DISABLED(USE_XMAX_PLUG) && DISABLED(USE_YMAX_PLUG) && DISABLED(USE_ZMAX_PLUG)
    #error "You probably want to use Max Endstops for DELTA!"
  #elif ENABLED(ENABLE_LEVELING_FADE_HEIGHT) && DISABLED(AUTO_BED_LEVELING_BILINEAR) && !UBL_DELTA
    #error "ENABLE_LEVELING_FADE_HEIGHT on DELTA requires AUTO_BED_LEVELING_BILINEAR or AUTO_BED_LEVELING_UBL."
  #elif ENABLED(DELTA_AUTO_CALIBRATION) && !PROBE_SELECTED
    #error "DELTA_AUTO_CALIBRATION requires a probe: PROBE_MANUALLY, FIX_MOUNTED_PROBE, BLTOUCH, SOLENOID_PROBE, Z_PROBE_ALLEN_KEY, Z_PROBE_SLED, Z Servo."
  #elif ENABLED(DELTA_AUTO_CALIBRATION) && ENABLED(PROBE_MANUALLY) && DISABLED(ULTIPANEL)
    #error "DELTA_AUTO_CALIBRATION requires an LCD controller with PROBE_MANUALLY."
  #elif ABL_GRID
    #if (GRID_MAX_POINTS_X & 1) == 0 || (GRID_MAX_POINTS_Y & 1) == 0
      #error "DELTA requires GRID_MAX_POINTS_X and GRID_MAX_POINTS_Y to be odd numbers."
    #elif GRID_MAX_POINTS_X < 3
      #error "DELTA requires GRID_MAX_POINTS_X and GRID_MAX_POINTS_Y to be 3 or higher."
    #endif
  #endif
#endif
static_assert(1 >= 0
  #if ENABLED(PROBE_MANUALLY)
    + 1
  #endif
  #if ENABLED(FIX_MOUNTED_PROBE)
    + 1
  #endif
  #if HAS_Z_SERVO_ENDSTOP && DISABLED(BLTOUCH)
    + 1
  #endif
  #if ENABLED(BLTOUCH)
    + 1
  #endif
  #if ENABLED(SOLENOID_PROBE)
    + 1
  #endif
  #if ENABLED(Z_PROBE_ALLEN_KEY)
    + 1
  #endif
  #if ENABLED(Z_PROBE_SLED)
    + 1
  #endif
  , "Please enable only one probe option: PROBE_MANUALLY, FIX_MOUNTED_PROBE, BLTOUCH, SOLENOID_PROBE, Z_PROBE_ALLEN_KEY, Z_PROBE_SLED, or Z Servo."
);
#if PROBE_SELECTED
  #if ENABLED(Z_PROBE_SLED) && ENABLED(DELTA)
    #error "You cannot use Z_PROBE_SLED with DELTA."
  #endif
  #if ENABLED(SOLENOID_PROBE)
    #if ENABLED(EXT_SOLENOID)
      #error "SOLENOID_PROBE is incompatible with EXT_SOLENOID."
    #elif !HAS_SOLENOID_1
      #error "SOLENOID_PROBE requires SOL1_PIN. It can be added to your Configuration.h."
    #endif
  #endif
  #if HAS_Z_SERVO_ENDSTOP
    #ifndef NUM_SERVOS
      #error "You must set NUM_SERVOS for a Z servo probe (Z_ENDSTOP_SERVO_NR)."
    #elif Z_ENDSTOP_SERVO_NR >= NUM_SERVOS
      #error "Z_ENDSTOP_SERVO_NR must be smaller than NUM_SERVOS."
    #endif
  #endif
  #if ENABLED(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN)
    #if ENABLED(Z_MIN_PROBE_ENDSTOP)
      #error "Enable only one option: Z_MIN_PROBE_ENDSTOP or Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN."
    #elif DISABLED(USE_ZMIN_PLUG)
      #error "Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN requires USE_ZMIN_PLUG to be enabled."
    #elif !HAS_Z_MIN
      #error "Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN requires the Z_MIN_PIN to be defined."
    #elif ENABLED(Z_MIN_PROBE_ENDSTOP_INVERTING) != ENABLED(Z_MIN_ENDSTOP_INVERTING)
      #error "Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN requires Z_MIN_ENDSTOP_INVERTING to match Z_MIN_PROBE_ENDSTOP_INVERTING."
    #endif
  #elif ENABLED(Z_MIN_PROBE_ENDSTOP)
    #if !HAS_Z_MIN_PROBE_PIN
      #error "Z_MIN_PROBE_ENDSTOP requires the Z_MIN_PROBE_PIN to be defined."
    #endif
  #elif DISABLED(PROBE_MANUALLY)
    #error "You must enable either Z_MIN_PROBE_ENDSTOP or Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN to use a probe."
  #endif
  #if !defined(Z_CLEARANCE_DEPLOY_PROBE)
    #error "You must define Z_CLEARANCE_DEPLOY_PROBE in your configuration."
  #elif !defined(Z_CLEARANCE_BETWEEN_PROBES)
    #error "You must define Z_CLEARANCE_BETWEEN_PROBES in your configuration."
  #elif Z_CLEARANCE_DEPLOY_PROBE < 0
    #error "Probes need Z_CLEARANCE_DEPLOY_PROBE >= 0."
  #elif Z_CLEARANCE_BETWEEN_PROBES < 0
    #error "Probes need Z_CLEARANCE_BETWEEN_PROBES >= 0."
  #endif
#else
  #if HAS_ABL
    #if ENABLED(AUTO_BED_LEVELING_UBL)
      #error "Unified Bed Leveling requires a probe: FIX_MOUNTED_PROBE, BLTOUCH, SOLENOID_PROBE, Z_PROBE_ALLEN_KEY, Z_PROBE_SLED, or Z Servo."
    #else
      #error "Auto Bed Leveling requires one of these: PROBE_MANUALLY, FIX_MOUNTED_PROBE, BLTOUCH, SOLENOID_PROBE, Z_PROBE_ALLEN_KEY, Z_PROBE_SLED, or a Z Servo."
    #endif
  #endif
#endif
#if ENABLED(Z_MIN_PROBE_REPEATABILITY_TEST) && !HAS_BED_PROBE
  #error "Z_MIN_PROBE_REPEATABILITY_TEST requires a probe: FIX_MOUNTED_PROBE, BLTOUCH, SOLENOID_PROBE, Z_PROBE_ALLEN_KEY, Z_PROBE_SLED, or Z Servo."
#endif
static_assert(1 >= 0
  #if ENABLED(AUTO_BED_LEVELING_LINEAR)
    + 1
  #endif
  #if ENABLED(AUTO_BED_LEVELING_3POINT)
    + 1
  #endif
  #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
    + 1
  #endif
  #if ENABLED(AUTO_BED_LEVELING_UBL)
    + 1
  #endif
  #if ENABLED(MESH_BED_LEVELING)
    + 1
  #endif
  , "Select only one of: MESH_BED_LEVELING, AUTO_BED_LEVELING_LINEAR, AUTO_BED_LEVELING_3POINT, AUTO_BED_LEVELING_BILINEAR or AUTO_BED_LEVELING_UBL."
);
#if ENABLED(AUTO_BED_LEVELING_UBL)
  #if IS_SCARA
    #error "AUTO_BED_LEVELING_UBL does not yet support SCARA printers."
  #elif DISABLED(EEPROM_SETTINGS)
    #error "AUTO_BED_LEVELING_UBL requires EEPROM_SETTINGS. Please update your configuration."
  #elif !WITHIN(GRID_MAX_POINTS_X, 3, 15) || !WITHIN(GRID_MAX_POINTS_Y, 3, 15)
    #error "GRID_MAX_POINTS_[XY] must be a whole number between 3 and 15."
  #else
    static_assert(WITHIN(UBL_PROBE_PT_1_X, MIN_PROBE_X, MAX_PROBE_X), "UBL_PROBE_PT_1_X can't be reached by the Z probe.");
    static_assert(WITHIN(UBL_PROBE_PT_2_X, MIN_PROBE_X, MAX_PROBE_X), "UBL_PROBE_PT_2_X can't be reached by the Z probe.");
    static_assert(WITHIN(UBL_PROBE_PT_3_X, MIN_PROBE_X, MAX_PROBE_X), "UBL_PROBE_PT_3_X can't be reached by the Z probe.");
    static_assert(WITHIN(UBL_PROBE_PT_1_Y, MIN_PROBE_Y, MAX_PROBE_Y), "UBL_PROBE_PT_1_Y can't be reached by the Z probe.");
    static_assert(WITHIN(UBL_PROBE_PT_2_Y, MIN_PROBE_Y, MAX_PROBE_Y), "UBL_PROBE_PT_2_Y can't be reached by the Z probe.");
    static_assert(WITHIN(UBL_PROBE_PT_3_Y, MIN_PROBE_Y, MAX_PROBE_Y), "UBL_PROBE_PT_3_Y can't be reached by the Z probe.");
  #endif
#elif HAS_ABL
  #if ENABLED(USE_RAW_KINEMATICS)
    #error "USE_RAW_KINEMATICS is not compatible with AUTO_BED_LEVELING"
  #endif
  #if IS_SCARA && DISABLED(AUTO_BED_LEVELING_BILINEAR)
    #error "Only AUTO_BED_LEVELING_BILINEAR currently supports SCARA bed leveling."
  #endif
  #if ABL_GRID
    #ifdef DELTA_PROBEABLE_RADIUS
      static_assert(LEFT_PROBE_BED_POSITION >= -DELTA_PROBEABLE_RADIUS, "LEFT_PROBE_BED_POSITION must be within DELTA_PROBEABLE_RADIUS.");
      static_assert(RIGHT_PROBE_BED_POSITION <= DELTA_PROBEABLE_RADIUS, "RIGHT_PROBE_BED_POSITION must be within DELTA_PROBEABLE_RADIUS.");
      static_assert(FRONT_PROBE_BED_POSITION >= -DELTA_PROBEABLE_RADIUS, "FRONT_PROBE_BED_POSITION must be within DELTA_PROBEABLE_RADIUS.");
      static_assert(BACK_PROBE_BED_POSITION <= DELTA_PROBEABLE_RADIUS, "BACK_PROBE_BED_POSITION must be within DELTA_PROBEABLE_RADIUS.");
    #else
      static_assert(LEFT_PROBE_BED_POSITION < RIGHT_PROBE_BED_POSITION, "LEFT_PROBE_BED_POSITION must be less than RIGHT_PROBE_BED_POSITION.");
      static_assert(FRONT_PROBE_BED_POSITION < BACK_PROBE_BED_POSITION, "FRONT_PROBE_BED_POSITION must be less than BACK_PROBE_BED_POSITION.");
      static_assert(LEFT_PROBE_BED_POSITION >= MIN_PROBE_X, "LEFT_PROBE_BED_POSITION can't be reached by the Z probe.");
      static_assert(RIGHT_PROBE_BED_POSITION <= MAX_PROBE_X, "RIGHT_PROBE_BED_POSITION can't be reached by the Z probe.");
      static_assert(FRONT_PROBE_BED_POSITION >= MIN_PROBE_Y, "FRONT_PROBE_BED_POSITION can't be reached by the Z probe.");
      static_assert(BACK_PROBE_BED_POSITION <= MAX_PROBE_Y, "BACK_PROBE_BED_POSITION can't be reached by the Z probe.");
    #endif
  #else 
    static_assert(WITHIN(ABL_PROBE_PT_1_X, MIN_PROBE_X, MAX_PROBE_X), "ABL_PROBE_PT_1_X can't be reached by the Z probe.");
    static_assert(WITHIN(ABL_PROBE_PT_2_X, MIN_PROBE_X, MAX_PROBE_X), "ABL_PROBE_PT_2_X can't be reached by the Z probe.");
    static_assert(WITHIN(ABL_PROBE_PT_3_X, MIN_PROBE_X, MAX_PROBE_X), "ABL_PROBE_PT_3_X can't be reached by the Z probe.");
    static_assert(WITHIN(ABL_PROBE_PT_1_Y, MIN_PROBE_Y, MAX_PROBE_Y), "ABL_PROBE_PT_1_Y can't be reached by the Z probe.");
    static_assert(WITHIN(ABL_PROBE_PT_2_Y, MIN_PROBE_Y, MAX_PROBE_Y), "ABL_PROBE_PT_2_Y can't be reached by the Z probe.");
    static_assert(WITHIN(ABL_PROBE_PT_3_Y, MIN_PROBE_Y, MAX_PROBE_Y), "ABL_PROBE_PT_3_Y can't be reached by the Z probe.");
  #endif 
#elif ENABLED(MESH_BED_LEVELING)
  #if ENABLED(DELTA)
    #error "MESH_BED_LEVELING does not yet support DELTA printers."
  #elif GRID_MAX_POINTS_X > 9 || GRID_MAX_POINTS_Y > 9
    #error "GRID_MAX_POINTS_X and GRID_MAX_POINTS_Y must be less than 10 for MBL."
  #endif
#endif
#if ENABLED(LCD_BED_LEVELING)
  #if DISABLED(ULTIPANEL)
    #error "LCD_BED_LEVELING requires an LCD controller."
  #elif DISABLED(MESH_BED_LEVELING) && !(HAS_ABL && ENABLED(PROBE_MANUALLY))
    #error "LCD_BED_LEVELING requires MESH_BED_LEVELING or PROBE_MANUALLY."
  #endif
#endif
#if X_HOME_BUMP_MM < 0 || Y_HOME_BUMP_MM < 0 || Z_HOME_BUMP_MM < 0
  #error "[XYZ]_HOME_BUMP_MM must be greater than or equal to 0."
#endif
#if ENABLED(Z_SAFE_HOMING)
  #if !WITHIN(Z_SAFE_HOMING_X_POINT, MIN_PROBE_X, MAX_PROBE_X)
    #if HAS_BED_PROBE
      #error "Z_SAFE_HOMING_X_POINT can't be reached by the Z probe."
    #else
      #error "Z_SAFE_HOMING_X_POINT can't be reached by the nozzle."
    #endif
  #elif !WITHIN(Z_SAFE_HOMING_Y_POINT, MIN_PROBE_Y, MAX_PROBE_Y)
    #if HAS_BED_PROBE
      #error "Z_SAFE_HOMING_Y_POINT can't be reached by the Z probe."
    #else
      #error "Z_SAFE_HOMING_Y_POINT can't be reached by the nozzle."
    #endif
  #endif
#endif 
#if ENABLED(DISABLE_X) || ENABLED(DISABLE_Y) || ENABLED(DISABLE_Z)
  #if ENABLED(HOME_AFTER_DEACTIVATE) || ENABLED(Z_SAFE_HOMING)
    #error "DISABLE_[XYZ] not compatible with HOME_AFTER_DEACTIVATE or Z_SAFE_HOMING."
  #endif
#endif 
#if ENABLED(ADVANCE) && ENABLED(LIN_ADVANCE)
  #error "You can enable ADVANCE or LIN_ADVANCE, but not both."
#endif
#if ENABLED(FILAMENT_WIDTH_SENSOR) && !HAS_FILAMENT_WIDTH_SENSOR
  #error "FILAMENT_WIDTH_SENSOR requires a FILWIDTH_PIN to be defined."
#endif
#if ENABLED(ULTIPANEL) && DISABLED(NEWPANEL) && DISABLED(SR_LCD_2W_NL) && !defined(SHIFT_CLK)
  #error "ULTIPANEL requires some kind of encoder."
#endif
#if ENCODER_PULSES_PER_STEP < 0
  #error "ENCODER_PULSES_PER_STEP should not be negative, use REVERSE_MENU_DIRECTION instead."
#endif
#if ENABLED(U8GLIB_SSD1306) && ENABLED(U8GLIB_SH1106)
  #error "Only enable one SAV_3DGLCD display type: U8GLIB_SSD1306 or U8GLIB_SH1106."
#endif
#if ENABLED(Z_PROBE_ALLEN_KEY) && (Z_HOME_DIR < 0) && ENABLED(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN)
  #error "You can't home to a z min endstop with a Z_PROBE_ALLEN_KEY"
#endif
#if ENABLED(DUAL_X_CARRIAGE)
  #if EXTRUDERS == 1
    #error "DUAL_X_CARRIAGE requires 2 (or more) extruders."
  #elif CORE_IS_XY || CORE_IS_XZ
    #error "DUAL_X_CARRIAGE cannot be used with COREXY, COREYX, COREXZ, or COREZX."
  #elif !HAS_X2_ENABLE || !HAS_X2_STEP || !HAS_X2_DIR
    #error "DUAL_X_CARRIAGE requires X2 stepper pins to be defined."
  #elif !HAS_X_MAX
    #error "DUAL_X_CARRIAGE requires USE_XMAX_PLUG and an X Max Endstop."
  #elif !defined(X2_HOME_POS) || !defined(X2_MIN_POS) || !defined(X2_MAX_POS)
    #error "DUAL_X_CARRIAGE requires X2_HOME_POS, X2_MIN_POS, and X2_MAX_POS."
  #elif X_HOME_DIR != -1 || X2_HOME_DIR != 1
    #error "DUAL_X_CARRIAGE requires X_HOME_DIR -1 and X2_HOME_DIR 1."
  #endif
#endif 
#if HAS_AUTO_FAN
  #if HAS_FAN0
    #if E0_AUTO_FAN_PIN == FAN_PIN
      #error "You cannot set E0_AUTO_FAN_PIN equal to FAN_PIN."
    #elif E1_AUTO_FAN_PIN == FAN_PIN
      #error "You cannot set E1_AUTO_FAN_PIN equal to FAN_PIN."
    #elif E2_AUTO_FAN_PIN == FAN_PIN
      #error "You cannot set E2_AUTO_FAN_PIN equal to FAN_PIN."
    #elif E3_AUTO_FAN_PIN == FAN_PIN
      #error "You cannot set E3_AUTO_FAN_PIN equal to FAN_PIN."
    #endif
  #endif
#endif
#if HAS_FAN0 && CONTROLLER_FAN_PIN == FAN_PIN
  #error "You cannot set CONTROLLER_FAN_PIN equal to FAN_PIN."
#endif
#if ENABLED(USE_CONTROLLER_FAN)
  #if !HAS_CONTROLLER_FAN
    #error "USE_CONTROLLER_FAN requires a CONTROLLER_FAN_PIN. Define in Configuration_adv.h."
  #elif E0_AUTO_FAN_PIN == CONTROLLER_FAN_PIN
    #error "You cannot set E0_AUTO_FAN_PIN equal to CONTROLLER_FAN_PIN."
  #elif E1_AUTO_FAN_PIN == CONTROLLER_FAN_PIN
    #error "You cannot set E1_AUTO_FAN_PIN equal to CONTROLLER_FAN_PIN."
  #elif E2_AUTO_FAN_PIN == CONTROLLER_FAN_PIN
    #error "You cannot set E2_AUTO_FAN_PIN equal to CONTROLLER_FAN_PIN."
  #elif E3_AUTO_FAN_PIN == CONTROLLER_FAN_PIN
    #error "You cannot set E3_AUTO_FAN_PIN equal to CONTROLLER_FAN_PIN."
  #endif
#endif
#if !HAS_HEATER_0
  #error "HEATER_0_PIN not defined for this board."
#elif !PIN_EXISTS(TEMP_0) && !(defined(MAX6675_SS) && MAX6675_SS >= 0)
  #error "TEMP_0_PIN not defined for this board."
#elif !PIN_EXISTS(E0_STEP) || !PIN_EXISTS(E0_DIR) || !PIN_EXISTS(E0_ENABLE)
  #error "E0_STEP_PIN, E0_DIR_PIN, or E0_ENABLE_PIN not defined for this board."
#elif TEMP_SENSOR_0 == 0
  #error "TEMP_SENSOR_0 is required."
#endif
#if HOTENDS > 1 || ENABLED(HEATERS_PARALLEL)
  #if !HAS_HEATER_1
    #error "HEATER_1_PIN not defined for this board."
  #endif
#endif
#if HOTENDS > 1
  #if TEMP_SENSOR_1 == 0
    #error "TEMP_SENSOR_1 is required with 2 or more HOTENDS."
  #elif !PIN_EXISTS(TEMP_1)
    #error "TEMP_1_PIN not defined for this board."
  #endif
  #if HOTENDS > 2
    #if TEMP_SENSOR_2 == 0
      #error "TEMP_SENSOR_2 is required with 3 or more HOTENDS."
    #elif !HAS_HEATER_2
      #error "HEATER_2_PIN not defined for this board."
    #elif !PIN_EXISTS(TEMP_2)
      #error "TEMP_2_PIN not defined for this board."
    #endif
    #if HOTENDS > 3
      #if TEMP_SENSOR_3 == 0
        #error "TEMP_SENSOR_3 is required with 4 or more HOTENDS."
      #elif !HAS_HEATER_3
        #error "HEATER_3_PIN not defined for this board."
      #elif !PIN_EXISTS(TEMP_3)
        #error "TEMP_3_PIN not defined for this board."
      #endif
      #if HOTENDS > 4
        #if TEMP_SENSOR_4 == 0
          #error "TEMP_SENSOR_4 is required with 5 HOTENDS."
        #elif !HAS_HEATER_4
          #error "HEATER_4_PIN not defined for this board."
        #elif !PIN_EXISTS(TEMP_4)
          #error "TEMP_4_PIN not defined for this board."
        #endif
      #elif TEMP_SENSOR_4 != 0
        #error "TEMP_SENSOR_4 shouldn't be set with only 4 extruders."
      #endif
    #elif TEMP_SENSOR_3 != 0
      #error "TEMP_SENSOR_3 shouldn't be set with only 3 extruders."
    #elif TEMP_SENSOR_4 != 0
      #error "TEMP_SENSOR_4 shouldn't be set with only 3 extruders."
    #endif
  #elif TEMP_SENSOR_2 != 0
    #error "TEMP_SENSOR_2 shouldn't be set with only 2 extruders."
  #elif TEMP_SENSOR_3 != 0
    #error "TEMP_SENSOR_3 shouldn't be set with only 2 extruders."
  #elif TEMP_SENSOR_4 != 0
    #error "TEMP_SENSOR_4 shouldn't be set with only 2 extruders."
  #endif
#elif TEMP_SENSOR_1 != 0 && DISABLED(TEMP_SENSOR_1_AS_REDUNDANT)
  #error "TEMP_SENSOR_1 shouldn't be set with only 1 extruder."
#elif TEMP_SENSOR_2 != 0
  #error "TEMP_SENSOR_2 shouldn't be set with only 1 extruder."
#elif TEMP_SENSOR_3 != 0
  #error "TEMP_SENSOR_3 shouldn't be set with only 1 extruder."
#elif TEMP_SENSOR_4 != 0
  #error "TEMP_SENSOR_4 shouldn't be set with only 1 extruder."
#endif
#if ENABLED(TEMP_SENSOR_1_AS_REDUNDANT) && TEMP_SENSOR_1 == 0
  #error "TEMP_SENSOR_1 is required with TEMP_SENSOR_1_AS_REDUNDANT."
#endif
#if ENABLED(TEMP_STAT_LEDS) && !PIN_EXISTS(STAT_LED_RED) && !PIN_EXISTS(STAT_LED_BLUE)
  #error "TEMP_STAT_LEDS requires STAT_LED_RED_PIN or STAT_LED_BLUE_PIN, preferably both."
#endif
#if ENABLED(DUAL_NOZZLE_DUPLICATION_MODE)
  #if HOTENDS != 2
    #error "DUAL_NOZZLE_DUPLICATION_MODE requires exactly 2 hotends."
  #elif ENABLED(DUAL_X_CARRIAGE)
    #error "DUAL_NOZZLE_DUPLICATION_MODE is incompatible with DUAL_X_CARRIAGE."
  #elif ENABLED(SINGLENOZZLE)
    #error "DUAL_NOZZLE_DUPLICATION_MODE is incompatible with SINGLENOZZLE."
  #elif ENABLED(MIXING_EXTRUDER)
    #error "DUAL_NOZZLE_DUPLICATION_MODE is incompatible with MIXING_EXTRUDER."
  #elif ENABLED(SWITCHING_EXTRUDER)
    #error "DUAL_NOZZLE_DUPLICATION_MODE is incompatible with SWITCHING_EXTRUDER."
  #endif
#endif
#if E_STEPPERS > 4
  #if !PIN_EXISTS(E4_STEP) || !PIN_EXISTS(E4_DIR) || !PIN_EXISTS(E4_ENABLE)
    #error "E4_STEP_PIN, E4_DIR_PIN, or E4_ENABLE_PIN not defined for this board."
  #endif
#elif E_STEPPERS > 3
  #if !PIN_EXISTS(E3_STEP) || !PIN_EXISTS(E3_DIR) || !PIN_EXISTS(E3_ENABLE)
    #error "E3_STEP_PIN, E3_DIR_PIN, or E3_ENABLE_PIN not defined for this board."
  #endif
#elif E_STEPPERS > 2
  #if !PIN_EXISTS(E2_STEP) || !PIN_EXISTS(E2_DIR) || !PIN_EXISTS(E2_ENABLE)
    #error "E2_STEP_PIN, E2_DIR_PIN, or E2_ENABLE_PIN not defined for this board."
  #endif
#elif E_STEPPERS > 1
  #if !PIN_EXISTS(E1_STEP) || !PIN_EXISTS(E1_DIR) || !PIN_EXISTS(E1_ENABLE)
    #error "E1_STEP_PIN, E1_DIR_PIN, or E1_ENABLE_PIN not defined for this board."
  #endif
#endif
#if DISABLED(USE_XMIN_PLUG) && DISABLED(USE_XMAX_PLUG) && !(ENABLED(Z_DUAL_ENDSTOPS) && WITHIN(Z2_USE_ENDSTOP, _XMAX_, _XMIN_))
 #error "You must enable USE_XMIN_PLUG or USE_XMAX_PLUG."
#elif DISABLED(USE_YMIN_PLUG) && DISABLED(USE_YMAX_PLUG) && !(ENABLED(Z_DUAL_ENDSTOPS) && WITHIN(Z2_USE_ENDSTOP, _YMAX_, _YMIN_))
 #error "You must enable USE_YMIN_PLUG or USE_YMAX_PLUG."
#elif DISABLED(USE_ZMIN_PLUG) && DISABLED(USE_ZMAX_PLUG) && !(ENABLED(Z_DUAL_ENDSTOPS) && WITHIN(Z2_USE_ENDSTOP, _ZMAX_, _ZMIN_))
 #error "You must enable USE_ZMIN_PLUG or USE_ZMAX_PLUG."
#elif ENABLED(Z_DUAL_ENDSTOPS)
  #if !Z2_USE_ENDSTOP
    #error "You must set Z2_USE_ENDSTOP with Z_DUAL_ENDSTOPS."
  #elif Z2_MAX_PIN == 0 && Z2_MIN_PIN == 0
    #error "Z2_USE_ENDSTOP has been assigned to a nonexistent endstop!"
  #elif ENABLED(DELTA)
    #error "Z_DUAL_ENDSTOPS is not compatible with DELTA."
  #endif
#elif !IS_SCARA
  #if X_HOME_DIR < 0 && DISABLED(USE_XMIN_PLUG)
    #error "Enable USE_XMIN_PLUG when homing X to MIN."
  #elif X_HOME_DIR > 0 && DISABLED(USE_XMAX_PLUG)
    #error "Enable USE_XMAX_PLUG when homing X to MAX."
  #elif Y_HOME_DIR < 0 && DISABLED(USE_YMIN_PLUG)
    #error "Enable USE_YMIN_PLUG when homing Y to MIN."
  #elif Y_HOME_DIR > 0 && DISABLED(USE_YMAX_PLUG)
    #error "Enable USE_YMAX_PLUG when homing Y to MAX."
  #elif Z_HOME_DIR < 0 && DISABLED(USE_ZMIN_PLUG)
    #error "Enable USE_ZMIN_PLUG when homing Z to MIN."
  #elif Z_HOME_DIR > 0 && DISABLED(USE_ZMAX_PLUG)
    #error "Enable USE_ZMAX_PLUG when homing Z to MAX."
  #endif
#endif
#if ENABLED(EMERGENCY_PARSER) && defined(USBCON)
  #error "EMERGENCY_PARSER does not work on boards with AT90USB processors (USBCON)."
#endif
#if ENABLED(EXPERIMENTAL_I2CBUS) && I2C_SLAVE_ADDRESS > 0
  #if I2C_SLAVE_ADDRESS < 8
    #error "I2C_SLAVE_ADDRESS can't be less than 8. (Addresses 0 - 7 are reserved.)"
  #elif I2C_SLAVE_ADDRESS > 127
    #error "I2C_SLAVE_ADDRESS can't be over 127. (Only 7 bits allowed.)"
  #endif
#endif
#if ENABLED(G38_PROBE_TARGET)
  #if !HAS_BED_PROBE
    #error "G38_PROBE_TARGET requires a bed probe."
  #elif !IS_CARTESIAN
    #error "G38_PROBE_TARGET requires a Cartesian machine."
  #endif
#endif
#define _RGB_TEST (PIN_EXISTS(RGB_LED_R) && PIN_EXISTS(RGB_LED_G) && PIN_EXISTS(RGB_LED_B))
#if ENABLED(RGB_LED)
  #if !_RGB_TEST
    #error "RGB_LED requires RGB_LED_R_PIN, RGB_LED_G_PIN, and RGB_LED_B_PIN."
  #elif ENABLED(RGBW_LED)
    #error "Please enable only one of RGB_LED and RGBW_LED."
  #endif
#elif ENABLED(RGBW_LED)
  #if !(_RGB_TEST && PIN_EXISTS(RGB_LED_W))
    #error "RGBW_LED requires RGB_LED_R_PIN, RGB_LED_G_PIN, RGB_LED_B_PIN, and RGB_LED_W_PIN."
  #endif
#elif ENABLED(PRINTER_EVENT_LEDS) && DISABLED(BLINKM) && DISABLED(PCA9632)
  #error "PRINTER_EVENT_LEDS requires BLINKM, PCA9632, RGB_LED, or RGBW_LED."
#endif
#if HAS_AUTO_FAN && EXTRUDER_AUTO_FAN_SPEED != 255
  #define AF_ERR_SUFF "_AUTO_FAN_PIN is not a PWM pin. Set EXTRUDER_AUTO_FAN_SPEED to 255."
  #if HAS_AUTO_FAN_0
    static_assert(GET_TIMER(E0_AUTO_FAN_PIN), "E0" AF_ERR_SUFF);
  #elif HAS_AUTO_FAN_1
    static_assert(GET_TIMER(E1_AUTO_FAN_PIN), "E1" AF_ERR_SUFF);
  #elif HAS_AUTO_FAN_2
    static_assert(GET_TIMER(E2_AUTO_FAN_PIN), "E2" AF_ERR_SUFF);
  #elif HAS_AUTO_FAN_3
    static_assert(GET_TIMER(E3_AUTO_FAN_PIN), "E3" AF_ERR_SUFF);
  #endif
#endif
static_assert(1 >= 0
  #if ENABLED(ULTIMAKERCONTROLLER)       && DISABLED(SAV_3DGLCD) && DISABLED(miniVIKI) && DISABLED(VIKI2)       && DISABLED(ELB_FULL_GRAPHIC_CONTROLLER) && DISABLED(PANEL_ONE)
    + 1
  #endif
  #if ENABLED(REPRAP_DISCOUNT_SMART_CONTROLLER) && DISABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
    + 1
  #endif
  #if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER) && DISABLED(BQ_LCD_SMART_CONTROLLER)
    + 1
  #endif
  #if ENABLED(LCD_FOR_MELZI)
    + 1
  #endif
  #if ENABLED(CARTESIO_UI)
    + 1
  #endif
  #if ENABLED(PANEL_ONE)
    + 1
  #endif
  #if ENABLED(MAKRPANEL)
    + 1
  #endif
  #if ENABLED(REPRAPWORLD_GRAPHICAL_LCD)
    + 1
  #endif
  #if ENABLED(VIKI2)
    + 1
  #endif
  #if ENABLED(miniVIKI)
    + 1
  #endif
  #if ENABLED(ELB_FULL_GRAPHIC_CONTROLLER)
    + 1
  #endif
  #if ENABLED(G3D_PANEL)
    + 1
  #endif
  #if ENABLED(MINIPANEL)
    + 1
  #endif
  #if ENABLED(REPRAPWORLD_KEYPAD) && DISABLED(CARTESIO_UI) && DISABLED(ANET_KEYPAD_LCD)
    + 1
  #endif
  #if ENABLED(RIGIDBOT_PANEL)
    + 1
  #endif
  #if ENABLED(RA_CONTROL_PANEL)
    + 1
  #endif
  #if ENABLED(LCD_I2C_SAINSMART_YWROBOT)
    + 1
  #endif
  #if ENABLED(LCM1602)
    + 1
  #endif
  #if ENABLED(LCD_I2C_PANELOLU2)
    + 1
  #endif
  #if ENABLED(LCD_I2C_VIKI)
    + 1
  #endif
  #if ENABLED(U8GLIB_SSD1306) && DISABLED(OLED_PANEL_TINYBOY2)
    + 1
  #endif
  #if ENABLED(SAV_3DLCD)
    + 1
  #endif
  #if ENABLED(BQ_LCD_SMART_CONTROLLER)
    + 1
  #endif
  #if ENABLED(SAV_3DGLCD)
    + 1
  #endif
  #if ENABLED(OLED_PANEL_TINYBOY2)
    + 1
  #endif
  #if ENABLED(ANET_KEYPAD_LCD)
    + 1
  #endif
  , "Please select no more than one LCD controller option."
);
#if ENABLED(HAVE_TMCDRIVER) && !(          ENABLED(  X_IS_TMC )       || ENABLED( X2_IS_TMC )       || ENABLED(  Y_IS_TMC )       || ENABLED( Y2_IS_TMC )       || ENABLED(  Z_IS_TMC )       || ENABLED( Z2_IS_TMC )       || ENABLED( E0_IS_TMC )       || ENABLED( E1_IS_TMC )       || ENABLED( E2_IS_TMC )       || ENABLED( E3_IS_TMC )       || ENABLED( E4_IS_TMC )   )
  #error "HAVE_TMCDRIVER requires at least one TMC stepper to be set."
#endif
#if ENABLED(HAVE_TMC2130)
  #if !( ENABLED(  X_IS_TMC2130 )       || ENABLED( X2_IS_TMC2130 )       || ENABLED(  Y_IS_TMC2130 )       || ENABLED( Y2_IS_TMC2130 )       || ENABLED(  Z_IS_TMC2130 )       || ENABLED( Z2_IS_TMC2130 )       || ENABLED( E0_IS_TMC2130 )       || ENABLED( E1_IS_TMC2130 )       || ENABLED( E2_IS_TMC2130 )       || ENABLED( E3_IS_TMC2130 )       || ENABLED( E4_IS_TMC2130 )   )
    #error "HAVE_TMC2130 requires at least one TMC2130 stepper to be set."
  #elif ENABLED(HYBRID_THRESHOLD) && DISABLED(STEALTHCHOP)
    #error "Enable STEALTHCHOP to use HYBRID_THRESHOLD."
  #endif
#endif
#if ENABLED(HAVE_L6470DRIVER) && !(          ENABLED(  X_IS_L6470 )       || ENABLED( X2_IS_L6470 )       || ENABLED(  Y_IS_L6470 )       || ENABLED( Y2_IS_L6470 )       || ENABLED(  Z_IS_L6470 )       || ENABLED( Z2_IS_L6470 )       || ENABLED( E0_IS_L6470 )       || ENABLED( E1_IS_L6470 )       || ENABLED( E2_IS_L6470 )       || ENABLED( E3_IS_L6470 )       || ENABLED( E4_IS_L6470 )   )
  #error "HAVE_L6470DRIVER requires at least one L6470 stepper to be set."
#endif
#if ENABLED(DIGIPOT_MCP4018)
  #if !defined(DIGIPOTS_I2C_SDA_X) || !defined(DIGIPOTS_I2C_SDA_Y) || !defined(DIGIPOTS_I2C_SDA_Z)     || !defined(DIGIPOTS_I2C_SDA_E0) || !defined(DIGIPOTS_I2C_SDA_E1)
      #error "DIGIPOT_MCP4018 requires DIGIPOTS_I2C_SDA_* pins to be defined."
  #endif
#endif
constexpr float sanity_arr_1[] = DEFAULT_AXIS_STEPS_PER_UNIT,
                sanity_arr_2[] = DEFAULT_MAX_FEEDRATE,
                sanity_arr_3[] = DEFAULT_MAX_ACCELERATION;
static_assert(COUNT(sanity_arr_1) >= XYZE, "DEFAULT_AXIS_STEPS_PER_UNIT requires 4 (or more) elements.");
static_assert(COUNT(sanity_arr_2) >= XYZE, "DEFAULT_MAX_FEEDRATE requires 4 (or more) elements.");
static_assert(COUNT(sanity_arr_3) >= XYZE, "DEFAULT_MAX_ACCELERATION requires 4 (or more) elements.");
static_assert(COUNT(sanity_arr_1) <= XYZE_N, "DEFAULT_AXIS_STEPS_PER_UNIT has too many elements.");
static_assert(COUNT(sanity_arr_2) <= XYZE_N, "DEFAULT_MAX_FEEDRATE has too many elements.");
static_assert(COUNT(sanity_arr_3) <= XYZE_N, "DEFAULT_MAX_ACCELERATION has too many elements.");
#if ENABLED(SPINDLE_LASER_ENABLE)
  #if !PIN_EXISTS(SPINDLE_LASER_ENABLE)
    #error "SPINDLE_LASER_ENABLE requires SPINDLE_LASER_ENABLE_PIN."
  #elif SPINDLE_DIR_CHANGE && !PIN_EXISTS(SPINDLE_DIR)
    #error "SPINDLE_DIR_PIN not defined."
  #elif ENABLED(SPINDLE_LASER_PWM) && PIN_EXISTS(SPINDLE_LASER_PWM)
    #if !(WITHIN(SPINDLE_LASER_PWM_PIN, 2, 13) || WITHIN(SPINDLE_LASER_PWM_PIN, 44, 46))
      #error "SPINDLE_LASER_PWM_PIN not assigned to a PWM pin."
    #elif SPINDLE_LASER_POWERUP_DELAY < 1
      #error "SPINDLE_LASER_POWERUP_DELAY must be greater than 0."
    #elif SPINDLE_LASER_POWERDOWN_DELAY < 1
      #error "SPINDLE_LASER_POWERDOWN_DELAY must be greater than 0."
    #elif !defined(SPINDLE_LASER_PWM_INVERT)
      #error "SPINDLE_LASER_PWM_INVERT missing."
    #elif !defined(SPEED_POWER_SLOPE) || !defined(SPEED_POWER_INTERCEPT) || !defined(SPEED_POWER_MIN) || !defined(SPEED_POWER_MAX)
      #error "SPINDLE_LASER_PWM equation constant(s) missing."
    #elif SPINDLE_LASER_PWM_PIN == 4 || WITHIN(SPINDLE_LASER_PWM_PIN, 11, 13)
      #error "Counter/Timer for SPINDLE_LASER_PWM_PIN is used by a system interrupt."
    #elif PIN_EXISTS(X_MAX) && X_MAX_PIN == SPINDLE_LASER_PWM_PIN
      #error "SPINDLE_LASER_PWM pin is in use by X_MAX endstop."
    #elif PIN_EXISTS(X_MIN) && X_MIN_PIN == SPINDLE_LASER_PWM_PIN
      #error "SPINDLE_LASER_PWM pin is in use by X_MIN endstop."
    #elif PIN_EXISTS(Z_STEP) && Z_STEP_PIN == SPINDLE_LASER_PWM_PIN
      #error "SPINDLE_LASER_PWM pin in use by Z_STEP."
    #elif NUM_SERVOS > 0 && (WITHIN(SPINDLE_LASER_PWM_PIN, 2, 3) || SPINDLE_LASER_PWM_PIN == 5)
      #error "Counter/Timer for SPINDLE_LASER_PWM_PIN is used by the servo system."
    #elif PIN_EXISTS(CASE_LIGHT) && SPINDLE_LASER_PWM_PIN == CASE_LIGHT_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by CASE_LIGHT_PIN."
    #elif PIN_EXISTS(E0_AUTO_FAN) && SPINDLE_LASER_PWM_PIN == E0_AUTO_FAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by E0_AUTO_FAN_PIN."
    #elif PIN_EXISTS(E1_AUTO_FAN) && SPINDLE_LASER_PWM_PIN == E1_AUTO_FAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by E1_AUTO_FAN_PIN."
    #elif PIN_EXISTS(E2_AUTO_FAN) && SPINDLE_LASER_PWM_PIN == E2_AUTO_FAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by E2_AUTO_FAN_PIN."
    #elif PIN_EXISTS(E3_AUTO_FAN) && SPINDLE_LASER_PWM_PIN == E3_AUTO_FAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by E3_AUTO_FAN_PIN."
    #elif PIN_EXISTS(E4_AUTO_FAN) && SPINDLE_LASER_PWM_PIN == E4_AUTO_FAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by E4_AUTO_FAN_PIN."
    #elif PIN_EXISTS(FAN) && SPINDLE_LASER_PWM_PIN == FAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used FAN_PIN."
    #elif PIN_EXISTS(FAN1) && SPINDLE_LASER_PWM_PIN == FAN1_PIN
      #error "SPINDLE_LASER_PWM_PIN is used FAN1_PIN."
    #elif PIN_EXISTS(FAN2) && SPINDLE_LASER_PWM_PIN == FAN2_PIN
      #error "SPINDLE_LASER_PWM_PIN is used FAN2_PIN."
    #elif PIN_EXISTS(CONTROLLERFAN) && SPINDLE_LASER_PWM_PIN == CONTROLLERFAN_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by CONTROLLERFAN_PIN."
    #elif PIN_EXISTS(MOTOR_CURRENT_PWM_XY) && SPINDLE_LASER_PWM_PIN == MOTOR_CURRENT_PWM_XY_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by MOTOR_CURRENT_PWM_XY."
    #elif PIN_EXISTS(MOTOR_CURRENT_PWM_Z) && SPINDLE_LASER_PWM_PIN == MOTOR_CURRENT_PWM_Z_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by MOTOR_CURRENT_PWM_Z."
    #elif PIN_EXISTS(MOTOR_CURRENT_PWM_E) && SPINDLE_LASER_PWM_PIN == MOTOR_CURRENT_PWM_E_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by MOTOR_CURRENT_PWM_E."
    #elif PIN_EXISTS(CASE_LIGHT) && SPINDLE_LASER_PWM_PIN == CASE_LIGHT_PIN
      #error "SPINDLE_LASER_PWM_PIN is used by CASE_LIGHT."
    #endif
  #endif
#endif 
#if !defined(EEPROM_SETTINGS)
#error MACRO_var_V010 need use eeprom and you must enable it.
#endif
