#pragma once

class IGame {
	public:
		// Key event callback
		virtual void keyEvent(char key) = 0;
		// One second tick
		virtual bool tick() = 0;
};
