﻿using System.Runtime.InteropServices;
using System.Text;

namespace Org.Prefixed.GuiBase.Support
{
    // from https://www.codeproject.com/Articles/138614/Advanced-Topics-in-PInvoke-String-Marshaling
    public class Utf8Marshaler : ICustomMarshaler {
        private static Utf8Marshaler _staticInstance;

        public IntPtr MarshalManagedToNative(object managedObj) {
            if (managedObj == null)
                return IntPtr.Zero;
            if (!(managedObj is string))
                throw new MarshalDirectiveException(
                    "UTF8Marshaler must be used on a string.");

            // not null terminated
            byte[] strbuf = Encoding.UTF8.GetBytes((string)managedObj); 
            IntPtr buffer = Marshal.AllocHGlobal(strbuf.Length + 1);
            Marshal.Copy(strbuf, 0, buffer, strbuf.Length);

            // write the terminating null
            Marshal.WriteByte(buffer + strbuf.Length, 0); 
            return buffer;
        }

        public unsafe object MarshalNativeToManaged(IntPtr pNativeData) {
            var walk = (byte*)pNativeData;

            // find the end of the string
            while (*walk != 0) {
                walk++;
            }
            var length = (int)(walk - (byte*)pNativeData);

            // should not be null terminated
            var strbuf = new byte[length];  
            // skip the trailing null
            Marshal.Copy((IntPtr)pNativeData, strbuf, 0, length); 
            var data = Encoding.UTF8.GetString(strbuf);
            return data;
        }

        public void CleanUpNativeData(IntPtr pNativeData) {
            Marshal.FreeHGlobal(pNativeData);            
        }

        public void CleanUpManagedData(object managedObj) {
        }

        public int GetNativeDataSize() {
            return -1;
        }

        public static ICustomMarshaler GetInstance(string cookie) {
            if (_staticInstance == null) {
                return _staticInstance = new Utf8Marshaler();
            }
            return _staticInstance;
        }
    }
}