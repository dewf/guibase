using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using CSharpFunctionalExtensions;
using Org.Prefixed.GuiBase.Support;
using ModuleHandle = Org.Prefixed.GuiBase.Support.ModuleHandle;

using static Org.Prefixed.GuiBase.Drawing;

namespace Org.Prefixed.GuiBase
{
    public static class Text
    {
        private static ModuleHandle _module;

        internal static void __ParagraphStyle_Setting_Array__Push(ParagraphStyle.Setting[] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                ParagraphStyle.Setting__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static ParagraphStyle.Setting[] __ParagraphStyle_Setting_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new ParagraphStyle.Setting[count];
            for (var i = 0; i < count; i++)
            {
                ret[i] = ParagraphStyle.Setting__Pop();
            }
            return ret;
        }

        // built-in array type: string[]

        // built-in array type: double[]

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

        internal static void __Run_Status_Array__Push(Run.Status[] items)
        {
            var intValues = items.Select(i => (byte)i).ToArray();
            NativeImplClient.PushUInt8Array(intValues);
        }

        internal static Run.Status[] __Run_Status_Array__Pop()
        {
            var intValues = NativeImplClient.PopUInt8Array();
            return intValues.Select(i => (Run.Status)i).ToArray();
        }

        // built-in array type: long[]

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

        internal static void __AttributedString_Options_Array__Push(AttributedString.Options[] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                AttributedString.Options__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static AttributedString.Options[] __AttributedString_Options_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new AttributedString.Options[count];
            for (var i = 0; i < count; i++)
            {
                ret[i] = AttributedString.Options__Pop();
            }
            return ret;
        }

