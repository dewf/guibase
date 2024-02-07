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
        private static ModuleMethodHandle _dropData_hasFormat;
        private static ModuleMethodHandle _dropData_getFiles;
        private static ModuleMethodHandle _dropData_getTextUTF8;
        private static ModuleMethodHandle _dropData_getFormat;
        private static ModuleMethodHandle _DropData_dispose;
        private static ModuleMethodHandle _dragRenderPayload_renderUTF8;
        private static ModuleMethodHandle _dragRenderPayload_renderFiles;
        private static ModuleMethodHandle _dragRenderPayload_renderFormat;
        private static ModuleMethodHandle _DragRenderPayload_dispose;
        private static ModuleMethodHandle _dragData_dragExec;
        private static ModuleMethodHandle _dragData_create;
        private static ModuleMethodHandle _DragData_dispose;
        private static ModuleMethodHandle _window_destroy;
        private static ModuleMethodHandle _window_show;
        private static ModuleMethodHandle _window_showRelativeTo;
        private static ModuleMethodHandle _window_showModal;
        private static ModuleMethodHandle _window_endModal;
        private static ModuleMethodHandle _window_hide;
        private static ModuleMethodHandle _window_invalidate;
        private static ModuleMethodHandle _window_setTitle;
        private static ModuleMethodHandle _window_focus;
        private static ModuleMethodHandle _window_mouseGrab;
        private static ModuleMethodHandle _window_getOSHandle;
        private static ModuleMethodHandle _window_enableDrops;
        private static ModuleMethodHandle _window_setMenuBar;
        private static ModuleMethodHandle _window_showContextMenu;
        private static ModuleMethodHandle _window_setCursor;
        private static ModuleMethodHandle _window_create;
        private static ModuleMethodHandle _window_mouseUngrab;
        private static ModuleMethodHandle _Window_dispose;
        private static ModuleMethodHandle _timer_create;
        private static ModuleMethodHandle _Timer_dispose;
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
        private static ModuleMethodHandle _clipData_setClipboard;
        private static ModuleMethodHandle _clipData_get;
        private static ModuleMethodHandle _clipData_flushClipboard;
        private static ModuleMethodHandle _ClipData_dispose;
        private static ModuleMethodHandle _fileDialog_openFile;
        private static ModuleMethodHandle _fileDialog_saveFile;
        private static ModuleMethodHandle _FileDialog_dispose;
        private static ModuleMethodHandle _messageBoxModal_show;
        private static ModuleMethodHandle _MessageBoxModal_dispose;
        private static InterfaceHandle _windowDelegate;
        private static InterfaceMethodHandle _windowDelegate_canClose;
        private static InterfaceMethodHandle _windowDelegate_closed;
        private static InterfaceMethodHandle _windowDelegate_destroyed;
        private static InterfaceMethodHandle _windowDelegate_mouseDown;
        private static InterfaceMethodHandle _windowDelegate_mouseUp;
        private static InterfaceMethodHandle _windowDelegate_mouseMove;
        private static InterfaceMethodHandle _windowDelegate_mouseEnter;
        private static InterfaceMethodHandle _windowDelegate_mouseLeave;
        private static InterfaceMethodHandle _windowDelegate_repaint;
        private static InterfaceMethodHandle _windowDelegate_moved;
        private static InterfaceMethodHandle _windowDelegate_resized;
        private static InterfaceMethodHandle _windowDelegate_keyDown;
        private static InterfaceMethodHandle _windowDelegate_dropFeedback;
        private static InterfaceMethodHandle _windowDelegate_dropLeave;
        private static InterfaceMethodHandle _windowDelegate_dropSubmit;
        private static ExceptionHandle _dropDataBadFormat;
        public static string KDragFormatUTF8 { get; private set; }
        public static string KDragFormatFiles { get; private set; }

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
            protected bool _disposed;
            internal Action(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
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
                    NativeImplClient.InvokeModuleMethod(_ClipData_dispose);
                    _disposed = true;
                }
            }
            public static void SetClipboard(DragData dragData)
            {
                DragData__Push(dragData);
                NativeImplClient.InvokeModuleMethod(_clipData_setClipboard);
            }
            public static ClipData Get()
            {
                NativeImplClient.InvokeModuleMethod(_clipData_get);
                return ClipData__Pop();
            }
            public static void FlushClipboard()
            {
                NativeImplClient.InvokeModuleMethod(_clipData_flushClipboard);
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

        // built-in array type: string[]

        public delegate bool DragRenderFunc(string requestedFormat, DragRenderPayload payload);

        internal static void DragRenderFunc__Push(DragRenderFunc callback)
        {
            void CallbackWrapper()
            {
                var requestedFormat = NativeImplClient.PopString();
                var payload = DragRenderPayload__Pop();
                NativeImplClient.PushBool(callback(requestedFormat, payload));
            }
            NativeImplClient.PushClientFuncVal(CallbackWrapper, Marshal.GetFunctionPointerForDelegate(callback));
        }

        internal static DragRenderFunc DragRenderFunc__Pop()
        {
            var id = NativeImplClient.PopServerFuncValId();
            var remoteFunc = new ServerFuncVal(id);
            bool Wrapper(string requestedFormat, DragRenderPayload payload)
            {
                DragRenderPayload__Push(payload);
                NativeImplClient.PushString(requestedFormat);
                remoteFunc.Exec();
                return NativeImplClient.PopBool();
            }
            return Wrapper;
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
                    NativeImplClient.InvokeModuleMethod(_DragData_dispose);
                    _disposed = true;
                }
            }
            public DropEffect DragExec(DropEffect canDoMask)
            {
                DropEffect__Push(canDoMask);
                DragData__Push(this);
                NativeImplClient.InvokeModuleMethod(_dragData_dragExec);
                return DropEffect__Pop();
            }
            public static DragData Create(string[] supportedFormats, DragRenderFunc renderFunc)
            {
                DragRenderFunc__Push(renderFunc);
                NativeImplClient.PushStringArray(supportedFormats);
                NativeImplClient.InvokeModuleMethod(_dragData_create);
                return DragData__Pop();
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

        public class DragRenderPayload : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal DragRenderPayload(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    DragRenderPayload__Push(this);
                    NativeImplClient.InvokeModuleMethod(_DragRenderPayload_dispose);
                    _disposed = true;
                }
            }
            public void RenderUTF8(string text)
            {
                NativeImplClient.PushString(text);
                DragRenderPayload__Push(this);
                NativeImplClient.InvokeModuleMethod(_dragRenderPayload_renderUTF8);
            }
            public void RenderFiles(string[] filenames)
            {
                NativeImplClient.PushStringArray(filenames);
                DragRenderPayload__Push(this);
                NativeImplClient.InvokeModuleMethod(_dragRenderPayload_renderFiles);
            }
            public void RenderFormat(string formatMIME, INativeBuffer<byte> data)
            {
                __Native_Byte_Buffer__Push(data, false);
                NativeImplClient.PushString(formatMIME);
                DragRenderPayload__Push(this);
                NativeImplClient.InvokeModuleMethod(_dragRenderPayload_renderFormat);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void DragRenderPayload__Push(DragRenderPayload thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static DragRenderPayload DragRenderPayload__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new DragRenderPayload(ptr) : null;
        }

        public class DropDataBadFormat : Exception
        {
            public readonly string Format;
            public DropDataBadFormat(string format) : base("DropDataBadFormat")
            {
                Format = format;
            }
            internal void PushAndSet()
            {
                NativeImplClient.PushString(Format);
                NativeImplClient.SetException(_dropDataBadFormat);
            }
            internal static void BuildAndThrow()
            {
                var format = NativeImplClient.PopString();
                throw new DropDataBadFormat(format);
            }
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
                    NativeImplClient.InvokeModuleMethod(_DropData_dispose);
                    _disposed = true;
                }
            }
            public bool HasFormat(string mimeFormat)
            {
                NativeImplClient.PushString(mimeFormat);
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethod(_dropData_hasFormat);
                return NativeImplClient.PopBool();
            }
            public string[] GetFiles() // throws DropDataBadFormat
            {
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_dropData_getFiles);
                return NativeImplClient.PopStringArray();
            }
            public string GetTextUTF8() // throws DropDataBadFormat
            {
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_dropData_getTextUTF8);
                return NativeImplClient.PopString();
            }
            public INativeBuffer<byte> GetFormat(string mimeFormat) // throws DropDataBadFormat
            {
                NativeImplClient.PushString(mimeFormat);
                DropData__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_dropData_getFormat);
                var __ret = __Native_Byte_Buffer__Pop();
                NativeImplClient.ServerClearSafetyArea();
                return __ret;
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

        public struct FileDialogResult {
            public bool Success;
            public string[] Filenames;
            public FileDialogResult(bool success, string[] filenames)
            {
                this.Success = success;
                this.Filenames = filenames;
            }
        }

        internal static void FileDialogResult__Push(FileDialogResult value, bool isReturn)
        {
            NativeImplClient.PushStringArray(value.Filenames);
            NativeImplClient.PushBool(value.Success);
        }

        internal static FileDialogResult FileDialogResult__Pop()
        {
            var success = NativeImplClient.PopBool();
            var filenames = NativeImplClient.PopStringArray();
            return new FileDialogResult(success, filenames);
        }

        public enum FileDialogMode
        {
            File,
            Folder
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void FileDialogMode__Push(FileDialogMode value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static FileDialogMode FileDialogMode__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (FileDialogMode)ret;
        }

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

        public struct FileDialogFilterSpec {
            public string Description;
            public string[] Extensions;
            public FileDialogFilterSpec(string description, string[] extensions)
            {
                this.Description = description;
                this.Extensions = extensions;
            }
        }

        internal static void FileDialogFilterSpec__Push(FileDialogFilterSpec value, bool isReturn)
        {
            NativeImplClient.PushStringArray(value.Extensions);
            NativeImplClient.PushString(value.Description);
        }

        internal static FileDialogFilterSpec FileDialogFilterSpec__Pop()
        {
            var description = NativeImplClient.PopString();
            var extensions = NativeImplClient.PopStringArray();
            return new FileDialogFilterSpec(description, extensions);
        }

        internal static void __FileDialogFilterSpec_Array__Push(FileDialogFilterSpec[] items, bool isReturn)
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

        internal static FileDialogFilterSpec[] __FileDialogFilterSpec_Array__Pop()
        {
            var f0Values = NativeImplClient.PopStringArray();
            var f1Values = __String_Array_Array__Pop();
            var count = f0Values.Length;
            var ret = new FileDialogFilterSpec[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                ret[i] = new FileDialogFilterSpec(f0, f1);
            }
            return ret;
        }

        public struct FileDialogOptions {
            public Window ForWindow;
            public FileDialogMode Mode;
            public FileDialogFilterSpec[] Filters;
            public bool AllowAll;
            public string DefaultExt;
            public bool AllowMultiple;
            public string SuggestedFilename;
            public FileDialogOptions(Window forWindow, FileDialogMode mode, FileDialogFilterSpec[] filters, bool allowAll, string defaultExt, bool allowMultiple, string suggestedFilename)
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

        internal static void FileDialogOptions__Push(FileDialogOptions value, bool isReturn)
        {
            NativeImplClient.PushString(value.SuggestedFilename);
            NativeImplClient.PushBool(value.AllowMultiple);
            NativeImplClient.PushString(value.DefaultExt);
            NativeImplClient.PushBool(value.AllowAll);
            __FileDialogFilterSpec_Array__Push(value.Filters, isReturn);
            FileDialogMode__Push(value.Mode);
            Window__Push(value.ForWindow);
        }

        internal static FileDialogOptions FileDialogOptions__Pop()
        {
            var forWindow = Window__Pop();
            var mode = FileDialogMode__Pop();
            var filters = __FileDialogFilterSpec_Array__Pop();
            var allowAll = NativeImplClient.PopBool();
            var defaultExt = NativeImplClient.PopString();
            var allowMultiple = NativeImplClient.PopBool();
            var suggestedFilename = NativeImplClient.PopString();
            return new FileDialogOptions(forWindow, mode, filters, allowAll, defaultExt, allowMultiple, suggestedFilename);
        }

        public class FileDialog : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal FileDialog(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    FileDialog__Push(this);
                    NativeImplClient.InvokeModuleMethod(_FileDialog_dispose);
                    _disposed = true;
                }
            }
            public static FileDialogResult OpenFile(FileDialogOptions opts)
            {
                FileDialogOptions__Push(opts, false);
                NativeImplClient.InvokeModuleMethod(_fileDialog_openFile);
                return FileDialogResult__Pop();
            }
            public static FileDialogResult SaveFile(FileDialogOptions opts)
            {
                FileDialogOptions__Push(opts, false);
                NativeImplClient.InvokeModuleMethod(_fileDialog_saveFile);
                return FileDialogResult__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void FileDialog__Push(FileDialog thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static FileDialog FileDialog__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new FileDialog(ptr) : null;
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
                    NativeImplClient.InvokeModuleMethod(_MenuBar_dispose);
                    _disposed = true;
                }
            }
            public void AddMenu(string label, Menu menu)
            {
                Menu__Push(menu);
                NativeImplClient.PushString(label);
                MenuBar__Push(this);
                NativeImplClient.InvokeModuleMethod(_menuBar_addMenu);
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

        public enum MessageBoxButtons
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
        internal static void MessageBoxButtons__Push(MessageBoxButtons value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MessageBoxButtons MessageBoxButtons__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (MessageBoxButtons)ret;
        }

        public enum MessageBoxIcon
        {
            Default = 0,
            Information,
            Warning,
            Question,
            Error
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MessageBoxIcon__Push(MessageBoxIcon value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MessageBoxIcon MessageBoxIcon__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (MessageBoxIcon)ret;
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

        public struct MessageBoxParams {
            public string Title;
            public string Message;
            public bool WithHelpButton;
            public MessageBoxIcon Icon;
            public MessageBoxButtons Buttons;
            public MessageBoxParams(string title, string message, bool withHelpButton, MessageBoxIcon icon, MessageBoxButtons buttons)
            {
                this.Title = title;
                this.Message = message;
                this.WithHelpButton = withHelpButton;
                this.Icon = icon;
                this.Buttons = buttons;
            }
        }

        internal static void MessageBoxParams__Push(MessageBoxParams value, bool isReturn)
        {
            MessageBoxButtons__Push(value.Buttons);
            MessageBoxIcon__Push(value.Icon);
            NativeImplClient.PushBool(value.WithHelpButton);
            NativeImplClient.PushString(value.Message);
            NativeImplClient.PushString(value.Title);
        }

        internal static MessageBoxParams MessageBoxParams__Pop()
        {
            var title = NativeImplClient.PopString();
            var message = NativeImplClient.PopString();
            var withHelpButton = NativeImplClient.PopBool();
            var icon = MessageBoxIcon__Pop();
            var buttons = MessageBoxButtons__Pop();
            return new MessageBoxParams(title, message, withHelpButton, icon, buttons);
        }

        public class MessageBoxModal : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal MessageBoxModal(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    MessageBoxModal__Push(this);
                    NativeImplClient.InvokeModuleMethod(_MessageBoxModal_dispose);
                    _disposed = true;
                }
            }
            public static MessageBoxResult Show(Window forWindow, MessageBoxParams mbParams)
            {
                MessageBoxParams__Push(mbParams, false);
                Window__Push(forWindow);
                NativeImplClient.InvokeModuleMethod(_messageBoxModal_show);
                return MessageBoxResult__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MessageBoxModal__Push(MessageBoxModal thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MessageBoxModal MessageBoxModal__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new MessageBoxModal(ptr) : null;
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
                    NativeImplClient.InvokeModuleMethod(_Timer_dispose);
                    _disposed = true;
                }
            }
            public static Timer Create(int msTimeout, TimerFunc func)
            {
                TimerFunc__Push(func);
                NativeImplClient.PushInt32(msTimeout);
                NativeImplClient.InvokeModuleMethod(_timer_create);
                return Timer__Pop();
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
            private WindowStyle _style;
            public WindowStyle Style
            {
                set
                {
                    _style = value;
                    UsedFields |= Fields.Style;
                }
            }
            public readonly bool HasStyle(out WindowStyle value)
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
                    NativeImplClient.InvokeModuleMethod(_Window_dispose);
                    _disposed = true;
                }
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
            public static void MouseUngrab()
            {
                NativeImplClient.InvokeModuleMethod(_window_mouseUngrab);
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
            public abstract void MouseUp(int x, int y, MouseButton button, Modifiers modifiers);
            public abstract void MouseMove(int x, int y, Modifiers modifiers);
            public abstract void MouseEnter(int x, int y, Modifiers modifiers);
            public abstract void MouseLeave(Modifiers modifiers);
            public abstract void Repaint(DrawContext context, int x, int y, int width, int height);
            public abstract void Moved(int x, int y);
            public abstract void Resized(int width, int height);
            public abstract void KeyDown(Key key, Modifiers modifiers, KeyLocation location);
            public abstract DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested);
            public abstract void DropLeave();
            public abstract void DropSubmit(DropData data, int x, int y, Modifiers modifiers, DropEffect effect);
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

            NativeImplClient.PushModuleConstants(_module);
            KDragFormatUTF8 = NativeImplClient.PopString();
            KDragFormatFiles = NativeImplClient.PopString();

            _moduleInit = NativeImplClient.GetModuleMethod(_module, "moduleInit");
            _moduleShutdown = NativeImplClient.GetModuleMethod(_module, "moduleShutdown");
            _runloop = NativeImplClient.GetModuleMethod(_module, "runloop");
            _exitRunloop = NativeImplClient.GetModuleMethod(_module, "exitRunloop");

            _dropData_hasFormat = NativeImplClient.GetModuleMethod(_module, "DropData_hasFormat");
            _dropData_getFiles = NativeImplClient.GetModuleMethod(_module, "DropData_getFiles");
            _dropData_getTextUTF8 = NativeImplClient.GetModuleMethod(_module, "DropData_getTextUTF8");
            _dropData_getFormat = NativeImplClient.GetModuleMethod(_module, "DropData_getFormat");
            _DropData_dispose = NativeImplClient.GetModuleMethod(_module, "DropData_dispose");
            _dragRenderPayload_renderUTF8 = NativeImplClient.GetModuleMethod(_module, "DragRenderPayload_renderUTF8");
            _dragRenderPayload_renderFiles = NativeImplClient.GetModuleMethod(_module, "DragRenderPayload_renderFiles");
            _dragRenderPayload_renderFormat = NativeImplClient.GetModuleMethod(_module, "DragRenderPayload_renderFormat");
            _DragRenderPayload_dispose = NativeImplClient.GetModuleMethod(_module, "DragRenderPayload_dispose");
            _dragData_dragExec = NativeImplClient.GetModuleMethod(_module, "DragData_dragExec");
            _dragData_create = NativeImplClient.GetModuleMethod(_module, "DragData_create");
            _DragData_dispose = NativeImplClient.GetModuleMethod(_module, "DragData_dispose");
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
            _window_create = NativeImplClient.GetModuleMethod(_module, "Window_create");
            _window_mouseUngrab = NativeImplClient.GetModuleMethod(_module, "Window_mouseUngrab");
            _Window_dispose = NativeImplClient.GetModuleMethod(_module, "Window_dispose");
            _timer_create = NativeImplClient.GetModuleMethod(_module, "Timer_create");
            _Timer_dispose = NativeImplClient.GetModuleMethod(_module, "Timer_dispose");
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
            _clipData_setClipboard = NativeImplClient.GetModuleMethod(_module, "ClipData_setClipboard");
            _clipData_get = NativeImplClient.GetModuleMethod(_module, "ClipData_get");
            _clipData_flushClipboard = NativeImplClient.GetModuleMethod(_module, "ClipData_flushClipboard");
            _ClipData_dispose = NativeImplClient.GetModuleMethod(_module, "ClipData_dispose");
            _fileDialog_openFile = NativeImplClient.GetModuleMethod(_module, "FileDialog_openFile");
            _fileDialog_saveFile = NativeImplClient.GetModuleMethod(_module, "FileDialog_saveFile");
            _FileDialog_dispose = NativeImplClient.GetModuleMethod(_module, "FileDialog_dispose");
            _messageBoxModal_show = NativeImplClient.GetModuleMethod(_module, "MessageBoxModal_show");
            _MessageBoxModal_dispose = NativeImplClient.GetModuleMethod(_module, "MessageBoxModal_dispose");

            _dropDataBadFormat = NativeImplClient.GetException(_module, "DropDataBadFormat");
            NativeImplClient.SetExceptionBuilder(_dropDataBadFormat, DropDataBadFormat.BuildAndThrow);

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

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseUp, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var button = MouseButton__Pop();
                var modifiers = Modifiers__Pop();
                inst.MouseUp(x, y, button, modifiers);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseMove, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                inst.MouseMove(x, y, modifiers);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseEnter, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                inst.MouseEnter(x, y, modifiers);
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_mouseLeave, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var modifiers = Modifiers__Pop();
                inst.MouseLeave(modifiers);
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

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_moved, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                inst.Moved(x, y);
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

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_dropFeedback, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var data = DropData__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                var suggested = DropEffect__Pop();
                DropEffect__Push(inst.DropFeedback(data, x, y, modifiers, suggested));
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_dropLeave, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                inst.DropLeave();
            });

            NativeImplClient.SetClientMethodWrapper(_windowDelegate_dropSubmit, delegate(ClientObject obj)
            {
                var inst = (ClientWindowDelegate) obj;
                var data = DropData__Pop();
                var x = NativeImplClient.PopInt32();
                var y = NativeImplClient.PopInt32();
                var modifiers = Modifiers__Pop();
                var effect = DropEffect__Pop();
                inst.DropSubmit(data, x, y, modifiers, effect);
            });

            ModuleInit();
        }

        internal static void Shutdown()
        {
            ModuleShutdown();
        }
    }
}
