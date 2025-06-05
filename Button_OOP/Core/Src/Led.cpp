/*
 * Led.cpp
 *
 *  Created on: May 31, 2025
 *      Author: athlb
 */

#include "Led.h"

Led::Led(GPIO_TypeDef *port, uint16_t pin) :
		gpioPort(port), gpioPin(pin) {
	// Configure GPIO pin as output
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);
}

void Led::turnOn() {
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
}

void Led::turnOff() {
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
}

void Led::toggle() {
	HAL_GPIO_TogglePin(gpioPort, gpioPin);
}

bool Led::isOn() const {
	return HAL_GPIO_ReadPin(gpioPort, gpioPin) == GPIO_PIN_SET;
}

Led::~Led() {
	// Destructor implementation (empty)
}
