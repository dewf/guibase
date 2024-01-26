using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

using static Org.Prefixed.GuiBase.Foundation;

namespace Org.Prefixed.GuiBase
{
    public static class Drawing
    {
        private static ModuleHandle _module;
        private static ModuleMethodHandle _color_createGenericRGB;
        private static ModuleMethodHandle _color_getConstantColor;
        private static ModuleMethodHandle _Color_dispose;
        private static ModuleMethodHandle _colorSpace_createWithName;
        private static ModuleMethodHandle _colorSpace_createDeviceGray;
        private static ModuleMethodHandle _ColorSpace_dispose;
        private static ModuleMethodHandle _gradient_createWithColorComponents;
        private static ModuleMethodHandle _Gradient_dispose;
        private static ModuleMethodHandle _path_createWithRect;
        private static ModuleMethodHandle _path_createWithEllipseInRect;
        private static ModuleMethodHandle _path_createWithRoundedRect;
        private static ModuleMethodHandle _Path_dispose;
        private static ModuleMethodHandle _drawContext_saveGState;
        private static ModuleMethodHandle _drawContext_restoreGState;
        private static ModuleMethodHandle _drawContext_setRGBFillColor;
        private static ModuleMethodHandle _drawContext_setRGBStrokeColor;
        private static ModuleMethodHandle _drawContext_fillRect;
        private static ModuleMethodHandle _drawContext_setTextMatrix;
        private static ModuleMethodHandle _drawContext_setTextPosition;
        private static ModuleMethodHandle _drawContext_beginPath;
        private static ModuleMethodHandle _drawContext_addArc;
        private static ModuleMethodHandle _drawContext_addArcToPoint;
        private static ModuleMethodHandle _drawContext_drawPath;
        private static ModuleMethodHandle _drawContext_setStrokeColorWithColor;
        private static ModuleMethodHandle _drawContext_strokeRectWithWidth;
        private static ModuleMethodHandle _drawContext_moveToPoint;
        private static ModuleMethodHandle _drawContext_addLineToPoint;
        private static ModuleMethodHandle _drawContext_strokePath;
        private static ModuleMethodHandle _drawContext_setLineDash;
        private static ModuleMethodHandle _drawContext_clearLineDash;
        private static ModuleMethodHandle _drawContext_setLineWidth;
        private static ModuleMethodHandle _drawContext_clip;
        private static ModuleMethodHandle _drawContext_clipToRect;
        private static ModuleMethodHandle _drawContext_translateCTM;
        private static ModuleMethodHandle _drawContext_scaleCTM;
        private static ModuleMethodHandle _drawContext_rotateCTM;
        private static ModuleMethodHandle _drawContext_concatCTM;
        private static ModuleMethodHandle _drawContext_addPath;
        private static ModuleMethodHandle _drawContext_fillPath;
        private static ModuleMethodHandle _drawContext_strokeRect;
        private static ModuleMethodHandle _drawContext_addRect;
        private static ModuleMethodHandle _drawContext_closePath;
        private static ModuleMethodHandle _drawContext_drawLinearGradient;
        private static ModuleMethodHandle _DrawContext_dispose;
        private static ModuleMethodHandle _attributedString_create;
        private static ModuleMethodHandle _AttributedString_dispose;
        private static ModuleMethodHandle _font_createFromFile;
        private static ModuleMethodHandle _font_createWithName;
        private static ModuleMethodHandle _Font_dispose;
        private static ModuleMethodHandle _line_getTypographicBounds;
        private static ModuleMethodHandle _line_getBoundsWithOptions;
        private static ModuleMethodHandle _line_draw;
        private static ModuleMethodHandle _line_createWithAttributedString;
        private static ModuleMethodHandle _Line_dispose;
        public static AffineTransform AffineTransformIdentity { get; private set; }

        public struct AffineTransform {
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

        public struct AttributedStringOptions
        {
            [Flags]
            internal enum Fields
            {
                ForegroundColor = 1,
                ForegroundColorFromContext = 2,
                Font = 4,
                StrokeWidth = 8,
                StrokeColor = 16
            }
            internal Fields UsedFields;

