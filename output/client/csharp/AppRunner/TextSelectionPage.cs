using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static AppRunner.Common;

namespace AppRunner;

public class TextSelectionPage : BasePage
{
    private readonly AttributedString _latinString;
    private readonly AttributedString _arabicString;
    private AttributedString _currentAttrString;
    
    private Frame? _frame;
    private Line[]? _lines;

    private Point _mousePos = new(-1, -1);
    private Rect _textRect;
    
    private long _mouseIndex;
    private long _startIndex;
    private long _endIndex;
    private bool _dragging;

    enum TextDirection
    {
        LeftToRight,
        RightToLeft
    }
    private TextDirection _textDirection;
    
    public TextSelectionPage(IWindowMethods windowMethods) : base(windowMethods)
    {
        using var font = Font.CreateWithName(Constants.TimesFontName, 36, new OptArgs());
        var black = Color.GetConstantColor(ColorConstants.Black);
        _latinString = AttributedString.Create(Constants.LoremIpsum, new AttributedStringOptions { Font = font, ForegroundColor = black });
        _arabicString = AttributedString.Create(Constants.ArabicSample, new AttributedStringOptions { Font = font, ForegroundColor = black });
        _currentAttrString = _latinString;
        _textDirection = TextDirection.LeftToRight;
    }

    private void DoLayout()
    {
        using var frameSetter = FrameSetter.CreateWithAttributedString(_currentAttrString);
        using var path = Drawing.Path.CreateWithRect(_textRect, new OptArgs());
    
        _frame?.Dispose();
    
        _frame = frameSetter.CreateFrame(RangeZero, path);
        _lines = _frame.GetLines(); // these aren't owned
    }

    public override void OnSize(int newWidth, int newHeight)
    {
        base.OnSize(newWidth, newHeight); // important!! ought to fix the API so this isn't required, though (have have one .OnSize to be used externally)
        
        _textRect = MakeRect(0, 0, Width, Height).Inset(20.5);
        DoLayout();
    }

    public override void OnKeyDown(Windowing.Key key, Windowing.Modifiers modifiers)
    {
        if (key == Windowing.Key.Space)
        {
            if (_currentAttrString == _latinString)
            {
                _currentAttrString = _arabicString;
                _textDirection = TextDirection.RightToLeft;
            }
            else
            {
                _currentAttrString = _latinString;
                _textDirection = TextDirection.LeftToRight;
            }
            DoLayout();
            Invalidate();
        }
    }

    public override void OnMouseMove(int x, int y, Windowing.Modifiers modifiers)
    {
        _mousePos = new Point(x, y);
        
        // calculate the cursor position (line/col etc)
        var origins = _frame!.GetLineOrigins(RangeZero);

        _mouseIndex = -1;
        foreach (var (line, origin) in _lines!.Zip(origins))
        {
            var bounds = line.GetBoundsWithOptions(0);
            var absBounds = bounds;
            absBounds.Origin.X += origin.X;
            absBounds.Origin.Y += origin.Y;
            if (absBounds.ContainsPoint(_mousePos))
            {
                // cursor location
                var hitPos = _mousePos;
                // point must be relative to line origin
                hitPos.X -= origin.X;
                hitPos.Y -= origin.Y;
                var index = line.GetStringIndexForPosition(hitPos);
                if (index >= 0)
                {
                    _mouseIndex = index;
                    if (_dragging)
                    {
                        _endIndex = _mouseIndex;
                    }
                }
                break;
            }
        }
        Invalidate();
    }
    
    public override void OnMouseLeave(Windowing.Modifiers modifiers)
    {
        _mouseIndex = -1;
        Invalidate();
    }

    public override void OnMouseDown(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
        // already know what line/index it is (if any)
        if (_mouseIndex >= 0)
        {
            // begin selection drag
            _startIndex = _mouseIndex;
            _dragging = true;
        }
        Invalidate();
    }

    public override void OnMouseUp(int x, int y, Windowing.MouseButton button, Windowing.Modifiers modifiers)
    {
        _startIndex = -1;
        _endIndex = -1;
        _dragging = false;
        Invalidate();
    }

