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
        private static InterfaceHandle _windowDelegate;
        private static InterfaceMethodHandle _windowDelegate_buttonClicked;
        private static InterfaceMethodHandle _windowDelegate_closed;
        private static InterfaceHandle _window;
        private static InterfaceMethodHandle _window_show;
        private static InterfaceMethodHandle _window_destroy;

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


        public interface Window : IDisposable
        {
            void Show();
            void Destroy();
        }

        internal static void Window__Push(Window thing, bool isReturn)
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

        internal static Window Window__Pop()
        {
            NativeImplClient.PopInstanceId(out var id, out var isClientId);
            if (id != 0)
            {
                if (!isClientId)
                {
                    return new ServerWindow(id);
                }
                else
                {
                    return (Window) ClientObject.GetById(id);
                }
            }
            else
            {
                return null;
            }
        }

        public abstract class ClientWindow : ClientObject, Window
        {
            public virtual void Dispose()
            {
                // override if necessary
            }
            public abstract void Show();
            public abstract void Destroy();
        }

        internal class ServerWindow : ServerObject, Window
        {
            public ServerWindow(int id) : base(id)
            {
            }

            public void Show()
            {
                NativeImplClient.InvokeInterfaceMethod(_window_show, Id);
            }

            public void Destroy()
            {
                NativeImplClient.InvokeInterfaceMethod(_window_destroy, Id);
            }

            public void Dispose()
            {
                ServerDispose();
            }
        }


        public interface WindowDelegate : IDisposable
        {
            void ButtonClicked(int x, int y, MouseButton button);
            void Closed();
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
            public abstract void ButtonClicked(int x, int y, MouseButton button);
            public abstract void Closed();
        }

        internal class ServerWindowDelegate : ServerObject, WindowDelegate
        {
            public ServerWindowDelegate(int id) : base(id)
            {
            }

            public void ButtonClicked(int x, int y, MouseButton button)
            {
                MouseButton__Push(button);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_buttonClicked, Id);
            }

            public void Closed()
            {
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_closed, Id);
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

        public static Window CreateWindow(int width, int height, string title, WindowDelegate del)
        {
            WindowDelegate__Push(del, false);
            NativeImplClient.PushString(title);
            NativeImplClient.PushInt32(height);
            NativeImplClient.PushInt32(width);
            NativeImplClient.InvokeModuleMethod(_createWindow);
            var __ret = Window__Pop();
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

            _windowDelegate = NativeImplClient.GetInterface(_module, "WindowDelegate");
            _windowDelegate_buttonClicked = NativeImplClient.GetInterfaceMethod(_windowDelegate, "buttonClicked");
            _windowDelegate_closed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "closed");

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_buttonClicked, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var button = MouseButton__Pop();
                inst.ButtonClicked(x, y, button);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_closed, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                inst.Closed();
            });

            _window = NativeImplClient.GetInterface(_module, "Window");
            _window_show = NativeImplClient.GetInterfaceMethod(_window, "show");
            _window_destroy = NativeImplClient.GetInterfaceMethod(_window, "destroy");

            NativeImplClient.SetClientMethodWrapper(_window_show, delegate(ClientObject obj)
            {
                var inst = (ClientWindow) obj;
                inst.Show();
            });

            NativeImplClient.SetClientMethodWrapper(_window_destroy, delegate(ClientObject obj)
            {
                var inst = (ClientWindow) obj;
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