            private Color _foregroundColor;
            public Color ForegroundColor
            {
                set
                {
                    _foregroundColor = value;
                    UsedFields |= Fields.ForegroundColor;
                }
            }
            public bool HasForegroundColor(out Color value)
            {
                if (UsedFields.HasFlag(Fields.ForegroundColor))
                {
                    value = _foregroundColor;
                    return true;
                }
                value = default;
                return false;
            }
            private bool _foregroundColorFromContext;
            public bool ForegroundColorFromContext
            {
                set
                {
                    _foregroundColorFromContext = value;
                    UsedFields |= Fields.ForegroundColorFromContext;
                }
            }
            public bool HasForegroundColorFromContext(out bool value)
            {
                if (UsedFields.HasFlag(Fields.ForegroundColorFromContext))
                {
                    value = _foregroundColorFromContext;
                    return true;
                }
                value = default;
                return false;
            }
            private Font _font;
            public Font Font
            {
                set
                {
                    _font = value;
                    UsedFields |= Fields.Font;
                }
            }
            public bool HasFont(out Font value)
            {
                if (UsedFields.HasFlag(Fields.Font))
                {
                    value = _font;
                    return true;
                }
                value = default;
                return false;
            }
            private double _strokeWidth;
            public double StrokeWidth
            {
                set
                {
                    _strokeWidth = value;
                    UsedFields |= Fields.StrokeWidth;
                }
            }
            public bool HasStrokeWidth(out double value)
            {
                if (UsedFields.HasFlag(Fields.StrokeWidth))
                {
                    value = _strokeWidth;
                    return true;
                }
                value = default;
                return false;
            }
            private Color _strokeColor;
            public Color StrokeColor
            {
                set
                {
                    _strokeColor = value;
                    UsedFields |= Fields.StrokeColor;
                }
            }
            public bool HasStrokeColor(out Color value)
            {
                if (UsedFields.HasFlag(Fields.StrokeColor))
                {
                    value = _strokeColor;
                    return true;
                }
                value = default;
                return false;
            }
        }
        internal static void AttributedStringOptions__Push(AttributedStringOptions value, bool isReturn)
        {
            if (value.HasStrokeColor(out var strokeColor))
            {
                Color__Push(strokeColor);
            }
            if (value.HasStrokeWidth(out var strokeWidth))
            {
                NativeImplClient.PushDouble(strokeWidth);
            }
            if (value.HasFont(out var font))
            {
                Font__Push(font);
            }
            if (value.HasForegroundColorFromContext(out var foregroundColorFromContext))
            {
                NativeImplClient.PushBool(foregroundColorFromContext);
            }
            if (value.HasForegroundColor(out var foregroundColor))
            {
                Color__Push(foregroundColor);
            }
            NativeImplClient.PushInt32((int)value.UsedFields);
        }
        internal static AttributedStringOptions AttributedStringOptions__Pop()
        {
            var opts = new AttributedStringOptions
            {
                UsedFields = (AttributedStringOptions.Fields)NativeImplClient.PopInt32()
            };
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.ForegroundColor))
            {
                opts.ForegroundColor = Color__Pop();
            }
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.ForegroundColorFromContext))
            {
                opts.ForegroundColorFromContext = NativeImplClient.PopBool();
            }
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.Font))
            {
                opts.Font = Font__Pop();
            }
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.StrokeWidth))
            {
                opts.StrokeWidth = NativeImplClient.PopDouble();
            }
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.StrokeColor))
            {
                opts.StrokeColor = Color__Pop();
            }
            return opts;
        }

        public class AttributedString : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal AttributedString(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    AttributedString__Push(this);
                    NativeImplClient.InvokeModuleMethod(_AttributedString_dispose);
                    _disposed = true;
                }
            }
            public static AttributedString Create(string s, AttributedStringOptions opts)
            {
                AttributedStringOptions__Push(opts, false);
                NativeImplClient.PushString(s);
                NativeImplClient.InvokeModuleMethod(_attributedString_create);
                return AttributedString__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void AttributedString__Push(AttributedString thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static AttributedString AttributedString__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new AttributedString(ptr) : null;
        }

        public enum ColorConstants
        {
            White,
            Black,
            Clear
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void ColorConstants__Push(ColorConstants value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static ColorConstants ColorConstants__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (ColorConstants)ret;
        }

        public class Color : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Color(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Color__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Color_dispose);
                    _disposed = true;
                }
            }
            public static Color CreateGenericRGB(double red, double green, double blue, double alpha)
            {
                NativeImplClient.PushDouble(alpha);
                NativeImplClient.PushDouble(blue);
                NativeImplClient.PushDouble(green);
                NativeImplClient.PushDouble(red);
                NativeImplClient.InvokeModuleMethod(_color_createGenericRGB);
                return Color__Pop();
            }
            public static Color GetConstantColor(ColorConstants which)
            {
                ColorConstants__Push(which);
                NativeImplClient.InvokeModuleMethod(_color_getConstantColor);
                return Color__Pop();
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

        public enum ColorSpaceName
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
        internal static void ColorSpaceName__Push(ColorSpaceName value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static ColorSpaceName ColorSpaceName__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (ColorSpaceName)ret;
        }

        public class ColorSpace : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal ColorSpace(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    ColorSpace__Push(this);
                    NativeImplClient.InvokeModuleMethod(_ColorSpace_dispose);
                    _disposed = true;
                }
            }
            public static ColorSpace CreateWithName(ColorSpaceName name)
            {
                ColorSpaceName__Push(name);
                NativeImplClient.InvokeModuleMethod(_colorSpace_createWithName);
                return ColorSpace__Pop();
            }
            public static ColorSpace CreateDeviceGray()
            {
                NativeImplClient.InvokeModuleMethod(_colorSpace_createDeviceGray);
                return ColorSpace__Pop();
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

        public enum PathDrawingMode
        {
            Fill,
            EOFill,
            Stroke,
            FillStroke,
            EOFillStroke
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void PathDrawingMode__Push(PathDrawingMode value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static PathDrawingMode PathDrawingMode__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (PathDrawingMode)ret;
        }

        // built-in array type: double[]

        [Flags]
        public enum GradientDrawingOptions
        {
            DrawsBeforeStartLocation = 1,
            DrawsAfterEndLocation = 2
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void GradientDrawingOptions__Push(GradientDrawingOptions value)
        {
            NativeImplClient.PushUInt32((uint)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static GradientDrawingOptions GradientDrawingOptions__Pop()
        {
            var ret = NativeImplClient.PopUInt32();
            return (GradientDrawingOptions)ret;
        }

        public class DrawContext : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal DrawContext(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    DrawContext__Push(this);
                    NativeImplClient.InvokeModuleMethod(_DrawContext_dispose);
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
            public void DrawPath(PathDrawingMode mode)
            {
                PathDrawingMode__Push(mode);
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
            public void DrawLinearGradient(Gradient gradient, Point startPoint, Point endPoint, GradientDrawingOptions drawOpts)
            {
                GradientDrawingOptions__Push(drawOpts);
                Point__Push(endPoint, false);
                Point__Push(startPoint, false);
                Gradient__Push(gradient);
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_drawContext_drawLinearGradient);
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

        public struct OptArgs
        {
            [Flags]
            internal enum Fields
            {
                Transform = 1
            }
            internal Fields UsedFields;

            private AffineTransform _transform;
            public AffineTransform Transform
            {
                set
                {
                    _transform = value;
                    UsedFields |= Fields.Transform;
                }
            }
            public bool HasTransform(out AffineTransform value)
            {
                if (UsedFields.HasFlag(Fields.Transform))
                {
                    value = _transform;
                    return true;
                }
                value = default;
                return false;
            }
        }
        internal static void OptArgs__Push(OptArgs value, bool isReturn)
        {
            if (value.HasTransform(out var transform))
            {
                AffineTransform__Push(transform, isReturn);
            }
            NativeImplClient.PushInt32((int)value.UsedFields);
        }
        internal static OptArgs OptArgs__Pop()
        {
            var opts = new OptArgs
            {
                UsedFields = (OptArgs.Fields)NativeImplClient.PopInt32()
            };
            if (opts.UsedFields.HasFlag(OptArgs.Fields.Transform))
            {
                opts.Transform = AffineTransform__Pop();
            }
            return opts;
        }

        public class Font : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Font(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Font__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Font_dispose);
                    _disposed = true;
                }
            }
            public static Font CreateFromFile(string path, double size, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(size);
                NativeImplClient.PushString(path);
                NativeImplClient.InvokeModuleMethod(_font_createFromFile);
                return Font__Pop();
            }
            public static Font CreateWithName(string name, double size, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(size);
                NativeImplClient.PushString(name);
                NativeImplClient.InvokeModuleMethod(_font_createWithName);
                return Font__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Font__Push(Font thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Font Font__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Font(ptr) : null;
        }

        public struct GradientStop {
            public double Location;
            public double Red;
            public double Green;
            public double Blue;
            public double Alpha;
            public GradientStop(double location, double red, double green, double blue, double alpha)
            {
                this.Location = location;
                this.Red = red;
                this.Green = green;
                this.Blue = blue;
                this.Alpha = alpha;
            }
        }

        internal static void GradientStop__Push(GradientStop value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Alpha);
            NativeImplClient.PushDouble(value.Blue);
            NativeImplClient.PushDouble(value.Green);
            NativeImplClient.PushDouble(value.Red);
            NativeImplClient.PushDouble(value.Location);
        }

        internal static GradientStop GradientStop__Pop()
        {
            var location = NativeImplClient.PopDouble();
            var red = NativeImplClient.PopDouble();
            var green = NativeImplClient.PopDouble();
            var blue = NativeImplClient.PopDouble();
            var alpha = NativeImplClient.PopDouble();
            return new GradientStop(location, red, green, blue, alpha);
        }

        internal static void __GradientStop_Array__Push(GradientStop[] items, bool isReturn)
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

        internal static GradientStop[] __GradientStop_Array__Pop()
        {
            var f0Values = NativeImplClient.PopDoubleArray();
            var f1Values = NativeImplClient.PopDoubleArray();
            var f2Values = NativeImplClient.PopDoubleArray();
            var f3Values = NativeImplClient.PopDoubleArray();
            var f4Values = NativeImplClient.PopDoubleArray();
            var count = f0Values.Length;
            var ret = new GradientStop[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                var f3 = f3Values[i];
                var f4 = f4Values[i];
                ret[i] = new GradientStop(f0, f1, f2, f3, f4);
            }
            return ret;
        }

        public class Gradient : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Gradient(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Gradient__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Gradient_dispose);
                    _disposed = true;
                }
            }
            public static Gradient CreateWithColorComponents(ColorSpace space, GradientStop[] stops)
            {
                __GradientStop_Array__Push(stops, false);
                ColorSpace__Push(space);
                NativeImplClient.InvokeModuleMethod(_gradient_createWithColorComponents);
                return Gradient__Pop();
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

        public struct TypographicBounds {
            public double Width;
            public double Ascent;
            public double Descent;
            public double Leading;
            public TypographicBounds(double width, double ascent, double descent, double leading)
            {
                this.Width = width;
                this.Ascent = ascent;
                this.Descent = descent;
                this.Leading = leading;
            }
        }

        internal static void TypographicBounds__Push(TypographicBounds value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Leading);
            NativeImplClient.PushDouble(value.Descent);
            NativeImplClient.PushDouble(value.Ascent);
            NativeImplClient.PushDouble(value.Width);
        }

        internal static TypographicBounds TypographicBounds__Pop()
        {
            var width = NativeImplClient.PopDouble();
            var ascent = NativeImplClient.PopDouble();
            var descent = NativeImplClient.PopDouble();
            var leading = NativeImplClient.PopDouble();
            return new TypographicBounds(width, ascent, descent, leading);
        }

        [Flags]
        public enum LineBoundsOptions
        {
            ExcludeTypographicLeading = 1,
            ExcludeTypographicShifts = 2,
            UseHangingPunctuation = 4,
            UseGlyphPathBounds = 8,
            UseOpticalBounds = 16
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void LineBoundsOptions__Push(LineBoundsOptions value)
        {
            NativeImplClient.PushUInt32((uint)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static LineBoundsOptions LineBoundsOptions__Pop()
        {
            var ret = NativeImplClient.PopUInt32();
            return (LineBoundsOptions)ret;
        }

        public class Line : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Line(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Line__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Line_dispose);
                    _disposed = true;
                }
            }
            public TypographicBounds GetTypographicBounds()
            {
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_getTypographicBounds);
                return TypographicBounds__Pop();
            }
            public Rect GetBoundsWithOptions(LineBoundsOptions opts)
            {
                LineBoundsOptions__Push(opts);
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_getBoundsWithOptions);
                return Rect__Pop();
            }
            public void Draw(DrawContext context)
            {
                DrawContext__Push(context);
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_draw);
            }
            public static Line CreateWithAttributedString(AttributedString str)
            {
                AttributedString__Push(str);
                NativeImplClient.InvokeModuleMethod(_line_createWithAttributedString);
                return Line__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Line__Push(Line thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Line Line__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Line(ptr) : null;
        }

        public class Path : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal Path(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                if (!_disposed)
                {
                    Path__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Path_dispose);
                    _disposed = true;
                }
            }
            public static Path CreateWithRect(Rect rect, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                Rect__Push(rect, false);
                NativeImplClient.InvokeModuleMethod(_path_createWithRect);
                return Path__Pop();
            }
            public static Path CreateWithEllipseInRect(Rect rect, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                Rect__Push(rect, false);
                NativeImplClient.InvokeModuleMethod(_path_createWithEllipseInRect);
                return Path__Pop();
            }
            public static Path CreateWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(cornerHeight);
                NativeImplClient.PushDouble(cornerWidth);
                Rect__Push(rect, false);
                NativeImplClient.InvokeModuleMethod(_path_createWithRoundedRect);
                return Path__Pop();
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

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Drawing");

            NativeImplClient.PushModuleConstants(_module);
            AffineTransformIdentity = AffineTransform__Pop();

            _color_createGenericRGB = NativeImplClient.GetModuleMethod(_module, "Color_createGenericRGB");
            _color_getConstantColor = NativeImplClient.GetModuleMethod(_module, "Color_getConstantColor");
            _Color_dispose = NativeImplClient.GetModuleMethod(_module, "Color_dispose");
            _colorSpace_createWithName = NativeImplClient.GetModuleMethod(_module, "ColorSpace_createWithName");
            _colorSpace_createDeviceGray = NativeImplClient.GetModuleMethod(_module, "ColorSpace_createDeviceGray");
            _ColorSpace_dispose = NativeImplClient.GetModuleMethod(_module, "ColorSpace_dispose");
            _gradient_createWithColorComponents = NativeImplClient.GetModuleMethod(_module, "Gradient_createWithColorComponents");
            _Gradient_dispose = NativeImplClient.GetModuleMethod(_module, "Gradient_dispose");
            _path_createWithRect = NativeImplClient.GetModuleMethod(_module, "Path_createWithRect");
            _path_createWithEllipseInRect = NativeImplClient.GetModuleMethod(_module, "Path_createWithEllipseInRect");
            _path_createWithRoundedRect = NativeImplClient.GetModuleMethod(_module, "Path_createWithRoundedRect");
            _Path_dispose = NativeImplClient.GetModuleMethod(_module, "Path_dispose");
            _drawContext_saveGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_saveGState");
            _drawContext_restoreGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_restoreGState");
            _drawContext_setRGBFillColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setRGBFillColor");
            _drawContext_setRGBStrokeColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setRGBStrokeColor");
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
            _DrawContext_dispose = NativeImplClient.GetModuleMethod(_module, "DrawContext_dispose");
            _attributedString_create = NativeImplClient.GetModuleMethod(_module, "AttributedString_create");
            _AttributedString_dispose = NativeImplClient.GetModuleMethod(_module, "AttributedString_dispose");
            _font_createFromFile = NativeImplClient.GetModuleMethod(_module, "Font_createFromFile");
            _font_createWithName = NativeImplClient.GetModuleMethod(_module, "Font_createWithName");
            _Font_dispose = NativeImplClient.GetModuleMethod(_module, "Font_dispose");
            _line_getTypographicBounds = NativeImplClient.GetModuleMethod(_module, "Line_getTypographicBounds");
            _line_getBoundsWithOptions = NativeImplClient.GetModuleMethod(_module, "Line_getBoundsWithOptions");
            _line_draw = NativeImplClient.GetModuleMethod(_module, "Line_draw");
            _line_createWithAttributedString = NativeImplClient.GetModuleMethod(_module, "Line_createWithAttributedString");
            _Line_dispose = NativeImplClient.GetModuleMethod(_module, "Line_dispose");

            // no static init
        }

        internal static void Shutdown()
        {
            // no static shutdown
        }
    }
}
