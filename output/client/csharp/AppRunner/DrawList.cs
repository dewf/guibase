namespace AppRunner;
using static Org.Prefixed.GuiBase.Drawing;

public class DrawList(DrawContext context)
{
    private readonly List<DrawCommand> _commands = [];
    
    public void SaveGState()
    {
        _commands.Add(new DrawCommand.SaveGState());
    }
    public void RestoreGState()
    {
        _commands.Add(new DrawCommand.RestoreGState());
    }
    public void SetRGBFillColor(double red, double green, double blue, double alpha)
    {
        _commands.Add(new DrawCommand.SetRGBFillColor(red, green, blue, alpha));
    }
    public void SetRGBStrokeColor(double red, double green, double blue, double alpha)
    {
        _commands.Add(new DrawCommand.SetRGBStrokeColor(red, green, blue, alpha));
    }
    public void SetFillColorWithColor(Color color)
    {
        _commands.Add(new DrawCommand.SetFillColorWithColor(color));
    }
    public void FillRect(Rect rect)
    {
        _commands.Add(new DrawCommand.FillRect(rect));
    }
    public void SetTextMatrix(AffineTransform t)
    {
        _commands.Add(new DrawCommand.SetTextMatrix(t));
    }
    public void SetTextPosition(double x, double y)
    {
        _commands.Add(new DrawCommand.SetTextPosition(x, y));
    }
    public void BeginPath()
    {
        _commands.Add(new DrawCommand.BeginPath());
    }
    public void AddArc(double x, double y, double radius, double startAngle, double endAngle, bool clockwise)
    {
        _commands.Add(new DrawCommand.AddArc(x, y, radius, startAngle, endAngle, clockwise));
    }
    public void AddArcToPoint(double x1, double y1, double x2, double y2, double radius)
    {
        _commands.Add(new DrawCommand.AddArcToPoint(x1, y1, x2, y2, radius));
    }
    public void DrawPath(PathDrawingMode mode)
    {
        _commands.Add(new DrawCommand.DrawPath(mode));
    }
    public void SetStrokeColorWithColor(Color color)
    {
        _commands.Add(new DrawCommand.SetStrokeColorWithColor(color));
    }
    public void StrokeRectWithWidth(Rect rect, double width)
    {
        _commands.Add(new DrawCommand.StrokeRectWithWidth(rect, width));
    }
    public void MoveToPoint(double x, double y)
    {
        _commands.Add(new DrawCommand.MoveToPoint(x, y));
    }
    public void AddLineToPoint(double x, double y)
    {
        _commands.Add(new DrawCommand.AddLineToPoint(x, y));
    }
    public void StrokePath()
    {
        _commands.Add(new DrawCommand.StrokePath());
    }
    public void SetLineDash(double phase, double[] lengths)
    {
        _commands.Add(new DrawCommand.SetLineDash(phase, lengths));
    }
    public void ClearLineDash()
    {
        _commands.Add(new DrawCommand.ClearLineDash());
    }
    public void SetLineWidth(double width)
    {
        _commands.Add(new DrawCommand.SetLineWidth(width));
    }
    public void Clip()
    {
        _commands.Add(new DrawCommand.Clip());
    }
    public void ClipToRect(Rect clipRect)
    {
        _commands.Add(new DrawCommand.ClipToRect(clipRect));
    }
    public void TranslateCTM(double tx, double ty)
    {
        _commands.Add(new DrawCommand.TranslateCTM(tx, ty));
    }
    public void ScaleCTM(double scaleX, double scaleY)
    {
        _commands.Add(new DrawCommand.ScaleCTM(scaleX, scaleY));
    }
    public void RotateCTM(double angle)
    {
        _commands.Add(new DrawCommand.RotateCTM(angle));
    }
    public void ConcatCTM(AffineTransform transform)
    {
        _commands.Add(new DrawCommand.ConcatCTM(transform));
    }
    public void AddPath(Path path)
    {
        _commands.Add(new DrawCommand.AddPath(path));
    }
    public void FillPath()
    {
        _commands.Add(new DrawCommand.FillPath());
    }
    public void StrokeRect(Rect rect)
    {
        _commands.Add(new DrawCommand.StrokeRect(rect));
    }
    public void AddRect(Rect rect)
    {
        _commands.Add(new DrawCommand.AddRect(rect));
    }
    public void ClosePath()
    {
        _commands.Add(new DrawCommand.ClosePath());
    }
    public void DrawLinearGradient(Gradient gradient, Point startPoint, Point endPoint, GradientDrawingOptions drawOpts)
    {
        _commands.Add(new DrawCommand.DrawLinearGradient(gradient, startPoint, endPoint, drawOpts));
    }
    public void DrawFrame(Frame frame)
    {
        _commands.Add(new DrawCommand.DrawFrame(frame));
    }
    public void Send()
    {
        var arr = _commands.ToArray();
        Console.WriteLine($"draw list array length: {arr.Length}");
        context.BatchDraw(arr);
        _commands.Clear();
    }
}
