using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

public class Page01(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    public override void Init()
    {
        base.Init();
    }

    private static void DrawStrokedLine(DrawContext context, Point start, Point end)
    {
        context.BeginPath();
        context.MoveToPoint(start.X, start.Y);
        context.AddLineToPoint(end.X, end.Y);
        context.DrawPath(PathDrawingMode.Stroke);
    }

    private static void DoBlueRect(DrawContext context, Rect r, double alpha)
    {
        context.SetRGBStrokeColor(1, 1, 0, alpha);
        context.SetRGBFillColor(0, 0, 1, alpha);
        context.StrokeRectWithWidth(r, 2);
        context.FillRect(r);
    }

    private static void CreateRectPath(DrawContext context, Rect rect)
    {
        context.MoveToPoint(rect.Origin.X, rect.Origin.Y);
        context.AddLineToPoint(rect.Origin.X + rect.Size.Width, rect.Origin.Y);
        context.AddLineToPoint(rect.Origin.X + rect.Size.Width, rect.Origin.Y + rect.Size.Height);
        context.AddLineToPoint(rect.Origin.X, rect.Origin.Y + rect.Size.Height);
    }

    public override void Render(DrawContext context, RenderArea area)
    {
        // max-size background
        context.SetRGBFillColor(0, 0, 0, 1);
        var rMax = new Rect(new Point(0, 0), new Size(Constants.MaxWidth, Constants.MaxHeight));
        context.FillRect(rMax);

        // normal size background
        context.SetRGBFillColor(0.1, 0.1, 0.3, 1);
        var rNormal = new Rect(new Point(0, 0), new Size(Constants.InitWidth, Constants.InitHeight));
        context.FillRect(rNormal);
        
        // if crossMask () {}
        // .....
        
        // dashed lines (??)
        context.SaveGState();
        
        var start = new Point(40, 280);
        var end = new Point(900, 280);
        var linesWidth = end.X - start.X;
        const double linesHeight = 50 * 5.0;
        double[] lengths = [12, 6, 5, 6, 5, 6];

        // black circle behind lines
        context.SetRGBFillColor(0, 0, 0, 1);
        context.SetRGBStrokeColor(0.4, 0, 0, 1);
        context.SetLineWidth(5.0);
        context.BeginPath();
        context.AddArc(start.X + linesWidth / 2, start.Y + linesHeight / 2, 300, 0, Math.PI * 2, false);
        context.DrawPath(PathDrawingMode.FillStroke);

        context.BeginPath();
        context.AddArc(start.X + linesWidth / 2, start.Y + linesHeight / 2, 300, 0, Math.PI * 2, false);
        context.Clip();
        
        // DASHED LINES ===================
        context.SetRGBStrokeColor(1, 1, 0, 1);

        // line 1 solid
        context.SetLineWidth(5);
        DrawStrokedLine(context, start, end);

        // line 2 long dashes
        context.TranslateCTM(0, 50);
        context.SetLineDash(0, lengths[..1]);
        DrawStrokedLine(context, start, end);

        // line 3 long short pattern
        context.TranslateCTM(0, 50);
        context.SetLineDash(0, lengths[..3]);
        DrawStrokedLine(context, start, end);

        // line 3.5! interrupting the show ======
        context.SaveGState();

        context.TranslateCTM(0, 25);

        context.SetLineWidth(12);
        context.ClearLineDash(); // temporarily disable ...
        context.SetRGBStrokeColor(0, 1, 1, 1);
        DrawStrokedLine(context, start, end);

        context.RestoreGState();
        // end line 3.5 ============
        
        // line 4 long short short
        context.TranslateCTM(0, 50);
        context.SetLineDash(0, lengths);
        DrawStrokedLine(context, start, end);

        // line 5 short short long
        context.TranslateCTM(0, 50);
        context.SetLineDash(lengths[0] + lengths[1], lengths);
        DrawStrokedLine(context, start, end);

        // line 6 solid line
        context.TranslateCTM(0, 50);
        context.ClearLineDash();    // reset to solid
        DrawStrokedLine(context, start, end);

        context.RestoreGState();
        // END DASHED LINES ==================
        
        // save pre-transforms
        context.SaveGState();

        context.SetRGBStrokeColor(0, 1, 0, 1);
        var r2 = new Rect(new Point(100, 100), new Size(250, 100));
        context.StrokeRectWithWidth(r2, 3.0);

        context.SetRGBStrokeColor(0, 0.5, 1, 1);
        for (var i = 0; i < 5; i++)
        {
            var n = 0.5 + ((i + 1) * 5);
            var r3 = new Rect(new Point(n, n), new Size(Constants.InitWidth - (n * 2), Constants.InitHeight - (n * 2)));
            context.StrokeRectWithWidth(r3, 1);
        }

        context.SetRGBStrokeColor(1, 0, 0, 1);
        for (var i = 0; i < 5; i++)
        {
            var n = 0.5 + ((i + 1) * 5);
            var r3 = new Rect(new Point(n, n), new Size(Constants.MinWidth - (n * 2), Constants.MinHeight - (n * 2)));
            context.StrokeRectWithWidth(r3, 1);
        }

        context.SetRGBStrokeColor(0, 1, 0, 1);
        for (var i = 0; i < 5; i++)
        {
            var n = 0.5 + ((i + 1) * 5);
            var r3 = new Rect(new Point(n, n), new Size(Constants.MaxWidth - (n * 2), Constants.MaxHeight - (n * 2)));
            context.StrokeRectWithWidth(r3, 1);
        }
        
        var r4 = new Rect(new Point(280, 100), new Size(200, 200));
        var alpha = 1.0 / 5;
        for (var i = 0; i < 5; i++)
        {
            r4.Origin.X += 20;
            r4.Origin.Y += 20;
            DoBlueRect(context, r4, alpha);
            alpha += 1.0 / 5;
        }
        
        var r5 = new Rect(new Point(0.5, 0.5), new Size(149, 149));
        context.TranslateCTM(280, 300);
        context.SetRGBFillColor(1, 0, .3, .2);
        context.SetRGBStrokeColor(0, 0, 0, 1);
        context.SetLineWidth(1);
        for (var i = 0; i < 5; i++)
        {
            CreateRectPath(context, r5);
            context.DrawPath((i % 2) != 0 ? PathDrawingMode.Fill : PathDrawingMode.FillStroke);
            context.TranslateCTM(-15, 15);
        }

        context.RestoreGState();
    }
}