        internal static void __Run_Info_Array__Push(Run.Info[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new AttributedString.Options[count];
            var f1Values = new Range[count];
            var f2Values = new Run.Status[count];
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
            __Run_Status_Array__Push(f2Values);
            __Range_Array__Push(f1Values, isReturn);
            __AttributedString_Options_Array__Push(f0Values, isReturn);
        }

        internal static Run.Info[] __Run_Info_Array__Pop()
        {
            var f0Values = __AttributedString_Options_Array__Pop();
            var f1Values = __Range_Array__Pop();
            var f2Values = __Run_Status_Array__Pop();
            var f3Values = __Rect_Array__Pop();
            var f4Values = __TypographicBounds_Array__Pop();
            var count = f0Values.Length;
            var ret = new Run.Info[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                var f3 = f3Values[i];
                var f4 = f4Values[i];
                ret[i] = new Run.Info(f0, f1, f2, f3, f4);
            }
            return ret;
        }

        internal static void __Run_Info_Array_Array__Push(Run.Info[][] values, bool isReturn)
        {
            foreach (var value in values.Reverse())
            {
                __Run_Info_Array__Push(value, isReturn);
            }
            NativeImplClient.PushSizeT((IntPtr)values.Length);
        }

        internal static Run.Info[][] __Run_Info_Array_Array__Pop()
        {
            var count = (int)NativeImplClient.PopSizeT();
            var ret = new Run.Info[count][];
            for (var i = 0; i < count; i++)
            {
                ret[i] = __Run_Info_Array__Pop();
            }
            return ret;
        }

        internal static void __Line_Info_Array__Push(Line.Info[] items, bool isReturn)
        {
            var count = items.Length;
            var f0Values = new Point[count];
            var f1Values = new TypographicBounds[count];
            var f2Values = new Run.Info[count][];
            for (var i = 0; i < count; i++)
            {
                f0Values[i] = items[i].Origin;
                f1Values[i] = items[i].LineTypoBounds;
                f2Values[i] = items[i].Runs;
            }
            __Run_Info_Array_Array__Push(f2Values, isReturn);
            __TypographicBounds_Array__Push(f1Values, isReturn);
            __Point_Array__Push(f0Values, isReturn);
        }

        internal static Line.Info[] __Line_Info_Array__Pop()
        {
            var f0Values = __Point_Array__Pop();
            var f1Values = __TypographicBounds_Array__Pop();
            var f2Values = __Run_Info_Array_Array__Pop();
            var count = f0Values.Length;
            var ret = new Line.Info[count];
            for (var i = 0; i < count; i++)
            {
                var f0 = f0Values[i];
                var f1 = f1Values[i];
                var f2 = f2Values[i];
                ret[i] = new Line.Info(f0, f1, f2);
            }
            return ret;
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
        internal static ModuleMethodHandle _attributedString_getLength;
        internal static ModuleMethodHandle _attributedString_createMutableCopy;
        internal static ModuleMethodHandle _attributedString_dispose;
        internal static ModuleMethodHandle _mutableAttributedString_replaceString;
        internal static ModuleMethodHandle _mutableAttributedString_setAttribute;
        internal static ModuleMethodHandle _mutableAttributedString_setCustomAttribute;
        internal static ModuleMethodHandle _mutableAttributedString_beginEditing;
        internal static ModuleMethodHandle _mutableAttributedString_endEditing;
        internal static ModuleMethodHandle _mutableAttributedString_dispose;
        internal static ModuleMethodHandle _font_createCopyWithSymbolicTraits;
        internal static ModuleMethodHandle _font_getAscent;
        internal static ModuleMethodHandle _font_getDescent;
        internal static ModuleMethodHandle _font_getUnderlineThickness;
        internal static ModuleMethodHandle _font_getUnderlinePosition;
        internal static ModuleMethodHandle _font_dispose;
        internal static ModuleMethodHandle _run_getAttributes;
        internal static ModuleMethodHandle _run_getTypographicBounds;
        internal static ModuleMethodHandle _run_getStringRange;
        internal static ModuleMethodHandle _run_getStatus;
        internal static ModuleMethodHandle _run_dispose;
        internal static ModuleMethodHandle _line_getStringRange;
        internal static ModuleMethodHandle _line_getTypographicBounds;
        internal static ModuleMethodHandle _line_getBoundsWithOptions;
        internal static ModuleMethodHandle _line_draw;
        internal static ModuleMethodHandle _line_getGlyphRuns;
        internal static ModuleMethodHandle _line_getOffsetForStringIndex;
        internal static ModuleMethodHandle _line_getStringIndexForPosition;
        internal static ModuleMethodHandle _line_dispose;
        internal static ModuleMethodHandle _frame_draw;
        internal static ModuleMethodHandle _frame_getLines;
        internal static ModuleMethodHandle _frame_getLineOrigins;
        internal static ModuleMethodHandle _frame_getLinesExtended;
        internal static ModuleMethodHandle _frame_dispose;
        internal static ModuleMethodHandle _frameSetter_createFrame;
        internal static ModuleMethodHandle _frameSetter_dispose;
        internal static ModuleMethodHandle _paragraphStyle_dispose;
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
                    NativeImplClient.InvokeModuleMethod(_attributedString_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static AttributedString Create(string s, Options opts)
            {
                Options__Push(opts, false);
                NativeImplClient.PushString(s);
                NativeImplClient.InvokeModuleMethod(_create);
                return AttributedString__Pop();
            }
            public struct Options
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
            internal static void Options__Push(Options value, bool isReturn)
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
            internal static Options Options__Pop()
            {
                var opts = new Options
                {
                    UsedFields = (Options.Fields)NativeImplClient.PopInt32()
                };
                if (opts.UsedFields.HasFlag(Options.Fields.ForegroundColor))
                {
                    opts.ForegroundColor = Color__Pop();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.ForegroundColorFromContext))
                {
                    opts.ForegroundColorFromContext = NativeImplClient.PopBool();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.Font))
                {
                    opts.Font = Font__Pop();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.StrokeWidth))
                {
                    opts.StrokeWidth = NativeImplClient.PopDouble();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.StrokeColor))
                {
                    opts.StrokeColor = Color__Pop();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.ParagraphStyle))
                {
                    opts.ParagraphStyle = ParagraphStyle__Pop();
                }
                if (opts.UsedFields.HasFlag(Options.Fields.Custom))
                {
                    opts.Custom = __String_Long_Map__Pop();
                }
                return opts;
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
                    NativeImplClient.InvokeModuleMethod(_mutableAttributedString_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static MutableAttributedString Create(long maxLength)
            {
                NativeImplClient.PushInt64(maxLength);
                NativeImplClient.InvokeModuleMethod(_create);
                return MutableAttributedString__Pop();
            }
            public void ReplaceString(Range range, string str)
            {
                NativeImplClient.PushString(str);
                Range__Push(range, false);
                MutableAttributedString__Push(this);
                NativeImplClient.InvokeModuleMethod(_mutableAttributedString_replaceString);
            }
            public void SetAttribute(Range range, AttributedString.Options attr)
            {
                AttributedString.Options__Push(attr, false);
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
                    NativeImplClient.InvokeModuleMethod(_font_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createFromFile;
            internal static ModuleMethodHandle _createWithName;

            public static Font CreateFromFile(string path, double size, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(size);
                NativeImplClient.PushString(path);
                NativeImplClient.InvokeModuleMethod(_createFromFile);
                return Font__Pop();
            }

            public static Font CreateWithName(string name, double size, Maybe<AffineTransform> transform)
            {
                __AffineTransform_Option__Push(transform, false);
                NativeImplClient.PushDouble(size);
                NativeImplClient.PushString(name);
                NativeImplClient.InvokeModuleMethod(_createWithName);
                return Font__Pop();
            }
            public struct Traits
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
            internal static void Traits__Push(Traits value, bool isReturn)
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
            internal static Traits Traits__Pop()
            {
                var opts = new Traits
                {
                    UsedFields = (Traits.Fields)NativeImplClient.PopInt32()
                };
                if (opts.UsedFields.HasFlag(Traits.Fields.Italic))
                {
                    opts.Italic = NativeImplClient.PopBool();
                }
                if (opts.UsedFields.HasFlag(Traits.Fields.Bold))
                {
                    opts.Bold = NativeImplClient.PopBool();
                }
                if (opts.UsedFields.HasFlag(Traits.Fields.Expanded))
                {
                    opts.Expanded = NativeImplClient.PopBool();
                }
                if (opts.UsedFields.HasFlag(Traits.Fields.Condensed))
                {
                    opts.Condensed = NativeImplClient.PopBool();
                }
                if (opts.UsedFields.HasFlag(Traits.Fields.Monospace))
                {
                    opts.Monospace = NativeImplClient.PopBool();
                }
                if (opts.UsedFields.HasFlag(Traits.Fields.Vertical))
                {
                    opts.Vertical = NativeImplClient.PopBool();
                }
                return opts;
            }
            public Font CreateCopyWithSymbolicTraits(double size, Maybe<AffineTransform> transform, Traits newTraits)
            {
                Traits__Push(newTraits, false);
                __AffineTransform_Option__Push(transform, false);
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
                    NativeImplClient.InvokeModuleMethod(_run_dispose);
                    _disposed = true;
                }
            }
            [Flags]
            public enum Status
            {
                NoStatus = 0,
                RightToLeft = 1,
                NonMonotonic = 1 << 1,
                HasNonIdentityMatrix = 1 << 2
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Status__Push(Status value)
            {
                NativeImplClient.PushUInt32((uint)value);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Status Status__Pop()
            {
                var ret = NativeImplClient.PopUInt32();
                return (Status)ret;
            }
            public struct Info {
                public AttributedString.Options Attrs;
                public Range SourceRange;
                public Status Status;
                public Rect Bounds;
                public TypographicBounds TypoBounds;
                public Info(AttributedString.Options attrs, Range sourceRange, Status status, Rect bounds, TypographicBounds typoBounds)
                {
                    this.Attrs = attrs;
                    this.SourceRange = sourceRange;
                    this.Status = status;
                    this.Bounds = bounds;
                    this.TypoBounds = typoBounds;
                }
            }

            internal static void Info__Push(Info value, bool isReturn)
            {
                TypographicBounds__Push(value.TypoBounds, isReturn);
                Rect__Push(value.Bounds, isReturn);
                Status__Push(value.Status);
                Range__Push(value.SourceRange, isReturn);
                AttributedString.Options__Push(value.Attrs, isReturn);
            }

            internal static Info Info__Pop()
            {
                var attrs = AttributedString.Options__Pop();
                var sourceRange = Range__Pop();
                var status = Status__Pop();
                var bounds = Rect__Pop();
                var typoBounds = TypographicBounds__Pop();
                return new Info(attrs, sourceRange, status, bounds, typoBounds);
            }
            public AttributedString.Options GetAttributes(string[] customKeys)
            {
                NativeImplClient.PushStringArray(customKeys);
                Run__Push(this);
                NativeImplClient.InvokeModuleMethod(_run_getAttributes);
                return AttributedString.Options__Pop();
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
            public Status GetStatus()
            {
                Run__Push(this);
                NativeImplClient.InvokeModuleMethod(_run_getStatus);
                return Status__Pop();
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
                    NativeImplClient.InvokeModuleMethod(_line_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createWithAttributedString;

            public static Line CreateWithAttributedString(AttributedString str)
            {
                AttributedString__Push(str);
                NativeImplClient.InvokeModuleMethod(_createWithAttributedString);
                return Line__Pop();
            }
            public struct Info {
                public Point Origin;
                public TypographicBounds LineTypoBounds;
                public Run.Info[] Runs;
                public Info(Point origin, TypographicBounds lineTypoBounds, Run.Info[] runs)
                {
                    this.Origin = origin;
                    this.LineTypoBounds = lineTypoBounds;
                    this.Runs = runs;
                }
            }

            internal static void Info__Push(Info value, bool isReturn)
            {
                __Run_Info_Array__Push(value.Runs, isReturn);
                TypographicBounds__Push(value.LineTypoBounds, isReturn);
                Point__Push(value.Origin, isReturn);
            }

            internal static Info Info__Pop()
            {
                var origin = Point__Pop();
                var lineTypoBounds = TypographicBounds__Pop();
                var runs = __Run_Info_Array__Pop();
                return new Info(origin, lineTypoBounds, runs);
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
                    NativeImplClient.InvokeModuleMethod(_frame_dispose);
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
            public Line.Info[] GetLinesExtended(string[] customKeys)
            {
                NativeImplClient.PushStringArray(customKeys);
                Frame__Push(this);
                NativeImplClient.InvokeModuleMethod(_frame_getLinesExtended);
                return __Line_Info_Array__Pop();
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
                    NativeImplClient.InvokeModuleMethod(_frameSetter_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _createWithAttributedString;

            public static FrameSetter CreateWithAttributedString(AttributedString str)
            {
                AttributedString__Push(str);
                NativeImplClient.InvokeModuleMethod(_createWithAttributedString);
                return FrameSetter__Pop();
            }
            public Frame CreateFrame(Range range, Drawing.Path path)
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
                    NativeImplClient.InvokeModuleMethod(_paragraphStyle_dispose);
                    _disposed = true;
                }
            }
            internal static ModuleMethodHandle _create;

            public static ParagraphStyle Create(Setting[] settings)
            {
                __ParagraphStyle_Setting_Array__Push(settings, false);
                NativeImplClient.InvokeModuleMethod(_create);
                return ParagraphStyle__Pop();
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
            public abstract record Setting
            {
                internal abstract void Push(bool isReturn);
                internal static Setting Pop()
                {
                    return NativeImplClient.PopInt32() switch
                    {
                        0 => Alignment.PopDerived(),
                        _ => throw new Exception("Setting.Pop() - unknown tag!")
                    };
                }
                public sealed record Alignment(TextAlignment Value) : Setting
                {
                    public TextAlignment Value { get; } = Value;
                    internal override void Push(bool isReturn)
                    {
                        TextAlignment__Push(Value);
                        // kind
                        NativeImplClient.PushInt32(0);
                    }
                    internal static Alignment PopDerived()
                    {
                        var value = TextAlignment__Pop();
                        return new Alignment(value);
                    }
                }
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static void Setting__Push(Setting thing, bool isReturn)
            {
                thing.Push(isReturn);
            }

            [MethodImpl(MethodImplOptions.AggressiveInlining)]
            internal static Setting Setting__Pop()
            {
                return Setting.Pop();
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

        internal static void __Init()
        {
            _module = NativeImplClient.GetModule("Text");
            // assign module handles
            _attributedString_getLength = NativeImplClient.GetModuleMethod(_module, "AttributedString_getLength");
            _attributedString_createMutableCopy = NativeImplClient.GetModuleMethod(_module, "AttributedString_createMutableCopy");
            _attributedString_dispose = NativeImplClient.GetModuleMethod(_module, "AttributedString_dispose");
            _mutableAttributedString_replaceString = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_replaceString");
            _mutableAttributedString_setAttribute = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_setAttribute");
            _mutableAttributedString_setCustomAttribute = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_setCustomAttribute");
            _mutableAttributedString_beginEditing = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_beginEditing");
            _mutableAttributedString_endEditing = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_endEditing");
            _mutableAttributedString_dispose = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString_dispose");
            _font_createCopyWithSymbolicTraits = NativeImplClient.GetModuleMethod(_module, "Font_createCopyWithSymbolicTraits");
            _font_getAscent = NativeImplClient.GetModuleMethod(_module, "Font_getAscent");
            _font_getDescent = NativeImplClient.GetModuleMethod(_module, "Font_getDescent");
            _font_getUnderlineThickness = NativeImplClient.GetModuleMethod(_module, "Font_getUnderlineThickness");
            _font_getUnderlinePosition = NativeImplClient.GetModuleMethod(_module, "Font_getUnderlinePosition");
            _font_dispose = NativeImplClient.GetModuleMethod(_module, "Font_dispose");
            _run_getAttributes = NativeImplClient.GetModuleMethod(_module, "Run_getAttributes");
            _run_getTypographicBounds = NativeImplClient.GetModuleMethod(_module, "Run_getTypographicBounds");
            _run_getStringRange = NativeImplClient.GetModuleMethod(_module, "Run_getStringRange");
            _run_getStatus = NativeImplClient.GetModuleMethod(_module, "Run_getStatus");
            _run_dispose = NativeImplClient.GetModuleMethod(_module, "Run_dispose");
            _line_getStringRange = NativeImplClient.GetModuleMethod(_module, "Line_getStringRange");
            _line_getTypographicBounds = NativeImplClient.GetModuleMethod(_module, "Line_getTypographicBounds");
            _line_getBoundsWithOptions = NativeImplClient.GetModuleMethod(_module, "Line_getBoundsWithOptions");
            _line_draw = NativeImplClient.GetModuleMethod(_module, "Line_draw");
            _line_getGlyphRuns = NativeImplClient.GetModuleMethod(_module, "Line_getGlyphRuns");
            _line_getOffsetForStringIndex = NativeImplClient.GetModuleMethod(_module, "Line_getOffsetForStringIndex");
            _line_getStringIndexForPosition = NativeImplClient.GetModuleMethod(_module, "Line_getStringIndexForPosition");
            _line_dispose = NativeImplClient.GetModuleMethod(_module, "Line_dispose");
            _frame_draw = NativeImplClient.GetModuleMethod(_module, "Frame_draw");
            _frame_getLines = NativeImplClient.GetModuleMethod(_module, "Frame_getLines");
            _frame_getLineOrigins = NativeImplClient.GetModuleMethod(_module, "Frame_getLineOrigins");
            _frame_getLinesExtended = NativeImplClient.GetModuleMethod(_module, "Frame_getLinesExtended");
            _frame_dispose = NativeImplClient.GetModuleMethod(_module, "Frame_dispose");
            _frameSetter_createFrame = NativeImplClient.GetModuleMethod(_module, "FrameSetter_createFrame");
            _frameSetter_dispose = NativeImplClient.GetModuleMethod(_module, "FrameSetter_dispose");
            _paragraphStyle_dispose = NativeImplClient.GetModuleMethod(_module, "ParagraphStyle_dispose");
            AttributedString._create = NativeImplClient.GetModuleMethod(_module, "AttributedString.create");
            MutableAttributedString._create = NativeImplClient.GetModuleMethod(_module, "MutableAttributedString.create");
            Font._createFromFile = NativeImplClient.GetModuleMethod(_module, "Font.createFromFile");
            Font._createWithName = NativeImplClient.GetModuleMethod(_module, "Font.createWithName");
            Line._createWithAttributedString = NativeImplClient.GetModuleMethod(_module, "Line.createWithAttributedString");
            FrameSetter._createWithAttributedString = NativeImplClient.GetModuleMethod(_module, "FrameSetter.createWithAttributedString");
            ParagraphStyle._create = NativeImplClient.GetModuleMethod(_module, "ParagraphStyle.create");

            // no static init
        }

        internal static void __Shutdown()
        {
            // no static shutdown
        }
    }
}
