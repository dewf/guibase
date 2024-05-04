using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using CSharpFunctionalExtensions;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

namespace Org.Prefixed.GuiBase
{
    public static class Drawing
    {
        private static ModuleHandle _module;

        // built-in array type: double[]

        private static void __AffineTransform_Option__Push(Maybe<AffineTransform> maybeValue, bool isReturn)
        {
            if (maybeValue.TryGetValue(out var value))
            {
                AffineTransform__Push(value, isReturn);
                NativeImplClient.PushBool(true);
            }
            else
            {
                NativeImplClient.PushBool(false);
            }
        }

        private static Maybe<AffineTransform> __AffineTransform_Option__Pop()
        {
            var hasValue = NativeImplClient.PopBool();
            if (hasValue)
            {
                return AffineTransform__Pop();
            }
            return Maybe<AffineTransform>.None;
        }

        internal static void __Point_Array__Push(Point[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new double[count];
            var f1Values = new double[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].X;
                f1Values[i] = items[i].Y;
            }
            NativeImplClient.PushDoubleArray(f1Values);
            NativeImplClient.PushDoubleArray(f0Values);
        }

        internal static Point[] __Point_Array__Pop()
        {
            var f0Values = NativeImplClient.PopDoubleArray();
            var f1Values = NativeImplClient.PopDoubleArray();
            var count = f0Values.Length;
            var ret = new Point[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                ret[i] = new Point(f0, f1);
            }
            return ret;
        }

