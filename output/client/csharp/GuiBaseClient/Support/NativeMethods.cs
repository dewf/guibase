using System.Runtime.InteropServices;

namespace Org.Prefixed.GuiBase.Support
{
    internal static class NativeMethods
    {
        internal delegate void ExecFunctionDelegate(int id);
        internal delegate void ClientMethodDelegate(IntPtr methodHandle, int objectId);
        internal delegate void ClientResourceReleaseDelegate(int id);
        internal delegate void ClientClearSafetyAreaDelegate();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern int nativeImplInit(
            ExecFunctionDelegate execFunctionDelegate,
            ClientMethodDelegate methodDelegate,
            ClientResourceReleaseDelegate resourceReleaseDelegate,
            ClientClearSafetyAreaDelegate clientClearSafetyAreaDelegate
            );

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void nativeImplShutdown();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr getModule(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(Utf8Marshaler))]
            string name);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr getModuleMethod(
            IntPtr module,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(Utf8Marshaler))]
            string name);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr getInterface(
            IntPtr module,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(Utf8Marshaler))]
            string name);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr getInterfaceMethod(
            IntPtr iface,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(Utf8Marshaler))]
            string name);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr getException(
            IntPtr module,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(Utf8Marshaler))]
            string name);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void invokeModuleMethod(IntPtr method);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr invokeModuleMethodWithExceptions(IntPtr method);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushPtr(IntPtr value);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr popPtr();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushPtrArray(IntPtr[] values, IntPtr count);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popPtrArray(out IntPtr valuesPtr, out IntPtr count); // void***, size_t*

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushSizeT(IntPtr value);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr popSizeT();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushSizeTArray(IntPtr[] values, IntPtr count);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popSizeTArray(out IntPtr valuesPtr, out IntPtr count); // size_t**, size_t*

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushBool(bool value);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool popBool();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushBoolArray(byte[] values, IntPtr count); // bool*, size_t

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popBoolArray(out IntPtr valuesPtr, out IntPtr count); // bool**, size_t*
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt8(sbyte x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern sbyte popInt8();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt8Array(sbyte[] values, IntPtr count); // size_t count
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popInt8Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt8(byte x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern byte popUInt8();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt8Array(byte[] values, IntPtr count); // size_t count
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popUInt8Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt16(short x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern short popInt16();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt16Array(short[] values, IntPtr count); // size_t count
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popInt16Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt16(ushort x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ushort popUInt16();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt16Array(ushort[] values, IntPtr count); // size_t count

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popUInt16Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt32(int x);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern int popInt32();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt32Array(int[] values, IntPtr count); // size_t count
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popInt32Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt32(uint x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern uint popUInt32();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt32Array(uint[] values, IntPtr count); // size_t count

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popUInt32Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt64(long x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern long popInt64();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInt64Array(long[] values, IntPtr count); // size_t count

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popInt64Array(out IntPtr values, out IntPtr count); // both args are pointers
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt64(ulong x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern ulong popUInt64();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushUInt64Array(ulong[] values, IntPtr count); // size_t count

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popUInt64Array(out IntPtr values, out IntPtr count); // both args are pointers

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushFloat(float x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern float popFloat();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushFloatArray(float[] values, IntPtr count);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popFloatArray(out IntPtr values, out IntPtr count);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushDouble(double x);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern double popDouble();
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushDoubleArray(double[] values, IntPtr count);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popDoubleArray(out IntPtr values, out IntPtr count);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushString(IntPtr str, IntPtr length); // size_t length

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popString(out IntPtr strPtr, out IntPtr length); // size_t* length

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushStringArray(IntPtr[] strs, IntPtr[] lengths, IntPtr count); // const char **, size_t*, size_t

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popStringArray(out IntPtr strsPtr, out IntPtr lengthsPtr, out IntPtr count); // const char ***, size_t**, size_t*

        public struct BufferDescriptor
        {
            public IntPtr Start;
            public int ElementSize;
            public IntPtr TotalCount;
            public IntPtr TotalSize;
        }

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushBuffer(int id, bool isClientId, ref BufferDescriptor descriptor);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void popBuffer(out int id, out bool isClientId, out BufferDescriptor descriptor);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushClientFunc(int id);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern int popServerFunc();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void execServerFunc(int id);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr execServerFuncWithExceptions(int id);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void invokeInterfaceMethod(IntPtr method, int serverId);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern IntPtr invokeInterfaceMethodWithExceptions(IntPtr method, int serverId);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushInstance(int id, bool isClientId);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern int popInstance(out bool isClientId);
        
        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushNull();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern int releaseServerResource(int id);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void clearServerSafetyArea();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void dumpTables();

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void pushModuleConstants(IntPtr module);

        [DllImport("GuiBaseServer.dll", CallingConvention = CallingConvention.Cdecl)]
        internal static extern void setException(IntPtr exceptionHandle);
    }
}