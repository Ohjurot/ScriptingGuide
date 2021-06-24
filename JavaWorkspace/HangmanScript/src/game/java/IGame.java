package game.java;

/***
 * Interface for a game
 * @author Ludwig Fuechsl
 *
 */
public interface IGame {
	/***
	 * Called when the user presses a key
	 * @param key Caps ASCII char of the pressed key
	 */
	public void keyEvent(char key);
	
	/***
	 * Called every second
	 * @return true as long as game should keep running
	 */
	public boolean tick();
}
