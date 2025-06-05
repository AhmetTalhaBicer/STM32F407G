/*
 * Button.h
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

class Button {
private:
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;
	GPIO_PinState activeState;  // HIGH or LOW when pressed
	uint32_t debounceTime;      // Debounce time in milliseconds
	uint32_t lastDebounceTime;  // Last time the button state changed
	bool lastState;             // Last stable state
	bool currentState;          // Current debounced state
	uint8_t buttonPressCount;   // Counter for button presses

public:
	// Constructor: port, pin, active state (default: LOW = pressed), debounce time in ms
	Button(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState activeState =
			GPIO_PIN_RESET, uint32_t debounceTimeMs = 20);

	// Initialize button with pull-up/down based on active state
	void init();

	// Read raw button state (not debounced)
	bool readRaw();

	// Read debounced state
	bool isPressed();

	// Update button state (should be called in a loop)
	void update();

	// Check if button was just pressed (rising edge detection)
	bool wasPressed();

	// Check if button was just released (falling edge detection)
	bool wasReleased();

	// Get the number of times the button has been pressed
	uint8_t getPressCount();
};

#endif /* BUTTON_H_ */
