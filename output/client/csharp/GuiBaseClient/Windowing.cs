using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

using static Org.Prefixed.GuiBase.Drawing;

namespace Org.Prefixed.GuiBase
{
    public static class Windowing
    {
        private static ModuleHandle _module;
        private static ModuleMethodHandle _moduleInit;
        private static ModuleMethodHandle _moduleShutdown;
        private static ModuleMethodHandle _runloop;
        private static ModuleMethodHandle _exitRunloop;
        private static ModuleMethodHandle _window_show;
        private static ModuleMethodHandle _window_destroy;
        private static ModuleMethodHandle _window_setMenuBar;
        private static ModuleMethodHandle _window_showContextMenu;
        private static ModuleMethodHandle _window_invalidate;
        private static ModuleMethodHandle _window_create;
        private static ModuleMethodHandle _Window_dispose;
        private static ModuleMethodHandle _icon_create;
        private static ModuleMethodHandle _Icon_dispose;
        private static ModuleMethodHandle _accelerator_create;
        private static ModuleMethodHandle _Accelerator_dispose;
        private static ModuleMethodHandle _action_create;
        private static ModuleMethodHandle _Action_dispose;
        private static ModuleMethodHandle _MenuItem_dispose;
        private static ModuleMethodHandle _menu_addAction;
        private static ModuleMethodHandle _menu_addSubmenu;
        private static ModuleMethodHandle _menu_addSeparator;
        private static ModuleMethodHandle _menu_create;
        private static ModuleMethodHandle _Menu_dispose;
        private static ModuleMethodHandle _menuBar_addMenu;
        private static ModuleMethodHandle _menuBar_create;
        private static ModuleMethodHandle _MenuBar_dispose;
        private static InterfaceHandle _windowDelegate;
        private static InterfaceMethodHandle _windowDelegate_canClose;
        private static InterfaceMethodHandle _windowDelegate_closed;
        private static InterfaceMethodHandle _windowDelegate_destroyed;
        private static InterfaceMethodHandle _windowDelegate_mouseDown;
        private static InterfaceMethodHandle _windowDelegate_mouseMove;
        private static InterfaceMethodHandle _windowDelegate_repaint;
        private static InterfaceMethodHandle _windowDelegate_resized;
        private static InterfaceMethodHandle _windowDelegate_keyDown;

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

