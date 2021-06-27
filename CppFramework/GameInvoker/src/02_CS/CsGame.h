#pragma once

#include <WinInclude.h>
#include <IGame.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

// A C# game
class CsGame : public IGame {
	public:
		// Constructor
		CsGame();
		// Destructor
		~CsGame();

		// Interface
		void keyEvent(char key) override;
		bool tick() override;

	private:
		// Mono generic stuff
		MonoDomain* m_ptrMonoDomain = nullptr;
		MonoAssembly* m_ptrGameAssembly = nullptr;
		MonoImage* m_ptrGameAssemblyImage = nullptr;
};
