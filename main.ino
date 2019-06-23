#include "BluetoothSerial.h"
#include "gklib/GemKit.h"


BluetoothSerial BT; // @suppress("Abstract class cannot be instantiated")
GemKit Gemma;


const static int ESP_BAUD_RATE = 115200;
const static int LOOP_PAUSE = 1000;
const static uint8_t ALERT_LED_PIN = 14;
const static uint8_t OK_LED_PIN = 12;
const static uint8_t SPEAKER_BTN_PIN = 13;

int speakerActive;

void setup() {
	delay(LOOP_PAUSE);
	Serial.begin(ESP_BAUD_RATE);
	Serial.print("Starting bluetooth... ");
	if (!BT.begin("GEMMA")) while (true);
	Serial.println("DONE");
	Serial.println("Starting gemma environment...");
	if (! Gemma.init()) while (true);
	Serial.println("DONE");
	pinMode(ALERT_LED_PIN, OUTPUT);
	pinMode(OK_LED_PIN, OUTPUT);
	pinMode(SPEAKER_BTN_PIN, INPUT);
	digitalWrite(ALERT_LED_PIN, LOW);
	digitalWrite(OK_LED_PIN, LOW);
	Serial.println("Waiting for requests...");
}

void loop() {
	speakerActive = digitalRead(SPEAKER_BTN_PIN);
	if (BT.available()) {
		String request = BT.readString();
		Serial.println("Request: " + request);
		if (request.equals(Request.intro)) {
			Gemma.playSetupIntro();
			Serial.println(request + "DONE");
			BT.println("ready");
		} else if (request.equals(Request.putseeds)) {
			Gemma.playSetupPutSeeds();
			Serial.println(request + " DONE");
			BT.println("ready");
		} else if (request.equals(Request.putsoil)) {
			Gemma.playSetupPutSoil();
			Serial.println(request + " DONE");
			BT.println("ready");
		} else if (request.equals(Request.usetank)) {
			Gemma.playSetupUseTank();
			Serial.println(request + " DONE");
			BT.println("ready");
		} else if (request.equals(Request.guide)) {
			Gemma.playSetupGuide();
			Serial.println(request + " DONE");
			BT.println("ready");
		} else if (request.equals(Request.check)) {
			Gemma.checkSensors();
			Serial.println(request + " " + Gemma.showStatus());
			BT.println(Gemma.showStatus());
			if (Gemma.alert()) {
				Serial.println("Sensors status: ALERT");
				digitalWrite(OK_LED_PIN, LOW);
				digitalWrite(ALERT_LED_PIN, HIGH);
				if (speakerActive == HIGH) {
					Gemma.playAlert();
				}
			} else {
				Serial.println("Sensors status: OK");
				digitalWrite(ALERT_LED_PIN, LOW);
				digitalWrite(OK_LED_PIN, HIGH);
				Gemma.playGoodState();
			}
		} else {
			Serial.println("Invalid request " + request);
			BT.println("invalid_request");
		}
	}
	delay(LOOP_PAUSE);
}
