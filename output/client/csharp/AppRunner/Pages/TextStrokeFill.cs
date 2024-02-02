using Org.Prefixed.GuiBase;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class TextStrokeFill(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    public override string PageTitle() => "Text Stroke/Fill";

    public override void Render(Drawing.DrawContext context, RenderArea area)
    {
        context.SetRGBFillColor(0.5, 0.5, 0.5, 1);
        context.FillRect(MakeRect(0, 0, Width, Height));
        context.ScaleCTM(3, 3);

        context.SetTextMatrix(Drawing.AffineTransformIdentity);

        var p = new Drawing.Point(20, 20);
        Drawing.Rect r;
        r.Origin = p;

        const string str2 = "Quartz♪❦♛あぎ";
        var attrs2 = new Drawing.AttributedStringOptions();

        // draw with default attributes
        PointAt(context, p);
        TextLine(context, p.X, p.Y, str2, attrs2);
        
        // draw with specific font and color
        p.Y += 30;
        PointAt(context, p);

        // larger font + blue color
        using var largeFont = Drawing.Font.CreateWithName(Constants.TimesFontName, 40, new Drawing.OptArgs());
        using var blueColor = Drawing.Color.CreateGenericRGB(0, 0.3, 1, 1);

        attrs2.Font = largeFont;
        attrs2.ForegroundColor = blueColor;
        TextLine(context, p.X, p.Y, str2, attrs2);

        /**** line3: draw stroked text ****/
        p.Y += 60;
        PointAt(context, p);
        
        attrs2.StrokeWidth = 1;
        TextLine(context, p.X, p.Y, str2, attrs2);
        
        // line 4: fill and stroke
        p.Y += 60;
        PointAt(context, p);

        // negative stroke = stroke and fill
        attrs2.StrokeWidth = -1;
        attrs2.StrokeColor = Drawing.Color.GetConstantColor(Drawing.ColorConstants.Black); // no need to dispose, because we don't own it
        TextLine(context, p.X, p.Y, str2, attrs2);

        // line 5: draw at baseline
        p.Y += 100;
        PointAt(context, p);

        TextLine(context, p.X, p.Y, str2, attrs2, false, true);
    }
}