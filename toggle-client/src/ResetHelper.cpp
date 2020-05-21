#include "ResetHelper.h"
#include "AppContext.h"

ResetHelper::ResetHelper(char _pinIn)
{
    reset_pinIn = _pinIn;
    pinMode(reset_pinIn, INPUT_PULLUP);
}

void ResetHelper::checkResetButton()
{
    char currentBtn = digitalRead(reset_pinIn);
    // Serial.print("Reset Pin: ");
    // Serial.println(currentBtn ? "1" : "0");

    if (currentBtn == LOW)
    {
        delay(RESET_BTN_TIME);
    }

    if (currentBtn == LOW)
    {
        Serial.println("TURN TO RESET MODE");
        AppContext::getInstance()->toResetMode();
        // stopConnectWifi = true;
        // configAPMode();
    }
}