/*
  This sketch shows how to use power save deepsleep mode
*/
#include <PowerSave.h>

//SET_DS_AON_TIMER_WAKEUP
//SET_DS_RTC_WAKEUP
//SET_DS_AON_GPIO_WAKEUP_D16
//SET_DS_AON_GPIO_WAKEUP_D17
//SET_DS_AON_GPIO_WAKEUP_D26
//SET_DS_AON_GPIO_WAKEUP_D27
#define DS_WAKEUP_SOURCE                SET_DS_AON_TIMER_WAKEUP

#define AON_TIMER_SLEEP_DURATION        5000
#define DS_RTC_ALARM_DAY                0
#define DS_RTC_ALARM_HOUR               0
#define DS_RTC_ALARM_MIN                0
#define DS_RTC_ALARM_SEC                10

void DeepSleep_wakeup(void) {
    printf("\r\nDeep sleep wakeuped! \r\n");
    uint32_t wakereason_number = PowerSave.AONWakeReason();

    if (wakereason_number == AONWakeReason_AON_GPIO) {
        printf("AonWakepin wakeup, wakepin is D%d. Wait 5s sleep again.    \r\n", PowerSave.WakePinCheck());
        delay(5000);
    } else if (wakereason_number == AONWakeReason_AON_TIMER) {
        PowerSave.AONTimerCmd();
        printf("Aontimer wakeup. Wait 5s sleep again.    \r\n");
        delay(5000);
    } else if (wakereason_number == AONWakeReason_RTC) {
        printf("RTC wakeup. Wait 5s sleep again.    \r\n");
        delay(5000);
    }

    PowerSave.AONWakeClear();
}

void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    PowerSave.begin(DEEPSLEEP_MODE);

    if (TRUE == (PowerSave.DsleepWakeStatusGet())) {
        DeepSleep_wakeup();
    }

    PowerSave.AONTimerDuration(0);

    switch (DS_WAKEUP_SOURCE) {
        case SET_DS_AON_TIMER_WAKEUP:
            PowerSave.DS_AON_TIMER_WAKEUP();
            PowerSave.AONTimerDuration(AON_TIMER_SLEEP_DURATION);
            break;
        case SET_DS_AON_GPIO_WAKEUP_D16:
            PowerSave.DS_AON_WAKEPIN_WAKEUP_D16();
            break;
        case SET_DS_AON_GPIO_WAKEUP_D17:
            PowerSave.DS_AON_WAKEPIN_WAKEUP_D17();
            break;
        case SET_DS_AON_GPIO_WAKEUP_D26:
            PowerSave.DS_AON_WAKEPIN_WAKEUP_D26();
            break;
        case SET_DS_AON_GPIO_WAKEUP_D27:
            PowerSave.DS_AON_WAKEPIN_WAKEUP_D27();
            break;
        case SET_DS_RTC_WAKEUP:
            PowerSave.DS_RTC_WAKEUP();
            PowerSave.RTCWakeSetup(DS_RTC_ALARM_DAY, DS_RTC_ALARM_HOUR, DS_RTC_ALARM_MIN, DS_RTC_ALARM_SEC);
            break;
        default:
            printf("Unknown wakeup source.    \r\n");
        break;
    }

    PowerSave.enable();
}

void loop() {
    delay(1000);
}
