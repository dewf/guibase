using System.Data.Common;
using AppRunner.Pages.Menus;
using AppRunner.Pages.Util;
using Org.Prefixed.GuiBase;
using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Windowing;
using static AppRunner.Pages.Util.Common;

namespace AppRunner.Pages;

public class WindowEventPage : BasePage
{
    private readonly IWindowMethods _windowMethods;
    
    private bool _dropInProgress;
    private bool _dropAllowed;
    private DropEffect _suggestedEffect;
    private double _animPhase;
    private string[]? _lastDroppedFiles;

    private readonly ClientMenuBar _menuBar;

    private readonly Rect _dragSourceRect = MakeRect(100, 100, 200, 200);

    private bool _mouseDownPotentialDrag;

    
    public override string PageTitle => "Windowing/Event testing";
    public override bool CanDrop => true;
    public override bool IsAnimating => _dropInProgress;

    private readonly MenuBar _nativeMenuBar;
    public override MenuBar? MenuBar => _nativeMenuBar;

    private void OnMenuInvalidation(object? sender, EventArgs args)
    {
        Invalidate(0, 0, Width, ClientMenuBar.MenuHeight);
    }

    private static MenuBar CreateMenuBar(IWindowMethods windowMethods)
    {
        // no 'using' since we're returning it
        var menuBar = MenuBar.Create();
        
        // file menu
        using var fileMenu = Menu.Create();
        // exit
        using var exitAccel = Accelerator.Create(Key.Q, Modifiers.Control);
        using var exitAction = Windowing.Action.Create("E&xit", null, exitAccel, () =>
        {
            Console.WriteLine("Exiting!");
            windowMethods.DestroyWindow();
        });
        fileMenu.AddAction(exitAction);
        
        // edit menu
        using var editMenu = Menu.Create();
        // copy
        using var copyAccel = Accelerator.Create(Key.C, Modifiers.Control);
        using var copyAction = Windowing.Action.Create("&Copy", null, copyAccel, () =>
        {
            using var dragData = DragData.Create(windowMethods.GetWindowHandle()); // would be kind of cool if we had another constructor that rendered from a delegate ... would make a lot more sense for deferred rendering
            dragData.AddFormat(KDragFormatUTF8);
            ClipData.SetClipboard(dragData);
            Console.WriteLine("Set UTF8 text to clipboard! (deferred rendering, though)");
            // dragData will be released, but I think it's OK because behind the scenes it's using COM reference counting for the actual (deferred) data payload
        });
        editMenu.AddAction(copyAction);
        // paste
        using var pasteAccel = Accelerator.Create(Key.V, Modifiers.Control);
        using var pasteAction = Windowing.Action.Create("&Paste", null, pasteAccel, () =>
        {
            using var data = ClipData.Get();
            if (data.HasFormat(KDragFormatUTF8))
            {
                var text = data.GetTextUTF8();
                Console.WriteLine($"Pasting from clipboard: [[{text}]]");
            }
        });
        editMenu.AddAction(pasteAction);

        // menubar
        menuBar.AddMenu("&File", fileMenu);
        menuBar.AddMenu("&Edit", editMenu);
        return menuBar;
    }

    public WindowEventPage(IWindowMethods windowMethods) : base(windowMethods)
    {
        _windowMethods = windowMethods;
        _menuBar = new ClientMenuBar(windowMethods);
        _menuBar.NeedsInvalidation += OnMenuInvalidation;
        
        _nativeMenuBar = CreateMenuBar(windowMethods);
    }

    public override void OnHostWindowMoved()
    {
        _menuBar.HostWindowMoved();
    }

    public override void OnMouseMove(int x, int y, Modifiers modifiers)
    {
        _menuBar.OnMouseMove(x, y);
        if (_mouseDownPotentialDrag)
        {
            // begin DnD drag
            using var dragData = DragData.Create(_windowMethods.GetWindowHandle());
            dragData.AddFormat(KDragFormatUTF8);
            var dropEffect = dragData.Execute(DropEffect.Copy);
            Console.WriteLine($"DnD Drop effect: {dropEffect} (source format: {KDragFormatUTF8})");
            // cancel the potential, otherwise they will keep happening!
            _mouseDownPotentialDrag = false;
        }
    }

