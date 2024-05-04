using CSharpFunctionalExtensions;
using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class TransformedShapesPage : BasePage
{
    private readonly Gradient _grad;    
    private readonly Gradient _grad2;
    
    public override string PageTitle => "Transformed Shapes";
    
    public TransformedShapesPage(IWindowMethods windowMethods) : base(windowMethods)
    {
        using var space = ColorSpace.CreateWithName(ColorSpace.Name.GenericRGB);
        _grad = Gradient.CreateWithColorComponents(space, [
            new Gradient.Stop(0, 0.0, 0.5, 1.0, 1.0),
            new Gradient.Stop(1, 0.0, 1.0, 0.0, 1.0)
        ]);
        _grad2 = Gradient.CreateWithColorComponents(space, [
            new Gradient.Stop(0, 0.0, 0.5, 1.0, 0.3),
            new Gradient.Stop(1, 0.0, 1.0, 0.0, 0.3)
        ]);
    }

    private static double DegreesToRadians(double degrees)
    {
        return (degrees * Math.PI) / 180;
    }

    private static void DrawPoint(DrawContext context, Point p, double radius)
    {
        context.BeginPath();
        context.AddArc(p.X, p.Y, radius, 0, DegreesToRadians(360), false);
        context.FillPath();
    }

    private void TransformTest(DrawContext context)
    {
        var r = MakeRect(100, 100, 500, 500);
        var start = new Point(100, 100);
        var end = new Point(100, 600);
        
        context.SetRGBFillColor(1, 0, 0, 1);
        DrawPoint(context, start, 5);
        DrawPoint(context, end, 5);

        context.SaveGState();

        // draw semi-transparent (darker against black) one first
        context.DrawLinearGradient(_grad2, start, end, 0);

        // original rect
        context.SetRGBStrokeColor(1, 1, 0, 1); // yellow
        context.StrokeRectWithWidth(r, 2);

        // transform
        context.TranslateCTM(256, 0);
        context.ScaleCTM(0.25, 0.5);
        context.RotateCTM(DegreesToRadians(22));

        // start/end, transformed
        context.SetRGBFillColor(1, 0, 0, 1);
        DrawPoint(context, start, 5);
        DrawPoint(context, end, 5);

        // rect, transformed
        context.SetRGBStrokeColor(1, 1, 0, 1); // yellow
        context.StrokeRectWithWidth(r, 2);

        // semi-transparent again, post-transform
        context.DrawLinearGradient(_grad2, start, end, 0);

        // rect-clipped, full bright version
        context.ClipToRect(r);
        context.DrawLinearGradient(_grad, start, end, 0);

        context.RestoreGState();
    }

    private void TriangleThing(DrawContext context, Point center, AffineTransform? m, double baseOpacity)
    {
        context.SaveGState();
        
        // triangle thing from page 01, as a mutable path

        // center 273.33, 343.33
        Point[] points =
        [
            new Point(center.X - 123.33, center.Y - 193.33),
            new Point(center.X + 266.67, center.Y + 3.33),
            new Point(center.X - 143.33, center.Y + 196.67)
        ];

        var maybeTransform =
            m.HasValue ? Maybe.From(m.Value) : Maybe.None;
        
        // line version
        using var linePath = MutablePath.Create();
        linePath.MoveToPoint(points[0].X, points[0].Y, maybeTransform);

        linePath.AddLineToPoint(points[1].X, points[1].Y, maybeTransform);
        linePath.AddLineToPoint(points[2].X, points[2].Y, maybeTransform);
        linePath.CloseSubpath();

        context.SetRGBStrokeColor(1, 1, 1,  baseOpacity * 0.5);
        context.SetLineWidth(2);
        context.SetLineDash(0, [ 3, 3 ]);
        context.AddPath(linePath);
        context.StrokePath();

        context.ClearLineDash();

        // curved version
        using var curvedPath = MutablePath.Create();
        var startEnd = BetweenPoints(points[2], points[0]);

        curvedPath.MoveToPoint(startEnd.X, startEnd.Y, maybeTransform);
        curvedPath.AddArcToPoint(points[0].X, points[0].Y, points[1].X, points[1].Y, 20, maybeTransform);
        curvedPath.AddArcToPoint(points[1].X, points[1].Y, points[2].X, points[2].Y, 20.0, maybeTransform);
        curvedPath.AddArcToPoint(points[2].X, points[2].Y, points[0].X, points[0].Y, 20.0, maybeTransform);
        curvedPath.CloseSubpath();

        context.SetRGBStrokeColor(0.85, 0, 1, baseOpacity * 0.75);
        context.SetLineWidth(4);
        context.AddPath(curvedPath);
        context.StrokePath();

        // restore
        context.RestoreGState();
    }

    private void MiscShapes(DrawContext context, Point center, AffineTransform? m, double baseOpacity)
    {
        var maybeTransform =
            m.HasValue ? Maybe.From(m.Value) : Maybe.None;

        context.SetLineWidth(2);
        
        const double pointsSide = 230;
        
        Point[] points = [
            new Point(center.X - pointsSide/2, center.Y - pointsSide/2 ),
            new Point(center.X + pointsSide/2, center.Y - pointsSide/2 ),
            new Point(center.X + pointsSide/2, center.Y + pointsSide/2 ),
            new Point(center.X - pointsSide/2, center.Y + pointsSide/2 ),
            
            // extra control points for final segment
            new Point(center.X - pointsSide/2 - 100.0, center.Y + pointsSide/2 - 20.0 ),
            new Point(center.X - pointsSide/2, center.Y - pointsSide/2 + 30.0 )
        ];
        
        const double ellipseWidth = 200;
        const double ellipseHeight = 100;
        var r = MakeRect(center.X - ellipseWidth/2, center.Y - ellipseHeight/2, ellipseWidth, ellipseHeight);

        // black background
        const double extra = 4;
        var r2 = MakeRect(center.X - 300.0 - extra, center.Y - pointsSide/2 - extra, 600.0 + extra*2, pointsSide + extra*2);
        using var bgRect = Drawing.Path.CreateWithRect(r2, maybeTransform);
        context.SetRGBFillColor(0, 0, 0, baseOpacity);
        context.AddPath(bgRect);
        context.FillPath();

        using var rounded = Drawing.Path.CreateWithRoundedRect(r, 10, 10, maybeTransform);
        using var mutable01 = rounded.CreateMutableCopy();

        var rSquare = MakeRect(center.X - ellipseWidth / 8, center.Y - ellipseWidth / 8, ellipseWidth / 4, ellipseWidth / 4);
        using var square = Drawing.Path.CreateWithRect(rSquare, Maybe.None); // no transform on the square itself, being added to path with xform
        mutable01.AddPath(square, maybeTransform);

        context.SetRGBStrokeColor(0.3, 0, 1, baseOpacity);
        context.AddPath(mutable01);
        context.StrokePath();

        using var ellipse = Drawing.Path.CreateWithEllipseInRect(r, maybeTransform);
        using var mutable02 = ellipse.CreateMutableCopy();
        
        mutable02.AddLines(points[..4], maybeTransform); // already includes implicit moveToPoint(point[0])
        mutable02.AddCurveToPoint(points[4].X, points[4].Y, points[5].X, points[5].Y, points[0].X, points[0].Y, maybeTransform);
        // closing the path looks a little nicer
        mutable02.CloseSubpath();

        context.SetRGBStrokeColor(1, 0, 0.3, baseOpacity);
        context.AddPath(mutable02);
        context.SetLineDash(0, [ 3, 3 ]);
        context.StrokePath();

        // clear dashes
        context.ClearLineDash();

        // quad curves
        using var mutable03 = MutablePath.Create();
        mutable03.MoveToPoint(center.X - 300.0, center.Y, maybeTransform);
        mutable03.AddQuadCurveToPoint(center.X - 150, center.Y - 150, center.X, center.Y, maybeTransform);
        mutable03.AddQuadCurveToPoint(center.X + 150, center.Y + 150, center.X + 300, center.Y, maybeTransform);

        context.AddPath(mutable03);
        context.SetRGBStrokeColor(1, 1, 1, baseOpacity);
        context.StrokePath();
    }

    private void SubPaths(DrawContext context, Point center, AffineTransform? m, double baseOpacity)
    {
        var maybeTransform =
            m.HasValue ? Maybe.From(m.Value) : Maybe.None;
        
        // final misc shapes
        Rect[] rects =
        [
            MakeRect(center.X + 20, center.Y - 90, 40.0, 40.0),
            MakeRect(center.X - 70, center.Y, 60.0, 60.0)
        ];
        using var mutable04 = MutablePath.Create();
        
        var r1 = MakeRect(center.X - 80.0, center.Y - 80.0, 40.0, 40.0);
        mutable04.AddRect(r1, maybeTransform);
        mutable04.AddRects(rects, maybeTransform);

        var r2 = MakeRect(center.X + 60, center.Y + 20, 60.0, 60.0);
        mutable04.AddRoundedRect(r2, 10, 10, maybeTransform);

        var r3 = MakeRect(center.X - 40, center.Y - 40, 80.0, 80.0);
        mutable04.AddEllipseInRect(r3, maybeTransform);

        // black outer path
        context.AddPath(mutable04);
        context.SetRGBStrokeColor(0, 0, 0, baseOpacity);
        context.SetLineWidth(6.5);
        context.StrokePath();

        // then cyan
        context.AddPath(mutable04);
        context.SetRGBStrokeColor(0, 0.8, 1, baseOpacity);
        context.SetLineWidth(2.5);
        context.StrokePath();
    }

    private void KeyholeThing(DrawContext context, Point center, AffineTransform? m, double colorInterp)
    {
        var maybeTransform =
            m.HasValue ? Maybe.From(m.Value) : Maybe.None;
        
        using var path = MutablePath.Create();

        double radius = 50;
        path.MoveToPoint(center.X + radius, center.Y, maybeTransform);
        path.AddArc(center.X, center.Y, radius, 0, Math.PI * 2.0 - (Math.PI/4), true, maybeTransform);
        
        path.AddRelativeArc(center.X, center.Y, radius + 70.71067, -(Math.PI/4), Math.PI/4, maybeTransform);

        // just a dot to test GetCurrentPoint
        var p1 = path.GetCurrentPoint();
        
        path.CloseSubpath();
        
        // draw a dot at p1 (underneath path)
        context.SetRGBFillColor(1, 1, 0, 1);
        context.AddArc(p1.X, p1.Y, 5.0, 0, Math.PI*2.0, true);
        context.FillPath();

        // draw path itself
        context.SetRGBStrokeColor(1 * colorInterp, 0, 0, 1);
        context.SetLineWidth(3);
        context.AddPath(path);
        context.StrokePath();
    }

    private void MutablePathTest(DrawContext context)
    {
        context.SaveGState();
        
        const int numSteps = 5;

        var center = new Point(750, 350);

        // complete subpaths (rect, ellipse, etc)
        var subPathsCenter = center;
        var m3 = MakeTransform(subPathsCenter, Math.PI / 10, 2);
        SubPaths(context, subPathsCenter, m3, 0.5);
        SubPaths(context, subPathsCenter, null, 1);

        // keyhole
        for (var i = numSteps; i >= 0; i--)
        {
            var scale = 1.0 + ((i * 1.0) / numSteps);
            var rot = (i * (Math.PI/6)) / numSteps;
            var color = 1.0 - (i / (double)numSteps);
            var m = MakeTransform(center, rot, scale);
            KeyholeThing(context, center, m, color);
        }
        
        // triangle w/ arc-to-point test
        var rotCenter = new Point(273.33, 343.33);
        for (var i = 0; i < numSteps + 1; i++)
        {
            var angle = (i * (Math.PI / 4.0)) / numSteps;
            var opacity = 1.0 - (i / (double)numSteps);
            var scale = 1.0 - ((i * 0.5) / numSteps);
            var m = MakeTransform(rotCenter, angle, scale);
            TriangleThing(context, rotCenter, m, opacity);
        }
        
        var shapesCenter = new Point(600, 600);
        var m2 = MakeTransform(shapesCenter, Math.PI/9.0, 0.5);
        MiscShapes(context, shapesCenter, m2, 1);
        
        context.RestoreGState();
    }
    
    public override void Render(DrawContext context, RenderArea area)
    {
        context.SetRGBFillColor(0, 0, 0, 1);
        context.FillRect(MakeRect(0, 0, Width, Height));
        TransformTest(context);
        MutablePathTest(context);
    }
}