    public override void Render(DrawContext context, RenderArea area)
    {
        context.SetRGBFillColor(0.5, 0.5, 0.5, 1);
        context.FillRect(MakeRect(0, 0, Width, Height));

        context.SetRGBStrokeColor(1, 1, 0, 1);
        context.SetLineWidth(1);
        context.StrokeRect(_textRect);
        
        context.SetTextMatrix(AffineTransformIdentity);
        var origins = _frame!.GetLineOrigins(RangeZero);
        
        //       auto useStartIndex = startIndex;
        var useStartIndex = _startIndex;
        var useEndIndex = _endIndex;
        if (useStartIndex > useEndIndex)
        {
            (useStartIndex, useEndIndex) = (useEndIndex, useStartIndex);
        }
        
        foreach (var (line, origin) in _lines!.Zip(origins))
        {
            var lineRange = line.GetStringRange();
            var bounds = line.GetBoundsWithOptions(0);
            var absBounds = bounds;
            absBounds.Origin.X = origin.X + bounds.Origin.X;
            absBounds.Origin.Y = origin.Y + bounds.Origin.Y;
            
            context.SetRGBFillColor(1, 0, 0, 1);
            context.AddArc(origin.X, origin.Y, 2, 0, Math.PI * 2, false);
            context.DrawPath(PathDrawingMode.Fill);
            
            // highlight line if mouse inside
            if (absBounds.ContainsPoint(_mousePos))
            {
                context.SetRGBFillColor(0, 0.8, 1, 0.25);
                context.FillRect(absBounds);
            }
            
            // range highlighting
            if (useStartIndex >= 0 && useEndIndex >= 0 &&
                lineRange.RangeEnd() > useStartIndex &&
                lineRange.Location < useEndIndex)
            {
                var clamped = bounds;
                
                // at least some portion of this line needs to be highlighted
                if (useStartIndex >= lineRange.Location && useStartIndex < lineRange.RangeEnd())
                {
                    var (xOffs, _) = line.GetOffsetForStringIndex(useStartIndex);
                    if (_textDirection == TextDirection.RightToLeft) {
                        // clamp rectangle end to xoffs
                        clamped.Size.Width = xOffs - clamped.Origin.X;
                    } else {
                        // clamp rectangle start to xoffs
                        var end = clamped.Origin.X + clamped.Size.Width;
                        clamped.Origin.X = xOffs;
                        clamped.Size.Width = end - xOffs; //-= xOffs;
                    }
                }
                
                if (useEndIndex >= lineRange.Location && useEndIndex < lineRange.RangeEnd())
                {
                    var (xOffs, _) = line.GetOffsetForStringIndex(useEndIndex);
                    if (_textDirection == TextDirection.RightToLeft) {
                        // clamp rectangle start to xoffs
                        var end = clamped.Origin.X + clamped.Size.Width;
                        clamped.Origin.X = xOffs;
                        clamped.Size.Width = end - xOffs; //-= xOffs;
                    } else {
                        // clamp rectangle end to xoffs
                        clamped.Size.Width = xOffs - clamped.Origin.X;
                    }
                }
                clamped.Origin.X += origin.X;
                clamped.Origin.Y += origin.Y;
                
                context.SetRGBFillColor(1, 1, 0, 1);
                context.FillRect(clamped);
            }
            
            // draw cursor position
            if (_mouseIndex >= lineRange.Location && _mouseIndex < lineRange.RangeEnd())
            {
                var (offs, _) = line.GetOffsetForStringIndex(_mouseIndex);
                var cursorXOffs = origin.X + offs;
                context.MoveToPoint(cursorXOffs, absBounds.Origin.Y);
                context.AddLineToPoint(cursorXOffs, absBounds.Origin.Y + absBounds.Size.Height);
                context.SetLineWidth(2);
                context.SetRGBStrokeColor(1, 0.85, 0, 1);
                context.StrokePath();
            }
        }
        _frame.Draw(context);
    }
}
