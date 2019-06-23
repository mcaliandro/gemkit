#ifndef _BTREQUEST_H_
#define _BTREQUEST_H_

#include "Arduino.h"

struct Requests {
	const String intro = "intro";
	const String putseeds = "put_seeds";
	const String putsoil = "put_soil";
	const String usetank = "use_tank";
	const String guide = "guide";
	const String check = "check";
} const static Request;


#endif
