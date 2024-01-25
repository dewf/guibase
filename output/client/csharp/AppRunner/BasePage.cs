using Org.Prefixed.GuiBase;

namespace AppRunner;

public interface IWindowMethods
{
    void Invalidate(int x, int y, int width, int height);
}

public struct RenderArea(int x, int y, int width, int height)
{
    public int X { get; } = x;
    public int Y { get; } = y;
    public int Width { get; } = width;
    public int Height { get; } = height;
}

public interface IPage
{
    void Init();
    void Render(Drawing.DrawContext context, RenderArea area);
    void Render2(Drawing.DrawContext context, RenderArea area);
    bool IsAnimating();
    void OnSize(int newWidth, int newHeight);
    void OnTimer(double secondsSinceLast);
}

public abstract class BasePage(IWindowMethods windowMethods) : IPage
{
    protected int Width, Height;
    
    protected void Invalidate()
    {
        windowMethods.Invalidate(0, 0, 0, 0);
    }

    protected void Invalidate(int x, int y, int width, int height)
    {
        windowMethods.Invalidate(x, y, width, height);
    }

    public virtual void Init()
    {
    }

    public abstract void Render(Drawing.DrawContext context, RenderArea area);

    public virtual void Render2(Drawing.DrawContext context, RenderArea area)
    {
        Render(context, area);
    }

    public virtual bool IsAnimating() => false;

    public virtual void OnSize(int newWidth, int newHeight)
    {
        Width = newWidth;
        Height = newHeight;
    }

    public virtual void OnTimer(double secondsSinceLast)
    {
    }
}
