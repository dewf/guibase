using Org.Prefixed.GuiBase;

using static Org.Prefixed.GuiBase.Drawing;
using static Org.Prefixed.GuiBase.Foundation;

namespace AppRunner;

public class Page01(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    //private Font? _serif;
    private AttributedString? _labelString;
    public override void Init()
    {
        // test create some fonts and layouts and stuff
        using var path = MakeConstantString("./_democontent/LiberationSerif-Regular.ttf");
        using var url = CreateWithFileSystemPath(path, URLPathStyle.POSIX, false);
        using var descriptors = FontManagerCreateFontDescriptorsFromURL(url);
        var items = descriptors.Items(); // what's returned by this method is not owned, so no disposal
        if (items.Length > 0)
        {
            var font = FontCreateWithFontDescriptor(items[0], 120.0, AffineTransformIdentity);
            Console.WriteLine("we got the font??");
            _labelString = CreateAttributedString("Quartz♪❦♛あぎ", new AttributedStringOptions
            {
                Font = font,
                ForegroundColor = CreateColor(0, 1, 1, 0.5)
            });
        }
        // release: array, url, path
    }

    public override void Render(DrawContext context, int x, int y, int width, int height)
    {
        context.SetRGBFillColor(0.2, 0.2, 0.3, 1);
        context.FillRect(MakeRect(0, 0, width, height));
        context.SetTextMatrix(AffineTransformIdentity);

        using var line = CreateLineWithAttributedString(_labelString);
        context.SetTextPosition(100, 300);
        line.Draw(context);

        // var text = MakeConstantString("Quartz♪❦♛あぎ");
        //
        // auto dict = dl_CFDictionaryCreateMutable(0);
        // dl_CFDictionarySetValue(dict, dl_kCTFontAttributeName, serif);
        // auto fgColor = dl_CGColorCreateGenericRGB(0, 1, 1, 0.5);
        // dl_CFDictionarySetValue(dict, dl_kCTForegroundColorAttributeName, fgColor);
        // auto labelString = dl_CFAttributedStringCreate(text, dict);

        // woot
        // context.SaveGState();
        //
        // // bordered
        // context.SetRGBFillColor(0.23, 0, 0.4, 1);
        // context.FillRect(new Rect(new Point(10, 10), new Size(Width - 20, Height - 20)));
        //
        // // overlapping
        // var rect = new Rect(new Point(100, 100), new Size(100, 100));
        // context.SetRGBFillColor(1, 0, 0, 0.5);
        // context.FillRect(rect);
        //
        // rect.Origin.X += 20;
        // rect.Origin.Y += 20;
        // context.SetRGBFillColor(0, 1, 0, 0.5);
        // context.FillRect(rect);
        //
        // rect.Origin.X += 20;
        // rect.Origin.Y += 20;
        // context.SetRGBFillColor(0, 0, 1, 0.5);
        // context.FillRect(rect);
        //
        // context.RestoreGState();
    }
}
