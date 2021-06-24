#pragma once

class IGame {
	public:
		// Virtual destruct
		virtual ~IGame() {};

		// Key event callback
		virtual void keyEvent(char key) = 0;
		// One second tick
		virtual bool tick() = 0;
};