        internal static void __Size_Array__Push(Size[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new double[count];
            var f1Values = new double[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Width;
                f1Values[i] = items[i].Height;
            }
            NativeImplClient.PushDoubleArray(f1Values);
            NativeImplClient.PushDoubleArray(f0Values);
        }

        internal static Size[] __Size_Array__Pop()
        {
            var f0Values = NativeImplClient.PopDoubleArray();
            var f1Values = NativeImplClient.PopDoubleArray();
            var count = f0Values.Length;
            var ret = new Size[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                ret[i] = new Size(f0, f1);
            }
            return ret;
        }

        internal static void __Rect_Array__Push(Rect[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new Point[count];
            var f1Values = new Size[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Origin;
                f1Values[i] = items[i].Size;
            }
            __Size_Array__Push(f1Values, isReturn);
            __Point_Array__Push(f0Values, isReturn);
        }

        internal static Rect[] __Rect_Array__Pop()
        {
            var f0Values = __Point_Array__Pop();
            var f1Values = __Size_Array__Pop();
            var count = f0Values.Length;
            var ret = new Rect[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                ret[i] = new Rect(f0, f1);
            }
            return ret;
        }

        internal static void __Gradient_Stop_Array__Push(Gradient.Stop[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new double[count];
            var f1Values = new double[count];
            var f2Values = new double[count];
            var f3Values = new double[count];
            var f4Values = new double[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Location;
                f1Values[i] = items[i].Red;
                f2Values[i] = items[i].Green;
                f3Values[i] = items[i].Blue;
                f4Values[i] = items[i].Alpha;
            }
            NativeImplClient.PushDoubleArray(f4Values);
            NativeImplClient.PushDoubleArray(f3Values);
            NativeImplClient.PushDoubleArray(f2Values);
            NativeImplClient.PushDoubleArray(f1Values);
            NativeImplClient.PushDoubleArray(f0Values);
        }

        internal static Gradient.Stop[] __Gradient_Stop_Array__Pop()
        {
            var f0Values = NativeImplClient.PopDoubleArray();
            var f1Values = NativeImplClient.PopDoubleArray();
            var f2Values = NativeImplClient.PopDoubleArray();
            var f3Values = NativeImplClient.PopDoubleArray();
            var f4Values = NativeImplClient.PopDoubleArray();
            var count = f0Values.Length;
            var ret = new Gradient.Stop[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                var f3 = f3Values[i];
                var f4 = f4Values[i];
                ret[i] = new Gradient.Stop(f0, f1, f2, f3, f4);
            }
            return ret;
        }

        internal static void __AffineBatchOps_Value_Array__Push(AffineBatchOps.Value[] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                AffineBatchOps.Value__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static AffineBatchOps.Value[] __AffineBatchOps_Value_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new AffineBatchOps.Value[count];
            for (var i = 0; i < count; i++)
            {
                ret[i] = AffineBatchOps.Value__Pop();
            }
            return ret;
        }
        internal static ModuleMethodHandle _color_dispose;
        internal static ModuleMethodHandle _colorSpace_dispose;
        internal static ModuleMethodHandle _gradient_dispose;
        internal static ModuleMethodHandle _path_getCurrentPoint;
        internal static ModuleMethodHandle _path_createCopy;
        internal static ModuleMethodHandle _path_createMutableCopy;
        internal static ModuleMethodHandle _path_dispose;
        internal static ModuleMethodHandle _mutablePath_addPath;
        internal static ModuleMethodHandle _mutablePath_addRect;
        internal static ModuleMethodHandle _mutablePath_addRects;
        internal static ModuleMethodHandle _mutablePath_addRoundedRect;
        internal static ModuleMethodHandle _mutablePath_addEllipseInRect;
        internal static ModuleMethodHandle _mutablePath_moveToPoint;
        internal static ModuleMethodHandle _mutablePath_addArc;
        internal static ModuleMethodHandle _mutablePath_addRelativeArc;
        internal static ModuleMethodHandle _mutablePath_addArcToPoint;
        internal static ModuleMethodHandle _mutablePath_addCurveToPoint;
        internal static ModuleMethodHandle _mutablePath_addLines;
        internal static ModuleMethodHandle _mutablePath_addLineToPoint;
        internal static ModuleMethodHandle _mutablePath_addQuadCurveToPoint;
        internal static ModuleMethodHandle _mutablePath_closeSubpath;
        internal static ModuleMethodHandle _mutablePath_dispose;
        internal static ModuleMethodHandle _drawContext_saveGState;
        internal static ModuleMethodHandle _drawContext_restoreGState;
        internal static ModuleMethodHandle _drawContext_setRGBFillColor;
        internal static ModuleMethodHandle _drawContext_setRGBStrokeColor;
        internal static ModuleMethodHandle _drawContext_setFillColorWithColor;
        internal static ModuleMethodHandle _drawContext_fillRect;
        internal static ModuleMethodHandle _drawContext_setTextMatrix;
        internal static ModuleMethodHandle _drawContext_setTextPosition;
        internal static ModuleMethodHandle _drawContext_beginPath;
        internal static ModuleMethodHandle _drawContext_addArc;
        internal static ModuleMethodHandle _drawContext_addArcToPoint;
        internal static ModuleMethodHandle _drawContext_drawPath;
        internal static ModuleMethodHandle _drawContext_setStrokeColorWithColor;
        internal static ModuleMethodHandle _drawContext_strokeRectWithWidth;
        internal static ModuleMethodHandle _drawContext_moveToPoint;
        internal static ModuleMethodHandle _drawContext_addLineToPoint;
        internal static ModuleMethodHandle _drawContext_strokePath;
        internal static ModuleMethodHandle _drawContext_setLineDash;
        internal static ModuleMethodHandle _drawContext_clearLineDash;
        internal static ModuleMethodHandle _drawContext_setLineWidth;
        internal static ModuleMethodHandle _drawContext_clip;
        internal static ModuleMethodHandle _drawContext_clipToRect;
        internal static ModuleMethodHandle _drawContext_translateCTM;
        internal static ModuleMethodHandle _drawContext_scaleCTM;
        internal static ModuleMethodHandle _drawContext_rotateCTM;
        internal static ModuleMethodHandle _drawContext_concatCTM;
        internal static ModuleMethodHandle _drawContext_addPath;
        internal static ModuleMethodHandle _drawContext_fillPath;
        internal static ModuleMethodHandle _drawContext_strokeRect;
        internal static ModuleMethodHandle _drawContext_addRect;
        internal static ModuleMethodHandle _drawContext_closePath;
        internal static ModuleMethodHandle _drawContext_drawLinearGradient;
        internal static ModuleMethodHandle _drawContext_setTextDrawingMode;
        internal static ModuleMethodHandle _drawContext_clipToMask;
        internal static ModuleMethodHandle _drawContext_drawImage;
        internal static ModuleMethodHandle _drawContext_dispose;
        internal static ModuleMethodHandle _bitmapLock_dispose;
        internal static ModuleMethodHandle _image_dispose;
        internal static ModuleMethodHandle _bitmapDrawContext_createImage;
        internal static ModuleMethodHandle _bitmapDrawContext_getData;
        internal static ModuleMethodHandle _bitmapDrawContext_dispose;
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
        public struct AffineTransform {
            internal static ModuleMethodHandle _translate;
            internal static ModuleMethodHandle _rotate;
            internal static ModuleMethodHandle _scale;
            internal static ModuleMethodHandle _concat;
            public static AffineTransform Identity { get; internal set; }

            public static AffineTransform Translate(AffineTransform input, double tx, double ty)
            {
                NativeImplClient.PushDouble(ty);
                NativeImplClient.PushDouble(tx);
                AffineTransform__Push(input, false);
                NativeImplClient.InvokeModuleMethod(_translate);
                return AffineTransform__Pop();
            }

            public static AffineTransform Rotate(AffineTransform input, double angle)
            {
                NativeImplClient.PushDouble(angle);
                AffineTransform__Push(input, false);
                NativeImplClient.InvokeModuleMethod(_rotate);
                return AffineTransform__Pop();
            }

            public static AffineTransform Scale(AffineTransform input, double sx, double sy)
            {
                NativeImplClient.PushDouble(sy);
                NativeImplClient.PushDouble(sx);
                AffineTransform__Push(input, false);
                NativeImplClient.InvokeModuleMethod(_scale);
                return AffineTransform__Pop();
            }

            public static AffineTransform Concat(AffineTransform t1, AffineTransform t2)
            {
                AffineTransform__Push(t2, false);
                AffineTransform__Push(t1, false);
                NativeImplClient.InvokeModuleMethod(_concat);
                return AffineTransform__Pop();
            }
            public double A;
            public double B;
            public double C;
            public double D;
            public double Tx;
            public double Ty;
            public AffineTransform(double a, double b, double c, double d, double tx, double ty)
            {
                this.A = a;
                this.B = b;
                this.C = c;
                this.D = d;
                this.Tx = tx;
                this.Ty = ty;
            }
        }

        internal static void AffineTransform__Push(AffineTransform value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Ty);
            NativeImplClient.PushDouble(value.Tx);
            NativeImplClient.PushDouble(value.D);
            NativeImplClient.PushDouble(value.C);
            NativeImplClient.PushDouble(value.B);
            NativeImplClient.PushDouble(value.A);
        }

        internal static AffineTransform AffineTransform__Pop()
        {
            var a = NativeImplClient.PopDouble();
            var b = NativeImplClient.PopDouble();
            var c = NativeImplClient.PopDouble();
            var d = NativeImplClient.PopDouble();
            var tx = NativeImplClient.PopDouble();
            var ty = NativeImplClient.PopDouble();
            return new AffineTransform(a, b, c, d, tx, ty);
        }
        public static class AffineBatchOps
        {
            internal static ModuleMethodHandle _process;

            public static AffineTransform Process(AffineTransform init, Value[] ops)
            {
                __AffineBatchOps_Value_Array__Push(ops, false);
                AffineTransform__Push(init, false);
                NativeImplClient.InvokeModuleMethod(_process);
                return AffineTransform__Pop();
            }
            public abstract record Value
            {
                internal abstract void Push(bool isReturn);
                internal static Value Pop()
                {
                    return NativeImplClient.PopInt32() switch
                    {
                        0 => Translate.PopDerived(),
                        1 => Rotate.PopDerived(),
                        2 => Scale.PopDerived(),
                        3 => Concat.PopDerived(),
                        _ => throw new Exception("Value.Pop() - unknown tag!")
                    };
                }
                public sealed record Translate(double Tx, double Ty) : Value
                {
                    public double Tx { get; } = Tx;
                    public double Ty { get; } = Ty;
                    internal override void Push(bool isReturn)
                    {
                        NativeImplClient.PushDouble(Ty);
                        NativeImplClient.PushDouble(Tx);
                        // kind
                        NativeImplClient.PushInt32(0);
                    }
                    internal static Translate PopDerived()
                    {
                        var tx = NativeImplClient.PopDouble();
                        var ty = NativeImplClient.PopDouble();
                        return new Translate(tx, ty);
                    }
                }
                public sealed record Rotate(double Angle) : Value
                {
                    public double Angle { get; } = Angle;
                    internal override void Push(bool isReturn)
                    {
                        NativeImplClient.PushDouble(Angle);
                        // kind
                        NativeImplClient.PushInt32(1);
                    }
                    internal static Rotate PopDerived()
                    {
                        var angle = NativeImplClient.PopDouble();
                        return new Rotate(angle);
                    }
                }
                public sealed record Scale(double Sx, double Sy) : Value
                {
                    public double Sx { get; } = Sx;
                    public double Sy { get; } = Sy;
                    internal override void Push(bool isReturn)
                    {
                        NativeImplClient.PushDouble(Sy);
                        NativeImplClient.PushDouble(Sx);
                        // kind
                        NativeImplClient.PushInt32(2);
                    }
                    internal static Scale PopDerived()
                    {
                        var sx = NativeImplClient.PopDouble();
                        var sy = NativeImplClient.PopDouble();
                        return new Scale(sx, sy);
                    }
                }
                public sealed record Concat(AffineTransform T2) : Value
                {
                    public AffineTransform T2 { get; } = T2;
                    internal override void Push(bool isReturn)
                    {
                        AffineTransform__Push(T2, isReturn);
                        // kind
                        NativeImplClient.PushInt32(3);
                    }
                    internal static Concat PopDerived()
                    {
                        var t2 = AffineTransform__Pop();
                        return new Concat(t2);
                    }
                }
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Value__Push(Value thing, bool isReturn)
            {
                thing.Push(isReturn);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Value Value__Pop()
            {
                return Value.Pop();
            }
        }
        public class Color : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Color(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Color__Push(this);
                    NativeImplClient.InvokeModuleMethod(_color_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createGenericRGB;
            internal static ModuleMethodHandle _getConstantColor;

            public static Color CreateGenericRGB(double red, double green, double blue, double alpha)
            {
                NativeImplClient.PushDouble(alpha);
                NativeImplClient.PushDouble(blue);
                NativeImplClient.PushDouble(green);
                NativeImplClient.PushDouble(red);
                NativeImplClient.InvokeModuleMethod(_createGenericRGB);
                return Color__Pop();
            }

            public static Color GetConstantColor(Constant which)
            {
                Constant__Push(which);
                NativeImplClient.InvokeModuleMethod(_getConstantColor);
                return Color__Pop();
            }
            public enum Constant
            {
                White,
                Black,
                Clear
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Constant__Push(Constant value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Constant Constant__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (Constant)ret;
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Color__Push(Color thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Color Color__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Color(ptr) : null;
        }
        public class ColorSpace : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal ColorSpace(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    ColorSpace__Push(this);
                    NativeImplClient.InvokeModuleMethod(_colorSpace_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createWithName;
            internal static ModuleMethodHandle _createDeviceGray;

            public static ColorSpace CreateWithName(Name name)
            {
                Name__Push(name);
                NativeImplClient.InvokeModuleMethod(_createWithName);
                return ColorSpace__Pop();
            }

            public static ColorSpace CreateDeviceGray()
            {
                NativeImplClient.InvokeModuleMethod(_createDeviceGray);
                return ColorSpace__Pop();
            }
            public enum Name
            {
                GenericGray,
                GenericRGB,
                GenericCMYK,
                GenericRGBLinear,
                AdobeRGB1998,
                SRGB,
                GenericGrayGamma2_2
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Name__Push(Name value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Name Name__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (Name)ret;
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void ColorSpace__Push(ColorSpace thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static ColorSpace ColorSpace__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new ColorSpace(ptr) : null;
        }
        public class Gradient : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Gradient(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Gradient__Push(this);
                    NativeImplClient.InvokeModuleMethod(_gradient_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createWithColorComponents;

            public static Gradient CreateWithColorComponents(ColorSpace space, Stop[] stops)
            {
                __Gradient_Stop_Array__Push(stops, false);
                ColorSpace__Push(space);
                NativeImplClient.InvokeModuleMethod(_createWithColorComponents);
                return Gradient__Pop();
            }
            [Flags]
            public enum DrawingOptions
            {
                DrawsBeforeStartLocation = 1,
                DrawsAfterEndLocation = 1 << 1
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void DrawingOptions__Push(DrawingOptions value)
            {
                NativeImplClient.PushUInt32((uint)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static DrawingOptions DrawingOptions__Pop()
            {
                var ret = NativeImplClient.PopUInt32();
                return (DrawingOptions)ret;
            }
            public struct Stop {
                public double Location;
                public double Red;
                public double Green;
                public double Blue;
                public double Alpha;
                public Stop(double location, double red, double green, double blue, double alpha)
                {
                    this.Location = location;
                    this.Red = red;
                    this.Green = green;
                    this.Blue = blue;
                    this.Alpha = alpha;
                }
            }

            internal static void Stop__Push(Stop value, bool isReturn)
            {
                NativeImplClient.PushDouble(value.Alpha);
                NativeImplClient.PushDouble(value.Blue);
                NativeImplClient.PushDouble(value.Green);
                NativeImplClient.PushDouble(value.Red);
                NativeImplClient.PushDouble(value.Location);
            }

            internal static Stop Stop__Pop()
            {
                var location = NativeImplClient.PopDouble();
                var red = NativeImplClient.PopDouble();
                var green = NativeImplClient.PopDouble();
                var blue = NativeImplClient.PopDouble();
                var alpha = NativeImplClient.PopDouble();
                return new Stop(location, red, green, blue, alpha);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Gradient__Push(Gradient thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Gradient Gradient__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Gradient(ptr) : null;
        }
        public class Path : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Path(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Path__Push(this);
                    NativeImplClient.InvokeModuleMethod(_path_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createWithRect;
            internal static ModuleMethodHandle _createWithEllipseInRect;
            internal static ModuleMethodHandle _createWithRoundedRect;

            public static Path CreateWithRect(Rect rect, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                Rect__Push(rect, false);
                NativeImplClient.InvokeModuleMethod(_createWithRect);
                return Path__Pop();
            }

            public static Path CreateWithEllipseInRect(Rect rect, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                Rect__Push(rect, false);
                NativeImplClient.InvokeModuleMethod(_createWithEllipseInRect);
                return Path__Pop();
            }

            public static Path CreateWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(cornerHeight);
                NativeImplClient.PushDouble(cornerWidth);
                Rect__Push(rect, false);
                NativeImplClient.InvokeModuleMethod(_createWithRoundedRect);
                return Path__Pop();
            }
            public enum DrawingMode
            {
                Fill,
                EOFill,
                Stroke,
                FillStroke,
                EOFillStroke
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void DrawingMode__Push(DrawingMode value)
            {
                NativeImplClient.PushInt32((int)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static DrawingMode DrawingMode__Pop()
            {
                var ret = NativeImplClient.PopInt32();
                return (DrawingMode)ret;
            }
            public Point GetCurrentPoint()
            {
                Path__Push(this);
                NativeImplClient.InvokeModuleMethod(_path_getCurrentPoint);
                return Point__Pop();
            }
            public Path CreateCopy()
            {
                Path__Push(this);
                NativeImplClient.InvokeModuleMethod(_path_createCopy);
                return Path__Pop();
            }
            public MutablePath CreateMutableCopy()
            {
                Path__Push(this);
                NativeImplClient.InvokeModuleMethod(_path_createMutableCopy);
                return MutablePath__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Path__Push(Path thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Path Path__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Path(ptr) : null;
        }
        public class MutablePath : Path
        {
            internal MutablePath(IntPtr nativeHandle) : base(nativeHandle)
            {
            }
            public override void Dispose()
            {
                if (!_disposed)
                {
                    MutablePath__Push(this);
                    NativeImplClient.InvokeModuleMethod(_mutablePath_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;
            internal static ExceptionHandle _transformException;

            public static MutablePath Create()
            {
                NativeImplClient.InvokeModuleMethod(_create);
                return MutablePath__Pop();
            }
            public class TransformException : Exception
            {
                public readonly string Error;
                public TransformException(string error) : base("TransformException")
                {
                    Error = error;
                }
                internal void PushAndSet()
                {
                    NativeImplClient.PushString(Error);
                    NativeImplClient.SetException(_transformException);
                }
                internal static void BuildAndThrow()
                {
                    var error = NativeImplClient.PopString();
                    throw new TransformException(error);
                }
            }
            public void AddPath(Path path2, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                Path__Push(path2);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addPath);
            }
            public void AddRect(Rect rect, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                Rect__Push(rect, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addRect);
            }
            public void AddRects(Rect[] rects, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                __Rect_Array__Push(rects, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addRects);
            }
            public void AddRoundedRect(Rect rect, double cornerWidth, double cornerHeight, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(cornerHeight);
                NativeImplClient.PushDouble(cornerWidth);
                Rect__Push(rect, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addRoundedRect);
            }
            public void AddEllipseInRect(Rect rect, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                Rect__Push(rect, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addEllipseInRect);
            }
            public void MoveToPoint(double x, double y, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_moveToPoint);
            }
            public void AddArc(double x, double y, double radius, double startAngle, double endAngle, bool clockwise, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushBool(clockwise);
                NativeImplClient.PushDouble(endAngle);
                NativeImplClient.PushDouble(startAngle);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addArc);
            }
            public void AddRelativeArc(double x, double y, double radius, double startAngle, double delta, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(delta);
                NativeImplClient.PushDouble(startAngle);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addRelativeArc);
            }
            public void AddArcToPoint(double x1, double y1, double x2, double y2, double radius, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y2);
                NativeImplClient.PushDouble(x2);
                NativeImplClient.PushDouble(y1);
                NativeImplClient.PushDouble(x1);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addArcToPoint);
            }
            public void AddCurveToPoint(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                NativeImplClient.PushDouble(cp2y);
                NativeImplClient.PushDouble(cp2x);
                NativeImplClient.PushDouble(cp1y);
                NativeImplClient.PushDouble(cp1x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addCurveToPoint);
            }
            public void AddLines(Point[] points, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                __Point_Array__Push(points, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addLines);
            }
            public void AddLineToPoint(double x, double y, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addLineToPoint);
            }
            public void AddQuadCurveToPoint(double cpx, double cpy, double x, double y, Maybe<AffineTransform> transform) // throws TransformException
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                NativeImplClient.PushDouble(cpy);
                NativeImplClient.PushDouble(cpx);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addQuadCurveToPoint);
            }
            public void CloseSubpath()
            {
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_closeSubpath);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MutablePath__Push(MutablePath thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MutablePath MutablePath__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new MutablePath(ptr) : null;
        }
        public enum TextDrawingMode
        {
            Fill,
            Stroke,
            FillStroke,
            Invisible,
            FillClip,
            StrokeClip,
            FillStrokeClip,
            Clip
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void TextDrawingMode__Push(TextDrawingMode value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static TextDrawingMode TextDrawingMode__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (TextDrawingMode)ret;
        }
        public class DrawContext : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal DrawContext(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    DrawContext__Push(this);
                    NativeImplClient.InvokeModuleMethod(_drawContext_dispose);
                    _disposed = true;
                }
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
            public void SetRGBStrokeColor(double red, double green, double blue, double alpha)
            {
                NativeImplClient.PushDouble(alpha);
                NativeImplClient.PushDouble(blue);
                NativeImplClient.PushDouble(green);
                NativeImplClient.PushDouble(red);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setRGBStrokeColor);
            }
            public void SetFillColorWithColor(Color color)
            {
                Color__Push(color);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setFillColorWithColor);
            }
            public void FillRect(Rect rect)
            {
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_fillRect);
            }
            public void SetTextMatrix(AffineTransform t)
            {
                AffineTransform__Push(t, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setTextMatrix);
            }
            public void SetTextPosition(double x, double y)
            {
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setTextPosition);
            }
            public void BeginPath()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_beginPath);
            }
            public void AddArc(double x, double y, double radius, double startAngle, double endAngle, bool clockwise)
            {
                NativeImplClient.PushBool(clockwise);
                NativeImplClient.PushDouble(endAngle);
                NativeImplClient.PushDouble(startAngle);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_addArc);
            }
            public void AddArcToPoint(double x1, double y1, double x2, double y2, double radius)
            {
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y2);
                NativeImplClient.PushDouble(x2);
                NativeImplClient.PushDouble(y1);
                NativeImplClient.PushDouble(x1);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_addArcToPoint);
            }
            public void DrawPath(Path.DrawingMode mode)
            {
                Path.DrawingMode__Push(mode);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_drawPath);
            }
            public void SetStrokeColorWithColor(Color color)
            {
                Color__Push(color);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setStrokeColorWithColor);
            }
            public void StrokeRectWithWidth(Rect rect, double width)
            {
                NativeImplClient.PushDouble(width);
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_strokeRectWithWidth);
            }
            public void MoveToPoint(double x, double y)
            {
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_moveToPoint);
            }
            public void AddLineToPoint(double x, double y)
            {
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_addLineToPoint);
            }
            public void StrokePath()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_strokePath);
            }
            public void SetLineDash(double phase, double[] lengths)
            {
                NativeImplClient.PushDoubleArray(lengths);
                NativeImplClient.PushDouble(phase);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setLineDash);
            }
            public void ClearLineDash()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_clearLineDash);
            }
            public void SetLineWidth(double width)
            {
                NativeImplClient.PushDouble(width);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setLineWidth);
            }
            public void Clip()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_clip);
            }
            public void ClipToRect(Rect clipRect)
            {
                Rect__Push(clipRect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_clipToRect);
            }
            public void TranslateCTM(double tx, double ty)
            {
                NativeImplClient.PushDouble(ty);
                NativeImplClient.PushDouble(tx);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_translateCTM);
            }
            public void ScaleCTM(double scaleX, double scaleY)
            {
                NativeImplClient.PushDouble(scaleY);
                NativeImplClient.PushDouble(scaleX);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_scaleCTM);
            }
            public void RotateCTM(double angle)
            {
                NativeImplClient.PushDouble(angle);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_rotateCTM);
            }
            public void ConcatCTM(AffineTransform transform)
            {
                AffineTransform__Push(transform, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_concatCTM);
            }
            public void AddPath(Path path)
            {
                Path__Push(path);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_addPath);
            }
            public void FillPath()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_fillPath);
            }
            public void StrokeRect(Rect rect)
            {
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_strokeRect);
            }
            public void AddRect(Rect rect)
            {
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_addRect);
            }
            public void ClosePath()
            {
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_closePath);
            }
            public void DrawLinearGradient(Gradient gradient, Point startPoint, Point endPoint, Gradient.DrawingOptions drawOpts)
            {
                Gradient.DrawingOptions__Push(drawOpts);
                Point__Push(endPoint, false);
                Point__Push(startPoint, false);
                Gradient__Push(gradient);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_drawLinearGradient);
            }
            public void SetTextDrawingMode(TextDrawingMode mode)
            {
                TextDrawingMode__Push(mode);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_setTextDrawingMode);
            }
            public void ClipToMask(Rect rect, Image mask)
            {
                Image__Push(mask);
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_clipToMask);
            }
            public void DrawImage(Rect rect, Image image)
            {
                Image__Push(image);
                Rect__Push(rect, false);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_drawImage);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void DrawContext__Push(DrawContext thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static DrawContext DrawContext__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new DrawContext(ptr) : null;
        }
        public enum ImageAlphaInfo
        {
            None,
            PremultipliedLast,
            PremultipliedFirst,
            Last,
            First,
            NoneSkipLast,
            NoneSkipFirst,
            Only
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void ImageAlphaInfo__Push(ImageAlphaInfo value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static ImageAlphaInfo ImageAlphaInfo__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (ImageAlphaInfo)ret;
        }
        [Flags]
        public enum BitmapInfo
        {
            AlphaInfoMask = 0x1F,
            FloatInfoMask = 0xF00,
            FloatComponents = 1 << 8,
            ByteOrderMask = 0x7000,
            ByteOrderDefault = 0 << 12,
            ByteOrder16Little = 1 << 12,
            ByteOrder32Little = 2 << 12,
            ByteOrder16Big = 3 << 12,
            ByteOrder32Big = 4 << 12
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void BitmapInfo__Push(BitmapInfo value)
        {
            NativeImplClient.PushUInt32((uint)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static BitmapInfo BitmapInfo__Pop()
        {
            var ret = NativeImplClient.PopUInt32();
            return (BitmapInfo)ret;
        }
        public class BitmapLock : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal BitmapLock(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    BitmapLock__Push(this);
                    NativeImplClient.InvokeModuleMethod(_bitmapLock_dispose);
                    _disposed = true;
                }
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void BitmapLock__Push(BitmapLock thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static BitmapLock BitmapLock__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new BitmapLock(ptr) : null;
        }
        public class Image : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Image(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Image__Push(this);
                    NativeImplClient.InvokeModuleMethod(_image_dispose);
                    _disposed = true;
                }
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Image__Push(Image thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Image Image__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Image(ptr) : null;
        }
        public class BitmapDrawContext : DrawContext
        {
            internal BitmapDrawContext(IntPtr nativeHandle) : base(nativeHandle)
            {
            }
            public override void Dispose()
            {
                if (!_disposed)
                {
                    BitmapDrawContext__Push(this);
                    NativeImplClient.InvokeModuleMethod(_bitmapDrawContext_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static BitmapDrawContext Create(int width, int height, int bitsPerComponent, int bytesPerRow, ColorSpace space, BitmapInfo bitmapInfo)
            {
                BitmapInfo__Push(bitmapInfo);
                ColorSpace__Push(space);
                NativeImplClient.PushInt32(bytesPerRow);
                NativeImplClient.PushInt32(bitsPerComponent);
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.InvokeModuleMethod(_create);
                return BitmapDrawContext__Pop();
            }
            public Image CreateImage()
            {
                BitmapDrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_bitmapDrawContext_createImage);
                return Image__Pop();
            }
            public BitmapLock GetData()
            {
                BitmapDrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_bitmapDrawContext_getData);
                return BitmapLock__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void BitmapDrawContext__Push(BitmapDrawContext thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static BitmapDrawContext BitmapDrawContext__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new BitmapDrawContext(ptr) : null;
        }

        internal static void __Init()
        {
            _module = NativeImplClient.GetModule("Drawing");
            // assign module constants
            NativeImplClient.PushModuleConstants(_module);
            AffineTransform.Identity = AffineTransform__Pop();
            // assign module handles
            _color_dispose = NativeImplClient.GetModuleMethod(_module, "Color_dispose");
            _colorSpace_dispose = NativeImplClient.GetModuleMethod(_module, "ColorSpace_dispose");
            _gradient_dispose = NativeImplClient.GetModuleMethod(_module, "Gradient_dispose");
            _path_getCurrentPoint = NativeImplClient.GetModuleMethod(_module, "Path_getCurrentPoint");
            _path_createCopy = NativeImplClient.GetModuleMethod(_module, "Path_createCopy");
            _path_createMutableCopy = NativeImplClient.GetModuleMethod(_module, "Path_createMutableCopy");
            _path_dispose = NativeImplClient.GetModuleMethod(_module, "Path_dispose");
            _mutablePath_addPath = NativeImplClient.GetModuleMethod(_module, "MutablePath_addPath");
            _mutablePath_addRect = NativeImplClient.GetModuleMethod(_module, "MutablePath_addRect");
            _mutablePath_addRects = NativeImplClient.GetModuleMethod(_module, "MutablePath_addRects");
            _mutablePath_addRoundedRect = NativeImplClient.GetModuleMethod(_module, "MutablePath_addRoundedRect");
            _mutablePath_addEllipseInRect = NativeImplClient.GetModuleMethod(_module, "MutablePath_addEllipseInRect");
            _mutablePath_moveToPoint = NativeImplClient.GetModuleMethod(_module, "MutablePath_moveToPoint");
            _mutablePath_addArc = NativeImplClient.GetModuleMethod(_module, "MutablePath_addArc");
            _mutablePath_addRelativeArc = NativeImplClient.GetModuleMethod(_module, "MutablePath_addRelativeArc");
            _mutablePath_addArcToPoint = NativeImplClient.GetModuleMethod(_module, "MutablePath_addArcToPoint");
            _mutablePath_addCurveToPoint = NativeImplClient.GetModuleMethod(_module, "MutablePath_addCurveToPoint");
            _mutablePath_addLines = NativeImplClient.GetModuleMethod(_module, "MutablePath_addLines");
            _mutablePath_addLineToPoint = NativeImplClient.GetModuleMethod(_module, "MutablePath_addLineToPoint");
            _mutablePath_addQuadCurveToPoint = NativeImplClient.GetModuleMethod(_module, "MutablePath_addQuadCurveToPoint");
            _mutablePath_closeSubpath = NativeImplClient.GetModuleMethod(_module, "MutablePath_closeSubpath");
            _mutablePath_dispose = NativeImplClient.GetModuleMethod(_module, "MutablePath_dispose");
            _drawContext_saveGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_saveGState");
            _drawContext_restoreGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_restoreGState");
            _drawContext_setRGBFillColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setRGBFillColor");
            _drawContext_setRGBStrokeColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setRGBStrokeColor");
            _drawContext_setFillColorWithColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setFillColorWithColor");
            _drawContext_fillRect = NativeImplClient.GetModuleMethod(_module, "DrawContext_fillRect");
            _drawContext_setTextMatrix = NativeImplClient.GetModuleMethod(_module, "DrawContext_setTextMatrix");
            _drawContext_setTextPosition = NativeImplClient.GetModuleMethod(_module, "DrawContext_setTextPosition");
            _drawContext_beginPath = NativeImplClient.GetModuleMethod(_module, "DrawContext_beginPath");
            _drawContext_addArc = NativeImplClient.GetModuleMethod(_module, "DrawContext_addArc");
            _drawContext_addArcToPoint = NativeImplClient.GetModuleMethod(_module, "DrawContext_addArcToPoint");
            _drawContext_drawPath = NativeImplClient.GetModuleMethod(_module, "DrawContext_drawPath");
            _drawContext_setStrokeColorWithColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setStrokeColorWithColor");
            _drawContext_strokeRectWithWidth = NativeImplClient.GetModuleMethod(_module, "DrawContext_strokeRectWithWidth");
            _drawContext_moveToPoint = NativeImplClient.GetModuleMethod(_module, "DrawContext_moveToPoint");
            _drawContext_addLineToPoint = NativeImplClient.GetModuleMethod(_module, "DrawContext_addLineToPoint");
            _drawContext_strokePath = NativeImplClient.GetModuleMethod(_module, "DrawContext_strokePath");
            _drawContext_setLineDash = NativeImplClient.GetModuleMethod(_module, "DrawContext_setLineDash");
            _drawContext_clearLineDash = NativeImplClient.GetModuleMethod(_module, "DrawContext_clearLineDash");
            _drawContext_setLineWidth = NativeImplClient.GetModuleMethod(_module, "DrawContext_setLineWidth");
            _drawContext_clip = NativeImplClient.GetModuleMethod(_module, "DrawContext_clip");
            _drawContext_clipToRect = NativeImplClient.GetModuleMethod(_module, "DrawContext_clipToRect");
            _drawContext_translateCTM = NativeImplClient.GetModuleMethod(_module, "DrawContext_translateCTM");
            _drawContext_scaleCTM = NativeImplClient.GetModuleMethod(_module, "DrawContext_scaleCTM");
            _drawContext_rotateCTM = NativeImplClient.GetModuleMethod(_module, "DrawContext_rotateCTM");
            _drawContext_concatCTM = NativeImplClient.GetModuleMethod(_module, "DrawContext_concatCTM");
            _drawContext_addPath = NativeImplClient.GetModuleMethod(_module, "DrawContext_addPath");
            _drawContext_fillPath = NativeImplClient.GetModuleMethod(_module, "DrawContext_fillPath");
            _drawContext_strokeRect = NativeImplClient.GetModuleMethod(_module, "DrawContext_strokeRect");
            _drawContext_addRect = NativeImplClient.GetModuleMethod(_module, "DrawContext_addRect");
            _drawContext_closePath = NativeImplClient.GetModuleMethod(_module, "DrawContext_closePath");
            _drawContext_drawLinearGradient = NativeImplClient.GetModuleMethod(_module, "DrawContext_drawLinearGradient");
            _drawContext_setTextDrawingMode = NativeImplClient.GetModuleMethod(_module, "DrawContext_setTextDrawingMode");
            _drawContext_clipToMask = NativeImplClient.GetModuleMethod(_module, "DrawContext_clipToMask");
            _drawContext_drawImage = NativeImplClient.GetModuleMethod(_module, "DrawContext_drawImage");
            _drawContext_dispose = NativeImplClient.GetModuleMethod(_module, "DrawContext_dispose");
            _bitmapLock_dispose = NativeImplClient.GetModuleMethod(_module, "BitmapLock_dispose");
            _image_dispose = NativeImplClient.GetModuleMethod(_module, "Image_dispose");
            _bitmapDrawContext_createImage = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_createImage");
            _bitmapDrawContext_getData = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_getData");
            _bitmapDrawContext_dispose = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_dispose");
            AffineTransform._translate = NativeImplClient.GetModuleMethod(_module, "AffineTransform.translate");
            AffineTransform._rotate = NativeImplClient.GetModuleMethod(_module, "AffineTransform.rotate");
            AffineTransform._scale = NativeImplClient.GetModuleMethod(_module, "AffineTransform.scale");
            AffineTransform._concat = NativeImplClient.GetModuleMethod(_module, "AffineTransform.concat");
            AffineBatchOps._process = NativeImplClient.GetModuleMethod(_module, "AffineBatchOps.process");
            Color._createGenericRGB = NativeImplClient.GetModuleMethod(_module, "Color.createGenericRGB");
            Color._getConstantColor = NativeImplClient.GetModuleMethod(_module, "Color.getConstantColor");
            ColorSpace._createWithName = NativeImplClient.GetModuleMethod(_module, "ColorSpace.createWithName");
            ColorSpace._createDeviceGray = NativeImplClient.GetModuleMethod(_module, "ColorSpace.createDeviceGray");
            Gradient._createWithColorComponents = NativeImplClient.GetModuleMethod(_module, "Gradient.createWithColorComponents");
            Path._createWithRect = NativeImplClient.GetModuleMethod(_module, "Path.createWithRect");
            Path._createWithEllipseInRect = NativeImplClient.GetModuleMethod(_module, "Path.createWithEllipseInRect");
            Path._createWithRoundedRect = NativeImplClient.GetModuleMethod(_module, "Path.createWithRoundedRect");
            MutablePath._create = NativeImplClient.GetModuleMethod(_module, "MutablePath.create");
            MutablePath._transformException = NativeImplClient.GetException(_module, "MutablePath.TransformException");
            NativeImplClient.SetExceptionBuilder(MutablePath._transformException, MutablePath.TransformException.BuildAndThrow);
            BitmapDrawContext._create = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext.create");

            // no static init
        }

        internal static void __Shutdown()
        {
            // no static shutdown
        }
    }
}
