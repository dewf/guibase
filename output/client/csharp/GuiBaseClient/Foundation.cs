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
    public static class Foundation
    {
        private static ModuleHandle _module;
        private static ModuleMethodHandle _cFString_makeConstant;
        private static ModuleMethodHandle _cFString_create;
        private static ModuleMethodHandle _CFString_dispose;
        private static ModuleMethodHandle _uRL_createWithFileSystemPath;
        private static ModuleMethodHandle _URL_dispose;

        public class CFString : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal CFString(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    CFString__Push(this);
                    NativeImplClient.InvokeModuleMethod(_CFString_dispose);
                    _disposed = true;
                }
            }
            public static CFString MakeConstant(string s)
            {
                NativeImplClient.PushString(s);
                NativeImplClient.InvokeModuleMethod(_cFString_makeConstant);
                return CFString__Pop();
            }
            public static CFString Create(string s)
            {
                NativeImplClient.PushString(s);
                NativeImplClient.InvokeModuleMethod(_cFString_create);
                return CFString__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void CFString__Push(CFString thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static CFString CFString__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new CFString(ptr) : null;
        }

        public enum URLPathStyle
        {
            POSIX = 0,
            Windows = 2
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void URLPathStyle__Push(URLPathStyle value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static URLPathStyle URLPathStyle__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (URLPathStyle)ret;
        }

        public class URL : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal URL(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    URL__Push(this);
                    NativeImplClient.InvokeModuleMethod(_URL_dispose);
                    _disposed = true;
                }
            }
            public static URL CreateWithFileSystemPath(CFString path, URLPathStyle pathStyle, bool isDirectory)
            {
                NativeImplClient.PushBool(isDirectory);
                URLPathStyle__Push(pathStyle);
                CFString__Push(path);
                NativeImplClient.InvokeModuleMethod(_uRL_createWithFileSystemPath);
                return URL__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void URL__Push(URL thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static URL URL__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new URL(ptr) : null;
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Foundation");

            _cFString_makeConstant = NativeImplClient.GetModuleMethod(_module, "CFString_makeConstant");
            _cFString_create = NativeImplClient.GetModuleMethod(_module, "CFString_create");
            _CFString_dispose = NativeImplClient.GetModuleMethod(_module, "CFString_dispose");
            _uRL_createWithFileSystemPath = NativeImplClient.GetModuleMethod(_module, "URL_createWithFileSystemPath");
            _URL_dispose = NativeImplClient.GetModuleMethod(_module, "URL_dispose");

            // no static init
        }

        internal static void Shutdown()
        {
            // no static shutdown
        }
    }
}
