using System.Threading;
using CGL;

namespace HangmanScript {
    public class HangGame : IGame {
        private string wordToGuess;

        public HangGame(string word) {
            this.wordToGuess = word;
        }

        public void keyEvent(char key) {
            // ...
        }

        public bool tick() {
            // Print word
            GameConsole.clearBuffer();
            GameConsole.putString(0, 0, "The word is: " + this.wordToGuess);
            GameConsole.present();

            // Sleep and return
            Thread.Sleep(4000);
            return false;
        }
    }
}
