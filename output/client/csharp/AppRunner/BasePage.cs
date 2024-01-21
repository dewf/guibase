using Org.Prefixed.GuiBase;

namespace AppRunner;

public interface IWindowMethods
{
    void Invalidate(int x, int y, int width, int height);
}

public interface IPage
{
    void Init();
    void Render(Drawing.DrawContext context, int x, int y, int width, int height);
    void Render2(Drawing.DrawContext context, int x, int y, int width, int height);
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

    public virtual void Render(Drawing.DrawContext context, int x, int y, int width, int height)
    {
    }

    public virtual void Render2(Drawing.DrawContext context, int x, int y, int width, int height)
    {
        Render(context, x, y, width, height);
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