        [Flags]
        public enum Modifiers
        {
            Shift = 1,
            Control = 2,
            Alt = 4,
            MacControl = 8
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Modifiers__Push(Modifiers value)
        {
            NativeImplClient.PushUInt32((uint)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Modifiers Modifiers__Pop()
        {
            var ret = NativeImplClient.PopUInt32();
            return (Modifiers)ret;
        }

        public class Accelerator : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Accelerator(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Accelerator__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Accelerator_dispose);
                    _disposed = true;
                }
            }
            public static Accelerator Create(Key key, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                Key__Push(key);
                NativeImplClient.InvokeModuleMethod(_accelerator_create);
                return Accelerator__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Accelerator__Push(Accelerator thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Accelerator Accelerator__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Accelerator(ptr) : null;
        }

        public delegate void MenuActionFunc();

        internal static void MenuActionFunc__Push(MenuActionFunc callback)
        {
            void CallbackWrapper()
            {
                callback();
            }
            NativeImplClient.PushClientFuncVal(CallbackWrapper, Marshal.GetFunctionPointerForDelegate(callback));
        }

        internal static MenuActionFunc MenuActionFunc__Pop()
        {
            var id = NativeImplClient.PopServerFuncValId();
            var remoteFunc = new ServerFuncVal(id);
            void Wrapper()
            {
                remoteFunc.Exec();
            }
            return Wrapper;
        }

        public class Action : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Action(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Action__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Action_dispose);
                    _disposed = true;
                }
            }
            public static Action Create(string label, Icon icon, Accelerator accel, MenuActionFunc func)
            {
                MenuActionFunc__Push(func);
                Accelerator__Push(accel);
                Icon__Push(icon);
                NativeImplClient.PushString(label);
                NativeImplClient.InvokeModuleMethod(_action_create);
                return Action__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Action__Push(Action thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Action Action__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Action(ptr) : null;
        }

        public class Icon : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Icon(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Icon__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Icon_dispose);
                    _disposed = true;
                }
            }
            public static Icon Create(string filename, int sizeToWidth)
            {
                NativeImplClient.PushInt32(sizeToWidth);
                NativeImplClient.PushString(filename);
                NativeImplClient.InvokeModuleMethod(_icon_create);
                return Icon__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Icon__Push(Icon thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Icon Icon__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Icon(ptr) : null;
        }

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

        public class Menu : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Menu(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Menu__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Menu_dispose);
                    _disposed = true;
                }
            }
            public MenuItem AddAction(Action action)
            {
                Action__Push(action);
                Menu__Push(this);
                NativeImplClient.InvokeModuleMethod(_menu_addAction);
                return MenuItem__Pop();
            }
            public MenuItem AddSubmenu(string label, Menu sub)
            {
                Menu__Push(sub);
                NativeImplClient.PushString(label);
                Menu__Push(this);
                NativeImplClient.InvokeModuleMethod(_menu_addSubmenu);
                return MenuItem__Pop();
            }
            public void AddSeparator()
            {
                Menu__Push(this);
                NativeImplClient.InvokeModuleMethod(_menu_addSeparator);
            }
            public static Menu Create()
            {
                NativeImplClient.InvokeModuleMethod(_menu_create);
                return Menu__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Menu__Push(Menu thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Menu Menu__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Menu(ptr) : null;
        }

        public class MenuBar : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal MenuBar(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    MenuBar__Push(this);
                    NativeImplClient.InvokeModuleMethod(_MenuBar_dispose);
                    _disposed = true;
                }
            }
            public MenuItem AddMenu(string label, Menu menu)
            {
                Menu__Push(menu);
                NativeImplClient.PushString(label);
                MenuBar__Push(this);
                NativeImplClient.InvokeModuleMethod(_menuBar_addMenu);
                return MenuItem__Pop();
            }
            public static MenuBar Create()
            {
                NativeImplClient.InvokeModuleMethod(_menuBar_create);
                return MenuBar__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MenuBar__Push(MenuBar thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MenuBar MenuBar__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new MenuBar(ptr) : null;
        }

        public class MenuItem : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal MenuItem(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    MenuItem__Push(this);
                    NativeImplClient.InvokeModuleMethod(_MenuItem_dispose);
                    _disposed = true;
                }
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MenuItem__Push(MenuItem thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MenuItem MenuItem__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new MenuItem(ptr) : null;
        }

        public enum MouseButton
        {
            None,
            Left,
            Middle,
            Right,
            Other
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MouseButton__Push(MouseButton value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MouseButton MouseButton__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (MouseButton)ret;
        }


        public enum WindowStyle
        {
            Default,
            Frameless,
            PluginWindow
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void WindowStyle__Push(WindowStyle value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static WindowStyle WindowStyle__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (WindowStyle)ret;
        }

        public struct WindowOptions
        {
            [Flags]
            internal enum Fields
            {
                MinWidth = 1,
                MinHeight = 2,
                MaxWidth = 4,
                MaxHeight = 8,
                Style = 16,
                NativeParent = 32
            }
            internal Fields UsedFields;

            private int _minWidth;
            public int MinWidth
            {
                set
                {
                    _minWidth = value;
                    UsedFields |= Fields.MinWidth;
                }
            }
            public bool HasMinWidth(out int value)
            {
                if (UsedFields.HasFlag(Fields.MinWidth))
                {
                    value = _minWidth;
                    return true;
                }
                value = default;
                return false;
            }
            private int _minHeight;
            public int MinHeight
            {
                set
                {
                    _minHeight = value;
                    UsedFields |= Fields.MinHeight;
                }
            }
            public bool HasMinHeight(out int value)
            {
                if (UsedFields.HasFlag(Fields.MinHeight))
                {
                    value = _minHeight;
                    return true;
                }
                value = default;
                return false;
            }
            private int _maxWidth;
            public int MaxWidth
            {
                set
                {
                    _maxWidth = value;
                    UsedFields |= Fields.MaxWidth;
                }
            }
            public bool HasMaxWidth(out int value)
            {
                if (UsedFields.HasFlag(Fields.MaxWidth))
                {
                    value = _maxWidth;
                    return true;
                }
                value = default;
                return false;
            }
            private int _maxHeight;
            public int MaxHeight
            {
                set
                {
                    _maxHeight = value;
                    UsedFields |= Fields.MaxHeight;
                }
            }
            public bool HasMaxHeight(out int value)
            {
                if (UsedFields.HasFlag(Fields.MaxHeight))
                {
                    value = _maxHeight;
                    return true;
                }
                value = default;
                return false;
            }
            private WindowStyle _style;
            public WindowStyle Style
            {
                set
                {
                    _style = value;
                    UsedFields |= Fields.Style;
                }
            }
            public bool HasStyle(out WindowStyle value)
            {
                if (UsedFields.HasFlag(Fields.Style))
                {
                    value = _style;
                    return true;
                }
                value = default;
                return false;
            }
            private IntPtr _nativeParent;
            public IntPtr NativeParent
            {
                set
                {
                    _nativeParent = value;
                    UsedFields |= Fields.NativeParent;
                }
            }
            public bool HasNativeParent(out IntPtr value)
            {
                if (UsedFields.HasFlag(Fields.NativeParent))
                {
                    value = _nativeParent;
                    return true;
                }
                value = default;
                return false;
            }
        }
        internal static void WindowOptions__Push(WindowOptions value, bool isReturn)
        {
            if (value.HasNativeParent(out var nativeParent))
            {
                NativeImplClient.PushSizeT(nativeParent);
            }
            if (value.HasStyle(out var style))
            {
                WindowStyle__Push(style);
            }
            if (value.HasMaxHeight(out var maxHeight))
            {
                NativeImplClient.PushInt32(maxHeight);
            }
            if (value.HasMaxWidth(out var maxWidth))
            {
                NativeImplClient.PushInt32(maxWidth);
            }
            if (value.HasMinHeight(out var minHeight))
            {
                NativeImplClient.PushInt32(minHeight);
            }
            if (value.HasMinWidth(out var minWidth))
            {
                NativeImplClient.PushInt32(minWidth);
            }
            NativeImplClient.PushInt32((int)value.UsedFields);
        }
        internal static WindowOptions WindowOptions__Pop()
        {
            var opts = new WindowOptions
            {
                UsedFields = (WindowOptions.Fields)NativeImplClient.PopInt32()
            };
            if (opts.UsedFields.HasFlag(WindowOptions.Fields.MinWidth))
            {
                opts.MinWidth = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowOptions.Fields.MinHeight))
            {
                opts.MinHeight = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowOptions.Fields.MaxWidth))
            {
                opts.MaxWidth = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowOptions.Fields.MaxHeight))
            {
                opts.MaxHeight = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowOptions.Fields.Style))
            {
                opts.Style = WindowStyle__Pop();
            }
            if (opts.UsedFields.HasFlag(WindowOptions.Fields.NativeParent))
            {
                opts.NativeParent = NativeImplClient.PopSizeT();
            }
            return opts;
        }

        public class Window : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Window(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Window__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Window_dispose);
                    _disposed = true;
                }
            }
            public void Show()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_show);
            }
            public void Destroy()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_destroy);
            }
            public void SetMenuBar(MenuBar menuBar)
            {
                MenuBar__Push(menuBar);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_setMenuBar);
            }
            public void ShowContextMenu(int x, int y, Menu menu)
            {
                Menu__Push(menu);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_showContextMenu);
            }
            public void Invalidate(int x, int y, int width, int height)
            {
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_invalidate);
            }
            public static Window Create(int width, int height, string title, WindowDelegate del, WindowOptions opts)
            {
                WindowOptions__Push(opts, false);
                WindowDelegate__Push(del, false);
                NativeImplClient.PushString(title);
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.InvokeModuleMethod(_window_create);
                return Window__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Window__Push(Window thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Window Window__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Window(ptr) : null;
        }


        public interface WindowDelegate : IDisposable
        {
            bool CanClose();
            void Closed();
            void Destroyed();
            void MouseDown(int x, int y, MouseButton button, Modifiers modifiers);
            void MouseMove(int x, int y, Modifiers modifiers);
            void Repaint(DrawContext context, int x, int y, int width, int height);
            void Resized(int width, int height);
            void KeyDown(Key key, Modifiers modifiers, KeyLocation location);
        }

        internal static void WindowDelegate__Push(WindowDelegate thing, bool isReturn)
        {
            if (thing != null)
            {
                ((IPushable)thing).Push(isReturn);
            }
            else
            {
                NativeImplClient.PushNull();
            }
        }

        internal static WindowDelegate WindowDelegate__Pop()
        {
            NativeImplClient.PopInstanceId(out var id, out var isClientId);
            if (id != 0)
            {
                if (!isClientId)
                {
                    return new ServerWindowDelegate(id);
                }
                else
                {
                    return (WindowDelegate) ClientObject.GetById(id);
                }
            }
            else
            {
                return null;
            }
        }

        public abstract class ClientWindowDelegate : ClientObject, WindowDelegate
        {
            public virtual void Dispose()
            {
                // override if necessary
            }
            public abstract bool CanClose();
            public abstract void Closed();
            public abstract void Destroyed();
            public abstract void MouseDown(int x, int y, MouseButton button, Modifiers modifiers);
            public abstract void MouseMove(int x, int y, Modifiers modifiers);
            public abstract void Repaint(DrawContext context, int x, int y, int width, int height);
            public abstract void Resized(int width, int height);
            public abstract void KeyDown(Key key, Modifiers modifiers, KeyLocation location);
        }

        internal class ServerWindowDelegate : ServerObject, WindowDelegate
        {
            public ServerWindowDelegate(int id) : base(id)
            {
            }

            public bool CanClose()
            {
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_canClose, Id);
                return NativeImplClient.PopBool();
            }

            public void Closed()
            {
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_closed, Id);
            }

            public void Destroyed()
            {
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_destroyed, Id);
            }

            public void MouseDown(int x, int y, MouseButton button, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                MouseButton__Push(button);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseDown, Id);
            }

            public void MouseMove(int x, int y, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseMove, Id);
            }

            public void Repaint(DrawContext context, int x, int y, int width, int height)
            {
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                DrawContext__Push(context);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_repaint, Id);
            }

            public void Resized(int width, int height)
            {
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_resized, Id);
            }

            public void KeyDown(Key key, Modifiers modifiers, KeyLocation location)
            {
                KeyLocation__Push(location);
                Modifiers__Push(modifiers);
                Key__Push(key);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_keyDown, Id);
            }

            public void Dispose()
            {
                ServerDispose();
            }
        }

        public static void ModuleInit()
        {
            NativeImplClient.InvokeModuleMethod(_moduleInit);
        }

        public static void ModuleShutdown()
        {
            NativeImplClient.InvokeModuleMethod(_moduleShutdown);
        }

        public static void Runloop()
        {
            NativeImplClient.InvokeModuleMethod(_runloop);
        }

        public static void ExitRunloop()
        {
            NativeImplClient.InvokeModuleMethod(_exitRunloop);
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Windowing");

            _moduleInit = NativeImplClient.GetModuleMethod(_module, "moduleInit");
            _moduleShutdown = NativeImplClient.GetModuleMethod(_module, "moduleShutdown");
            _runloop = NativeImplClient.GetModuleMethod(_module, "runloop");
            _exitRunloop = NativeImplClient.GetModuleMethod(_module, "exitRunloop");

            _window_show = NativeImplClient.GetModuleMethod(_module, "Window_show");
            _window_destroy = NativeImplClient.GetModuleMethod(_module, "Window_destroy");
            _window_setMenuBar = NativeImplClient.GetModuleMethod(_module, "Window_setMenuBar");
            _window_showContextMenu = NativeImplClient.GetModuleMethod(_module, "Window_showContextMenu");
            _window_invalidate = NativeImplClient.GetModuleMethod(_module, "Window_invalidate");
            _window_create = NativeImplClient.GetModuleMethod(_module, "Window_create");
            _Window_dispose = NativeImplClient.GetModuleMethod(_module, "Window_dispose");
            _icon_create = NativeImplClient.GetModuleMethod(_module, "Icon_create");
            _Icon_dispose = NativeImplClient.GetModuleMethod(_module, "Icon_dispose");
            _accelerator_create = NativeImplClient.GetModuleMethod(_module, "Accelerator_create");
            _Accelerator_dispose = NativeImplClient.GetModuleMethod(_module, "Accelerator_dispose");
            _action_create = NativeImplClient.GetModuleMethod(_module, "Action_create");
            _Action_dispose = NativeImplClient.GetModuleMethod(_module, "Action_dispose");
            _MenuItem_dispose = NativeImplClient.GetModuleMethod(_module, "MenuItem_dispose");
            _menu_addAction = NativeImplClient.GetModuleMethod(_module, "Menu_addAction");
            _menu_addSubmenu = NativeImplClient.GetModuleMethod(_module, "Menu_addSubmenu");
            _menu_addSeparator = NativeImplClient.GetModuleMethod(_module, "Menu_addSeparator");
            _menu_create = NativeImplClient.GetModuleMethod(_module, "Menu_create");
            _Menu_dispose = NativeImplClient.GetModuleMethod(_module, "Menu_dispose");
            _menuBar_addMenu = NativeImplClient.GetModuleMethod(_module, "MenuBar_addMenu");
            _menuBar_create = NativeImplClient.GetModuleMethod(_module, "MenuBar_create");
            _MenuBar_dispose = NativeImplClient.GetModuleMethod(_module, "MenuBar_dispose");

            _windowDelegate = NativeImplClient.GetInterface(_module, "WindowDelegate");
            _windowDelegate_canClose = NativeImplClient.GetInterfaceMethod(_windowDelegate, "canClose");
            _windowDelegate_closed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "closed");
            _windowDelegate_destroyed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "destroyed");
            _windowDelegate_mouseDown = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseDown");
            _windowDelegate_mouseMove = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseMove");
            _windowDelegate_repaint = NativeImplClient.GetInterfaceMethod(_windowDelegate, "repaint");
            _windowDelegate_resized = NativeImplClient.GetInterfaceMethod(_windowDelegate, "resized");
            _windowDelegate_keyDown = NativeImplClient.GetInterfaceMethod(_windowDelegate, "keyDown");

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_canClose, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                NativeImplClient.PushBool(inst.CanClose());
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_closed, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                inst.Closed();
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_destroyed, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                inst.Destroyed();
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseDown, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var button = MouseButton__Pop();
                var modifiers = Modifiers__Pop();
                inst.MouseDown(x, y, button, modifiers);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseMove, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                inst.MouseMove(x, y, modifiers);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_repaint, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var context = DrawContext__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var width = NativeImplClient.PopInt32();
                var height = NativeImplClient.PopInt32();
                inst.Repaint(context, x, y, width, height);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_resized, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var width = NativeImplClient.PopInt32();
                var height = NativeImplClient.PopInt32();
                inst.Resized(width, height);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_keyDown, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var key = Key__Pop();
                var modifiers = Modifiers__Pop();
                var location = KeyLocation__Pop();
                inst.KeyDown(key, modifiers, location);
            });

            ModuleInit();
        }

        internal static void Shutdown()
        {
            ModuleShutdown();
        }
    }
}
