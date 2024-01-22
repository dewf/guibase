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
        private static ModuleMethodHandle _makeRect;
        private static ModuleMethodHandle _createColor;
        private static ModuleMethodHandle _createAttributedString;
        private static ModuleMethodHandle _fontManagerCreateFontDescriptorsFromURL;
        private static ModuleMethodHandle _fontCreateWithFontDescriptor;
        private static ModuleMethodHandle _createLineWithAttributedString;
        private static ModuleMethodHandle _drawContext_saveGState;
        private static ModuleMethodHandle _drawContext_restoreGState;
        private static ModuleMethodHandle _drawContext_setRGBFillColor;
        private static ModuleMethodHandle _drawContext_fillRect;
        private static ModuleMethodHandle _drawContext_setTextMatrix;
        private static ModuleMethodHandle _drawContext_setTextPosition;
        private static ModuleMethodHandle _DrawContext_dispose;
        private static ModuleMethodHandle _Color_dispose;
        private static ModuleMethodHandle _AttributedString_dispose;
        private static ModuleMethodHandle _FontDescriptor_dispose;
        private static ModuleMethodHandle _fontDescriptorArray_items;
        private static ModuleMethodHandle _FontDescriptorArray_dispose;
        private static ModuleMethodHandle _Font_dispose;
        private static ModuleMethodHandle _line_getTypographicBounds;
        private static ModuleMethodHandle _line_getBoundsWithOptions;
        private static ModuleMethodHandle _line_draw;
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
                AttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_AttributedString_dispose);
                _disposed = true;
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

        public struct AttributedStringOptions
        {
            [Flags]
            internal enum Fields
            {
                Font2 = 1,
                ForegroundColor = 2
            }
            internal Fields UsedFields;

            private Font _font2;
            public Font Font2
            {
                set
                {
                    _font2 = value;
                    UsedFields |= Fields.Font2;
                }
            }
            public bool HasFont2(out Font value)
            {
                if (UsedFields.HasFlag(Fields.Font2))
                {
                    value = _font2;
                    return true;
                }
                value = default;
                return false;
            }
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
        }
        internal static void AttributedStringOptions__Push(AttributedStringOptions value, bool isReturn)
        {
            if (value.HasForegroundColor(out var foregroundColor))
            {
                Color__Push(foregroundColor);
            }
            if (value.HasFont2(out var font2))
            {
                Font__Push(font2);
            }
            NativeImplClient.PushInt32((int)value.UsedFields);
        }
        internal static AttributedStringOptions AttributedStringOptions__Pop()
        {
            var opts = new AttributedStringOptions
            {
                UsedFields = (AttributedStringOptions.Fields)NativeImplClient.PopInt32()
            };
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.Font2))
            {
                opts.Font2 = Font__Pop();
            }
            if (opts.UsedFields.HasFlag(AttributedStringOptions.Fields.ForegroundColor))
            {
                opts.ForegroundColor = Color__Pop();
            }
            return opts;
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
                Color__Push(this);
                NativeImplClient.InvokeModuleMethod(_Color_dispose);
                _disposed = true;
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
                DrawContext__Push(this);
                NativeImplClient.InvokeModuleMethod(_DrawContext_dispose);
                _disposed = true;
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
                Font__Push(this);
                NativeImplClient.InvokeModuleMethod(_Font_dispose);
                _disposed = true;
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

        public class FontDescriptor : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal FontDescriptor(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                FontDescriptor__Push(this);
                NativeImplClient.InvokeModuleMethod(_FontDescriptor_dispose);
                _disposed = true;
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void FontDescriptor__Push(FontDescriptor thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static FontDescriptor FontDescriptor__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new FontDescriptor(ptr) : null;
        }

        internal static void __FontDescriptor_Array__Push(FontDescriptor[] items)
        {
            var ptrs = items.Select(item => item.NativeHandle).ToArray();
            NativeImplClient.PushPtrArray(ptrs);
        }
        internal static FontDescriptor[] __FontDescriptor_Array__Pop()
        {
            return NativeImplClient.PopPtrArray()
                .Select(ptr => ptr != IntPtr.Zero ? new FontDescriptor(ptr) : null)
                .ToArray();
        }

        public class FontDescriptorArray : IDisposable
        {
            internal readonly IntPtr NativeHandle;
            private bool _disposed;
            internal FontDescriptorArray(IntPtr nativeHandle)
            {
                NativeHandle = nativeHandle;
            }
            public void Dispose()
            {
                FontDescriptorArray__Push(this);
                NativeImplClient.InvokeModuleMethod(_FontDescriptorArray_dispose);
                _disposed = true;
            }
            public FontDescriptor[] Items()
            {
                FontDescriptorArray__Push(this);
                NativeImplClient.InvokeModuleMethod(_fontDescriptorArray_items);
                return __FontDescriptor_Array__Pop();
            }
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static void FontDescriptorArray__Push(FontDescriptorArray thing)
        {
            NativeImplClient.PushPtr(thing?.NativeHandle ?? IntPtr.Zero);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        internal static FontDescriptorArray FontDescriptorArray__Pop()
        {
            var ptr = NativeImplClient.PopPtr();
            return ptr != IntPtr.Zero ? new FontDescriptorArray(ptr) : null;
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
                Line__Push(this);
                NativeImplClient.InvokeModuleMethod(_Line_dispose);
                _disposed = true;
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

        public static Rect MakeRect(double x, double y, double width, double height)
        {
            NativeImplClient.PushDouble(height);
            NativeImplClient.PushDouble(width);
            NativeImplClient.PushDouble(y);
            NativeImplClient.PushDouble(x);
            NativeImplClient.InvokeModuleMethod(_makeRect);
            return Rect__Pop();
        }

        public static Color CreateColor(double red, double green, double blue, double alpha)
        {
            NativeImplClient.PushDouble(alpha);
            NativeImplClient.PushDouble(blue);
            NativeImplClient.PushDouble(green);
            NativeImplClient.PushDouble(red);
            NativeImplClient.InvokeModuleMethod(_createColor);
            return Color__Pop();
        }

        public static AttributedString CreateAttributedString(string s, AttributedStringOptions opts)
        {
            AttributedStringOptions__Push(opts, false);
            NativeImplClient.PushString(s);
            NativeImplClient.InvokeModuleMethod(_createAttributedString);
            return AttributedString__Pop();
        }

        public static FontDescriptorArray FontManagerCreateFontDescriptorsFromURL(URL fileUrl)
        {
            URL__Push(fileUrl);
            NativeImplClient.InvokeModuleMethod(_fontManagerCreateFontDescriptorsFromURL);
            return FontDescriptorArray__Pop();
        }

        public static Font FontCreateWithFontDescriptor(FontDescriptor descriptor, double size, AffineTransform matrix)
        {
            AffineTransform__Push(matrix, false);
            NativeImplClient.PushDouble(size);
            FontDescriptor__Push(descriptor);
            NativeImplClient.InvokeModuleMethod(_fontCreateWithFontDescriptor);
            return Font__Pop();
        }

        public static Line CreateLineWithAttributedString(AttributedString str)
        {
            AttributedString__Push(str);
            NativeImplClient.InvokeModuleMethod(_createLineWithAttributedString);
            return Line__Pop();
        }

        internal static void Init()
        {
            _module = NativeImplClient.GetModule("Drawing");

            NativeImplClient.PushModuleConstants(_module);
            AffineTransformIdentity = AffineTransform__Pop();

            _makeRect = NativeImplClient.GetModuleMethod(_module, "makeRect");
            _createColor = NativeImplClient.GetModuleMethod(_module, "createColor");
            _createAttributedString = NativeImplClient.GetModuleMethod(_module, "createAttributedString");
            _fontManagerCreateFontDescriptorsFromURL = NativeImplClient.GetModuleMethod(_module, "fontManagerCreateFontDescriptorsFromURL");
            _fontCreateWithFontDescriptor = NativeImplClient.GetModuleMethod(_module, "fontCreateWithFontDescriptor");
            _createLineWithAttributedString = NativeImplClient.GetModuleMethod(_module, "createLineWithAttributedString");

            _drawContext_saveGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_saveGState");
            _drawContext_restoreGState = NativeImplClient.GetModuleMethod(_module, "DrawContext_restoreGState");
            _drawContext_setRGBFillColor = NativeImplClient.GetModuleMethod(_module, "DrawContext_setRGBFillColor");
            _drawContext_fillRect = NativeImplClient.GetModuleMethod(_module, "DrawContext_fillRect");
            _drawContext_setTextMatrix = NativeImplClient.GetModuleMethod(_module, "DrawContext_setTextMatrix");
            _drawContext_setTextPosition = NativeImplClient.GetModuleMethod(_module, "DrawContext_setTextPosition");
            _DrawContext_dispose = NativeImplClient.GetModuleMethod(_module, "DrawContext_dispose");
            _Color_dispose = NativeImplClient.GetModuleMethod(_module, "Color_dispose");
            _AttributedString_dispose = NativeImplClient.GetModuleMethod(_module, "AttributedString_dispose");
            _FontDescriptor_dispose = NativeImplClient.GetModuleMethod(_module, "FontDescriptor_dispose");
            _fontDescriptorArray_items = NativeImplClient.GetModuleMethod(_module, "FontDescriptorArray_items");
            _FontDescriptorArray_dispose = NativeImplClient.GetModuleMethod(_module, "FontDescriptorArray_dispose");
            _Font_dispose = NativeImplClient.GetModuleMethod(_module, "Font_dispose");
            _line_getTypographicBounds = NativeImplClient.GetModuleMethod(_module, "Line_getTypographicBounds");
            _line_getBoundsWithOptions = NativeImplClient.GetModuleMethod(_module, "Line_getBoundsWithOptions");
            _line_draw = NativeImplClient.GetModuleMethod(_module, "Line_draw");
            _Line_dispose = NativeImplClient.GetModuleMethod(_module, "Line_dispose");

            // no static init
        }

        internal static void Shutdown()
        {
            // no static shutdown
        }
    }
}
