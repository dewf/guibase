﻿using static Org.Prefixed.GuiBase.Drawing;

using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class ResizeGradient(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    public override string PageTitle => "Resize Gradient";
    
    public override void Render(DrawContext context, RenderArea area)
    {
        using var grad1 = GetGradient(0.3, 0.2, 1, 1, 1, 0.3, 0, 1);
        var start = new Point(100, 100);
        var end = new Point(Width - 100, Height - 100);
        context.DrawLinearGradient(grad1, start, end, Gradient.DrawingOptions.DrawsBeforeStartLocation | Gradient.DrawingOptions.DrawsAfterEndLocation);

        using var grad2 = GetGradient(0, 0, 0, 0.5, 1, 1, 1, 0.5);
        start = new Point(100, Height - 100);
        end = new Point(Width - 100, 100);
        context.DrawLinearGradient(grad2, start, end, 0);

        using var grad3 = GetGradient(0, 1, 1, 1, 0, 0, 0, 1);
        start = new Point(Width / 2.0 - 50, 0);
        end = new Point(Width / 2.0 + 50, 0);
        context.DrawLinearGradient(grad3, start, end, 0);
        
        using var grad4 = GetGradient(1, 0, 1, 0.5, 0, 0, 0, 0.5);
        start = new Point(0, Height / 2.0 - 50);
        end = new Point(0, Height / 2.0 + 50);
        context.DrawLinearGradient(grad4, start, end, 0);
    }
}
