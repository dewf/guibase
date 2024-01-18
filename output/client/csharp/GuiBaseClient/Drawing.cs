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
    public static class Drawing
    {
        private static ModuleHandle _module;
        private static ModuleMethodHandle _drawContext_saveGState;
        private static ModuleMethodHandle _drawContext_restoreGState;
        private static ModuleMethodHandle _drawContext_setRGBFillColor;
        private static ModuleMethodHandle _drawContext_fillRect;

        public struct Point {
            public double X;
            public double Y;
            public Point(double x, double y)
            {
                this.X = x;
                this.Y = y;
            }
        }

        internal static void Point__Push(Point value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Y);
            NativeImplClient.PushDouble(value.X);
        }

        internal static Point Point__Pop()
        {
            var x = NativeImplClient.PopDouble();
            var y = NativeImplClient.PopDouble();
            return new Point(x, y);
        }

        public struct Size {
            public double Width;
            public double Height;
            public Size(double width, double height)
            {
                this.Width = width;
                this.Height = height;
            }
        }

        internal static void Size__Push(Size value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Height);
            NativeImplClient.PushDouble(value.Width);
        }

        internal static Size Size__Pop()
        {
            var width = NativeImplClient.PopDouble();
            var height = NativeImplClient.PopDouble();
            return new Size(width, height);
        }

        public struct Rect {
            public Point Origin;
            public Size Size;
            public Rect(Point origin, Size size)
            {
                this.Origin = origin;
                this.Size = size;
            }
        }

        internal static void Rect__Push(Rect value, bool isReturn)
        {
            Size__Push(value.Size, isReturn);
            Point__Push(value.Origin, isReturn);
        }

        internal static Rect Rect__Pop()
        {
            var origin = Point__Pop();
            var size = Size__Pop();
            return new Rect(origin, size);
        }

        public class DrawContext
        {
            internal readonly IntPtr NativeHandle;
            internal DrawContext(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }

            public void SaveGState()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_saveGState);
            }

            public void RestoreGState()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_restoreGState);
            }

            public void SetRGBFillColor(double red, double green, double blue, double alpha)
            {
                NativeImplClient.PushDouble(alpha);
                NativeImplClient.PushDouble(blue);
                NativeImplClient.PushDouble(green);
                NativeImplClient.PushDouble(red);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setRGBFillColor);
            }

            public void FillRect(Rect rect)
            {
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_fillRect);
            }
        }

        internal static void DrawContext__Push(DrawContext thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        internal static DrawContext DrawContext__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new DrawContext(ptr) : null;
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Drawing");

            _drawContext_saveGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_saveGState");
            _drawContext_restoreGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_restoreGState");
            _drawContext_setRGBFillColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setRGBFillColor");
            _drawContext_fillRect = NativeImplClient.GetModuleMethod(_module, "DrawContext_fillRect");

            // no static init
        }

        internal static void Shutdown()
        {
            // no static shutdown
        }
    }
}
