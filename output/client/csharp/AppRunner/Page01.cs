using Org.Prefixed.GuiBase;

using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Foundation;

namespace AppRunner;

public class Page01(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    public override void Init()
    {
        // test create some fonts and layouts and stuff
        var path = MakeConstantString("./_democontent/LiberationSerif-Regular.ttf");
        var url = CreateWithFileSystemPath(path, URLPathStyle.POSIX, false);
        var descriptors = FontManagerCreateFontDescriptorsFromURL(url);
        var items = descriptors.Items();
        if (items.Length > 0)
        {
            var font = FontCreateWithFontDescriptor(items[0], 120.0, AffineTransformIdentity);
            Console.WriteLine("we got the font??");
        }
        // release: array, url, path
    }

    public override void Render(Drawing.DrawContext context, int x, int y, int width, int height)
    {
        context.SaveGState();
        
        // bordered
        context.SetRGBFillColor(0.23, 0, 0.4, 1);
        context.FillRect(new Rect(new Point(10, 10), new Size(Width - 20, Height - 20)));

        // overlapping
        var rect = new Rect(new Point(100, 100), new Size(100, 100));
        context.SetRGBFillColor(1, 0, 0, 0.5);
        context.FillRect(rect);

        rect.Origin.X += 20;
        rect.Origin.Y += 20;
        context.SetRGBFillColor(0, 1, 0, 0.5);
        context.FillRect(rect);
        
        rect.Origin.X += 20;
        rect.Origin.Y += 20;
        context.SetRGBFillColor(0, 0, 1, 0.5);
        context.FillRect(rect);

        context.RestoreGState();
    }
}
