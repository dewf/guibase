using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class TextStrokeTestingPage(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    public override string PageTitle() => "Text Stroke/Testing";
    
    private void ClipPre(DrawContext context, TextDrawingMode mode, Rect bounds, double xpos, double ypos)
    {
        if (mode is TextDrawingMode.Clip or TextDrawingMode.FillClip or TextDrawingMode.StrokeClip or TextDrawingMode.FillStrokeClip)
        {
            context.SaveGState();
            var rect = MakeRect(xpos, ypos, bounds.Size.Width, bounds.Size.Height);
            context.StrokeRect(rect);
        }
    }
    
    private static readonly Gradient Gradient = GetGradient(1, 0, 1, 1, 0, 1, 1, 1);
    private void ClipPost(DrawContext context, TextDrawingMode mode, Rect bounds, double xpos, double ypos)
    {
        if (mode is TextDrawingMode.Clip or TextDrawingMode.FillClip or TextDrawingMode.StrokeClip or TextDrawingMode.FillStrokeClip)
        {
            var start = new Point(xpos, ypos);
            var end = new Point(xpos + bounds.Size.Width, ypos + bounds.Size.Height);
            context.DrawLinearGradient(Gradient, start, end, 0);
            context.RestoreGState();
        }
    }

    private void StrokeTesting(DrawContext context, MutableAttributedString attrString, Font font, bool useForegroundColor, double xpos)
    {
    	// dict
        var totalRange = MakeRange(0, attrString.GetLength());
        attrString.SetAttribute(totalRange, new AttributedStringOptions { Font = font });
        attrString.SetAttribute(totalRange, new AttributedStringOptions { ForegroundColorFromContext = useForegroundColor });
        using var line0 = Line.CreateWithAttributedString(attrString);

        // variations
        using var as1 = attrString.CreateMutableCopy(0);
        as1.SetAttribute(totalRange, new AttributedStringOptions { StrokeWidth = 2 });
        using var line1 = Line.CreateWithAttributedString(as1);

        using var as2 = attrString.CreateMutableCopy(0);
        as2.SetAttribute(totalRange, new AttributedStringOptions{ StrokeWidth = -2 });
        using var line2 = Line.CreateWithAttributedString(as2);

        using var green = Color.CreateGenericRGB(0, 1, 0, 1);
        using var as3 = attrString.CreateMutableCopy(0);
        as3.SetAttribute(totalRange, new AttributedStringOptions { StrokeWidth = 2, StrokeColor = green });
        using var line3 = Line.CreateWithAttributedString(as3);
        
        context.SetRGBFillColor(0, 0.8, 1, 1);
        context.SetRGBStrokeColor(1, 1, 0, 1);
        context.SetLineWidth(1.5);

        var typoBounds = line0.GetTypographicBounds();
        var rect = line0.GetBoundsWithOptions(LineBoundsOptions.UseOpticalBounds);

        var ypos = 0.0;
        TextDrawingMode[] modeList = [TextDrawingMode.Fill, TextDrawingMode.Stroke, TextDrawingMode.FillStroke, TextDrawingMode.StrokeClip];
        foreach (var mode in modeList)
        {
            context.SetTextDrawingMode(mode);
            
            ClipPre(context, mode, rect, xpos, ypos);
            context.SetTextPosition(xpos, ypos + typoBounds.Ascent);
            line0.Draw(context);
            ClipPost(context, mode, rect, xpos, ypos);
            ypos += 60;
            
            context.SetTextPosition(xpos + 20, ypos + typoBounds.Ascent);
            line1.Draw(context);
            ypos += 60;
            
            context.SetTextPosition(xpos + 40, ypos + typoBounds.Ascent);
            line2.Draw(context);
            ypos += 60;
            
            context.SetTextPosition(xpos + 60, ypos + typoBounds.Ascent);
            line3.Draw(context);
            ypos += 60;
        }
    }
    
    public override void Render(Drawing.DrawContext context, RenderArea area)
    {
        context.SetRGBFillColor(0.5, 0.5, 0.5, 1);
        context.FillRect(MakeRect(0, 0, Width, Height));

        context.SetTextMatrix(AffineTransformIdentity);

        using var font = Font.CreateWithName("Times New Roman", 70, new OptArgs());
        using var attrString = MutableAttributedString.Create(0);

        attrString.ReplaceString(RangeZero, "Testing 123!");
        
        StrokeTesting(context, attrString, font, false, 0);
        StrokeTesting(context, attrString, font, true, 400);
    }
}
