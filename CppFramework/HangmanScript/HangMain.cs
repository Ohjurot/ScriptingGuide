using CGL;

namespace HangmanScript {
    /// <summary>
    /// Main class
    /// </summary>
    public class HangMain {
        /// <summary>
        /// Main function
        /// </summary>
        public static IGame main(){
            string word = RandomWord.getRandomWord();
            return new HangGame(word);
        }
    }
}
