#include "AudioPlayer.h"
using namespace audiomapping;

AudioPlayer::AudioPlayer() {} // @suppress("Class members should be properly initialized")

// return true if the DFPlayer has been initialized
bool AudioPlayer::init(uint8_t rxPin, uint8_t txPin, uint8_t busyPin) {
	busyControl = busyPin;
	pinMode(busyControl, INPUT);
	// use HardwareSerial instance Serial1
	Serial1.begin(SERIAL_BAUD_RATE, SERIAL_8N1, rxPin, txPin);
	delay(WAIT);
	if (! dfplayer.begin(Serial1)) {
		return false;
	}
	dfplayer.volume(VOLUME_START);
	dfplayer.EQ(DFPLAYER_EQ_NORMAL);
	dfplayer.outputDevice(DFPLAYER_DEVICE_SD);
	dfplayer.reset();
	dfplayer.disableLoop();
	return true;
}

bool AudioPlayer::isAvailable() {
	delay(WAIT);
	return (digitalRead(busyControl) == HIGH);
}

void AudioPlayer::alertThirst() {
	dfplayer.play(Alert.thirst.file_id);
	delay(Alert.thirst.duration * SECOND);
}

void AudioPlayer::alertCold() {
	dfplayer.play(Alert.cold.file_id);
	delay(Alert.cold.duration * SECOND);
}

void AudioPlayer::alertSun() {
	dfplayer.play(Alert.sun.file_id);
	delay(Alert.thirst.duration * SECOND);
}

void AudioPlayer::alertHot() {
	dfplayer.play(Alert.hot.file_id);
	delay(Alert.hot.duration * SECOND);
}

void AudioPlayer::noAlert() {
	dfplayer.play(Alert.good.file_id);
	delay(Alert.good.duration * SECOND);
}

void AudioPlayer::setupIntro() {
	dfplayer.play(Setup.intro.file_id);
	delay(Setup.intro.duration * SECOND);
}

void AudioPlayer::setupPutSeeds() {
	dfplayer.play(Setup.putseeds.file_id);
	delay(Setup.putseeds.duration * SECOND);
}

void AudioPlayer::setupPutSoil() {
	dfplayer.play(Setup.putsoil.file_id);
	delay(Setup.putsoil.duration * SECOND);
}

void AudioPlayer::setupUseTank() {
	dfplayer.play(Setup.usetank.file_id);
	delay(Setup.usetank.duration * SECOND);
}

void AudioPlayer::setupGuide() {
	dfplayer.play(Setup.guide.file_id);
	delay(Setup.guide.duration * SECOND);
}
