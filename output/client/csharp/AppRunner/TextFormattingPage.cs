using Org.Prefixed.GuiBase;
using static AppRunner.Common;
using static Org.Prefixed.GuiBase.Drawing;

namespace AppRunner;

internal class ClientAttrMap
{
    private readonly Dictionary<long, CustomRunAttribute> _customRunAttributes = new();
    // no de-duplication at present, this is really just meant to be used per render, so the IDs will never reach that high
    private long _nextAttributeId = 1;
    public long Insert(CustomRunAttribute attr)
    {
        var id = _nextAttributeId++;
        _customRunAttributes.Add(id, attr);
        return id;
    }
    public CustomRunAttribute AttrFor(long id)
    {
        return _customRunAttributes[id];
    }
}

public class TextFormattingPage(IWindowMethods windowMethods) : BasePage(windowMethods)
{
    private const string Text = """
                                This paragraph of text rendered with DirectWrite is based on IDWriteTextFormat and IDWriteTextLayout
                                 objects and uses a custom format specifier passed to the SetDrawingEffect method, and thus is
                                 capable of different RBG RGB foreground colors, such as red, green, and blue as well as double
                                 underline, triple underline, single strikethrough, double strikethrough, triple strikethrough, or combinations thereof.
                                 Also possible is something often referred to as an overline, as well as a squiggly (squiggly?) underline.
                                """;
    // custom run attributes:
    private const string BackgroundKey = "kDLBackgroundAttributeName"; // color
    private const string HighlightKey = "kDLHighlightAttributeName"; // color
    private const string StrikeCountKey = "kDLStrikeCountAttributeName"; // int
    private const string StrikeColorKey = "kDLStrikeColorAttributeName"; // color
    private const string UnderlineKey = "kDLUnderlineStyleAttributeName"; // enum
    private const string UnderlineColor = "kDLUnderlineColorAttributeName"; // color
    
