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
    private readonly Rect _dragSourceRect = MakeRect(100, 100, 200, 200);
    private readonly Rect _mouseGrabRect = MakeRect(400, 100, 200, 200);
    private bool _mouseDownPotentialDrag;
    private bool _grabDragging;
    private readonly Menu _contextMenu;
    
    public override string PageTitle => "Windowing/Event testing";
    public override bool CanDrop => true;
    public override bool IsAnimating => _dropInProgress;

    private readonly MenuBar _nativeMenuBar;
    public override MenuBar? MenuBar => _nativeMenuBar;

    private static Menu CreateContextMenu(IWindowMethods windowMethods)
    {
        var menu = Menu.Create();
        
        // these could have accelerators if the actions were installed in the menubar (for our win32 implementation, that's how keyboard accelerators are installed)
        
        var action1 = MenuAction.Create("Show MessageBox #1", null, null, () =>
        {
            var result = MessageBoxModal.Show(windowMethods.GetWindowHandle(), new MessageBoxParams
            {
                Buttons = MessageBoxButtons.AbortRetryIgnore,
                Icon = MessageBoxIcon.Error,
                Message = "Hello from MessageBox!",
                Title = "This is the MB Title",
                WithHelpButton = false
            });
            Console.WriteLine($"MessageBox result: {result}");
        });
        menu.AddAction(action1);

        var action2 = MenuAction.Create("Some Action 2", null, null, () => Console.WriteLine("You clicked Action2"));
        menu.AddAction(action2);
        
        return menu;
    }

    public WindowEventPage(IWindowMethods windowMethods) : base(windowMethods)
    {
        _windowMethods = windowMethods;
        
        _nativeMenuBar = CreateMenuBar(windowMethods);
        _contextMenu = CreateContextMenu(windowMethods);
    }

    public override void OnMouseMove(int x, int y, Modifiers modifiers)
    {
        if (_mouseDownPotentialDrag)
        {
            // begin DnD drag
            using var dragData = DragData.Create([KDragFormatUTF8], (format, payload) =>
            {
                if (format == KDragFormatUTF8)
                {
                    payload.RenderUTF8("hello from DnD source!!! UTF8 in the house");
                    return true;
                }
                return false;
            });
            var dropEffect = dragData.DragExec(DropEffect.Copy);
            Console.WriteLine($"DnD Drop effect: {dropEffect} (source format: {KDragFormatUTF8})");
            // cancel the potential, otherwise they will keep happening!
            _mouseDownPotentialDrag = false;
        } else if (_grabDragging)
        {
            Console.WriteLine($"Grab drag movement: {x}/{y}");
        }
    }

    public override void OnMouseDown(int x, int y, MouseButton button, Modifiers modifiers)
    {
        if (button == MouseButton.Left)
        {
            _mouseDownPotentialDrag = _dragSourceRect.ContainsPoint(new Point(x, y));

            if (_mouseGrabRect.ContainsPoint(new Point(x, y)))
            {
                _grabDragging = true;
                GrabMouse();
                SetCursor(CursorStyle.Move);
            }
        } else if (button == MouseButton.Right)
        {
            _windowMethods.ShowContextMenu(x, y, _contextMenu);
        }
    }

    public override void OnMouseUp(int x, int y, MouseButton button, Modifiers modifiers)
    {
        _mouseDownPotentialDrag = false;
        if (_grabDragging)
        {
            Console.WriteLine("grabbed mouse released!");
            _grabDragging = false;
            UngrabMouse();
            SetCursor(CursorStyle.Default);
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
        
        // drag rect
        context.SetStrokeColorWithColor(orange);
        context.SetLineWidth(2);
        context.StrokeRect(_dragSourceRect);
        CenterText(context, _dragSourceRect, "Drag Source", new AttributedStringOptions { Font = smallFont, ForegroundColor = orange });
        
        // grab rect
        context.SetStrokeColorWithColor(orange);
        context.SetLineWidth(2);
        context.StrokeRect(_mouseGrabRect);
        CenterText(context, _mouseGrabRect, "Mouse Grab", new AttributedStringOptions { Font = smallFont, ForegroundColor = orange });
        
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

    public override void OnTimer(double secondsSinceLast)
    {
        // 1 complete cycle per second?
        _animPhase = (_animPhase + (secondsSinceLast * 8.0)) % 8.0;
        Invalidate();
    }
    
    private static MenuBar CreateMenuBar(IWindowMethods windowMethods)
    {
        // no 'using' since we're returning it
        var menuBar = MenuBar.Create();
        
        // file menu
        using var fileMenu = Menu.Create();
        
        // open
        using var openAccel = Accelerator.Create(Key.O, Modifiers.Control);
        using var openAction = MenuAction.Create("&Open", null, openAccel, () =>
        {
            var result = FileDialog.OpenFile(new FileDialogOptions {
                ForWindow = windowMethods.GetWindowHandle(),
                Filters = [
                    new FileDialogFilterSpec("Text Files (*.txt, *.doc)", ["txt", "doc"])
                ],
                Mode = FileDialogMode.File,
                AllowAll = true,
                AllowMultiple = false,
                DefaultExt = "txt",
                SuggestedFilename = "none"
            });
            Console.WriteLine(result.Success ? $"success: opened file [{result.Filenames[0]}]" : "Canceled");
        });
        fileMenu.AddAction(openAction);
        
        // save
        using var saveAccel = Accelerator.Create(Key.S, Modifiers.Control);
        using var saveAction = MenuAction.Create("&Save", null, saveAccel, () =>
        {
            var result = FileDialog.SaveFile(new FileDialogOptions
            {
                ForWindow = windowMethods.GetWindowHandle(),
                Filters =
                [
                    new FileDialogFilterSpec("Text Files (*.txt, *.doc)", ["txt", "doc"])
                ],
                Mode = FileDialogMode.File,
                AllowAll = true,
                AllowMultiple = false,
                DefaultExt = "txt",
                SuggestedFilename = "TestDocument.txt"
            });
            Console.WriteLine(result.Success ? $"success: saved file [{result.Filenames[0]}]" : "Canceled");
        });
        fileMenu.AddAction(saveAction);
        
        // separator
        fileMenu.AddSeparator();
        
        // exit
        using var exitAccel = Accelerator.Create(Key.Q, Modifiers.Control);
        using var exitAction = MenuAction.Create("E&xit", null, exitAccel, () =>
        {
            Console.WriteLine("Exiting!");
            windowMethods.DestroyWindow();
        });
        fileMenu.AddAction(exitAction);
        
        // edit menu
        using var editMenu = Menu.Create();
        // copy
        using var copyAccel = Accelerator.Create(Key.C, Modifiers.Control);
        using var copyAction = MenuAction.Create("&Copy", null, copyAccel, () =>
        {
            using var dragData = DragData.Create([KDragFormatUTF8], (format, payload) =>
            {
                Console.WriteLine("#### WE ARE ACTIVELY RENDERING ######");
                if (format == KDragFormatUTF8)
                {
                    payload.RenderUTF8("HELLO FROM CLIPBOARD COPY!!!!");
                    return true;
                }
                return false;
            });
            ClipData.SetClipboard(dragData);
            // dragData will be released, but I think it's OK because behind the scenes it's using COM reference counting for the actual (deferred) delegate stuff
        });
        editMenu.AddAction(copyAction);
        // paste
        using var pasteAccel = Accelerator.Create(Key.V, Modifiers.Control);
        using var pasteAction = MenuAction.Create("&Paste", null, pasteAccel, () =>
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
}
