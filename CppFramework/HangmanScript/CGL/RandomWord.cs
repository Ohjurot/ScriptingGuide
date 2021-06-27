using System;
using System.Runtime.CompilerServices;

namespace CGL {
    /// <summary>
    /// Random word provider
    /// </summary>
    public class RandomWord {

        /// <summary>
        /// Get a random word
        /// </summary>
        /// <returns>Random word</returns>
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static string getRandomWord();
    }
}