    public override void OnMouseDown(int x, int y, MouseButton button, Modifiers modifiers)
    {
        if (y < ClientMenuBar.MenuHeight)
        {
            _menuBar.OnMouseDown(x, y);
        }
        else
        {
            _menuBar.PublicHide();
            _mouseDownPotentialDrag = _dragSourceRect.ContainsPoint(new Point(x, y));
        }
    }

    public override void Render(DrawContext context, RenderArea area)
    {
        using var smallFont = Font.CreateWithName(Constants.TimesFontName, 16, new OptArgs());
        using var font = Font.CreateWithName(Constants.TimesFontName, 32, new OptArgs());
        using var largeFont = Font.CreateWithName(Constants.FuturaFontName, 64, new OptArgs());
        using var orange = Color.CreateGenericRGB(1, 0.75, 0, 1);
        using var black = Color.GetConstantColor(ColorConstants.Black);
        using var green = Color.CreateGenericRGB(0, 1, 0.6, 0.8);
        using var lightBlue = Color.CreateGenericRGB(0.3, 0.3, 1.0, 1);

        var totalRect = MakeRect(0, 0, Width, Height);

        // background
        context.SetRGBFillColor(0, 0.3, 0.4, 1);
        context.FillRect(totalRect);
        
        // menu
        context.SaveGState();
        var menuRect = MakeRect(0, 0, Width, ClientMenuBar.MenuHeight);
        context.ClipToRect(menuRect);
        _menuBar.Render(context, Width);
        context.RestoreGState();
        
        // drag rect
        context.SetStrokeColorWithColor(orange);
        context.SetLineWidth(2);
        context.StrokeRect(_dragSourceRect);
        CenterText(context, _dragSourceRect, "Drag Source", new AttributedStringOptions { Font = smallFont, ForegroundColor = orange });
        
        // etc
        // TextLine(context, 20, 40, "DnD Testing", new AttributedStringOptions { Font = font, ForegroundColor = orange }, withGradient:false);
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
        } else if (_lastDroppedFiles != null)
        {
            var items =
                new[] { "you dropped:" }
                    .Concat(_lastDroppedFiles.Select(fname => $" - {fname}"));
            var joined = string.Join("\n", items);
            using var attrString = AttributedString.Create(joined, new AttributedStringOptions { Font = font, ForegroundColor = lightBlue });
            using var frameSetter = FrameSetter.CreateWithAttributedString(attrString);
            using var path = Drawing.Path.CreateWithRect(totalRect.Inset(60), new OptArgs());
            using var frame = frameSetter.CreateFrame(RangeZero, path);
            frame.Draw(context);
        }
    }

    public override DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested)
    {
        _dropInProgress = true;
        _suggestedEffect = suggested;
        // timer is animating / invalidating
        // Invalidate();
        
        if (data.HasFormat(KDragFormatFiles) || data.HasFormat(KDragFormatUTF8))
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
        if (data.HasFormat(KDragFormatFiles))
        {
            _lastDroppedFiles = data.GetFiles();
            foreach (var filename in data.GetFiles())
            {
                Console.WriteLine($"file {filename} dropped!");
            }
        } else if (data.HasFormat(KDragFormatUTF8))
        {
            var text = data.GetTextUTF8();
            Console.WriteLine($"got text drop: [{text}]");
        }
        _dropInProgress = false;
        _dropAllowed = false;
        // timer no longer invalidating:
        Invalidate();
    }

    public override void DragRender(DragRenderPayload payload, string requestedFormat)
    {
        if (requestedFormat == KDragFormatUTF8)
        {
            payload.RenderUTF8("Hello from the Window Event Page!! This text will be rendered when dragging or copying to clipboard.");
        }
        else
        {
            Console.WriteLine($"DragRender: we failed to render [{requestedFormat}] !");
        }
    }

    public override void OnTimer(double secondsSinceLast)
    {
        // 1 complete cycle per second?
        _animPhase = (_animPhase + (secondsSinceLast * 8.0)) % 8.0;
        Invalidate();
    }
}
