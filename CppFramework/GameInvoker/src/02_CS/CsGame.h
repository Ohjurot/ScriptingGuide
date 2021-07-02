#pragma once

#include <WinInclude.h>
#include <IGame.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#include <02_CS/CsBind.h>

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

		// Mono Methods
		MonoMethod* m_ptrTickMethod = nullptr;
		MonoMethod* m_ptrKeyEventMethod = nullptr;

		// Mono Object
		MonoObject* m_ptrGameObject = nullptr;
		uint32_t m_gameObjectGCHandle = 0;
};
