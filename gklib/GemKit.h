#ifndef _GEMKIT_H_
#define _GEMKIT_H_


#include "AudioPlayer.h"
#include "Requests.h"
#include "Sensors.h"


class GemKit {
private:
	const static uint8_t PIN_DFPLAYER_BUSY = 18;	// GPIO18 -> 18
	const static uint8_t PIN_DFPLAYER_RX = 17;		// GPIO17 -> 17
	const static uint8_t PIN_DFPLAYER_TX = 16;		// GPIO16 -> 16
	const static uint8_t PIN_LIGHT = 34;			// GPIO34 -> 34
	const static uint8_t PIN_MOISTURE_POWER = 25;	// GPIO25 -> 25
	const static uint8_t PIN_MOISTURE = 35;			// GPIO35 -> 35
	const static uint8_t PIN_PIR_DIGITAL = 26;		// GPIO26 -> 26
	const static uint8_t PIN_PIR_ANALOG = 39; 		// GPIO39 -> VN/SN
	const static uint8_t PIN_TEMPERATURE = 27;		// GPIO27 -> 27

	const static uint8_t SENSORS_NUM = 3;
	enum alert : uint8_t { ambient, light, water };
	threshold sensorsAlert[SENSORS_NUM];

	AudioPlayer audioPlayer;
	Temperature ambientSensor;
	Light lightSensor;
	Moisture moistureSensor;
	Proximity proximitySensor;

public:
	GemKit();
	bool init();
	bool alert();
	void checkSensors();
	void playAlert();
	void playGoodState();
	void playSetupIntro();
	void playSetupPutSeeds();
	void playSetupPutSoil();
	void playSetupUseTank();
	void playSetupGuide();
	String showStatus();
};


#endif
