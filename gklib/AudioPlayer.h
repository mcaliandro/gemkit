#ifndef _AUDIOPLAYER_H_
#define _AUDIOPLAYER_H_

#include "Arduino.h"
#include "AudioMapping.h"
#include "DFRobotDFPlayerMini.h"


class AudioPlayer {
private:
	const static int SERIAL_BAUD_RATE = 9600;
	const static uint8_t VOLUME_MIN = 0;
	const static uint8_t VOLUME_MAX = 30;
	const static uint8_t VOLUME_START = 30;
	const static int WAIT = 500;
	const static int SECOND = 1000;
	DFRobotDFPlayerMini dfplayer;
	uint8_t busyControl;

public:
	AudioPlayer();
	bool init(uint8_t, uint8_t, uint8_t);
	void wait(uint8_t);
	bool isAvailable();

	void alertThirst();
	void alertCold();
	void alertSun();
	void alertHot();
	void noAlert();

	void setupIntro();
	void setupPutSeeds();
	void setupPutSoil();
	void setupUseTank();
	void setupGuide();
};


#endif
