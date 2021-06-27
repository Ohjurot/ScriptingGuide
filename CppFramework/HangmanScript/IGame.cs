using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HangmanScript {
    public interface IGame {
        bool tick();
        void keyEvent(char key);
    }
}
