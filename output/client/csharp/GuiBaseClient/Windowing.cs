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
        private static InterfaceHandle _iWindowDelegate;
        private static InterfaceMethodHandle _iWindowDelegate_canClose;
        private static InterfaceMethodHandle _iWindowDelegate_closed;
        private static InterfaceMethodHandle _iWindowDelegate_destroyed;
        private static InterfaceMethodHandle _iWindowDelegate_mouseDown;
        private static InterfaceMethodHandle _iWindowDelegate_repaint;
        private static InterfaceHandle _iWindow;
        private static InterfaceMethodHandle _iWindow_show;
        private static InterfaceMethodHandle _iWindow_destroy;


        public interface IWindow : IDisposable
        {
            void Show();
            void Destroy();
        }

        internal static void IWindow__Push(IWindow thing, bool isReturn)
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

        internal static IWindow IWindow__Pop()
        {
            NativeImplClient.PopInstanceId(out var id, out var isClientId);
            if (id != 0)
            {
                if (!isClientId)
                {
                    return new ServerIWindow(id);
                }
                else
                {
                    return (IWindow) ClientObject.GetById(id);
                }
            }
            else
            {
                return null;
            }
        }

        public abstract class ClientIWindow : ClientObject, IWindow
        {
            public virtual void Dispose()
            {
                // override if necessary
            }
            public abstract void Show();
            public abstract void Destroy();
        }

        internal class ServerIWindow : ServerObject, IWindow
        {
            public ServerIWindow(int id) : base(id)
            {
            }

            public void Show()
            {
                NativeImplClient.InvokeInterfaceMethod(_iWindow_show, Id);
            }

            public void Destroy()
            {
                NativeImplClient.InvokeInterfaceMethod(_iWindow_destroy, Id);
            }

            public void Dispose()
            {
                ServerDispose();
            }
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

        public enum Modifiers
        {
            Shift,
            Control,
            Alt,
            MacControl
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Modifiers__Push(Modifiers value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Modifiers Modifiers__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (Modifiers)ret;
        }

        internal static void __ModifiersSet__Push(HashSet<Modifiers> items, bool isReturn)
        {
            var intValues = items.Select(i => (sbyte)i).ToArray();
            NativeImplClient.PushInt8Array(intValues);
        }

        internal static HashSet<Modifiers> __ModifiersSet__Pop()
        {
            var intValues = NativeImplClient.PopInt8Array();
            return intValues.Select(i => (Modifiers)i).ToHashSet();
        }



        public interface IWindowDelegate : IDisposable
        {
            bool CanClose();
            void Closed();
            void Destroyed();
            void MouseDown(int x, int y, MouseButton button, HashSet<Modifiers> modifiers);
            void Repaint(DrawContext context, int x, int y, int width, int height);
        }

        internal static void IWindowDelegate__Push(IWindowDelegate thing, bool isReturn)
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

        internal static IWindowDelegate IWindowDelegate__Pop()
        {
            NativeImplClient.PopInstanceId(out var id, out var isClientId);
            if (id != 0)
            {
                if (!isClientId)
                {
                    return new ServerIWindowDelegate(id);
                }
                else
                {
                    return (IWindowDelegate) ClientObject.GetById(id);
                }
            }
            else
            {
                return null;
            }
        }

        public abstract class ClientIWindowDelegate : ClientObject, IWindowDelegate
        {
            public virtual void Dispose()
            {
                // override if necessary
            }
            public abstract bool CanClose();
            public abstract void Closed();
            public abstract void Destroyed();
            public abstract void MouseDown(int x, int y, MouseButton button, HashSet<Modifiers> modifiers);
            public abstract void Repaint(DrawContext context, int x, int y, int width, int height);
        }

        internal class ServerIWindowDelegate : ServerObject, IWindowDelegate
        {
            public ServerIWindowDelegate(int id) : base(id)
            {
            }

            public bool CanClose()
            {
                NativeImplClient.InvokeInterfaceMethod(_iWindowDelegate_canClose, Id);
                return NativeImplClient.PopBool();
            }

            public void Closed()
            {
                NativeImplClient.InvokeInterfaceMethod(_iWindowDelegate_closed, Id);
            }

            public void Destroyed()
            {
                NativeImplClient.InvokeInterfaceMethod(_iWindowDelegate_destroyed, Id);
            }

            public void MouseDown(int x, int y, MouseButton button, HashSet<Modifiers> modifiers)
            {
                __ModifiersSet__Push(modifiers, false);
                MouseButton__Push(button);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_iWindowDelegate_mouseDown, Id);
            }

            public void Repaint(DrawContext context, int x, int y, int width, int height)
            {
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                DrawContext__Push(context, false);
                NativeImplClient.InvokeInterfaceMethod(_iWindowDelegate_repaint, Id);
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

        public struct WindowProperties
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
        internal static void WindowProperties__Push(WindowProperties value, bool isReturn)
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
        internal static WindowProperties WindowProperties__Pop()
        {
            var opts = new WindowProperties
            {
                UsedFields = (WindowProperties.Fields)NativeImplClient.PopInt32()
            };
            if (opts.UsedFields.HasFlag(WindowProperties.Fields.MinWidth))
            {
                opts.MinWidth = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowProperties.Fields.MinHeight))
            {
                opts.MinHeight = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowProperties.Fields.MaxWidth))
            {
                opts.MaxWidth = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowProperties.Fields.MaxHeight))
            {
                opts.MaxHeight = NativeImplClient.PopInt32();
            }
            if (opts.UsedFields.HasFlag(WindowProperties.Fields.Style))
            {
                opts.Style = WindowStyle__Pop();
            }
            if (opts.UsedFields.HasFlag(WindowProperties.Fields.NativeParent))
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

        public static IWindow CreateWindow(int width, int height, string title, IWindowDelegate del, WindowProperties props)
        {
            WindowProperties__Push(props, false);
            IWindowDelegate__Push(del, false);
            NativeImplClient.PushString(title);
            NativeImplClient.PushInt32(height);
            NativeImplClient.PushInt32(width);
            NativeImplClient.InvokeModuleMethod(_createWindow);
            var __ret = IWindow__Pop();
            NativeImplClient.ServerClearSafetyArea();
            return __ret;
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Windowing");

            _moduleInit = NativeImplClient.GetModuleMethod(_module, "moduleInit");
            _moduleShutdown = NativeImplClient.GetModuleMethod(_module, "moduleShutdown");
            _runloop = NativeImplClient.GetModuleMethod(_module, "runloop");
            _exitRunloop = NativeImplClient.GetModuleMethod(_module, "exitRunloop");
            _createWindow = NativeImplClient.GetModuleMethod(_module, "createWindow");

            _iWindowDelegate = NativeImplClient.GetInterface(_module, "IWindowDelegate");
            _iWindowDelegate_canClose = NativeImplClient.GetInterfaceMethod(_iWindowDelegate, "canClose");
            _iWindowDelegate_closed = NativeImplClient.GetInterfaceMethod(_iWindowDelegate, "closed");
            _iWindowDelegate_destroyed = NativeImplClient.GetInterfaceMethod(_iWindowDelegate, "destroyed");
            _iWindowDelegate_mouseDown = NativeImplClient.GetInterfaceMethod(_iWindowDelegate, "mouseDown");
            _iWindowDelegate_repaint = NativeImplClient.GetInterfaceMethod(_iWindowDelegate, "repaint");

            NativeImplClient.SetClientMethodWrapper(_iWindowDelegate_canClose, delegate(ClientObject obj)
            {
                var inst = (ClientIWindowDelegate) obj;
                NativeImplClient.PushBool(inst.CanClose());
            });

            NativeImplClient.SetClientMethodWrapper(_iWindowDelegate_closed, delegate(ClientObject obj)
            {
                var inst = (ClientIWindowDelegate) obj;
                inst.Closed();
            });

            NativeImplClient.SetClientMethodWrapper(_iWindowDelegate_destroyed, delegate(ClientObject obj)
            {
                var inst = (ClientIWindowDelegate) obj;
                inst.Destroyed();
            });

            NativeImplClient.SetClientMethodWrapper(_iWindowDelegate_mouseDown, delegate(ClientObject obj)
            {
                var inst = (ClientIWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var button = MouseButton__Pop();
                var modifiers = __ModifiersSet__Pop();
                inst.MouseDown(x, y, button, modifiers);
            });

            NativeImplClient.SetClientMethodWrapper(_iWindowDelegate_repaint, delegate(ClientObject obj)
            {
                var inst = (ClientIWindowDelegate) obj;
                var context = DrawContext__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var width = NativeImplClient.PopInt32();
                var height = NativeImplClient.PopInt32();
                inst.Repaint(context, x, y, width, height);
            });

            _iWindow = NativeImplClient.GetInterface(_module, "IWindow");
            _iWindow_show = NativeImplClient.GetInterfaceMethod(_iWindow, "show");
            _iWindow_destroy = NativeImplClient.GetInterfaceMethod(_iWindow, "destroy");

            NativeImplClient.SetClientMethodWrapper(_iWindow_show, delegate(ClientObject obj)
            {
                var inst = (ClientIWindow) obj;
                inst.Show();
            });

            NativeImplClient.SetClientMethodWrapper(_iWindow_destroy, delegate(ClientObject obj)
            {
                var inst = (ClientIWindow) obj;
                inst.Destroy();
            });

            ModuleInit();
        }

        internal static void Shutdown()
        {
            ModuleShutdown();
        }
    }
}
