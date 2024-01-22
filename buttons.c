#include <buttons.h>
#include "hardware/gpio.h"
#include <stdbool.h>

const int BUTTON_PINS[NUM_BUTTONS] = {9,10,11,12,13};

void buttons_init(){
  for (int buttonIdx = 0; buttonIdx < NUM_BUTTONS; buttonIdx++){
    const int gpioNumber = BUTTON_PINS[buttonIdx];
    gpio_init(gpioNumber);
    gpio_set_dir(gpioNumber, GPIO_IN);
    gpio_pull_up(gpioNumber);}}

enum BUTTON_STATE buttonRead(int buttonIdx)
{
    static bool prevBtnStates[NUM_BUTTONS] = { false };

    const int gpioNumber = BUTTON_PINS[buttonIdx];
    const bool prevState = prevBtnStates[buttonIdx];
    const bool currentState = gpio_get(gpioNumber);
    prevBtnStates[buttonIdx] = currentState;

    if (!prevState && currentState)
    {
        return BUTTON_RELEASED;
    }
    else if (prevState && !currentState)
    {
        return BUTTON_PRESSED;
    }
    else if (!prevState && !currentState)
    {
        return BUTTON_HELD_PRESSED;
    }
    else
    {
        return BUTTON_NOT_PRESSED;
    }
}
