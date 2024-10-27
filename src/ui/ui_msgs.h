#ifndef _XLCD_MESSAGING
#define _XLCD_MESSAGING

#ifdef __cplusplus
extern "C"
{
#endif

    enum XTOUCH_MESSAGE
    {
        XTOUCH_ON_MQTT,
        XTOUCH_ON_LIGHT_REPORT,
        XTOUCH_ON_BED_TEMP,
        XTOUCH_ON_BED_TARGET_TEMP,
        XTOUCH_ON_NOZZLE_TEMP,
        XTOUCH_ON_NOZZLE_TARGET_TEMP,
        XTOUCH_ON_CHAMBER_TEMP,
        XTOUCH_ON_AMS,
        XTOUCH_ON_WIFI_SIGNAL,
        XTOUCH_ON_PART_FAN_SPEED,
        XTOUCH_ON_PART_AUX_SPEED,
        XTOUCH_ON_PART_CHAMBER_SPEED,
        XTOUCH_ON_IPCAM,
        XTOUCH_ON_IPCAM_TIMELAPSE,
        XTOUCH_ON_PRINT_STATUS,
        XTOUCH_ON_AMS_BITS,
        XTOUCH_ON_ERROR,
        XTOUCH_ON_SSDP,
        XTOUCH_ON_AMS_SLOT_UPDATE,
        XTOUCH_ON_FILENAME_UPDATE,
        XTOUCH_ON_CLOUD_SELECT,
        XTOUCH_ON_CODE_ENTERED,
        XTOUCH_COMMAND_STOP,
        XTOUCH_COMMAND_PAUSE,
        XTOUCH_COMMAND_RESUME,
        XTOUCH_COMMAND_LIGHT_TOGGLE,
        XTOUCH_COMMAND_HOME,
        XTOUCH_COMMAND_RIGHT,
        XTOUCH_COMMAND_LEFT,
        XTOUCH_COMMAND_UP,
        XTOUCH_COMMAND_DOWN,
        XTOUCH_COMMAND_BED_TARGET_TEMP,
        XTOUCH_COMMAND_NOZZLE_TARGET_TEMP,
        XTOUCH_COMMAND_PART_FAN_SPEED,
        XTOUCH_COMMAND_AUX_FAN_SPEED,
        XTOUCH_COMMAND_CHAMBER_FAN_SPEED,
        XTOUCH_COMMAND_PRINT_SPEED,
        XTOUCH_COMMAND_EXTRUDE_UP,
        XTOUCH_COMMAND_EXTRUDE_DOWN,
        XTOUCH_COMMAND_UNLOAD_FILAMENT,
        XTOUCH_COMMAND_LOAD_FILAMENT,
        XTOUCH_COMMAND_CLEAN_PRINT_ERROR,
        XTOUCH_COMMAND_AMS_CONTROL,

        XTOUCH_CONTROL_INC_SWITCH,
        XTOUCH_CONTROL_AXIS_SWITCH,
        XTOUCH_SETTINGS_RESET_DEVICE,
        XTOUCH_SETTINGS_UNPAIR,
        XTOUCH_SETTINGS_BACKLIGHT,
        XTOUCH_SETTINGS_BACKLIGHT_SET,
        XTOUCH_SETTINGS_TFTOFF_SET,
        XTOUCH_SETTINGS_TFT_INVERT,
        XTOUCH_SETTINGS_TFT_FLIP,
        XTOUCH_SETTINGS_CHAMBER_TEMP,
        XTOUCH_SETTINGS_SAVE,

        XTOUCH_FIRMWARE_UPDATE,
        XTOUCH_FIRMWARE_UPDATE_PROGRESS,

    };

    struct XTOUCH_MESSAGE_DATA
    {
        unsigned long long data;
    };

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif