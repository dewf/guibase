using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

public class Page02(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    private AttributedString? _labelString;
    public override void Init()
    {
        // test create some fonts and layouts and stuff
        using var font = Font.CreateFromFile("./_democontent/LiberationSerif-Regular.ttf", 120.0, AffineTransformIdentity);
        _labelString = AttributedString.Create("Quartz♪❦♛あぎ", new AttributedStringOptions
        {
            Font = font,
            ForegroundColor = Color.Create(0, 1, 1, 0.5)
        });
        // this is going to auto-dispose the font, but the attributed string's internal dictionary should have retained it
    }

    public override void Render(DrawContext context, int x, int y, int width, int height)
    {
        context.SetRGBFillColor(0.2, 0.2, 0.3, 1);
        context.FillRect(MakeRect(0, 0, width, height));
        context.SetTextMatrix(AffineTransformIdentity);

        using var line = Line.CreateWithAttributedString(_labelString);

        double yAdvance;
        double x2 = 100;
        double y2 = 200;

        Common.DrawLineAt(context, line, x2, y2, out yAdvance);

        // // concentric circles to test arcs
        // dl_CGContextSetRGBStrokeColor(c, 0, 0.4, 1, 1);
        // dl_CGContextSetLineWidth(c, 2.0);
        // x = width / 2.0;
        // y = (height * 2.0) / 3.0;
        // //dl_CGContextMoveToPoint(c, x, y);
        // dl_CGContextBeginPath(c);
        // dl_CGContextAddArc(c, x, y, 240, 0, 2 * M_PI, 1);
        // dl_CGContextStrokePath(c);
        //
        // dl_CGContextSetLineWidth(c, 10);
        // dl_CGFloat radius = 230;
        // dl_CGFloat startAngle = 0;
        // for (int i = 0; i < 10; i++) {
        //     auto endAngle = startAngle + M_PI;
        //
        //     dl_CGContextBeginPath(c);
        //     dl_CGContextAddArc(c, x, y, radius, startAngle, endAngle, 1);
        //     dl_CGContextSetRGBStrokeColor(c, 0, 0.6, 1, 1);
        //     dl_CGContextStrokePath(c);
        //
        //     startAngle += M_PI;
        //     endAngle += M_PI;
        //     dl_CGContextBeginPath(c);
        //     dl_CGContextAddArc(c, x, y, radius, startAngle, endAngle, 1);
        //     dl_CGContextSetRGBStrokeColor(c, 0, 0, 0, 1);
        //     dl_CGContextStrokePath(c);
        //
        //     startAngle += M_PI + M_PI / 6;
        //     radius -= 15;
        // }
    }
}
