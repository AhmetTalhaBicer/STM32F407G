/*
 * Led.h
 *
 *  Created on: May 31, 2025
 *      Author: athlb
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx_hal.h"

class Led {
private:
	GPIO_TypeDef *gpioPort;
	uint16_t gpioPin;

public:
	// Constructor: GPIO portu ve pini alır
	Led(GPIO_TypeDef *port, uint16_t pin);

	// Destructor
	~Led();

	// LED'i aç
	void turnOn();

	// LED'i kapat
	void turnOff();

	// LED durumunu tersine çevir (toggle)
	void toggle();

	// LED durumunu oku (açık/kapalı)
	bool isOn() const;

	// Butonun kaç kere basıldığını sayar
	void countPresses() {
	}
};

#endif /* LED_H_ */
