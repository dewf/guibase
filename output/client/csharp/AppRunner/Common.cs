using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

public static class Common
{
    public static Rect MakeRect(double x, double y, double width, double height)
    {
        return new Rect(new Point(x, y), new Size(width, height));
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

        using var green = Color.Create(0, 1, 0, 1);
        using var magenta = Color.Create(1, 0, 1, 1);
        using var blue = Color.Create(0, 0.3, 1, 1);
        using var yellow = Color.Create(1, 1, 0, 1);
        using var orange = Color.Create(1, 0.6, 0, 1);

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
}
