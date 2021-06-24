package game.java.hangman;

import console.game.lib.GameConsole;
import game.java.IGame;

public class HangGame implements IGame {
	private String wordToGuess;
	private String inputChars = "";
	private int failures = 0;
	private int playTime = 0;
	private int leftChars;
	
	/***
	 * Hang Game constructor
	 * @param word Word to be guessed
	 */
	public HangGame(String word) {
		this.wordToGuess = word;
		leftChars = word.length();
	}
	
	@Override
	public void keyEvent(char key) {
		// Check if not already pressed
		if(inputChars.indexOf(key) == -1) {
			// Check if is failure
			if(wordToGuess.indexOf(key) == -1) {
				failures++;
			}else {
				// Decrement chars left
				for(int i = 0; i < wordToGuess.length(); i++) {
					if(wordToGuess.charAt(i) == key) {
						leftChars--;
					}
				}
			}
			
			// Redraw console text
			redraw();
			
			// Now has been pressed
			inputChars += key;
		}
	}

	@Override
	public boolean tick() {
		// Timing
		playTime++;
		
		// Check fail condition
		if(failures > 5) {
			// Output fail
			GameConsole.clearBuffer();
			GameConsole.putString(5, 5, "You have LOST!", false);
			GameConsole.putString(5, 6, "The word was: " + wordToGuess, false);
			GameConsole.present();
			
			// End game
			simpleSleep(4000);
			return false;
		}
		
		// Check win condition
		if(leftChars == 0) {
			// Output win
			GameConsole.clearBuffer();
			GameConsole.putString(5, 5, "You have WON!", false);
			GameConsole.putString(5, 6, "The word was: " + wordToGuess, false);
			GameConsole.present();
			
			// End game
			simpleSleep(4000);
			return false;
		}
		
		// Redraw
		redraw();
		
		// Continue game
		return true;
	}
	
	// Redraw console
	private void redraw() {
		// Clear
		GameConsole.clearBuffer();
		
		// Compute secs and mins
		int secs = playTime % 60;
		int mins = playTime / 60;
		
		// Output time
		GameConsole.putString(0, 0, String.format("Playtime: %02d:%02d", mins, secs), false);
		// Output failures
		GameConsole.putString(100, 0, String.format("Failures: %d / 5", failures), false);
		
		// Output chars
		for(int i = 0; i < 26; i++) {
			if(inputChars.indexOf('A' + i) == -1) {
				GameConsole.putChar(8 + (4 * i), 5, (char)('A' + i));
			}
		}
		
		// Output instruction
		GameConsole.putString(35, 10, ">>> Try guessing the next char <<<", false);
		
		// Output guessing word
		String guess = "Guessing Word: ";
		for(int i = 0; i < wordToGuess.length(); i++) {
			if(inputChars.indexOf(wordToGuess.charAt(i)) != -1) {
				guess += wordToGuess.charAt(i) + " ";
			}else {
				guess += "_ ";
			}
		}
		GameConsole.putString(10, 16, guess, false);
		
		// Present
		GameConsole.present();
	}
	
	/***
	 * Simple sleep function
	 * @param duration time to sleep
	 */
	private void simpleSleep(int duration) {
		// Sleep
		try {
			Thread.sleep(duration);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
