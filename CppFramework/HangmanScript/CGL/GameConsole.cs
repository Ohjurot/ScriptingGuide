using System;
using System.Runtime.CompilerServices;

namespace CGL {
    public class GameConsole {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void clearBuffer();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void present();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void putChar(UInt16 x, UInt16 y, char c);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public extern static void putString(UInt16 x, UInt16 y, string str, bool wrap = true);
    }
}
