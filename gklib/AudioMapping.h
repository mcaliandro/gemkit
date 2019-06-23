#ifndef _AUDIOMAPPING_H_
#define _AUDIOMAPPING_H_

#include "Arduino.h"

namespace audiomapping {
	struct AudioFile {
		uint8_t file_id;
		uint8_t duration;
	};

	struct AudioAlert {
		const AudioFile thirst = {6,5};
		const AudioFile cold = {7,6};
		const AudioFile hot = {8,4};
		const AudioFile sun = {9,5};
		const AudioFile good = {10, 6};
	} const static Alert;

	struct AudioSetup {
		const AudioFile intro = {1,15};
		const AudioFile putseeds = {2,6};
		const AudioFile putsoil = {3,5};
		const AudioFile usetank = {4,4};
		const AudioFile guide = {5,51};
	} const static Setup;
}

#endif
