using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using CSharpFunctionalExtensions;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

namespace Org.Prefixed.GuiBase
{
    public static class Keys
    {
        private static ModuleHandle _module;
        public enum KeyLocation
        {
            Default,
            Left,
            Right,
            NumPad
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void KeyLocation__Push(KeyLocation value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static KeyLocation KeyLocation__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (KeyLocation)ret;
        }
        public enum Key
        {
            Unknown,
            Escape,
            Tab,
            Backspace,
            Return,
            Space,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            F16,
            F17,
            F18,
            F19,
            _0,
            _1,
            _2,
            _3,
            _4,
            _5,
            _6,
            _7,
            _8,
            _9,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Control,
            Shift,
            AltOption,
            WinCommand,
            Fn,
            Insert,
            Delete,
            PageUp,
            PageDown,
            Home,
            End,
            LeftArrow,
            UpArrow,
            RightArrow,
            DownArrow,
            KP0,
            KP1,
            KP2,
            KP3,
            KP4,
            KP5,
            KP6,
            KP7,
            KP8,
            KP9,
            KPClear,
            KPEquals,
            KPDivide,
            KPMultiply,
            KPSubtract,
            KPAdd,
            KPEnter,
            KPDecimal,
            CapsLock,
            NumLock,
            ScrollLock,
            PrintScreen,
            Pause,
            Cancel,
            MediaMute,
            MediaVolumeDown,
            MediaVolumeUp,
            MediaNext,
            MediaPrev,
            MediaStop,
            MediaPlayPause
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Key__Push(Key value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Key Key__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (Key)ret;
        }

        internal static void __Init()
        {
            _module = NativeImplClient.GetModule("Keys");
            // assign module handles

            // no static init
        }

        internal static void __Shutdown()
        {
            // no static shutdown
        }
    }
}
