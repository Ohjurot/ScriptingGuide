package game.java.hangman;

import console.game.lib.GameConsole;
import game.java.IGame;

public class HangGame implements IGame {
	private String wordToGuess;
	
	/***
	 * Hang Game constructor
	 * @param word Word to be guessed
	 */
	public HangGame(String word) {
		this.wordToGuess = word;
	}
	
	@Override
	public void keyEvent(char key) {
		// TODO Implement event function
	}

	@Override
	public boolean tick() {
		// Set some text
		GameConsole.clearBuffer();
		GameConsole.putString(0, 0, wordToGuess, false);
		GameConsole.present();
		
		// Sleep
		try {
			Thread.sleep(4000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		// TODO Implement tick function
		return false;
	}

}
