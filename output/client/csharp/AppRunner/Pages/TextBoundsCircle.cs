﻿using CSharpFunctionalExtensions;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Text;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class TextBoundsCircle : BasePage
{
    private readonly AttributedString _labelString;
    
    public override string PageTitle => "Text Bounds + Concentric Circles";
    
    public TextBoundsCircle(IWindowMethods windowMethods) : base(windowMethods)
    {
        // test create some fonts and layouts and stuff
        using var font = Font.CreateFromFile("./_democontent/LiberationSerif-Regular.ttf", 120.0, Maybe.None);
        _labelString = AttributedString.Create("Quartz♪❦♛あぎ", new AttributedString.Options
        {
            Font = font,
            ForegroundColor = Color.CreateGenericRGB(0, 1, 1, 0.5)
        });
        // this is going to auto-dispose the font, but the attributed string's internal dictionary should have retained it
    }

    public override void Render(DrawContext context, RenderArea area)
    {
        context.SetRGBFillColor(0.2, 0.2, 0.3, 1);
        context.FillRect(MakeRect(0, 0, Width, Height));
        context.SetTextMatrix(AffineTransform.Identity);

        using var line = Line.CreateWithAttributedString(_labelString);

        double yAdvance;
        double x = 100;
        double y = 200;

        DrawLineAt(context, line, x, y, out yAdvance);

        // concentric circles to test arcs
        context.SetRGBStrokeColor(0, 0.4, 1, 1);
        context.SetLineWidth(2.0);
        x = Width / 2.0;
        y = (Height * 2.0) / 3.0;
        //dl_CGContextMoveToPoint(c, x, y);
        context.BeginPath();
        context.AddArc(x, y, 240, 0, 2 * Math.PI, true);
        context.StrokePath();

        context.SetLineWidth(10);
        double radius = 230;
        double startAngle = 0;
        for (var i = 0; i < 10; i++)
        {
            var endAngle = startAngle + Math.PI;
            
            context.BeginPath();
            context.AddArc(x, y, radius, startAngle, endAngle, true);
            context.SetRGBStrokeColor(0, 0.6, 1, 1);
            context.StrokePath();

            startAngle += Math.PI;
            endAngle += Math.PI;
            context.BeginPath();
            context.AddArc(x, y, radius, startAngle, endAngle, true);
            context.SetRGBStrokeColor(0, 0, 0, 1);
            context.StrokePath();

            startAngle += Math.PI + (Math.PI / 6);
            radius -= 15;
        }
    }
}
