using System.Threading;
using CGL;

namespace HangmanScript {
    public class HangGame : IGame {
        private string wordToGuess;
        private bool exit = false;

        public HangGame(string word) {
            this.wordToGuess = word;

            // Print word
            GameConsole.clearBuffer();
            GameConsole.putString(0, 0, "The word is: " + this.wordToGuess);
            GameConsole.present();
        }

        public void keyEvent(char key) {
            // Check if exit
            if(key == 'X') {
                exit = true;
            }
        }

        public bool tick() {
            // Sleep and return
            return !exit;
        }
    }
}
