using AppRunner.Pages.Util;
using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Windowing;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class DragDropTesting(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    public override string PageTitle => "DnD Testing";
    public override bool CanDrop => true;
    private bool _dropInProgress;
    private bool _dropAllowed;
    private DropEffect _suggestedEffect;
    
    private double _animPhase;
    public override bool IsAnimating => _dropInProgress;
    public override void Render(DrawContext context, RenderArea area)
    {
        using var font = Font.CreateWithName(Constants.TimesFontName, 32, new OptArgs());
        using var largeFont = Font.CreateWithName(Constants.FuturaFontName, 64, new OptArgs());
        using var orange = Color.CreateGenericRGB(1, 0.75, 0, 1);
        using var black = Color.GetConstantColor(ColorConstants.Black);
        using var green = Color.CreateGenericRGB(0, 1, 0.6, 0.8);

        var totalRect = MakeRect(0, 0, Width, Height);

        context.SetFillColorWithColor(black);
        context.FillRect(totalRect);
        TextLine(context, 20, 20, "DnD Testing", new AttributedStringOptions { Font = font, ForegroundColor = orange }, withGradient:false);

        if (_dropInProgress && _dropAllowed)
        {
            var rect = totalRect.Inset(20);
            using var path = Drawing.Path.CreateWithRoundedRect(rect, 20, 20, new OptArgs());
            context.SetStrokeColorWithColor(green);
            context.SetLineDash(_animPhase, [4, 4]);
            context.SetLineWidth(8);
            context.AddPath(path);
            context.DrawPath(PathDrawingMode.Stroke);

            var effectLabel = _suggestedEffect switch
            {
                DropEffect.Copy => "Copy",
                DropEffect.Move => "Move",
                DropEffect.Link => "Link",
                DropEffect.Other => "Other",
                _ => "None"
            };
            CenterText(context, totalRect, effectLabel, new AttributedStringOptions { Font = largeFont, ForegroundColor = green });
        }
    }

    public override DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested)
    {
        _dropInProgress = true;
        _suggestedEffect = suggested;
        // timer is animating / invalidating
        // Invalidate();
        
        if (data.HasFormat(KDragFormatFiles))
        {
            _dropAllowed = true;
            return DropEffect.Copy | DropEffect.Link | DropEffect.Move;
        }
        _dropAllowed = false;
        return DropEffect.None;
    }

    public override void DropLeave()
    {
        _dropInProgress = false;
        _dropAllowed = false;
        Invalidate();
    }

    public override void DropSubmit(DropData data, int x, int y, Modifiers modifiers, DropEffect effect)
    {
        Console.WriteLine("drop submitted!");
        _dropInProgress = false;
        _dropAllowed = false;
        // timer no longer invalidating:
        Invalidate();
    }
    
    public override void OnTimer(double secondsSinceLast)
    {
        // 1 complete cycle per second?
        _animPhase = (_animPhase + (secondsSinceLast * 8.0)) % 8.0;
        Invalidate();
    }
}
