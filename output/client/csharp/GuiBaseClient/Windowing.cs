using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

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

        public static IWindow CreateWindow(int width, int height, string title, IWindowDelegate del)
        {
            IWindowDelegate__Push(del, false);
            NativeImplClient.PushString(title);
            NativeImplClient.PushInt32(height);
            NativeImplClient.PushInt32(width);
            NativeImplClient.InvokeModuleMethod(_createWindow);
            var __ret = IWindow__Pop();
            NativeImplClient.ServerClearSafetyArea();
            return __ret;
        }

        public static void Init()
        {
            Debug.Assert(NativeImplClient.Init() == 0);
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

        public static void Shutdown()
        {
            ModuleShutdown();
            NativeImplClient.Shutdown();
        }

        public static void DumpTables()
        {
            NativeImplClient.DumpTables();
        }
    }
}