    public override void Render(DrawContext context, RenderArea area)
    {
        context.SetRGBFillColor(100 / 255.0, 149 / 255.0, 237 / 255.0, 1);
        context.FillRect(MakeRect(0, 0, Width, Height));

        context.SetTextMatrix(AffineTransformIdentity);

        using var timesFont = Font.CreateWithName("Times New Roman", 40.0, new OptArgs());
        using var timesItalic = timesFont.CreateCopyWithSymbolicTraits(0, new FontTraits { Italic = true }, new OptArgs()); // 0 = preserve size

        var attrManager = new ClientAttrMap();
        
        // RECT ===========================
        var rect = MakeRect(0, 0, Width, Height);
        using var rectPath = Drawing.Path.CreateWithRect(rect, new OptArgs());

        using var black = Color.CreateGenericRGB(0, 0, 0, 1);
        using var magenta = Color.CreateGenericRGB(1, 0, 1, 1);
        using var alphaYellow = Color.CreateGenericRGB(1, 1, 0, 0.5);
        using var red = Color.CreateGenericRGB(1, 0, 0, 1);
        using var green = Color.CreateGenericRGB(0, 1, 0, 1);
        using var blue = Color.CreateGenericRGB(0, 0, 1, 1);
        using var yellow = Color.CreateGenericRGB(1, 1, 0, 1);
        
        using var attrString = MutableAttributedString.Create(0); // 0 = amt of storage to reserve, no hint
        attrString.ReplaceString(new Drawing.Range.Zero(), Text); // was: MakeRange(0, 0), not sure if that's the same, should be

        var strLen = attrString.GetLength();
        var fullRange = MakeRange(0, strLen);
        
        // begin batch editing
        attrString.BeginEditing();

        // this was two different lines originally
        attrString.SetAttribute(fullRange, new AttributedStringOptions { ForegroundColor = black, Font = timesFont });

        Drawing.Range range;

        range = StringFind(Text, "IDWriteTextFormat");
        attrString.SetAttribute(range, new AttributedStringOptions { Font = timesItalic });
        
        range = StringFind(Text, "IDWriteTextLayout");
        attrString.SetAttribute(range, new AttributedStringOptions { Font = timesItalic });

        range = StringFind(Text, "IDWriteTextFormat and IDWriteTextLayout objects");
        attrString.SetCustomAttribute(range, BackgroundKey, attrManager.Insert(new ColorAttribute(magenta)));

        range = StringFind(Text, "the SetDrawingEffect method");
        attrString.SetCustomAttribute(range, HighlightKey, attrManager.Insert(new ColorAttribute(alphaYellow)));

        range = StringFind(Text, "SetDrawingEffect");
        attrString.SetAttribute(range, new AttributedStringOptions { Font = timesItalic });
        
        // RBG strikethrough
        range = StringFind(Text, "RBG");
        attrString.SetAttribute(MakeRange(range.Location(), 1), new AttributedStringOptions { ForegroundColor = red });
        attrString.SetAttribute(MakeRange(range.Location() + 1, 1), new AttributedStringOptions { ForegroundColor = blue });
        attrString.SetAttribute(MakeRange(range.Location() + 2, 1), new AttributedStringOptions { ForegroundColor = green });
        // strike count:
        attrString.SetCustomAttribute(range, StrikeCountKey, attrManager.Insert(new IntAttribute(1)));
        
        // RGB
        range = StringFind(Text, "RGB");
        attrString.SetAttribute(MakeRange(range.Location(), 1), new AttributedStringOptions { ForegroundColor = red });
        attrString.SetAttribute(MakeRange(range.Location() + 1, 1), new AttributedStringOptions { ForegroundColor = green });
        attrString.SetAttribute(MakeRange(range.Location() + 2, 1), new AttributedStringOptions { ForegroundColor = blue });
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Single)));
        attrString.SetCustomAttribute(range, UnderlineColor, attrManager.Insert(new ColorAttribute(yellow)));
        
        range = StringFind(Text, " red");
        attrString.SetAttribute(range, new AttributedStringOptions { ForegroundColor = red });
        range = StringFind(Text, "green");
        attrString.SetAttribute(range, new AttributedStringOptions { ForegroundColor = green });
        range = StringFind(Text, "blue");
        attrString.SetAttribute(range, new AttributedStringOptions { ForegroundColor = blue });
        
        range = StringFind(Text, "double underline");
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Double)));

        range = StringFind(Text, "triple underline");
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Triple)));
        
        range = StringFind(Text, "single strikethrough");
        attrString.SetCustomAttribute(range, StrikeCountKey, attrManager.Insert(new IntAttribute(1)));

        range = StringFind(Text, "double strikethrough");
        attrString.SetCustomAttribute(range, StrikeCountKey, attrManager.Insert(new IntAttribute(2)));

        range = StringFind(Text, "triple strikethrough");
        attrString.SetCustomAttribute(range, StrikeCountKey, attrManager.Insert(new IntAttribute(3)));
        
        range = StringFind(Text, "combinations");
        attrString.SetCustomAttribute(range, StrikeCountKey, attrManager.Insert(new IntAttribute(2)));
        attrString.SetCustomAttribute(range, StrikeColorKey, attrManager.Insert(new ColorAttribute(red)));
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Triple)));

        range = StringFind(Text, "thereof");
        attrString.SetCustomAttribute(range, StrikeCountKey, attrManager.Insert(new IntAttribute(3)));
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Double)));
        attrString.SetCustomAttribute(range, UnderlineColor, attrManager.Insert(new ColorAttribute(blue)));
        
        range = StringFind(Text, "overline");
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Overline)));
        attrString.SetCustomAttribute(range, UnderlineColor, attrManager.Insert(new ColorAttribute(blue)));

        range = StringFind(Text, "squiggly (squiggly?) underline");
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Squiggly)));
        attrString.SetCustomAttribute(range, UnderlineColor, attrManager.Insert(new ColorAttribute(blue)));

        range = StringFind(Text, "(squiggly?)");
        attrString.SetCustomAttribute(range, UnderlineColor, attrManager.Insert(new ColorAttribute(red)));

        range = StringFind(Text, "IDWriteTextLayout");
        attrString.SetCustomAttribute(range, UnderlineKey, attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Squiggly)));
        attrString.SetCustomAttribute(range, UnderlineColor, attrManager.Insert(new ColorAttribute(blue)));
        attrString.SetCustomAttribute(range, HighlightKey, attrManager.Insert(new ColorAttribute(alphaYellow)));
        
        // end batch editing
        attrString.EndEditing();

        // framesetter
        using var frameSetter = FrameSetter.CreateWithAttributedString(attrString.GetNormalAttributedString_REMOVEME()); // we need opaque inheritance!
        using var frame = frameSetter.CreateFrame(new Drawing.Range.Zero(), rectPath); // don't know what the final argument NULL could be (not implemented yet)

        // draw background color, underlines
        // drawFrameEffects(c, frame, rect, Background, black);

        // draw text + built-in CT effects
        // dl_CTFrameDraw(frame, c);
        frame.Draw(context);

        // draw strikethroughs, highlights
        // drawFrameEffects(c, frame, rect, Overlay, black);
    }
}
