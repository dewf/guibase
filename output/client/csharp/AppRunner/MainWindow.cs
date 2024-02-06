using static Org.Prefixed.GuiBase.Windowing;
using static Org.Prefixed.GuiBase.Drawing;
using System.Diagnostics;
using AppRunner.Pages;

namespace AppRunner;

internal class MainWindow : BaseWindowDelegate, IWindowMethods
{
    private int _width = Constants.InitWidth; 
    private int _height = Constants.InitHeight;

    private Window? _window;
    private readonly SpinningFlower _page01;
    private readonly TextBoundsCircle _page02;
    private readonly TextStrokeFill _page03;
    private readonly ResizeGradient _page04;
    private readonly TextFormattingPage _page05;
    private readonly GradLabelPage _page06;
    private readonly TextStrokeTestingPage _page07;
    private readonly TextSelectionPage _page08;
    private readonly TransformedShapesPage _page09;
    private readonly WindowEventPage _page10;
    private IPage _currentPage;

    private readonly Stopwatch _watch = new();

    public bool IsDestroyed { get; private set; }

    private MainWindow()
    {
        // page init
        _page01 = new SpinningFlower(this);
        _page02 = new TextBoundsCircle(this);
        _page03 = new TextStrokeFill(this);
        _page04 = new ResizeGradient(this);
        _page05 = new TextFormattingPage(this);
        _page06 = new GradLabelPage(this);
        _page07 = new TextStrokeTestingPage(this);
        _page08 = new TextSelectionPage(this);
        _page09 = new TransformedShapesPage(this);
        _page10 = new WindowEventPage(this);
        _currentPage = _page01;
    }
    
    public static MainWindow Create()
    {
        var options = new WindowOptions
        {
            MinWidth = Constants.MinWidth,
            MinHeight = Constants.MinHeight,
            MaxWidth = Constants.MaxWidth,
            MaxHeight = Constants.MaxHeight
        };
        var ret = new MainWindow();
        ret._window = Window.Create(Constants.InitWidth, Constants.InitHeight, "this is the first window! 🚀", ret, options);
        ret._window.SetTitle(ret._currentPage.PageTitle);
        ret._window.EnableDrops(ret._currentPage.CanDrop);
        return ret;
    }

    public Window GetWindowHandle()
    {
        if (_window != null)
        {
            return _window;
        }
        throw new Exception("MainWindowDelegate: GetWindowHandle() can't be called yet!");
    }

    public override bool CanClose() => true;

    public override void Closed()
    {
        Console.WriteLine("window closed!!");
    }

    public override void Destroyed()
    {
        IsDestroyed = true;
        Console.WriteLine("window destroyed! exiting runloop");
        ExitRunloop();
    }

    public override void MouseDown(int x, int y, MouseButton button, Modifiers modifiers)
    {
        _currentPage.OnMouseDown(x, y, button, modifiers);
    }

    public override void MouseUp(int x, int y, MouseButton button, Modifiers modifiers)
    {
        _currentPage.OnMouseUp(x, y, button, modifiers);
    }

    public override void MouseMove(int x, int y, Modifiers modifiers)
    {
        _currentPage.OnMouseMove(x, y, modifiers);
    }

    public override void MouseLeave(Modifiers modifiers)
    {
        _currentPage.OnMouseLeave(modifiers);
    }

    public override void MouseEnter(int x, int y, Modifiers modifiers)
    {
        _currentPage.OnMouseEnter(x, y, modifiers);
    }
    
    private void SelectPage(IPage page)
    {
        _currentPage = page;
        _currentPage.OnSize(_width, _height);
        _window!.SetTitle(_currentPage.PageTitle);
        _window!.EnableDrops(_currentPage.CanDrop);
        _window!.SetMenuBar(_currentPage.MenuBar); // might be null, that's OK
        Invalidate(0, 0, _width, _height);
    }

    public override void KeyDown(Key key, Modifiers modifiers, KeyLocation location)
    {
        switch (key)
        {
            case Key._1:
                SelectPage(_page01);
                break;
            case Key._2:
                SelectPage(_page02);
                break;
            case Key._3:
                SelectPage(_page03);
                break;
            case Key._4:
                SelectPage(_page04);
                break;
            case Key._5:
                SelectPage(_page05);
                break;
            case Key._6:
                SelectPage(_page06);
                break;
            case Key._7:
                SelectPage(_page07);
                break;
            case Key._8:
                SelectPage(_page08);
                break;
            case Key._9:
                SelectPage(_page09);
                break;
            case Key._0:
                SelectPage(_page10);
                break;
            default:
                _currentPage.OnKeyDown(key, modifiers);
                break;
        }
    }

    public override void Repaint(DrawContext context, int x, int y, int width, int height)
    {
        // _watch.Restart();
        
        // don't think we need to save/restore state, created afresh every time?
        // will have to see how macOS behaves ...
        context.SaveGState();
        _currentPage.Render(context, new RenderArea(x, y, width, height));
        context.RestoreGState();
        
        // _watch.Stop();
        // Console.WriteLine($"rendering time: {_watch.ElapsedMilliseconds}ms");
    }

    public override void Moved(int x, int y)
    {
        _currentPage.OnHostWindowMoved();
    }
    
    public override void Resized(int width, int height)
    {
        _width = width;
        _height = height;
        _currentPage.OnSize(_width, _height);
    }

    public override DropEffect DropFeedback(DropData data, int x, int y, Modifiers modifiers, DropEffect suggested)
    {
        return _currentPage.CanDrop ? _currentPage.DropFeedback(data, x, y, modifiers, suggested) : DropEffect.None;
    }

    public override void DropLeave()
    {
        if (_currentPage.CanDrop) _currentPage.DropLeave();
    }

    public override void DropSubmit(DropData data, int x, int y, Modifiers modifiers, DropEffect effect)
    {
        if (_currentPage.CanDrop) _currentPage.DropSubmit(data, x, y, modifiers, effect);
    }

    public void Invalidate(int x, int y, int width, int height)
    {
        _window!.Invalidate(x, y, width, height);
    }

    public void ShowContextMenu(int x, int y, Menu menu)
    {
        _window!.ShowContextMenu(x, y, menu);
    }

    public void TimerTick(double secondsSinceLast)
    {
        if (_currentPage.IsAnimating)
        {
            _currentPage.OnTimer(secondsSinceLast);
        }
    }
    
    public void DestroyWindow()
    {
        _window!.Destroy();
    }

    public void Show()
    {
        _window!.Show();
    }
}
