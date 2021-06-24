package console.game.lib;

/***
 * Console class form CGL
 * @author Ludwig Fuechsl
 *
 */
public class GameConsole {
	/***
	 * Clear the console back buffer
	 */
	public static native void clearBuffer();
	
	/***
	 * Present the console back buffer to the user
	 */
	public static native void present();
	
	/***
	 * Put a char on the console back buffer
	 * @param x X Position (Zero based index)
	 * @param y Y Position (Zero based index)
	 * @param c Char to put on the console
	 */
	public static native void putChar(int x, int y, char c);
	
	/***
	 * Put a string on the console back buffer
	 * @param x X Position (Zero based index)
	 * @param y Y Position (Zero based index)
	 * @param str String to be printed
	 * @param wrapp Indicates that the string is allowed to wrap over to the next line
	 */
	public static native void putString(int x, int y, String str, boolean wrapp);
}
