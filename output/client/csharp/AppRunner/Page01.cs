using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

public class Page01(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    private double _animAngle = 0;
    private int _mouseX, _mouseY;
    private bool _doCrossMask = false;

    public override void OnMouseMove(int x, int y, Windowing.Modifiers modifiers)
    {
        _mouseX = x;
        _mouseY = y;
        if (_doCrossMask) // or animating
        {
            Invalidate();
        }
    }

    public override void OnKeyDown(Windowing.Key key, Windowing.Modifiers modifiers)
    {
        if (key == Windowing.Key.C)
        {
            _doCrossMask = !_doCrossMask;
            Invalidate();
        }
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

    private static void DoClippedCircle(DrawContext context)
    {
        var circleCenter = new Point(100, 100);
        const double circleRadius = 100.0;
        const double startingAngle = 0.0;
        const double endingAngle = Math.PI * 2;
        var ourRect = new Rect(new Point(15, 15), new Size(170, 170));
        var totalArea = new Rect(new Point(0, 0), new Size(170 + 100 + 5 + 150 + 100 - 50, 200));

        // white background
        context.SetRGBFillColor(1, 1, 1, 1);
        context.FillRect(totalArea);

        // filled circle
        context.SetRGBFillColor(0.663, 0, 0.031, 1);
        context.BeginPath();
        // construct cirle path counterclockwise
        context.AddArc(circleCenter.X, circleCenter.Y, circleRadius, startingAngle, endingAngle, false);
        context.DrawPath(PathDrawingMode.Fill);

        // stroked square
        context.StrokeRect(ourRect);

        // translate to side
        context.TranslateCTM(ourRect.Size.Width + circleRadius + 5, 0);

        // create rect path + clip
        context.BeginPath();
        context.AddRect(ourRect);
        context.Clip();

        // circle again (clipped now)
        context.BeginPath();
        // construct cirle path counterclockwise
        context.AddArc(circleCenter.X, circleCenter.Y, circleRadius, startingAngle, endingAngle, false);
        context.DrawPath(PathDrawingMode.FillStroke);
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

        if (_doCrossMask)
        {
            // circular clip
            var clippy = new Rect(new Point(_mouseX - (400.0 / 2), _mouseY - (400.0 / 2)), new Size(400, 400));
            context.BeginPath();
            var clx = clippy.Origin.X + (clippy.Size.Width / 2);
            var cly = clippy.Origin.Y + (clippy.Size.Height / 2);
            context.AddArc(clx, cly, clippy.Size.Width / 2, 0, Math.PI * 2, false);
            context.Clip();
            // cross inside that
            var crossWidth = clippy.Size.Width / 3;
            var vert = new Rect(new Point(clx - (crossWidth / 2), clippy.Origin.Y), new Size(crossWidth, clippy.Size.Height));
            var horz = new Rect(new Point(clippy.Origin.X, cly - (crossWidth / 2)), new Size(clippy.Size.Width, crossWidth));
            context.BeginPath();
            context.AddRect(vert);
            context.AddRect(horz);
            context.Clip();
        }
        
        // DASHED LINES ===================
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
        
        // alpha rects ==========================================
        context.SaveGState();

        var r6 = new Rect(new Point(0, 0), new Size(130, 100));
        var r7 = new Rect(new Point(120, 90), new Size(5, 5));
        var numRects = 6;
        var tint = 1.0;
        var tintAdjust = 1.0 / numRects;
        var rotAngle = (Math.PI * 2) / numRects;

        context.TranslateCTM(800, 400);
        context.ScaleCTM(3, 3);

        context.RotateCTM(_animAngle);

        using var rounded = Drawing.Path.CreateWithRoundedRect(r6, 10, 10, AffineTransformIdentity);
        using var cornerCircle = Drawing.Path.CreateWithEllipseInRect(r7, AffineTransformIdentity);
        for (var i = 0; i < numRects; i++)
        {
            context.SetRGBFillColor(tint, tint / 2, 0, tint);
            context.AddPath(rounded);
            context.FillPath();

            context.SetRGBStrokeColor(0, 0, 0, 1);
            context.AddPath(rounded);
            context.SetLineWidth(1.5);
            context.StrokePath();

            // yellow corner thing
            context.SetRGBFillColor(1, 1, 0, 1);
            context.AddPath(cornerCircle);
            context.FillPath();

            context.RotateCTM(rotAngle);
            tint -= tintAdjust;
        }
        context.RestoreGState();
        
        // clipping example =====================================
        context.SaveGState();

        context.ScaleCTM(0.75, 0.75);
        context.TranslateCTM(70, 740);

        DoClippedCircle(context);

        context.RestoreGState();
        
        // curved corner triangle thing =========================
        context.SaveGState();

        var points = new[] { new Point(150, 150), new Point(540, 340), new Point(130, 540) };

        // line version
        context.MoveToPoint(points[0].X, points[0].Y);
        context.AddLineToPoint(points[1].X, points[1].Y);
        context.AddLineToPoint(points[2].X, points[2].Y);
        context.ClosePath();

        context.SetRGBStrokeColor(1, 1, 1, 0.5);
        context.SetLineWidth(1);
        context.StrokePath();

        // curved version
        var startEnd = Common.BetweenPoints(points[2], points[0]);
        context.MoveToPoint(startEnd.X, startEnd.Y);
        context.AddArcToPoint(points[0].X, points[0].Y, points[1].X, points[1].Y, 20);
        context.AddArcToPoint(points[1].X, points[1].Y, points[2].X, points[2].Y, 20);
        context.AddArcToPoint(points[2].X, points[2].Y, points[0].X, points[0].Y, 20);
        context.ClosePath();

        context.SetRGBStrokeColor(1, 1, 0, 1);
        context.SetLineWidth(2);
        context.StrokePath();

        context.RestoreGState();
    }
}
