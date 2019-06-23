#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <DallasTemperature.h>
#include <OneWire.h>
#include "Arduino.h"

enum threshold { below, good, above };


class Light {
private:
	const int minThreshold = 30;
	uint8_t analogPin;
	int rate;
public:
	Light();
	void init(uint8_t);
	threshold check();
	int getRate();
};


class Moisture {
private:
	const static uint8_t minThreshold = 70;
	uint8_t analogPin;
	uint8_t powerPin;
	int rate;
public:
	Moisture();
	void init(uint8_t, uint8_t);
	threshold check();
	int getRate();
};


class Proximity {
private:
	uint8_t analogPin;
	uint8_t digitalPin;
public:
	Proximity();
	void init(uint8_t, uint8_t);
	bool check();
};


class Temperature {
private:
	const static uint8_t minThreshold = 18;
	const static uint8_t maxThreshold = 40;
	DallasTemperature sensors;
	uint8_t devices;
	float rate;
public:
	Temperature();
	bool init(uint8_t);
	threshold check();
	float getRate();
};


#endif
