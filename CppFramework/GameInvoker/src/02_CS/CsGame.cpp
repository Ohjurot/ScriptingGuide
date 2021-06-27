#include "CsGame.h"

CsGame::CsGame() {
	// Current directory as mono dir
	mono_set_dirs(".", ".");
	
	// Create mono domain
	m_ptrMonoDomain = mono_jit_init("CsGame");
	if (m_ptrMonoDomain) {
		// Load a mono assembly HangmanScript.dll
		m_ptrGameAssembly = mono_domain_assembly_open(m_ptrMonoDomain, "HangmanScript.dll");
		if (m_ptrGameAssembly) {
			// Loading mono image
			m_ptrGameAssemblyImage = mono_assembly_get_image(m_ptrGameAssembly);
			if (m_ptrGameAssemblyImage) {
				int i = 0;
			}
		}
	}
}

CsGame::~CsGame() {
	// Release the domain
	if (m_ptrMonoDomain) {
		mono_jit_cleanup(m_ptrMonoDomain);
	}
}

void CsGame::keyEvent(char key) {

}

bool CsGame::tick() {
	return false;
}
