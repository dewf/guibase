using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

public static class Common
{
    public static readonly Drawing.Point PointZero = new(0, 0);
    
    // rect methods
    public static Rect MakeRect(double x, double y, double width, double height)
    {
        return new Rect(new Point(x, y), new Size(width, height));
    }
    public static Rect Inset(this Rect rect, double amount)
    {
        return MakeRect(rect.Origin.X + amount, rect.Origin.Y + amount, rect.Size.Width - amount * 2,
            rect.Size.Height - amount * 2);
    }
    public static string RectToString(Rect r)
    {
        return $"{r.Origin.X}/{r.Origin.Y}/{r.Size.Width}/{r.Size.Height}";
    }
    public static readonly Drawing.Rect RectZero = MakeRect(0, 0, 0, 0);

    public static bool ContainsPoint(this Rect r, Point p)
    {
        return p.X >= r.Origin.X && p.Y >= r.Origin.Y &&
               p.X < (r.Origin.X + r.Size.Width) &&
               p.Y < (r.Origin.Y + r.Size.Height);
    }

    // range methods
    public static long RangeEnd(this Drawing.Range r)
    {
        return r.Location + r.Length;
    }

    public static Drawing.Range MakeRange(long location, long length)
    {
        return new Drawing.Range(location, length);
    }

    public static readonly Drawing.Range RangeZero = new(0, 0);
    public static readonly Drawing.Range RangeNotFound = new(-1, -1);

    public static Drawing.Range StringFind(string str, string substring)
    {
        var result = str.IndexOf(substring, StringComparison.Ordinal);
        if (result >= 0)
        {
            return MakeRange(result, substring.Length);
        }
        return RangeNotFound;
    }
    
    public static void PointAt(DrawContext context, Point p)
    {
        context.SaveGState();
        context.SetRGBFillColor(1, 0, 0, 1);
        context.BeginPath();
        context.AddArc(p.X, p.Y, 2.5, 0, Math.PI * 2, false);
        context.DrawPath(PathDrawingMode.Fill);
        context.RestoreGState();
    }

    public static void DrawRect(DrawContext context, Rect r, Color color, double width)
    {
        context.SetStrokeColorWithColor(color);
        context.StrokeRectWithWidth(r, width);
    }
    
    public static void DrawLine(DrawContext context, Point from, Point to, Color color)
    {
        context.BeginPath();
        context.MoveToPoint(from.X, from.Y);
        context.AddLineToPoint(to.X, to.Y);
        context.SetStrokeColorWithColor(color);
        context.StrokePath();
    }
    
    public static void DrawLineAt(DrawContext context, Line line, double x, double y, out double yAdvance)
    {
        context.SaveGState();

        using var green = Color.CreateGenericRGB(0, 1, 0, 1);
        using var magenta = Color.CreateGenericRGB(1, 0, 1, 1);
        using var blue = Color.CreateGenericRGB(0, 0.3, 1, 1);
        using var yellow = Color.CreateGenericRGB(1, 1, 0, 1);
        using var orange = Color.CreateGenericRGB(1, 0.6, 0, 1);

        var typoBounds = line.GetTypographicBounds();
        
        PointAt(context, new Point(x, y));
        
        var lineBounds = line.GetBoundsWithOptions(0); //0 = same as dl_kCTLineBoundsUseOpticalBounds?
        lineBounds.Origin.X += x;
        lineBounds.Origin.Y += y;
        DrawRect(context, lineBounds, green, 1);

        yAdvance = lineBounds.Size.Height;

        var glyphBounds = line.GetBoundsWithOptions(LineBoundsOptions.UseGlyphPathBounds);
        glyphBounds.Origin.X += x;
        glyphBounds.Origin.Y += y;
        DrawRect(context, glyphBounds, magenta, 1);
        
        // various lines
        context.SetLineDash(0, [4.0, 4.0]);
        context.SetLineWidth(2);

        // baseline
        DrawLine(context, new Point(x, y), new Point(x + lineBounds.Size.Width, y), blue);

        // descent
        DrawLine(context, new Point(x, y + typoBounds.Descent), new Point(x + lineBounds.Size.Width, y + typoBounds.Descent), yellow);

        // leading
        DrawLine(context, new Point(x, y + typoBounds.Descent + typoBounds.Leading), new Point(x + lineBounds.Size.Width, y + typoBounds.Descent + typoBounds.Leading), orange);

        // ascent
        DrawLine(context, new Point(x, y - typoBounds.Ascent), new Point(x + lineBounds.Size.Width, y - typoBounds.Ascent), yellow);
        
        // text itself
        context.SetTextPosition(x, y);
        line.Draw(context);
        
        // opaques will be auto-disposed ...
        context.RestoreGState();
    }

    public static Point BetweenPoints(Point a, Point b)
    {
        var x = (a.X + b.X) / 2;
        var y = (a.Y + b.Y) / 2;
        return new Point(x, y);
    }

    public static Gradient GetGradient(
        double fromRed, double fromGreen, double fromBlue, double fromAlpha,
        double toRed, double toGreen, double toBlue, double toAlpha)
    {
        var start = new GradientStop(0, fromRed, fromGreen, fromBlue, fromAlpha);
        var end = new GradientStop(1, toRed, toGreen, toBlue, toAlpha);
        using var space = ColorSpace.CreateWithName(ColorSpaceName.GenericRGB);
        return Gradient.CreateWithColorComponents(space, [start, end]);
    }
    
    private static readonly double[] Dashes = [2, 2];
    public static void DashedRect(DrawContext context, Rect r)
    {
        context.SetRGBStrokeColor(0, 0, 0, 1);
        context.SetLineDash(0, Dashes);
        context.StrokeRect(r);
    }
    
    private static readonly Gradient DashedRectGradient = GetGradient(0.8, 0.8, 0.3, 1, 1, 0.5, 0.4, 1);
    public static void GradientDashedRect(DrawContext context, Rect r)
    {
        context.SaveGState();
        context.ClipToRect(r);
        Point start, end;
        start = r.Origin;
        end.X = r.Origin.X + r.Size.Width;
        end.Y = r.Origin.Y + r.Size.Height;
        context.DrawLinearGradient(DashedRectGradient, start, end, 0);
        // gradient is static, don't release

        context.RestoreGState(); // clear clip rect

        context.SaveGState();
        context.SetLineWidth(1);
        DashedRect(context, r);
        context.RestoreGState();
    }
    
    public static void TextLine(DrawContext context, double x, double y, string text, AttributedStringOptions attrOpts, bool withGradient = true, bool fromBaseline = false)
    {
        using var labelString = AttributedString.Create(text, attrOpts);
        using var line = Line.CreateWithAttributedString(labelString);

        var typoBounds = line.GetTypographicBounds();

        var bounds = line.GetBoundsWithOptions(0);
        bounds.Origin = new Point(x, y);
        bounds.Origin.X -= 0.5;
        bounds.Origin.Y -= 0.5;
        bounds.Size.Width += 1;
        bounds.Size.Height += 1;
        if (withGradient)
        {
            GradientDashedRect(context, bounds);
        }

        if (fromBaseline)
        {
            context.SetTextPosition(x, y);
        }
        else
        {
            context.SetTextPosition(x, y + typoBounds.Ascent);
        }
        
        line.Draw(context);
    }
}
