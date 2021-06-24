package game.java.hangman;

import console.game.lib.RandomWord;
import game.java.IGame;

/***
 * Main entry point called by c++ class
 * @author Ludwig Fuechsl
 *
 */
public class HangMain {
	/***
	 * Main entry point function
	 * @return IGame that is being executed
	 */
	static IGame main() {
		String word = RandomWord.getRandomWord();
		return new HangGame(word);
	}
}
