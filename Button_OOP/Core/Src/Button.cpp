/*
 * Button.cpp
 */

#include "Button.h"

Button::Button(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState activeState,
		uint32_t debounceTimeMs) :
		gpioPort(port), gpioPin(pin), activeState(activeState), debounceTime(
				debounceTimeMs), lastDebounceTime(0), lastState(false), currentState(
				false), buttonPressCount(0) {
}

void Button::init() {
	// Configure GPIO pin as input with pull-up/down
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;

	// Set appropriate pull-up/pull-down based on active state
	if (activeState == GPIO_PIN_RESET) {
		GPIO_InitStruct.Pull = GPIO_PULLUP;    // Button active LOW, use pull-up
	} else {
		GPIO_InitStruct.Pull = GPIO_PULLDOWN; // Button active HIGH, use pull-down
	}

	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);
}

bool Button::readRaw() {
	// Return true if the button is pressed (matches active state)
	return (HAL_GPIO_ReadPin(gpioPort, gpioPin) == activeState);
}

void Button::update() {
	// Read the current physical state
	bool reading = readRaw();

	// Check if the state changed
	if (reading != lastState) {
		// Reset the debouncing timer
		lastDebounceTime = HAL_GetTick();
	}

	// If enough time has passed, update the current state
	if ((HAL_GetTick() - lastDebounceTime) > debounceTime) {
		// Only update if the debounced state changed
		if (reading != currentState) {
			currentState = reading;
		}
	}

	// Save the raw state for next comparison
	lastState = reading;
}

bool Button::isPressed() {
	return currentState;
}

bool Button::wasPressed() {
	static bool prevState = false;
	bool pressed = false;

	// Rising edge detection
	if (currentState && !prevState) {
		pressed = true;
	}

	prevState = currentState;
	return pressed;
}

bool Button::wasReleased() {
	static bool prevState = false;
	bool released = false;

	// Falling edge detection
	if (!currentState && prevState) {
		released = true;
	}

	prevState = currentState;
	return released;
}

uint8_t Button::getPressCount() {
	if (wasPressed()) {
		buttonPressCount++;
	}
	return buttonPressCount;
}
