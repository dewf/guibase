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
        private static ModuleMethodHandle _createWindow;
        private static ModuleMethodHandle _createIcon;
        private static ModuleMethodHandle _createAccelerator;
        private static ModuleMethodHandle _createAction;
        private static ModuleMethodHandle _createMenu;
        private static ModuleMethodHandle _createMenuBar;
        private static ModuleMethodHandle _window_show;
        private static ModuleMethodHandle _window_destroy;
        private static ModuleMethodHandle _window_setMenuBar;
        private static ModuleMethodHandle _window_showContextMenu;
        private static ModuleMethodHandle _menu_addAction;
        private static ModuleMethodHandle _menu_addSubmenu;
        private static ModuleMethodHandle _menu_addSeparator;
        private static ModuleMethodHandle _menuBar_addMenu;
        private static InterfaceHandle _windowDelegate;
        private static InterfaceMethodHandle _windowDelegate_canClose;
        private static InterfaceMethodHandle _windowDelegate_closed;
        private static InterfaceMethodHandle _windowDelegate_destroyed;
        private static InterfaceMethodHandle _windowDelegate_mouseDown;
        private static InterfaceMethodHandle _windowDelegate_repaint;
        private static InterfaceMethodHandle _windowDelegate_resized;
        private static InterfaceMethodHandle _windowDelegate_performAction;

        public class Accelerator
        {
            internal readonly IntPtr NativeHandle;
            internal Accelerator(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
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

        public class Action
        {
            internal readonly IntPtr NativeHandle;
            internal Action(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
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

        public class Icon
        {
            internal readonly IntPtr NativeHandle;
            internal Icon(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
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




        public class Menu
        {
            internal readonly IntPtr NativeHandle;
            internal Menu(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
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

        public class MenuBar
        {
            internal readonly IntPtr NativeHandle;
            internal MenuBar(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }

            public MenuItem AddMenu(string label, Menu menu)
            {
                Menu__Push(menu);
                NativeImplClient.PushString(label);
                MenuBar__Push(this);
                NativeImplClient.InvokeModuleMethod(_menuBar_addMenu);
            return MenuItem__Pop();
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

        public class MenuItem
        {
            internal readonly IntPtr NativeHandle;
            internal MenuItem(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
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

        public enum Modifier
        {
            Shift,
            Control,
            Alt,
            MacControl
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Modifier__Push(Modifier value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Modifier Modifier__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (Modifier)ret;
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


        public class Window
        {
            internal readonly IntPtr NativeHandle;
            internal Window(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
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

        internal static void __ModifierSet__Push(HashSet<Modifier> items, bool isReturn)
        {
            var intValues = items.Select(i => (sbyte)i).ToArray();
            NativeImplClient.PushInt8Array(intValues);
        }

        internal static HashSet<Modifier> __ModifierSet__Pop()
        {
            var intValues = NativeImplClient.PopInt8Array();
            return intValues.Select(i => (Modifier)i).ToHashSet();
        }


        public interface WindowDelegate : IDisposable
        {
            bool CanClose();
            void Closed();
            void Destroyed();
            void MouseDown(int x, int y, MouseButton button, HashSet<Modifier> modifiers);
            void Repaint(DrawContext context, int x, int y, int width, int height);
            void Resized(int width, int height);
            void PerformAction(int id, Action action);
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
            public abstract void MouseDown(int x, int y, MouseButton button, HashSet<Modifier> modifiers);
            public abstract void Repaint(DrawContext context, int x, int y, int width, int height);
            public abstract void Resized(int width, int height);
            public abstract void PerformAction(int id, Action action);
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

            public void MouseDown(int x, int y, MouseButton button, HashSet<Modifier> modifiers)
            {
                __ModifierSet__Push(modifiers, false);
                MouseButton__Push(button);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseDown, Id);
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

            public void PerformAction(int id, Action action)
            {
                Action__Push(action);
                NativeImplClient.PushInt32(id);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_performAction, Id);
            }

            public void Dispose()
            {
                ServerDispose();
            }
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

        public static Window CreateWindow(int width, int height, string title, WindowDelegate del, WindowOptions opts)
        {
            WindowOptions__Push(opts, false);
            WindowDelegate__Push(del, false);
            NativeImplClient.PushString(title);
            NativeImplClient.PushInt32(height);
            NativeImplClient.PushInt32(width);
            NativeImplClient.InvokeModuleMethod(_createWindow);
            return Window__Pop();
        }

        public static Icon CreateIcon(string filename, int sizeToWidth)
        {
            NativeImplClient.PushInt32(sizeToWidth);
            NativeImplClient.PushString(filename);
            NativeImplClient.InvokeModuleMethod(_createIcon);
            return Icon__Pop();
        }

        public static Accelerator CreateAccelerator(Key key, HashSet<Modifier> modifiers)
        {
            __ModifierSet__Push(modifiers, false);
            Key__Push(key);
            NativeImplClient.InvokeModuleMethod(_createAccelerator);
            return Accelerator__Pop();
        }

        public static Action CreateAction(int id, string label, Icon icon, Accelerator accel)
        {
            Accelerator__Push(accel);
            Icon__Push(icon);
            NativeImplClient.PushString(label);
            NativeImplClient.PushInt32(id);
            NativeImplClient.InvokeModuleMethod(_createAction);
            return Action__Pop();
        }

        public static Menu CreateMenu()
        {
            NativeImplClient.InvokeModuleMethod(_createMenu);
            return Menu__Pop();
        }

        public static MenuBar CreateMenuBar()
        {
            NativeImplClient.InvokeModuleMethod(_createMenuBar);
            return MenuBar__Pop();
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Windowing");

            _moduleInit = NativeImplClient.GetModuleMethod(_module, "moduleInit");
            _moduleShutdown = NativeImplClient.GetModuleMethod(_module, "moduleShutdown");
            _runloop = NativeImplClient.GetModuleMethod(_module, "runloop");
            _exitRunloop = NativeImplClient.GetModuleMethod(_module, "exitRunloop");
            _createWindow = NativeImplClient.GetModuleMethod(_module, "createWindow");
            _createIcon = NativeImplClient.GetModuleMethod(_module, "createIcon");
            _createAccelerator = NativeImplClient.GetModuleMethod(_module, "createAccelerator");
            _createAction = NativeImplClient.GetModuleMethod(_module, "createAction");
            _createMenu = NativeImplClient.GetModuleMethod(_module, "createMenu");
            _createMenuBar = NativeImplClient.GetModuleMethod(_module, "createMenuBar");

            _window_show = NativeImplClient.GetModuleMethod(_module, "Window_show");
            _window_destroy = NativeImplClient.GetModuleMethod(_module, "Window_destroy");
            _window_setMenuBar = NativeImplClient.GetModuleMethod(_module, "Window_setMenuBar");
            _window_showContextMenu = NativeImplClient.GetModuleMethod(_module, "Window_showContextMenu");
            _menu_addAction = NativeImplClient.GetModuleMethod(_module, "Menu_addAction");
            _menu_addSubmenu = NativeImplClient.GetModuleMethod(_module, "Menu_addSubmenu");
            _menu_addSeparator = NativeImplClient.GetModuleMethod(_module, "Menu_addSeparator");
            _menuBar_addMenu = NativeImplClient.GetModuleMethod(_module, "MenuBar_addMenu");

            _windowDelegate = NativeImplClient.GetInterface(_module, "WindowDelegate");
            _windowDelegate_canClose = NativeImplClient.GetInterfaceMethod(_windowDelegate, "canClose");
            _windowDelegate_closed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "closed");
            _windowDelegate_destroyed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "destroyed");
            _windowDelegate_mouseDown = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseDown");
            _windowDelegate_repaint = NativeImplClient.GetInterfaceMethod(_windowDelegate, "repaint");
            _windowDelegate_resized = NativeImplClient.GetInterfaceMethod(_windowDelegate, "resized");
            _windowDelegate_performAction = NativeImplClient.GetInterfaceMethod(_windowDelegate, "performAction");

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
                var modifiers = __ModifierSet__Pop();
                inst.MouseDown(x, y, button, modifiers);
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

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_performAction, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var id = NativeImplClient.PopInt32();
                var action = Action__Pop();
                inst.PerformAction(id, action);
            });

            ModuleInit();
        }

        internal static void Shutdown()
        {
            ModuleShutdown();
        }
    }
}
