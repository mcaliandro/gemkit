#include "GemKit.h"

GemKit::GemKit() {
	for (uint8_t i=0; i<SENSORS_NUM; i++) {
		sensorsAlert[i] = threshold::good;
	}
}

bool GemKit::init() {
	bool initOK = true;
	if (!audioPlayer.init(PIN_DFPLAYER_RX, PIN_DFPLAYER_TX, PIN_DFPLAYER_BUSY)) {
		Serial.println("DFPlayer initialization failed!");
		initOK = false;
	}
	if (!ambientSensor.init(PIN_TEMPERATURE)) {
		Serial.println("Temperature sensor not found!");
		initOK = false;
	}
	lightSensor.init(PIN_LIGHT);
	moistureSensor.init(PIN_MOISTURE_POWER, PIN_MOISTURE);
	proximitySensor.init(PIN_PIR_ANALOG, PIN_PIR_DIGITAL);
	return initOK;
}

// return true if sensors status is not good
bool GemKit::alert() {
	for (uint8_t i=0; i<SENSORS_NUM; i++) {
		if (sensorsAlert[i] != threshold::good) {
			return true;
		}
	}
	return false;
}

void GemKit::checkSensors() {
	sensorsAlert[ambient] = ambientSensor.check();
	sensorsAlert[light] = lightSensor.check();
	sensorsAlert[water] = moistureSensor.check();
}

void GemKit::playAlert() {
	if (sensorsAlert[ambient] == threshold::below) {
		audioPlayer.alertCold();
	} else if (sensorsAlert[ambient] == threshold::above) {
		audioPlayer.alertHot();
	}
	if (sensorsAlert[light] == threshold::below) {
		audioPlayer.alertSun();
	}
	if (sensorsAlert[water] == threshold::below) {
		audioPlayer.alertThirst();
	}
}

void GemKit::playGoodState() {
	audioPlayer.noAlert();
}

void GemKit::playSetupIntro() {
	audioPlayer.setupIntro();
}

void GemKit::playSetupPutSeeds() {
	audioPlayer.setupPutSeeds();
}

void GemKit::playSetupPutSoil() {
	audioPlayer.setupPutSoil();
}

void GemKit::playSetupUseTank() {
	audioPlayer.setupUseTank();
}

void GemKit::playSetupGuide() {
	audioPlayer.setupGuide();
}

String GemKit::showStatus() {
	return "L" + String(lightSensor.getRate()) +
		" M" + String(moistureSensor.getRate()) +
		" T" + String(ambientSensor.getRate());
}


