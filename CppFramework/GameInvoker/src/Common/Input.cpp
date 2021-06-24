#include "Input.h"

char CommonInput::getInput() {
	// All keyz
	const char* keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	// Select
	char selection = ' ';
	for (const char* p = keys; *p != '\0'; p++) {
		EVAL_KEY(*p, selection);
	}

	// Return selection
	return selection;
}