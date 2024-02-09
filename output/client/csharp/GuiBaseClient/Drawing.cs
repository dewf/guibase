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
        private static ModuleMethodHandle _AffineTransformTranslate;
        private static ModuleMethodHandle _AffineTransformRotate;
        private static ModuleMethodHandle _AffineTransformScale;
        private static ModuleMethodHandle _AffineTransformConcat;
        private static ModuleMethodHandle _Color_dispose;
        private static ModuleMethodHandle _color_createGenericRGB;
        private static ModuleMethodHandle _color_getConstantColor;
        private static ModuleMethodHandle _ColorSpace_dispose;
        private static ModuleMethodHandle _colorSpace_createWithName;
        private static ModuleMethodHandle _colorSpace_createDeviceGray;
        private static ModuleMethodHandle _Gradient_dispose;
        private static ModuleMethodHandle _gradient_createWithColorComponents;
        private static ModuleMethodHandle _path_getCurrentPoint;
        private static ModuleMethodHandle _path_createCopy;
        private static ModuleMethodHandle _path_createMutableCopy;
        private static ModuleMethodHandle _Path_dispose;
        private static ModuleMethodHandle _path_createWithRect;
        private static ModuleMethodHandle _path_createWithEllipseInRect;
        private static ModuleMethodHandle _path_createWithRoundedRect;
        private static ModuleMethodHandle _mutablePath_addPath;
        private static ModuleMethodHandle _mutablePath_addRect;
        private static ModuleMethodHandle _mutablePath_addRects;
        private static ModuleMethodHandle _mutablePath_addRoundedRect;
        private static ModuleMethodHandle _mutablePath_addEllipseInRect;
        private static ModuleMethodHandle _mutablePath_moveToPoint;
        private static ModuleMethodHandle _mutablePath_addArc;
        private static ModuleMethodHandle _mutablePath_addRelativeArc;
        private static ModuleMethodHandle _mutablePath_addArcToPoint;
        private static ModuleMethodHandle _mutablePath_addCurveToPoint;
        private static ModuleMethodHandle _mutablePath_addLines;
        private static ModuleMethodHandle _mutablePath_addLineToPoint;
        private static ModuleMethodHandle _mutablePath_addQuadCurveToPoint;
        private static ModuleMethodHandle _mutablePath_closeSubpath;
        private static ModuleMethodHandle _MutablePath_dispose;
        private static ModuleMethodHandle _mutablePath_create;
        private static ModuleMethodHandle _drawContext_saveGState;
        private static ModuleMethodHandle _drawContext_restoreGState;
        private static ModuleMethodHandle _drawContext_setRGBFillColor;
        private static ModuleMethodHandle _drawContext_setRGBStrokeColor;
        private static ModuleMethodHandle _drawContext_setFillColorWithColor;
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
        private static ModuleMethodHandle _drawContext_setTextDrawingMode;
        private static ModuleMethodHandle _drawContext_clipToMask;
        private static ModuleMethodHandle _drawContext_drawImage;
        private static ModuleMethodHandle _DrawContext_dispose;
        private static ModuleMethodHandle _attributedString_getLength;
        private static ModuleMethodHandle _attributedString_createMutableCopy;
        private static ModuleMethodHandle _AttributedString_dispose;
        private static ModuleMethodHandle _attributedString_create;
        private static ModuleMethodHandle _mutableAttributedString_replaceString;
        private static ModuleMethodHandle _mutableAttributedString_setAttribute;
        private static ModuleMethodHandle _mutableAttributedString_setCustomAttribute;
        private static ModuleMethodHandle _mutableAttributedString_beginEditing;
        private static ModuleMethodHandle _mutableAttributedString_endEditing;
        private static ModuleMethodHandle _MutableAttributedString_dispose;
        private static ModuleMethodHandle _mutableAttributedString_create;
        private static ModuleMethodHandle _font_createCopyWithSymbolicTraits;
        private static ModuleMethodHandle _font_getAscent;
        private static ModuleMethodHandle _font_getDescent;
        private static ModuleMethodHandle _font_getUnderlineThickness;
        private static ModuleMethodHandle _font_getUnderlinePosition;
        private static ModuleMethodHandle _Font_dispose;
        private static ModuleMethodHandle _font_createFromFile;
        private static ModuleMethodHandle _font_createWithName;
        private static ModuleMethodHandle _run_getAttributes;
        private static ModuleMethodHandle _run_getTypographicBounds;
        private static ModuleMethodHandle _run_getStringRange;
        private static ModuleMethodHandle _run_getStatus;
        private static ModuleMethodHandle _Run_dispose;
        private static ModuleMethodHandle _line_getStringRange;
        private static ModuleMethodHandle _line_getTypographicBounds;
        private static ModuleMethodHandle _line_getBoundsWithOptions;
        private static ModuleMethodHandle _line_draw;
        private static ModuleMethodHandle _line_getGlyphRuns;
        private static ModuleMethodHandle _line_getOffsetForStringIndex;
        private static ModuleMethodHandle _line_getStringIndexForPosition;
        private static ModuleMethodHandle _Line_dispose;
        private static ModuleMethodHandle _line_createWithAttributedString;
        private static ModuleMethodHandle _frame_draw;
        private static ModuleMethodHandle _frame_getLines;
        private static ModuleMethodHandle _frame_getLineOrigins;
        private static ModuleMethodHandle _frame_getLinesExtended;
        private static ModuleMethodHandle _Frame_dispose;
        private static ModuleMethodHandle _frameSetter_createFrame;
        private static ModuleMethodHandle _FrameSetter_dispose;
        private static ModuleMethodHandle _frameSetter_createWithAttributedString;
        private static ModuleMethodHandle _ParagraphStyle_dispose;
        private static ModuleMethodHandle _paragraphStyle_create;
        private static ModuleMethodHandle _BitmapLock_dispose;
        private static ModuleMethodHandle _Image_dispose;
        private static ModuleMethodHandle _bitmapDrawContext_createImage;
        private static ModuleMethodHandle _bitmapDrawContext_getData;
        private static ModuleMethodHandle _BitmapDrawContext_dispose;
        private static ModuleMethodHandle _bitmapDrawContext_create;
        private static ExceptionHandle _mutablePathTransformException;
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

        // built-in array type: string[]

        // built-in array type: long[]

        internal static void __String_Long_Map__Push(Dictionary<string, long> map, bool isReturn)
        {
            NativeImplClient.PushInt64Array(map.Values.ToArray());
            NativeImplClient.PushStringArray(map.Keys.ToArray());
        }

        internal static Dictionary<string, long> __String_Long_Map__Pop()
        {
            var keys = NativeImplClient.PopStringArray();
            var values = NativeImplClient.PopInt64Array();
            var ret = new Dictionary<string,long>();
            for (var i = 0; i < keys.Length; i++)
            {
                ret[keys[i]] = values[i];
            }
            return ret;
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
                StrokeColor = 16,
                ParagraphStyle = 32,
                Custom = 64
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
            public readonly bool HasForegroundColor(out Color value)
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
            public readonly bool HasForegroundColorFromContext(out bool value)
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
            public readonly bool HasFont(out Font value)
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
            public readonly bool HasStrokeWidth(out double value)
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
            public readonly bool HasStrokeColor(out Color value)
            {
                if (UsedFields.HasFlag(Fields.StrokeColor))
                {
                    value = _strokeColor;
                    return true;
                }
                value = default;
                return false;
            }
            private ParagraphStyle _paragraphStyle;
            public ParagraphStyle ParagraphStyle
            {
                set
                {
                    _paragraphStyle = value;
                    UsedFields |= Fields.ParagraphStyle;
                }
            }
            public readonly bool HasParagraphStyle(out ParagraphStyle value)
            {
                if (UsedFields.HasFlag(Fields.ParagraphStyle))
                {
                    value = _paragraphStyle;
                    return true;
                }
                value = default;
                return false;
            }
            private Dictionary<string,long> _custom;
            public Dictionary<string,long> Custom
            {
                set
                {
                    _custom = value;
                    UsedFields |= Fields.Custom;
                }
            }
            public readonly bool HasCustom(out Dictionary<string,long> value)
            {
                if (UsedFields.HasFlag(Fields.Custom))
                {
                    value = _custom;
                    return true;
                }
                value = default;
                return false;
            }
        }
        internal static void AttributedStringOptions__Push(AttributedStringOptions value, bool isReturn)
        {
            if (value.HasCustom(out var custom))
            {
                __String_Long_Map__Push(custom, isReturn);
            }
            if (value.HasParagraphStyle(out var paragraphStyle))
            {
                ParagraphStyle__Push(paragraphStyle);
            }
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
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.ParagraphStyle))
            {
                opts.ParagraphStyle = ParagraphStyle__Pop();
            }
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.Custom))
            {
                opts.Custom = __String_Long_Map__Pop();
            }
            return opts;
        }

        public class AttributedString : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal AttributedString(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
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
            public long GetLength()
            {
                AttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_attributedString_getLength);
                return NativeImplClient.PopInt64();
            }
            public MutableAttributedString CreateMutableCopy(long maxLength)
            {
                NativeImplClient.PushInt64(maxLength);
                AttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_attributedString_createMutableCopy);
                return MutableAttributedString__Pop();
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
                    NativeImplClient.InvokeModuleMethod(_BitmapDrawContext_dispose);
                    _disposed = true;
                }
            }
            public static BitmapDrawContext Create(int width, int height, int bitsPerComponent, int bytesPerRow, ColorSpace space, BitmapInfo bitmapInfo)
            {
                BitmapInfo__Push(bitmapInfo);
                ColorSpace__Push(space);
                NativeImplClient.PushInt32(bytesPerRow);
                NativeImplClient.PushInt32(bitsPerComponent);
                NativeImplClient.PushInt32(height);
                NativeImplClient.PushInt32(width);
                NativeImplClient.InvokeModuleMethod(_bitmapDrawContext_create);
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
                    NativeImplClient.InvokeModuleMethod(_BitmapLock_dispose);
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
            DrawsAfterEndLocation = 1 << 1
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

        public struct FontTraits
        {
            [Flags]
            internal enum Fields
            {
                Italic = 1,
                Bold = 2,
                Expanded = 4,
                Condensed = 8,
                Monospace = 16,
                Vertical = 32
            }
            internal Fields UsedFields;

            private bool _italic;
            public bool Italic
            {
                set
                {
                    _italic = value;
                    UsedFields |= Fields.Italic;
                }
            }
            public readonly bool HasItalic(out bool value)
            {
                if (UsedFields.HasFlag(Fields.Italic))
                {
                    value = _italic;
                    return true;
                }
                value = default;
                return false;
            }
            private bool _bold;
            public bool Bold
            {
                set
                {
                    _bold = value;
                    UsedFields |= Fields.Bold;
                }
            }
            public readonly bool HasBold(out bool value)
            {
                if (UsedFields.HasFlag(Fields.Bold))
                {
                    value = _bold;
                    return true;
                }
                value = default;
                return false;
            }
            private bool _expanded;
            public bool Expanded
            {
                set
                {
                    _expanded = value;
                    UsedFields |= Fields.Expanded;
                }
            }
            public readonly bool HasExpanded(out bool value)
            {
                if (UsedFields.HasFlag(Fields.Expanded))
                {
                    value = _expanded;
                    return true;
                }
                value = default;
                return false;
            }
            private bool _condensed;
            public bool Condensed
            {
                set
                {
                    _condensed = value;
                    UsedFields |= Fields.Condensed;
                }
            }
            public readonly bool HasCondensed(out bool value)
            {
                if (UsedFields.HasFlag(Fields.Condensed))
                {
                    value = _condensed;
                    return true;
                }
                value = default;
                return false;
            }
            private bool _monospace;
            public bool Monospace
            {
                set
                {
                    _monospace = value;
                    UsedFields |= Fields.Monospace;
                }
            }
            public readonly bool HasMonospace(out bool value)
            {
                if (UsedFields.HasFlag(Fields.Monospace))
                {
                    value = _monospace;
                    return true;
                }
                value = default;
                return false;
            }
            private bool _vertical;
            public bool Vertical
            {
                set
                {
                    _vertical = value;
                    UsedFields |= Fields.Vertical;
                }
            }
            public readonly bool HasVertical(out bool value)
            {
                if (UsedFields.HasFlag(Fields.Vertical))
                {
                    value = _vertical;
                    return true;
                }
                value = default;
                return false;
            }
        }
        internal static void FontTraits__Push(FontTraits value, bool isReturn)
        {
            if (value.HasVertical(out var vertical))
            {
                NativeImplClient.PushBool(vertical);
            }
            if (value.HasMonospace(out var monospace))
            {
                NativeImplClient.PushBool(monospace);
            }
            if (value.HasCondensed(out var condensed))
            {
                NativeImplClient.PushBool(condensed);
            }
            if (value.HasExpanded(out var expanded))
            {
                NativeImplClient.PushBool(expanded);
            }
            if (value.HasBold(out var bold))
            {
                NativeImplClient.PushBool(bold);
            }
            if (value.HasItalic(out var italic))
            {
                NativeImplClient.PushBool(italic);
            }
            NativeImplClient.PushInt32((int)value.UsedFields);
        }
        internal static FontTraits FontTraits__Pop()
        {
            var opts = new FontTraits
            {
                UsedFields = (FontTraits.Fields)NativeImplClient.PopInt32()
            };
            if (opts.UsedFields.HasFlag(FontTraits.Fields.Italic))
            {
                opts.Italic = NativeImplClient.PopBool();
            }
            if (opts.UsedFields.HasFlag(FontTraits.Fields.Bold))
            {
                opts.Bold = NativeImplClient.PopBool();
            }
            if (opts.UsedFields.HasFlag(FontTraits.Fields.Expanded))
            {
                opts.Expanded = NativeImplClient.PopBool();
            }
            if (opts.UsedFields.HasFlag(FontTraits.Fields.Condensed))
            {
                opts.Condensed = NativeImplClient.PopBool();
            }
            if (opts.UsedFields.HasFlag(FontTraits.Fields.Monospace))
            {
                opts.Monospace = NativeImplClient.PopBool();
            }
            if (opts.UsedFields.HasFlag(FontTraits.Fields.Vertical))
            {
                opts.Vertical = NativeImplClient.PopBool();
            }
            return opts;
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
            public readonly bool HasTransform(out AffineTransform value)
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
            protected bool _disposed;
            internal Font(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
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
            public Font CreateCopyWithSymbolicTraits(double size, FontTraits newTraits, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                FontTraits__Push(newTraits, false);
                NativeImplClient.PushDouble(size);
                Font__Push(this);
                NativeImplClient.InvokeModuleMethod(_font_createCopyWithSymbolicTraits);
                return Font__Pop();
            }
            public double GetAscent()
            {
                Font__Push(this);
                NativeImplClient.InvokeModuleMethod(_font_getAscent);
                return NativeImplClient.PopDouble();
            }
            public double GetDescent()
            {
                Font__Push(this);
                NativeImplClient.InvokeModuleMethod(_font_getDescent);
                return NativeImplClient.PopDouble();
            }
            public double GetUnderlineThickness()
            {
                Font__Push(this);
                NativeImplClient.InvokeModuleMethod(_font_getUnderlineThickness);
                return NativeImplClient.PopDouble();
            }
            public double GetUnderlinePosition()
            {
                Font__Push(this);
                NativeImplClient.InvokeModuleMethod(_font_getUnderlinePosition);
                return NativeImplClient.PopDouble();
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

        internal static void __Line_Array__Push(Line[] items)
        {
            var ptrs = items.Select(item => item.NativeHandle).ToArray();
            NativeImplClient.PushPtrArray(ptrs);
        }
        internal static Line[] __Line_Array__Pop()
        {
            return NativeImplClient.PopPtrArray()
                .Select(ptr => ptr != IntPtr.Zero ? new Line(ptr) : null)
                .ToArray();
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

        public struct Range {
            public long Location;
            public long Length;
            public Range(long location, long length)
            {
                this.Location = location;
                this.Length = length;
            }
        }

        internal static void Range__Push(Range value, bool isReturn)
        {
            NativeImplClient.PushInt64(value.Length);
            NativeImplClient.PushInt64(value.Location);
        }

        internal static Range Range__Pop()
        {
            var location = NativeImplClient.PopInt64();
            var length = NativeImplClient.PopInt64();
            return new Range(location, length);
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

        internal static void __TypographicBounds_Array__Push(TypographicBounds[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new double[count];
            var f1Values = new double[count];
            var f2Values = new double[count];
            var f3Values = new double[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Width;
                f1Values[i] = items[i].Ascent;
                f2Values[i] = items[i].Descent;
                f3Values[i] = items[i].Leading;
            }
            NativeImplClient.PushDoubleArray(f3Values);
            NativeImplClient.PushDoubleArray(f2Values);
            NativeImplClient.PushDoubleArray(f1Values);
            NativeImplClient.PushDoubleArray(f0Values);
        }

        internal static TypographicBounds[] __TypographicBounds_Array__Pop()
        {
            var f0Values = NativeImplClient.PopDoubleArray();
            var f1Values = NativeImplClient.PopDoubleArray();
            var f2Values = NativeImplClient.PopDoubleArray();
            var f3Values = NativeImplClient.PopDoubleArray();
            var count = f0Values.Length;
            var ret = new TypographicBounds[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                var f3 = f3Values[i];
                ret[i] = new TypographicBounds(f0, f1, f2, f3);
            }
            return ret;
        }

        internal static void __AttributedStringOptions_Array__Push(AttributedStringOptions[] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                AttributedStringOptions__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static AttributedStringOptions[] __AttributedStringOptions_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new AttributedStringOptions[count];
            for (var i = 0; i < count; i++)
            {
                ret[i] = AttributedStringOptions__Pop();
            }
            return ret;
        }

        internal static void __Range_Array__Push(Range[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new long[count];
            var f1Values = new long[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Location;
                f1Values[i] = items[i].Length;
            }
            NativeImplClient.PushInt64Array(f1Values);
            NativeImplClient.PushInt64Array(f0Values);
        }

        internal static Range[] __Range_Array__Pop()
        {
            var f0Values = NativeImplClient.PopInt64Array();
            var f1Values = NativeImplClient.PopInt64Array();
            var count = f0Values.Length;
            var ret = new Range[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                ret[i] = new Range(f0, f1);
            }
            return ret;
        }

        [Flags]
        public enum RunStatus
        {
            NoStatus = 0,
            RightToLeft = 1,
            NonMonotonic = 1 << 1,
            HasNonIdentityMatrix = 1 << 2
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void RunStatus__Push(RunStatus value)
        {
            NativeImplClient.PushUInt32((uint)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static RunStatus RunStatus__Pop()
        {
            var ret = NativeImplClient.PopUInt32();
            return (RunStatus)ret;
        }

        internal static void __RunStatus_Array__Push(RunStatus[] items)
        {
            var intValues = items.Select(i => (uint)i).ToArray();
            NativeImplClient.PushUInt32Array(intValues);
        }

        internal static RunStatus[] __RunStatus_Array__Pop()
        {
            var intValues = NativeImplClient.PopUInt32Array();
            return intValues.Select(i => (RunStatus)i).ToArray();
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

        public struct RunInfo {
            public AttributedStringOptions Attrs;
            public Range SourceRange;
            public RunStatus Status;
            public Rect Bounds;
            public TypographicBounds TypoBounds;
            public RunInfo(AttributedStringOptions attrs, Range sourceRange, RunStatus status, Rect bounds, TypographicBounds typoBounds)
            {
                this.Attrs = attrs;
                this.SourceRange = sourceRange;
                this.Status = status;
                this.Bounds = bounds;
                this.TypoBounds = typoBounds;
            }
        }

        internal static void RunInfo__Push(RunInfo value, bool isReturn)
        {
            TypographicBounds__Push(value.TypoBounds, isReturn);
            Rect__Push(value.Bounds, isReturn);
            RunStatus__Push(value.Status);
            Range__Push(value.SourceRange, isReturn);
            AttributedStringOptions__Push(value.Attrs, isReturn);
        }

        internal static RunInfo RunInfo__Pop()
        {
            var attrs = AttributedStringOptions__Pop();
            var sourceRange = Range__Pop();
            var status = RunStatus__Pop();
            var bounds = Rect__Pop();
            var typoBounds = TypographicBounds__Pop();
            return new RunInfo(attrs, sourceRange, status, bounds, typoBounds);
        }

        internal static void __RunInfo_Array__Push(RunInfo[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new AttributedStringOptions[count];
            var f1Values = new Range[count];
            var f2Values = new RunStatus[count];
            var f3Values = new Rect[count];
            var f4Values = new TypographicBounds[count];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Attrs;
                f1Values[i] = items[i].SourceRange;
                f2Values[i] = items[i].Status;
                f3Values[i] = items[i].Bounds;
                f4Values[i] = items[i].TypoBounds;
            }
            __TypographicBounds_Array__Push(f4Values, isReturn);
            __Rect_Array__Push(f3Values, isReturn);
            __RunStatus_Array__Push(f2Values);
            __Range_Array__Push(f1Values, isReturn);
            __AttributedStringOptions_Array__Push(f0Values, isReturn);
        }

        internal static RunInfo[] __RunInfo_Array__Pop()
        {
            var f0Values = __AttributedStringOptions_Array__Pop();
            var f1Values = __Range_Array__Pop();
            var f2Values = __RunStatus_Array__Pop();
            var f3Values = __Rect_Array__Pop();
            var f4Values = __TypographicBounds_Array__Pop();
            var count = f0Values.Length;
            var ret = new RunInfo[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                var f3 = f3Values[i];
                var f4 = f4Values[i];
                ret[i] = new RunInfo(f0, f1, f2, f3, f4);
            }
            return ret;
        }

        internal static void __RunInfo_Array_Array__Push(RunInfo[][] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                __RunInfo_Array__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static RunInfo[][] __RunInfo_Array_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new RunInfo[count][];
            for (var i = 0; i < count; i++)
            {
                ret[i] = __RunInfo_Array__Pop();
            }
            return ret;
        }

        public struct LineInfo {
            public Point Origin;
            public TypographicBounds LineTypoBounds;
            public RunInfo[] Runs;
            public LineInfo(Point origin, TypographicBounds lineTypoBounds, RunInfo[] runs)
            {
                this.Origin = origin;
                this.LineTypoBounds = lineTypoBounds;
                this.Runs = runs;
            }
        }

        internal static void LineInfo__Push(LineInfo value, bool isReturn)
        {
            __RunInfo_Array__Push(value.Runs, isReturn);
            TypographicBounds__Push(value.LineTypoBounds, isReturn);
            Point__Push(value.Origin, isReturn);
        }

        internal static LineInfo LineInfo__Pop()
        {
            var origin = Point__Pop();
            var lineTypoBounds = TypographicBounds__Pop();
            var runs = __RunInfo_Array__Pop();
            return new LineInfo(origin, lineTypoBounds, runs);
        }

        internal static void __LineInfo_Array__Push(LineInfo[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new Point[count];
            var f1Values = new TypographicBounds[count];
            var f2Values = new RunInfo[count][];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Origin;
                f1Values[i] = items[i].LineTypoBounds;
                f2Values[i] = items[i].Runs;
            }
            __RunInfo_Array_Array__Push(f2Values, isReturn);
            __TypographicBounds_Array__Push(f1Values, isReturn);
            __Point_Array__Push(f0Values, isReturn);
        }

        internal static LineInfo[] __LineInfo_Array__Pop()
        {
            var f0Values = __Point_Array__Pop();
            var f1Values = __TypographicBounds_Array__Pop();
            var f2Values = __RunInfo_Array_Array__Pop();
            var count = f0Values.Length;
            var ret = new LineInfo[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                ret[i] = new LineInfo(f0, f1, f2);
            }
            return ret;
        }

        public class Frame : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Frame(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Frame__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Frame_dispose);
                    _disposed = true;
                }
            }
            public void Draw(DrawContext context)
            {
                DrawContext__Push(context);
                Frame__Push(this);
                NativeImplClient.InvokeModuleMethod(_frame_draw);
            }
            public Line[] GetLines()
            {
                Frame__Push(this);
                NativeImplClient.InvokeModuleMethod(_frame_getLines);
                return __Line_Array__Pop();
            }
            public Point[] GetLineOrigins(Range range)
            {
                Range__Push(range, false);
                Frame__Push(this);
                NativeImplClient.InvokeModuleMethod(_frame_getLineOrigins);
                return __Point_Array__Pop();
            }
            public LineInfo[] GetLinesExtended(string[] customKeys)
            {
                NativeImplClient.PushStringArray(customKeys);
                Frame__Push(this);
                NativeImplClient.InvokeModuleMethod(_frame_getLinesExtended);
                return __LineInfo_Array__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Frame__Push(Frame thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Frame Frame__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Frame(ptr) : null;
        }

        public class FrameSetter : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal FrameSetter(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    FrameSetter__Push(this);
                    NativeImplClient.InvokeModuleMethod(_FrameSetter_dispose);
                    _disposed = true;
                }
            }
            public static FrameSetter CreateWithAttributedString(AttributedString str)
            {
                AttributedString__Push(str);
                NativeImplClient.InvokeModuleMethod(_frameSetter_createWithAttributedString);
                return FrameSetter__Pop();
            }
            public Frame CreateFrame(Range range, Path path)
            {
                Path__Push(path);
                Range__Push(range, false);
                FrameSetter__Push(this);
                NativeImplClient.InvokeModuleMethod(_frameSetter_createFrame);
                return Frame__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void FrameSetter__Push(FrameSetter thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static FrameSetter FrameSetter__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new FrameSetter(ptr) : null;
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
                    NativeImplClient.InvokeModuleMethod(_Image_dispose);
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
        public enum LineBoundsOptions
        {
            ExcludeTypographicLeading = 1,
            ExcludeTypographicShifts = 1 << 1,
            UseHangingPunctuation = 1 << 2,
            UseGlyphPathBounds = 1 << 3,
            UseOpticalBounds = 1 << 4
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

        internal static void __Run_Array__Push(Run[] items)
        {
            var ptrs = items.Select(item => item.NativeHandle).ToArray();
            NativeImplClient.PushPtrArray(ptrs);
        }
        internal static Run[] __Run_Array__Pop()
        {
            return NativeImplClient.PopPtrArray()
                .Select(ptr => ptr != IntPtr.Zero ? new Run(ptr) : null)
                .ToArray();
        }

        internal static void __DoubleDouble_Tuple__Push((double, double) value, bool isReturn)
        {
            NativeImplClient.PushDouble(value.Item2);
            NativeImplClient.PushDouble(value.Item1);
        }

        internal static (double, double) __DoubleDouble_Tuple__Pop()
        {
            var _0 = NativeImplClient.PopDouble();
            var _1 = NativeImplClient.PopDouble();
            return (_0, _1);
        }

        public class Line : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Line(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Line__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Line_dispose);
                    _disposed = true;
                }
            }
            public static Line CreateWithAttributedString(AttributedString str)
            {
                AttributedString__Push(str);
                NativeImplClient.InvokeModuleMethod(_line_createWithAttributedString);
                return Line__Pop();
            }
            public Range GetStringRange()
            {
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_getStringRange);
                return Range__Pop();
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
            public Run[] GetGlyphRuns()
            {
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_getGlyphRuns);
                return __Run_Array__Pop();
            }
            public (double, double) GetOffsetForStringIndex(long charIndex)
            {
                NativeImplClient.PushInt64(charIndex);
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_getOffsetForStringIndex);
                return __DoubleDouble_Tuple__Pop();
            }
            public long GetStringIndexForPosition(Point p)
            {
                Point__Push(p, false);
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_line_getStringIndexForPosition);
                return NativeImplClient.PopInt64();
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

        public class MutableAttributedString : AttributedString
        {
            internal MutableAttributedString(IntPtr nativeHandle) : base(nativeHandle)
            {
            }
            public override void Dispose()
            {
                if (!_disposed)
                {
                    MutableAttributedString__Push(this);
                    NativeImplClient.InvokeModuleMethod(_MutableAttributedString_dispose);
                    _disposed = true;
                }
            }
            public static MutableAttributedString Create(long maxLength)
            {
                NativeImplClient.PushInt64(maxLength);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_create);
                return MutableAttributedString__Pop();
            }
            public void ReplaceString(Range range, string str)
            {
                NativeImplClient.PushString(str);
                Range__Push(range, false);
                MutableAttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_replaceString);
            }
            public void SetAttribute(Range range, AttributedStringOptions attr)
            {
                AttributedStringOptions__Push(attr, false);
                Range__Push(range, false);
                MutableAttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_setAttribute);
            }
            public void SetCustomAttribute(Range range, string key, long value)
            {
                NativeImplClient.PushInt64(value);
                NativeImplClient.PushString(key);
                Range__Push(range, false);
                MutableAttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_setCustomAttribute);
            }
            public void BeginEditing()
            {
                MutableAttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_beginEditing);
            }
            public void EndEditing()
            {
                MutableAttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_endEditing);
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void MutableAttributedString__Push(MutableAttributedString thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static MutableAttributedString MutableAttributedString__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new MutableAttributedString(ptr) : null;
        }

        public class MutablePathTransformException : Exception
        {
            public readonly string Error;
            public MutablePathTransformException(string error) : base("MutablePathTransformException")
            {
                Error = error;
            }
            internal void PushAndSet()
            {
                NativeImplClient.PushString(Error);
                NativeImplClient.SetException(_mutablePathTransformException);
            }
            internal static void BuildAndThrow()
            {
                var error = NativeImplClient.PopString();
                throw new MutablePathTransformException(error);
            }
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
                    NativeImplClient.InvokeModuleMethod(_MutablePath_dispose);
                    _disposed = true;
                }
            }
            public static MutablePath Create()
            {
                NativeImplClient.InvokeModuleMethod(_mutablePath_create);
                return MutablePath__Pop();
            }
            public void AddPath(Path path2, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                Path__Push(path2);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addPath);
            }
            public void AddRect(Rect rect, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                Rect__Push(rect, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addRect);
            }
            public void AddRects(Rect[] rects, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                __Rect_Array__Push(rects, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addRects);
            }
            public void AddRoundedRect(Rect rect, double cornerWidth, double cornerHeight, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(cornerHeight);
                NativeImplClient.PushDouble(cornerWidth);
                Rect__Push(rect, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addRoundedRect);
            }
            public void AddEllipseInRect(Rect rect, OptArgs optArgs)
            {
                OptArgs__Push(optArgs, false);
                Rect__Push(rect, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutablePath_addEllipseInRect);
            }
            public void MoveToPoint(double x, double y, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_moveToPoint);
            }
            public void AddArc(double x, double y, double radius, double startAngle, double endAngle, bool clockwise, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushBool(clockwise);
                NativeImplClient.PushDouble(endAngle);
                NativeImplClient.PushDouble(startAngle);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addArc);
            }
            public void AddRelativeArc(double x, double y, double radius, double startAngle, double delta, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(delta);
                NativeImplClient.PushDouble(startAngle);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addRelativeArc);
            }
            public void AddArcToPoint(double x1, double y1, double x2, double y2, double radius, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(radius);
                NativeImplClient.PushDouble(y2);
                NativeImplClient.PushDouble(x2);
                NativeImplClient.PushDouble(y1);
                NativeImplClient.PushDouble(x1);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addArcToPoint);
            }
            public void AddCurveToPoint(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                NativeImplClient.PushDouble(cp2y);
                NativeImplClient.PushDouble(cp2x);
                NativeImplClient.PushDouble(cp1y);
                NativeImplClient.PushDouble(cp1x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addCurveToPoint);
            }
            public void AddLines(Point[] points, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                __Point_Array__Push(points, false);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addLines);
            }
            public void AddLineToPoint(double x, double y, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
                NativeImplClient.PushDouble(y);
                NativeImplClient.PushDouble(x);
                MutablePath__Push(this);
                NativeImplClient.InvokeModuleMethodWithExceptions(_mutablePath_addLineToPoint);
            }
            public void AddQuadCurveToPoint(double cpx, double cpy, double x, double y, OptArgs optArgs) // throws MutablePathTransformException
            {
                OptArgs__Push(optArgs, false);
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

        public enum TextAlignment
        {
            Left,
            Right,
            Center,
            Justified,
            Natural
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void TextAlignment__Push(TextAlignment value)
        {
            NativeImplClient.PushInt32((int)value);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static TextAlignment TextAlignment__Pop()
        {
            var ret = NativeImplClient.PopInt32();
            return (TextAlignment)ret;
        }

        public abstract record ParagraphStyleSetting
        {
            public sealed record Alignment(TextAlignment Value) : ParagraphStyleSetting
            {
                public TextAlignment Value { get; } = Value;
            }
        }

        private enum ParagraphStyleSetting__Tag
        {
            Alignment
        }

        internal static void ParagraphStyleSetting__Push(ParagraphStyleSetting thing, bool isReturn)
        {
            ParagraphStyleSetting__Tag which;
            switch (thing)
            {
                case ParagraphStyleSetting.Alignment alignment:
                    which = ParagraphStyleSetting__Tag.Alignment;
                    TextAlignment__Push(alignment.Value);
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(thing));
            }
            NativeImplClient.PushInt32((int)which);
        }

        internal static ParagraphStyleSetting ParagraphStyleSetting__Pop()
        {
            var which = NativeImplClient.PopInt32();
            switch ((ParagraphStyleSetting__Tag)which)
            {
                case ParagraphStyleSetting__Tag.Alignment:
                {
                    var value = TextAlignment__Pop();
                    return new ParagraphStyleSetting.Alignment(value);
                }
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        internal static void __ParagraphStyleSetting_Array__Push(ParagraphStyleSetting[] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                ParagraphStyleSetting__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static ParagraphStyleSetting[] __ParagraphStyleSetting_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new ParagraphStyleSetting[count];
            for (var i = 0; i < count; i++)
            {
                ret[i] = ParagraphStyleSetting__Pop();
            }
            return ret;
        }

        public class ParagraphStyle : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal ParagraphStyle(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    ParagraphStyle__Push(this);
                    NativeImplClient.InvokeModuleMethod(_ParagraphStyle_dispose);
                    _disposed = true;
                }
            }
            public static ParagraphStyle Create(ParagraphStyleSetting[] settings)
            {
                __ParagraphStyleSetting_Array__Push(settings, false);
                NativeImplClient.InvokeModuleMethod(_paragraphStyle_create);
                return ParagraphStyle__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void ParagraphStyle__Push(ParagraphStyle thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static ParagraphStyle ParagraphStyle__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new ParagraphStyle(ptr) : null;
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

        public class Run : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            protected bool _disposed;
            internal Run(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public virtual void Dispose()
            {
                if (!_disposed)
                {
                    Run__Push(this);
                    NativeImplClient.InvokeModuleMethod(_Run_dispose);
                    _disposed = true;
                }
            }
            public AttributedStringOptions GetAttributes(string[] customKeys)
            {
                NativeImplClient.PushStringArray(customKeys);
                Run__Push(this);
                NativeImplClient.InvokeModuleMethod(_run_getAttributes);
                return AttributedStringOptions__Pop();
            }
            public TypographicBounds GetTypographicBounds(Range range)
            {
                Range__Push(range, false);
                Run__Push(this);
                NativeImplClient.InvokeModuleMethod(_run_getTypographicBounds);
                return TypographicBounds__Pop();
            }
            public Range GetStringRange()
            {
                Run__Push(this);
                NativeImplClient.InvokeModuleMethod(_run_getStringRange);
                return Range__Pop();
            }
            public RunStatus GetStatus()
            {
                Run__Push(this);
                NativeImplClient.InvokeModuleMethod(_run_getStatus);
                return RunStatus__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void Run__Push(Run thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static Run Run__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new Run(ptr) : null;
        }

        public static AffineTransform AffineTransformTranslate(AffineTransform input, double tx, double ty)
        {
            NativeImplClient.PushDouble(ty);
            NativeImplClient.PushDouble(tx);
            AffineTransform__Push(input, false);
            NativeImplClient.InvokeModuleMethod(_AffineTransformTranslate);
            return AffineTransform__Pop();
        }

        public static AffineTransform AffineTransformRotate(AffineTransform input, double angle)
        {
            NativeImplClient.PushDouble(angle);
            AffineTransform__Push(input, false);
            NativeImplClient.InvokeModuleMethod(_AffineTransformRotate);
            return AffineTransform__Pop();
        }

        public static AffineTransform AffineTransformScale(AffineTransform input, double sx, double sy)
        {
            NativeImplClient.PushDouble(sy);
            NativeImplClient.PushDouble(sx);
            AffineTransform__Push(input, false);
            NativeImplClient.InvokeModuleMethod(_AffineTransformScale);
            return AffineTransform__Pop();
        }

        public static AffineTransform AffineTransformConcat(AffineTransform t1, AffineTransform t2)
        {
            AffineTransform__Push(t2, false);
            AffineTransform__Push(t1, false);
            NativeImplClient.InvokeModuleMethod(_AffineTransformConcat);
            return AffineTransform__Pop();
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Drawing");

            NativeImplClient.PushModuleConstants(_module);
            AffineTransformIdentity = AffineTransform__Pop();

            _AffineTransformTranslate = NativeImplClient.GetModuleMethod(_module, "AffineTransformTranslate");
            _AffineTransformRotate = NativeImplClient.GetModuleMethod(_module, "AffineTransformRotate");
            _AffineTransformScale = NativeImplClient.GetModuleMethod(_module, "AffineTransformScale");
            _AffineTransformConcat = NativeImplClient.GetModuleMethod(_module, "AffineTransformConcat");

            _Color_dispose = NativeImplClient.GetModuleMethod(_module, "Color_dispose");
            _color_createGenericRGB = NativeImplClient.GetModuleMethod(_module, "Color_createGenericRGB");
            _color_getConstantColor = NativeImplClient.GetModuleMethod(_module, "Color_getConstantColor");
            _ColorSpace_dispose = NativeImplClient.GetModuleMethod(_module, "ColorSpace_dispose");
            _colorSpace_createWithName = NativeImplClient.GetModuleMethod(_module, "ColorSpace_createWithName");
            _colorSpace_createDeviceGray = NativeImplClient.GetModuleMethod(_module, "ColorSpace_createDeviceGray");
            _Gradient_dispose = NativeImplClient.GetModuleMethod(_module, "Gradient_dispose");
            _gradient_createWithColorComponents = NativeImplClient.GetModuleMethod(_module, "Gradient_createWithColorComponents");
            _path_getCurrentPoint = NativeImplClient.GetModuleMethod(_module, "Path_getCurrentPoint");
            _path_createCopy = NativeImplClient.GetModuleMethod(_module, "Path_createCopy");
            _path_createMutableCopy = NativeImplClient.GetModuleMethod(_module, "Path_createMutableCopy");
            _Path_dispose = NativeImplClient.GetModuleMethod(_module, "Path_dispose");
            _path_createWithRect = NativeImplClient.GetModuleMethod(_module, "Path_createWithRect");
            _path_createWithEllipseInRect = NativeImplClient.GetModuleMethod(_module, "Path_createWithEllipseInRect");
            _path_createWithRoundedRect = NativeImplClient.GetModuleMethod(_module, "Path_createWithRoundedRect");
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
            _MutablePath_dispose = NativeImplClient.GetModuleMethod(_module, "MutablePath_dispose");
            _mutablePath_create = NativeImplClient.GetModuleMethod(_module, "MutablePath_create");
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
            _DrawContext_dispose = NativeImplClient.GetModuleMethod(_module, "DrawContext_dispose");
            _attributedString_getLength = NativeImplClient.GetModuleMethod(_module, "AttributedString_getLength");
            _attributedString_createMutableCopy = NativeImplClient.GetModuleMethod(_module, "AttributedString_createMutableCopy");
            _AttributedString_dispose = NativeImplClient.GetModuleMethod(_module, "AttributedString_dispose");
            _attributedString_create = NativeImplClient.GetModuleMethod(_module, "AttributedString_create");
            _mutableAttributedString_replaceString = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_replaceString");
            _mutableAttributedString_setAttribute = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_setAttribute");
            _mutableAttributedString_setCustomAttribute = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_setCustomAttribute");
            _mutableAttributedString_beginEditing = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_beginEditing");
            _mutableAttributedString_endEditing = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_endEditing");
            _MutableAttributedString_dispose = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_dispose");
            _mutableAttributedString_create = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_create");
            _font_createCopyWithSymbolicTraits = NativeImplClient.GetModuleMethod(_module, "Font_createCopyWithSymbolicTraits");
            _font_getAscent = NativeImplClient.GetModuleMethod(_module, "Font_getAscent");
            _font_getDescent = NativeImplClient.GetModuleMethod(_module, "Font_getDescent");
            _font_getUnderlineThickness = NativeImplClient.GetModuleMethod(_module, "Font_getUnderlineThickness");
            _font_getUnderlinePosition = NativeImplClient.GetModuleMethod(_module, "Font_getUnderlinePosition");
            _Font_dispose = NativeImplClient.GetModuleMethod(_module, "Font_dispose");
            _font_createFromFile = NativeImplClient.GetModuleMethod(_module, "Font_createFromFile");
            _font_createWithName = NativeImplClient.GetModuleMethod(_module, "Font_createWithName");
            _run_getAttributes = NativeImplClient.GetModuleMethod(_module, "Run_getAttributes");
            _run_getTypographicBounds = NativeImplClient.GetModuleMethod(_module, "Run_getTypographicBounds");
            _run_getStringRange = NativeImplClient.GetModuleMethod(_module, "Run_getStringRange");
            _run_getStatus = NativeImplClient.GetModuleMethod(_module, "Run_getStatus");
            _Run_dispose = NativeImplClient.GetModuleMethod(_module, "Run_dispose");
            _line_getStringRange = NativeImplClient.GetModuleMethod(_module, "Line_getStringRange");
            _line_getTypographicBounds = NativeImplClient.GetModuleMethod(_module, "Line_getTypographicBounds");
            _line_getBoundsWithOptions = NativeImplClient.GetModuleMethod(_module, "Line_getBoundsWithOptions");
            _line_draw = NativeImplClient.GetModuleMethod(_module, "Line_draw");
            _line_getGlyphRuns = NativeImplClient.GetModuleMethod(_module, "Line_getGlyphRuns");
            _line_getOffsetForStringIndex = NativeImplClient.GetModuleMethod(_module, "Line_getOffsetForStringIndex");
            _line_getStringIndexForPosition = NativeImplClient.GetModuleMethod(_module, "Line_getStringIndexForPosition");
            _Line_dispose = NativeImplClient.GetModuleMethod(_module, "Line_dispose");
            _line_createWithAttributedString = NativeImplClient.GetModuleMethod(_module, "Line_createWithAttributedString");
            _frame_draw = NativeImplClient.GetModuleMethod(_module, "Frame_draw");
            _frame_getLines = NativeImplClient.GetModuleMethod(_module, "Frame_getLines");
            _frame_getLineOrigins = NativeImplClient.GetModuleMethod(_module, "Frame_getLineOrigins");
            _frame_getLinesExtended = NativeImplClient.GetModuleMethod(_module, "Frame_getLinesExtended");
            _Frame_dispose = NativeImplClient.GetModuleMethod(_module, "Frame_dispose");
            _frameSetter_createFrame = NativeImplClient.GetModuleMethod(_module, "FrameSetter_createFrame");
            _FrameSetter_dispose = NativeImplClient.GetModuleMethod(_module, "FrameSetter_dispose");
            _frameSetter_createWithAttributedString = NativeImplClient.GetModuleMethod(_module, "FrameSetter_createWithAttributedString");
            _ParagraphStyle_dispose = NativeImplClient.GetModuleMethod(_module, "ParagraphStyle_dispose");
            _paragraphStyle_create = NativeImplClient.GetModuleMethod(_module, "ParagraphStyle_create");
            _BitmapLock_dispose = NativeImplClient.GetModuleMethod(_module, "BitmapLock_dispose");
            _Image_dispose = NativeImplClient.GetModuleMethod(_module, "Image_dispose");
            _bitmapDrawContext_createImage = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_createImage");
            _bitmapDrawContext_getData = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_getData");
            _BitmapDrawContext_dispose = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_dispose");
            _bitmapDrawContext_create = NativeImplClient.GetModuleMethod(_module, "BitmapDrawContext_create");

            _mutablePathTransformException = NativeImplClient.GetException(_module, "MutablePathTransformException");
            NativeImplClient.SetExceptionBuilder(_mutablePathTransformException, MutablePathTransformException.BuildAndThrow);

            // no static init
        }

        internal static void Shutdown()
        {
            // no static shutdown
        }
    }
}
