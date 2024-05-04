using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using CSharpFunctionalExtensions;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

using static Org.Prefixed.GuiBase.Keys;
using static Org.Prefixed.GuiBase.Drawing;

namespace Org.Prefixed.GuiBase
{
    public static class Windowing
    {
        private static ModuleHandle _module;

        // built-in array type: string[]

        internal static void __String_Array_Array__Push(string[][] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                NativeImplClient.PushStringArray(value);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static string[][] __String_Array_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new string[count][];
            for (var i = 0; i < count; i++)
            {
                ret[i] = NativeImplClient.PopStringArray();
            }
            return ret;
        }

        internal static void __FileDialog_FilterSpec_Array__Push(FileDialog.FilterSpec[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new string[count];
            var f1Values = new string[count][];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Description;
                f1Values[i] = items[i].Extensions;
            }
            __String_Array_Array__Push(f1Values, isReturn);
            NativeImplClient.PushStringArray(f0Values);
        }

        internal static FileDialog.FilterSpec[] __FileDialog_FilterSpec_Array__Pop()
        {
            var f0Values = NativeImplClient.PopStringArray();
            var f1Values = __String_Array_Array__Pop();
            var count = f0Values.Length;
            var ret = new FileDialog.FilterSpec[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                ret[i] = new FileDialog.FilterSpec(f0, f1);
            }
            return ret;
        }

        internal static void __Native_Byte_Buffer__Push(INativeBuffer<byte> buf, bool isReturn)
        {
            if (buf != null)
            {
                ((IPushable)buf).Push(isReturn);
            }
            else
            {
                NativeImplClient.PushNull();
            }
        }

