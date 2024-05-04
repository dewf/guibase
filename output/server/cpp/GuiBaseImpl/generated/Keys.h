#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <optional>
#include "../support/result.h"

namespace Keys
{

    enum class KeyLocation {
        Default,
        Left,
        Right,
        NumPad
    };

    enum class Key {
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
    };
}
