#include "Sensors.h"
#define INPUT_MIN 0
#define INPUT_MAX 4095
#define VALUE_MIN 0
#define VALUE_MAX 100


/* =======================================
 * 				LIGHT SENSOR
 * =======================================
 */

Light::Light() {} // @suppress("Class members should be properly initialized")

void Light::init(uint8_t pin) {
	analogPin = pin;
	pinMode(analogPin, INPUT);
}

threshold Light::check() {
	rate = map(analogRead(analogPin), INPUT_MIN, INPUT_MAX, VALUE_MIN, VALUE_MAX);
	if (rate < minThreshold) {
		return threshold::below;
	}
	return threshold::good;
}

int Light::getRate() {
	return rate;
}



/* =======================================
 * 			  MOISTURE SENSOR
 * =======================================
 */

Moisture::Moisture() {} // @suppress("Class members should be properly initialized")

void Moisture::init(uint8_t power, uint8_t analog) {
	powerPin = power;
	analogPin = analog;
	pinMode(powerPin, OUTPUT);
	pinMode(analogPin, INPUT);
	digitalWrite(powerPin, LOW);
}

threshold Moisture::check() {
	digitalWrite(powerPin, HIGH);
	delay(1000);
	rate = map(analogRead(analogPin), INPUT_MIN, INPUT_MAX, VALUE_MIN, VALUE_MAX);
	digitalWrite(powerPin, LOW);
	if (rate < minThreshold) {
		return threshold::below;
	}
	return threshold::good;
}

int Moisture::getRate() {
	return rate;
}



/* =======================================
 * 			  PROXIMITY SENSOR
 * =======================================
 */

Proximity::Proximity() {} // @suppress("Class members should be properly initialized")
void Proximity::init(uint8_t analog, uint8_t digital) {
	analogPin = analog;
	digitalPin = digital;
	pinMode(analogPin, INPUT);
	pinMode(digitalPin, INPUT);
}

bool Proximity::check() {
	return (digitalRead(digitalPin) == HIGH);
}



/* =======================================
 * 			TEMPERATURE SENSOR
 * =======================================
 */

Temperature::Temperature() {} // @suppress("Class members should be properly initialized")

// return true if at least one sensor has been detected
bool Temperature::init(uint8_t pin) {
	// Configure DS18B20 sensor
	sensors.setOneWire(new OneWire(pin));
	sensors.begin();
	devices = sensors.getDeviceCount();
	return (devices > 0);
}

threshold Temperature::check() {
	sensors.requestTemperatures();
	rate = 0.0;
	for (uint8_t i = 0; i < devices; i++) {
		rate += sensors.getTempCByIndex(i);
	}
	rate /= devices;
	if (rate < minThreshold) {
		return threshold::below;
	}
	if (rate > maxThreshold) {
		return threshold::above;
	}
	return threshold::good;
}

float Temperature::getRate() {
	return rate;
}