        internal static INativeBuffer<byte> __Native_Byte_Buffer__Pop()
        {
            NativeMethods.popBuffer(out var id, out var isClientId, out var bufferDescriptor);
            if (id != 0)
            {
                if (isClientId)
                {
                    return ClientBuffer<byte>.GetById(id);
                }
                else
                {
                    return new ServerBuffer<byte>(id, bufferDescriptor);
                }
            }
            else
            {
                return null;
            }
        }
        internal static ModuleMethodHandle _moduleInit;
        internal static ModuleMethodHandle _moduleShutdown;
        internal static ModuleMethodHandle _runloop;
        internal static ModuleMethodHandle _exitRunloop;
        internal static ModuleMethodHandle _icon_dispose;
        internal static ModuleMethodHandle _accelerator_dispose;
        internal static ModuleMethodHandle _menuAction_dispose;
        internal static ModuleMethodHandle _menuItem_dispose;
        internal static ModuleMethodHandle _menu_addAction;
        internal static ModuleMethodHandle _menu_addSubmenu;
        internal static ModuleMethodHandle _menu_addSeparator;
        internal static ModuleMethodHandle _menu_dispose;
        internal static ModuleMethodHandle _menuBar_addMenu;
        internal static ModuleMethodHandle _menuBar_dispose;
        internal static ModuleMethodHandle _dropData_hasFormat;
        internal static ModuleMethodHandle _dropData_getFiles;
        internal static ModuleMethodHandle _dropData_getTextUTF8;
        internal static ModuleMethodHandle _dropData_getFormat;
        internal static ModuleMethodHandle _dropData_dispose;
        internal static ModuleMethodHandle _dragData_dragExec;
        internal static ModuleMethodHandle _dragData_dispose;
        internal static ModuleMethodHandle _clipData_dispose;
        internal static ModuleMethodHandle _window_destroy;
        internal static ModuleMethodHandle _window_show;
        internal static ModuleMethodHandle _window_showRelativeTo;
        internal static ModuleMethodHandle _window_showModal;
        internal static ModuleMethodHandle _window_endModal;
        internal static ModuleMethodHandle _window_hide;
        internal static ModuleMethodHandle _window_invalidate;
        internal static ModuleMethodHandle _window_setTitle;
        internal static ModuleMethodHandle _window_focus;
        internal static ModuleMethodHandle _window_mouseGrab;
        internal static ModuleMethodHandle _window_getOSHandle;
        internal static ModuleMethodHandle _window_enableDrops;
        internal static ModuleMethodHandle _window_setMenuBar;
        internal static ModuleMethodHandle _window_showContextMenu;
        internal static ModuleMethodHandle _window_setCursor;
        internal static ModuleMethodHandle _window_dispose;
        internal static ModuleMethodHandle _timer_dispose;
        internal static InterfaceHandle _windowDelegate;
        internal static InterfaceMethodHandle _windowDelegate_canClose;
        internal static InterfaceMethodHandle _windowDelegate_closed;
        internal static InterfaceMethodHandle _windowDelegate_destroyed;
        internal static InterfaceMethodHandle _windowDelegate_mouseDown;
        internal static InterfaceMethodHandle _windowDelegate_mouseUp;
        internal static InterfaceMethodHandle _windowDelegate_mouseMove;
        internal static InterfaceMethodHandle _windowDelegate_mouseEnter;
        internal static InterfaceMethodHandle _windowDelegate_mouseLeave;
        internal static InterfaceMethodHandle _windowDelegate_repaint;
        internal static InterfaceMethodHandle _windowDelegate_moved;
        internal static InterfaceMethodHandle _windowDelegate_resized;
        internal static InterfaceMethodHandle _windowDelegate_keyDown;
        internal static InterfaceMethodHandle _windowDelegate_dropFeedback;
        internal static InterfaceMethodHandle _windowDelegate_dropLeave;
        internal static InterfaceMethodHandle _windowDelegate_dropSubmit;
        public static string KDragFormatUTF8 { get; internal set; }
        public static string KDragFormatFiles { get; internal set; }

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
        [Flags]
        public enum Modifiers
        {
            Shift = 1,
            Control = 1 << 1,
            Alt = 1 << 2,
            MacControl = 1 << 3
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
        public class Icon : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Icon(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Icon__Push(this);
                    NativeImplClient.InvokeModuleMethod(_icon_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static Icon Create(string filename, int sizeToWidth)
            {
                NativeImplClient.PushInt32(sizeToWidth);
                NativeImplClient.PushString(filename);
                NativeImplClient.InvokeModuleMethod(_create);
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
        public class Accelerator : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Accelerator(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Accelerator__Push(this);
                    NativeImplClient.InvokeModuleMethod(_accelerator_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static Accelerator Create(Key key, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                Key__Push(key);
                NativeImplClient.InvokeModuleMethod(_create);
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
        public class MenuAction : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal MenuAction(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    MenuAction__Push(this);
                    NativeImplClient.InvokeModuleMethod(_menuAction_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static MenuAction Create(string label, Icon icon, Accelerator accel, ActionFunc func)
            {
                ActionFunc__Push(func);
                Accelerator__Push(accel);
                Icon__Push(icon);
                NativeImplClient.PushString(label);
                NativeImplClient.InvokeModuleMethod(_create);
                return MenuAction__Pop();
            }
            public delegate void ActionFunc();

            internal static void ActionFunc__Push(ActionFunc callback)
            {
                void CallbackWrapper()
                {
                    callback();
                }
                NativeImplClient.PushClientFuncVal(CallbackWrapper, Marshal.GetFunctionPointerForDelegate(callback));
            }

            internal static ActionFunc ActionFunc__Pop()
            {
                var id = NativeImplClient.PopServerFuncValId();
                var remoteFunc = new ServerFuncVal(id);
                void Wrapper()
                {
                    remoteFunc.Exec();
                }
                return Wrapper;
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MenuAction__Push(MenuAction thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MenuAction MenuAction__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new MenuAction(ptr) : null;
        }
        public class MenuItem : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal MenuItem(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    MenuItem__Push(this);
                    NativeImplClient.InvokeModuleMethod(_menuItem_dispose);
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
        public class Menu : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Menu(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Menu__Push(this);
                    NativeImplClient.InvokeModuleMethod(_menu_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static Menu Create()
            {
                NativeImplClient.InvokeModuleMethod(_create);
                return Menu__Pop();
            }
            public MenuItem AddAction(MenuAction action)
            {
                MenuAction__Push(action);
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
        public class MenuBar : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal MenuBar(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    MenuBar__Push(this);
                    NativeImplClient.InvokeModuleMethod(_menuBar_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static MenuBar Create()
            {
                NativeImplClient.InvokeModuleMethod(_create);
                return MenuBar__Pop();
            }
            public void AddMenu(string label, Menu menu)
            {
                Menu__Push(menu);
                NativeImplClient.PushString(label);
                MenuBar__Push(this);
                NativeImplClient.InvokeModuleMethod(_menuBar_addMenu);
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
        public class DropData : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal DropData(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    DropData__Push(this);
                    NativeImplClient.InvokeModuleMethod(_dropData_dispose);
                    _disposed = true;
                }
            }
            internal static ExceptionHandle _badFormat;
            public class BadFormat : Exception
            {
                public readonly string Format;
                public BadFormat(string format) : base("BadFormat")
                {
                    Format = format;
                }
                internal void PushAndSet()
                {
                    NativeImplClient.PushString(Format);
                    NativeImplClient.SetException(_badFormat);
                }
                internal static void BuildAndThrow()
                {
                    var format = NativeImplClient.PopString();
                    throw new BadFormat(format);
                }
            }
            public bool HasFormat(string mimeFormat)
            {
                NativeImplClient.PushString(mimeFormat);
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethod(_dropData_hasFormat);
                return NativeImplClient.PopBool();
            }
            public string[] GetFiles() // throws BadFormat
            {
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_dropData_getFiles);
                return NativeImplClient.PopStringArray();
            }
            public string GetTextUTF8() // throws BadFormat
            {
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_dropData_getTextUTF8);
                return NativeImplClient.PopString();
            }
            public INativeBuffer<byte> GetFormat(string mimeFormat) // throws BadFormat
            {
                NativeImplClient.PushString(mimeFormat);
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_dropData_getFormat);
                return __Native_Byte_Buffer__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void DropData__Push(DropData thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static DropData DropData__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new DropData(ptr) : null;
        }
        [Flags]
        public enum DropEffect
        {
            None = 0,
            Copy = 1,
            Move = 1 << 1,
            Link = 1 << 2,
            Other = 1 << 3
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void DropEffect__Push(DropEffect value)
        {
            NativeImplClient.PushUInt32((uint)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static DropEffect DropEffect__Pop()
        {
            var ret = NativeImplClient.PopUInt32();
            return (DropEffect)ret;
        }
        public class DragData : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal DragData(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    DragData__Push(this);
                    NativeImplClient.InvokeModuleMethod(_dragData_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;
            internal static ModuleMethodHandle _renderPayload_renderUTF8;
            internal static ModuleMethodHandle _renderPayload_renderFiles;
            internal static ModuleMethodHandle _renderPayload_renderFormat;
            internal static ModuleMethodHandle _renderPayload_dispose;

            public static DragData Create(string[] supportedFormats, RenderFunc renderFunc)
            {
                RenderFunc__Push(renderFunc);
                NativeImplClient.PushStringArray(supportedFormats);
                NativeImplClient.InvokeModuleMethod(_create);
                return DragData__Pop();
            }
            public class RenderPayload : IDisposable
            {
                internal readonly IntPtr NativeHandle;
                protected bool _disposed;
                internal RenderPayload(IntPtr nativeHandle)
                {
                    NativeHandle = nativeHandle;
                }
                public virtual void Dispose()
                {
                    if (!_disposed)
                    {
                        RenderPayload__Push(this);
                        NativeImplClient.InvokeModuleMethod(_renderPayload_dispose);
                        _disposed = true;
                    }
                }
                public void RenderUTF8(string text)
                {
                    NativeImplClient.PushString(text);
                    RenderPayload__Push(this);
                    NativeImplClient.InvokeModuleMethod(_renderPayload_renderUTF8);
                }
                public void RenderFiles(string[] filenames)
                {
                    NativeImplClient.PushStringArray(filenames);
                    RenderPayload__Push(this);
                    NativeImplClient.InvokeModuleMethod(_renderPayload_renderFiles);
                }
                public void RenderFormat(string formatMIME, INativeBuffer<byte> data)
                {
                    __Native_Byte_Buffer__Push(data, false);
                    NativeImplClient.PushString(formatMIME);
                    RenderPayload__Push(this);
                    NativeImplClient.InvokeModuleMethod(_renderPayload_renderFormat);
                }
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void RenderPayload__Push(RenderPayload thing)
            {
                NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static RenderPayload RenderPayload__Pop()
            {
                var ptr = NativeImplClient.PopPtr();
                return ptr != IntPtr.Zero ? new RenderPayload(ptr) : null;
            }
            public delegate bool RenderFunc(string requestedFormat, RenderPayload payload);

            internal static void RenderFunc__Push(RenderFunc callback)
            {
                void CallbackWrapper()
                {
                    var requestedFormat = NativeImplClient.PopString();
                    var payload = RenderPayload__Pop();
                    NativeImplClient.PushBool(callback(requestedFormat, payload));
                }
                NativeImplClient.PushClientFuncVal(CallbackWrapper, Marshal.GetFunctionPointerForDelegate(callback));
            }

            internal static RenderFunc RenderFunc__Pop()
            {
                var id = NativeImplClient.PopServerFuncValId();
                var remoteFunc = new ServerFuncVal(id);
                bool Wrapper(string requestedFormat, RenderPayload payload)
                {
                    RenderPayload__Push(payload);
                    NativeImplClient.PushString(requestedFormat);
                    remoteFunc.Exec();
                    return NativeImplClient.PopBool();
                }
                return Wrapper;
            }
            public DropEffect DragExec(DropEffect canDoMask)
            {
                DropEffect__Push(canDoMask);
                DragData__Push(this);
                NativeImplClient.InvokeModuleMethod(_dragData_dragExec);
                return DropEffect__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void DragData__Push(DragData thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static DragData DragData__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new DragData(ptr) : null;
        }
        public class ClipData : DropData
        {
            internal ClipData(IntPtr nativeHandle) : base(nativeHandle)
            {
            }
            public override void Dispose()
            {
                if (!_disposed)
                {
                    ClipData__Push(this);
                    NativeImplClient.InvokeModuleMethod(_clipData_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _setClipboard;
            internal static ModuleMethodHandle _get;
            internal static ModuleMethodHandle _flushClipboard;

            public static void SetClipboard(DragData dragData)
            {
                DragData__Push(dragData);
                NativeImplClient.InvokeModuleMethod(_setClipboard);
            }

            public static ClipData Get()
            {
                NativeImplClient.InvokeModuleMethod(_get);
                return ClipData__Pop();
            }

            public static void FlushClipboard()
            {
                NativeImplClient.InvokeModuleMethod(_flushClipboard);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void ClipData__Push(ClipData thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static ClipData ClipData__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new ClipData(ptr) : null;
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

        public interface WindowDelegate : IDisposable
        {
            void IDisposable.Dispose()
            {
                // nothing by default
            }
            bool CanClose();
            void Closed();
            void Destroyed();
            void MouseDown(int x, int y, MouseButton button, Modifiers modifiers);
            void MouseUp(int x, int y, MouseButton button, Modifiers modifiers);
            void MouseMove(int x, int y, Modifiers modifiers);
            void MouseEnter(int x, int y, Modifiers modifiers);
            void MouseLeave(Modifiers modifiers);
            void Repaint(DrawContext context, int x, int y, int width, int height);
            void Moved(int x, int y);
            void Resized(int width, int height);
            void KeyDown(Key key, Modifiers modifiers, KeyLocation location);
            DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested);
            void DropLeave();
            void DropSubmit(DropData data, int x, int y, Modifiers modifiers, DropEffect effect);
        }

        private static Dictionary<WindowDelegate, IPushable> __WindowDelegateToPushable = new();
        internal class __WindowDelegateWrapper : ClientInterfaceWrapper<WindowDelegate>
        {
            public __WindowDelegateWrapper(WindowDelegate rawInterface) : base(rawInterface)
            {
            }
            protected override void ReleaseExtra()
            {
                // remove the raw interface from the lookup table, no longer needed
                __WindowDelegateToPushable.Remove(RawInterface);
            }
        }

        internal static void WindowDelegate__Push(WindowDelegate thing, bool isReturn)
        {
            if (thing != null)
            {
                if (__WindowDelegateToPushable.TryGetValue(thing, out var pushable))
                {
                    // either an already-known client thing, or a server thing
                    pushable.Push(isReturn);
                }
                else
                {
                    // as-yet-unknown client thing - wrap and add to lookup table
                    pushable = new __WindowDelegateWrapper(thing);
                    __WindowDelegateToPushable.Add(thing, pushable);
                }
                pushable.Push(isReturn);
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
                if (isClientId)
                {
                    // we must have sent it over originally, so wrapper must exist
                    var wrapper = (__WindowDelegateWrapper)ClientObject.GetById(id);
                    return wrapper.RawInterface;
                }
                else // server ID
                {
                    var thing = new ServerWindowDelegate(id);
                    // add to lookup table before returning
                    __WindowDelegateToPushable.Add(thing, thing);
                    return thing;
                }
            }
            else
            {
                return null;
            }
        }

        private class ServerWindowDelegate : ServerObject, WindowDelegate
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

            public void MouseUp(int x, int y, MouseButton button, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                MouseButton__Push(button);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseUp, Id);
            }

            public void MouseMove(int x, int y, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseMove, Id);
            }

            public void MouseEnter(int x, int y, Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseEnter, Id);
            }

            public void MouseLeave(Modifiers modifiers)
            {
                Modifiers__Push(modifiers);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_mouseLeave, Id);
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

            public void Moved(int x, int y)
            {
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_moved, Id);
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

            public DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested)
            {
                DropEffect__Push(suggested);
                Modifiers__Push(modifiers);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                DropData__Push(data);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_dropFeedback, Id);
                return DropEffect__Pop();
            }

            public void DropLeave()
            {
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_dropLeave, Id);
            }

            public void DropSubmit(DropData data, int x, int y, Modifiers modifiers, DropEffect effect)
            {
                DropEffect__Push(effect);
                Modifiers__Push(modifiers);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                DropData__Push(data);
                NativeImplClient.InvokeInterfaceMethod(_windowDelegate_dropSubmit, Id);
            }

            protected override void ReleaseExtra()
            {
                // remove from lookup table
                __WindowDelegateToPushable.Remove(this);
            }

            public void Dispose()
            {
                // will invoke ReleaseExtra() for us
                ServerDispose();
            }
        }
        public enum CursorStyle
        {
            Default,
            TextSelect,
            BusyWait,
            Cross,
            UpArrow,
            ResizeTopLeftBottomRight,
            ResizeTopRightBottomLeft,
            ResizeLeftRight,
            ResizeUpDown,
            Move,
            Unavailable,
            HandSelect,
            PointerWorking,
            HelpSelect,
            LocationSelect,
            PersonSelect,
            Handwriting
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void CursorStyle__Push(CursorStyle value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static CursorStyle CursorStyle__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (CursorStyle)ret;
        }
        public class Window : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Window(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Window__Push(this);
                    NativeImplClient.InvokeModuleMethod(_window_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;
            internal static ModuleMethodHandle _mouseUngrab;

            public static Window Create(int width, int height, string title, WindowDelegate del, Options opts)
            {
                Options__Push(opts, false);
                WindowDelegate__Push(del, false);
                NativeImplClient.PushString(title);
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.InvokeModuleMethod(_create);
                return Window__Pop();
            }

            public static void MouseUngrab()
            {
                NativeImplClient.InvokeModuleMethod(_mouseUngrab);
            }
            public enum Style
            {
                Default,
                Frameless,
                PluginWindow
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Style__Push(Style value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Style Style__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (Style)ret;
            }
            public struct Options
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
                public readonly bool HasMinWidth(out int value)
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
                public readonly bool HasMinHeight(out int value)
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
                public readonly bool HasMaxWidth(out int value)
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
                public readonly bool HasMaxHeight(out int value)
                {
                    if (UsedFields.HasFlag(Fields.MaxHeight))
                    {
                        value = _maxHeight;
                        return true;
                    }
                    value = default;
                    return false;
                }
                private Style _style;
                public Style Style
                {
                    set
                    {
                        _style = value;
                        UsedFields |= Fields.Style;
                    }
                }
                public readonly bool HasStyle(out Style value)
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
                public readonly bool HasNativeParent(out IntPtr value)
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
            internal static void Options__Push(Options value, bool isReturn)
            {
                if (value.HasNativeParent(out var nativeParent))
                {
                    NativeImplClient.PushSizeT(nativeParent);
                }
                if (value.HasStyle(out var style))
                {
                    Style__Push(style);
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
            internal static Options Options__Pop()
            {
                var opts = new Options
                {
                    UsedFields = (Options.Fields)NativeImplClient.PopInt32()
                };
                if (opts.UsedFields.HasFlag(Options.Fields.MinWidth))
                {
                    opts.MinWidth = NativeImplClient.PopInt32();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.MinHeight))
                {
                    opts.MinHeight = NativeImplClient.PopInt32();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.MaxWidth))
                {
                    opts.MaxWidth = NativeImplClient.PopInt32();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.MaxHeight))
                {
                    opts.MaxHeight = NativeImplClient.PopInt32();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.Style))
                {
                    opts.Style = Style__Pop();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.NativeParent))
                {
                    opts.NativeParent = NativeImplClient.PopSizeT();
                }
                return opts;
            }
            public void Destroy()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_destroy);
            }
            public void Show()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_show);
            }
            public void ShowRelativeTo(Window other, int x, int y, int newWidth, int newHeight)
            {
                NativeImplClient.PushInt32(newHeight);
                NativeImplClient.PushInt32(newWidth);
                NativeImplClient.PushInt32(y);
                NativeImplClient.PushInt32(x);
                Window__Push(other);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_showRelativeTo);
            }
            public void ShowModal(Window parent)
            {
                Window__Push(parent);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_showModal);
            }
            public void EndModal()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_endModal);
            }
            public void Hide()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_hide);
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
            public void SetTitle(string title)
            {
                NativeImplClient.PushString(title);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_setTitle);
            }
            public void Focus()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_focus);
            }
            public void MouseGrab()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_mouseGrab);
            }
            public IntPtr GetOSHandle()
            {
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_getOSHandle);
                return NativeImplClient.PopSizeT();
            }
            public void EnableDrops(bool enable)
            {
                NativeImplClient.PushBool(enable);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_enableDrops);
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
            public void SetCursor(CursorStyle style)
            {
                CursorStyle__Push(style);
                Window__Push(this);
                NativeImplClient.InvokeModuleMethod(_window_setCursor);
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
        public class Timer : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Timer(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Timer__Push(this);
                    NativeImplClient.InvokeModuleMethod(_timer_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static Timer Create(int msTimeout, TimerFunc func)
            {
                TimerFunc__Push(func);
                NativeImplClient.PushInt32(msTimeout);
                NativeImplClient.InvokeModuleMethod(_create);
                return Timer__Pop();
            }
            public delegate void TimerFunc(double secondsSinceLast);

            internal static void TimerFunc__Push(TimerFunc callback)
            {
                void CallbackWrapper()
                {
                    var secondsSinceLast = NativeImplClient.PopDouble();
                    callback(secondsSinceLast);
                }
                NativeImplClient.PushClientFuncVal(CallbackWrapper, Marshal.GetFunctionPointerForDelegate(callback));
            }

            internal static TimerFunc TimerFunc__Pop()
            {
                var id = NativeImplClient.PopServerFuncValId();
                var remoteFunc = new ServerFuncVal(id);
                void Wrapper(double secondsSinceLast)
                {
                    NativeImplClient.PushDouble(secondsSinceLast);
                    remoteFunc.Exec();
                }
                return Wrapper;
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Timer__Push(Timer thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Timer Timer__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Timer(ptr) : null;
        }
        public static class FileDialog
        {
            internal static ModuleMethodHandle _openFile;
            internal static ModuleMethodHandle _saveFile;

            public static DialogResult OpenFile(Options opts)
            {
                Options__Push(opts, false);
                NativeImplClient.InvokeModuleMethod(_openFile);
                return DialogResult__Pop();
            }

            public static DialogResult SaveFile(Options opts)
            {
                Options__Push(opts, false);
                NativeImplClient.InvokeModuleMethod(_saveFile);
                return DialogResult__Pop();
            }
            public enum Mode
            {
                File,
                Folder
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Mode__Push(Mode value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Mode Mode__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (Mode)ret;
            }
            public struct FilterSpec {
                public string Description;
                public string[] Extensions;
                public FilterSpec(string description, string[] extensions)
                {
                    this.Description = description;
                    this.Extensions = extensions;
                }
            }

            internal static void FilterSpec__Push(FilterSpec value, bool isReturn)
            {
                NativeImplClient.PushStringArray(value.Extensions);
                NativeImplClient.PushString(value.Description);
            }

            internal static FilterSpec FilterSpec__Pop()
            {
                var description = NativeImplClient.PopString();
                var extensions = NativeImplClient.PopStringArray();
                return new FilterSpec(description, extensions);
            }
            public struct Options {
                public Window ForWindow;
                public Mode Mode;
                public FilterSpec[] Filters;
                public bool AllowAll;
                public string DefaultExt;
                public bool AllowMultiple;
                public string SuggestedFilename;
                public Options(Window forWindow, Mode mode, FilterSpec[] filters, bool allowAll, string defaultExt, bool allowMultiple, string suggestedFilename)
                {
                    this.ForWindow = forWindow;
                    this.Mode = mode;
                    this.Filters = filters;
                    this.AllowAll = allowAll;
                    this.DefaultExt = defaultExt;
                    this.AllowMultiple = allowMultiple;
                    this.SuggestedFilename = suggestedFilename;
                }
            }

            internal static void Options__Push(Options value, bool isReturn)
            {
                NativeImplClient.PushString(value.SuggestedFilename);
                NativeImplClient.PushBool(value.AllowMultiple);
                NativeImplClient.PushString(value.DefaultExt);
                NativeImplClient.PushBool(value.AllowAll);
                __FileDialog_FilterSpec_Array__Push(value.Filters, isReturn);
                Mode__Push(value.Mode);
                Window__Push(value.ForWindow);
            }

            internal static Options Options__Pop()
            {
                var forWindow = Window__Pop();
                var mode = Mode__Pop();
                var filters = __FileDialog_FilterSpec_Array__Pop();
                var allowAll = NativeImplClient.PopBool();
                var defaultExt = NativeImplClient.PopString();
                var allowMultiple = NativeImplClient.PopBool();
                var suggestedFilename = NativeImplClient.PopString();
                return new Options(forWindow, mode, filters, allowAll, defaultExt, allowMultiple, suggestedFilename);
            }
            public struct DialogResult {
                public bool Success;
                public string[] Filenames;
                public DialogResult(bool success, string[] filenames)
                {
                    this.Success = success;
                    this.Filenames = filenames;
                }
            }

            internal static void DialogResult__Push(DialogResult value, bool isReturn)
            {
                NativeImplClient.PushStringArray(value.Filenames);
                NativeImplClient.PushBool(value.Success);
            }

            internal static DialogResult DialogResult__Pop()
            {
                var success = NativeImplClient.PopBool();
                var filenames = NativeImplClient.PopStringArray();
                return new DialogResult(success, filenames);
            }
        }
        public static class MessageBoxModal
        {
            internal static ModuleMethodHandle _show;

            public static MessageBoxResult Show(Window forWindow, Params mbParams)
            {
                Params__Push(mbParams, false);
                Window__Push(forWindow);
                NativeImplClient.InvokeModuleMethod(_show);
                return MessageBoxResult__Pop();
            }
            public enum Buttons
            {
                Default = 0,
                AbortRetryIgnore,
                CancelTryContinue,
                Ok,
                OkCancel,
                RetryCancel,
                YesNo,
                YesNoCancel
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Buttons__Push(Buttons value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Buttons Buttons__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (Buttons)ret;
            }
            public enum Icon
            {
                Default = 0,
                Information,
                Warning,
                Question,
                Error
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Icon__Push(Icon value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Icon Icon__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (Icon)ret;
            }
            public struct Params {
                public string Title;
                public string Message;
                public bool WithHelpButton;
                public Icon Icon;
                public Buttons Buttons;
                public Params(string title, string message, bool withHelpButton, Icon icon, Buttons buttons)
                {
                    this.Title = title;
                    this.Message = message;
                    this.WithHelpButton = withHelpButton;
                    this.Icon = icon;
                    this.Buttons = buttons;
                }
            }

            internal static void Params__Push(Params value, bool isReturn)
            {
                Buttons__Push(value.Buttons);
                Icon__Push(value.Icon);
                NativeImplClient.PushBool(value.WithHelpButton);
                NativeImplClient.PushString(value.Message);
                NativeImplClient.PushString(value.Title);
            }

            internal static Params Params__Pop()
            {
                var title = NativeImplClient.PopString();
                var message = NativeImplClient.PopString();
                var withHelpButton = NativeImplClient.PopBool();
                var icon = Icon__Pop();
                var buttons = Buttons__Pop();
                return new Params(title, message, withHelpButton, icon, buttons);
            }
            public enum MessageBoxResult
            {
                Abort,
                Cancel,
                Continue,
                Ignore,
                No,
                Ok,
                Retry,
                TryAgain,
                Yes
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void MessageBoxResult__Push(MessageBoxResult value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static MessageBoxResult MessageBoxResult__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (MessageBoxResult)ret;
            }
        }

        internal static void __Init()
        {
            _module = NativeImplClient.GetModule("Windowing");
            // assign module constants
            NativeImplClient.PushModuleConstants(_module);
            KDragFormatUTF8 = NativeImplClient.PopString();
            KDragFormatFiles = NativeImplClient.PopString();
            // assign module handles
            _moduleInit = NativeImplClient.GetModuleMethod(_module, "moduleInit");
            _moduleShutdown = NativeImplClient.GetModuleMethod(_module, "moduleShutdown");
            _runloop = NativeImplClient.GetModuleMethod(_module, "runloop");
            _exitRunloop = NativeImplClient.GetModuleMethod(_module, "exitRunloop");
            _icon_dispose = NativeImplClient.GetModuleMethod(_module, "Icon_dispose");
            _accelerator_dispose = NativeImplClient.GetModuleMethod(_module, "Accelerator_dispose");
            _menuAction_dispose = NativeImplClient.GetModuleMethod(_module, "MenuAction_dispose");
            _menuItem_dispose = NativeImplClient.GetModuleMethod(_module, "MenuItem_dispose");
            _menu_addAction = NativeImplClient.GetModuleMethod(_module, "Menu_addAction");
            _menu_addSubmenu = NativeImplClient.GetModuleMethod(_module, "Menu_addSubmenu");
            _menu_addSeparator = NativeImplClient.GetModuleMethod(_module, "Menu_addSeparator");
            _menu_dispose = NativeImplClient.GetModuleMethod(_module, "Menu_dispose");
            _menuBar_addMenu = NativeImplClient.GetModuleMethod(_module, "MenuBar_addMenu");
            _menuBar_dispose = NativeImplClient.GetModuleMethod(_module, "MenuBar_dispose");
            _dropData_hasFormat = NativeImplClient.GetModuleMethod(_module, "DropData_hasFormat");
            _dropData_getFiles = NativeImplClient.GetModuleMethod(_module, "DropData_getFiles");
            _dropData_getTextUTF8 = NativeImplClient.GetModuleMethod(_module, "DropData_getTextUTF8");
            _dropData_getFormat = NativeImplClient.GetModuleMethod(_module, "DropData_getFormat");
            _dropData_dispose = NativeImplClient.GetModuleMethod(_module, "DropData_dispose");
            _dragData_dragExec = NativeImplClient.GetModuleMethod(_module, "DragData_dragExec");
            _dragData_dispose = NativeImplClient.GetModuleMethod(_module, "DragData_dispose");
            _clipData_dispose = NativeImplClient.GetModuleMethod(_module, "ClipData_dispose");
            _window_destroy = NativeImplClient.GetModuleMethod(_module, "Window_destroy");
            _window_show = NativeImplClient.GetModuleMethod(_module, "Window_show");
            _window_showRelativeTo = NativeImplClient.GetModuleMethod(_module, "Window_showRelativeTo");
            _window_showModal = NativeImplClient.GetModuleMethod(_module, "Window_showModal");
            _window_endModal = NativeImplClient.GetModuleMethod(_module, "Window_endModal");
            _window_hide = NativeImplClient.GetModuleMethod(_module, "Window_hide");
            _window_invalidate = NativeImplClient.GetModuleMethod(_module, "Window_invalidate");
            _window_setTitle = NativeImplClient.GetModuleMethod(_module, "Window_setTitle");
            _window_focus = NativeImplClient.GetModuleMethod(_module, "Window_focus");
            _window_mouseGrab = NativeImplClient.GetModuleMethod(_module, "Window_mouseGrab");
            _window_getOSHandle = NativeImplClient.GetModuleMethod(_module, "Window_getOSHandle");
            _window_enableDrops = NativeImplClient.GetModuleMethod(_module, "Window_enableDrops");
            _window_setMenuBar = NativeImplClient.GetModuleMethod(_module, "Window_setMenuBar");
            _window_showContextMenu = NativeImplClient.GetModuleMethod(_module, "Window_showContextMenu");
            _window_setCursor = NativeImplClient.GetModuleMethod(_module, "Window_setCursor");
            _window_dispose = NativeImplClient.GetModuleMethod(_module, "Window_dispose");
            _timer_dispose = NativeImplClient.GetModuleMethod(_module, "Timer_dispose");
            _windowDelegate = NativeImplClient.GetInterface(_module, "WindowDelegate");
            _windowDelegate_canClose = NativeImplClient.GetInterfaceMethod(_windowDelegate, "canClose");
            _windowDelegate_closed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "closed");
            _windowDelegate_destroyed = NativeImplClient.GetInterfaceMethod(_windowDelegate, "destroyed");
            _windowDelegate_mouseDown = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseDown");
            _windowDelegate_mouseUp = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseUp");
            _windowDelegate_mouseMove = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseMove");
            _windowDelegate_mouseEnter = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseEnter");
            _windowDelegate_mouseLeave = NativeImplClient.GetInterfaceMethod(_windowDelegate, "mouseLeave");
            _windowDelegate_repaint = NativeImplClient.GetInterfaceMethod(_windowDelegate, "repaint");
            _windowDelegate_moved = NativeImplClient.GetInterfaceMethod(_windowDelegate, "moved");
            _windowDelegate_resized = NativeImplClient.GetInterfaceMethod(_windowDelegate, "resized");
            _windowDelegate_keyDown = NativeImplClient.GetInterfaceMethod(_windowDelegate, "keyDown");
            _windowDelegate_dropFeedback = NativeImplClient.GetInterfaceMethod(_windowDelegate, "dropFeedback");
            _windowDelegate_dropLeave = NativeImplClient.GetInterfaceMethod(_windowDelegate, "dropLeave");
            _windowDelegate_dropSubmit = NativeImplClient.GetInterfaceMethod(_windowDelegate, "dropSubmit");
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_canClose, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                NativeImplClient.PushBool(inst.CanClose());
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_closed, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                inst.Closed();
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_destroyed, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                inst.Destroyed();
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseDown, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var button = MouseButton__Pop();
                var modifiers = Modifiers__Pop();
                inst.MouseDown(x, y, button, modifiers);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseUp, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var button = MouseButton__Pop();
                var modifiers = Modifiers__Pop();
                inst.MouseUp(x, y, button, modifiers);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseMove, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                inst.MouseMove(x, y, modifiers);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseEnter, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                inst.MouseEnter(x, y, modifiers);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseLeave, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var modifiers = Modifiers__Pop();
                inst.MouseLeave(modifiers);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_repaint, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var context = DrawContext__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var width = NativeImplClient.PopInt32();
                var height = NativeImplClient.PopInt32();
                inst.Repaint(context, x, y, width, height);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_moved, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                inst.Moved(x, y);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_resized, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var width = NativeImplClient.PopInt32();
                var height = NativeImplClient.PopInt32();
                inst.Resized(width, height);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_keyDown, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var key = Key__Pop();
                var modifiers = Modifiers__Pop();
                var location = KeyLocation__Pop();
                inst.KeyDown(key, modifiers, location);
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_dropFeedback, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var data = DropData__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                var suggested = DropEffect__Pop();
                DropEffect__Push(inst.DropFeedback(data, x, y, modifiers, suggested));
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_dropLeave, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                inst.DropLeave();
            });
            NativeImplClient.SetClientMethodWrapper(_windowDelegate_dropSubmit, delegate(ClientObject obj)
            {
                var inst = ((__WindowDelegateWrapper)obj).RawInterface;
                var data = DropData__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                var effect = DropEffect__Pop();
                inst.DropSubmit(data, x, y, modifiers, effect);
            });
            Icon._create = NativeImplClient.GetModuleMethod(_module, "Icon.create");
            Accelerator._create = NativeImplClient.GetModuleMethod(_module, "Accelerator.create");
            MenuAction._create = NativeImplClient.GetModuleMethod(_module, "MenuAction.create");
            Menu._create = NativeImplClient.GetModuleMethod(_module, "Menu.create");
            MenuBar._create = NativeImplClient.GetModuleMethod(_module, "MenuBar.create");
            DropData._badFormat = NativeImplClient.GetException(_module, "DropData.BadFormat");
            NativeImplClient.SetExceptionBuilder(DropData._badFormat, DropData.BadFormat.BuildAndThrow);
            DragData._create = NativeImplClient.GetModuleMethod(_module, "DragData.create");
            DragData._renderPayload_renderUTF8 = NativeImplClient.GetModuleMethod(_module, "DragData.RenderPayload_renderUTF8");
            DragData._renderPayload_renderFiles = NativeImplClient.GetModuleMethod(_module, "DragData.RenderPayload_renderFiles");
            DragData._renderPayload_renderFormat = NativeImplClient.GetModuleMethod(_module, "DragData.RenderPayload_renderFormat");
            DragData._renderPayload_dispose = NativeImplClient.GetModuleMethod(_module, "DragData.RenderPayload_dispose");
            ClipData._setClipboard = NativeImplClient.GetModuleMethod(_module, "ClipData.setClipboard");
            ClipData._get = NativeImplClient.GetModuleMethod(_module, "ClipData.get");
            ClipData._flushClipboard = NativeImplClient.GetModuleMethod(_module, "ClipData.flushClipboard");
            Window._create = NativeImplClient.GetModuleMethod(_module, "Window.create");
            Window._mouseUngrab = NativeImplClient.GetModuleMethod(_module, "Window.mouseUngrab");
            Timer._create = NativeImplClient.GetModuleMethod(_module, "Timer.create");
            FileDialog._openFile = NativeImplClient.GetModuleMethod(_module, "FileDialog.openFile");
            FileDialog._saveFile = NativeImplClient.GetModuleMethod(_module, "FileDialog.saveFile");
            MessageBoxModal._show = NativeImplClient.GetModuleMethod(_module, "MessageBoxModal.show");

            ModuleInit();
        }

        internal static void __Shutdown()
        {
            ModuleShutdown();
        }
    }
}
