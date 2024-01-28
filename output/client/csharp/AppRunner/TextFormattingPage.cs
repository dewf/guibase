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
    public Dictionary<string, CustomRunAttribute> GetMap(Dictionary<string, long> idMap)
    {
		return idMap
			.Select(pair => new KeyValuePair<string, CustomRunAttribute>(pair.Key, _customRunAttributes[pair.Value]))
			.ToDictionary();
    }
}

public class TextFormattingPage : BasePage
{
	private const string Text =
		"This paragraph of text rendered with DirectWrite is based on IDWriteTextFormat and IDWriteTextLayout " +
		"objects and uses a custom format specifier passed to the SetDrawingEffect method, and thus is " +
		"capable of different RBG RGB foreground colors, such as red, green, and blue as well as double " +
		"underline, triple underline, single strikethrough, double strikethrough, triple strikethrough, or combinations thereof. " +
		"Also possible is something often referred to as an overline, as well as a squiggly (squiggly?) underline.";
	
    // custom run attributes:
    private const string BackgroundKey = "kDLBackgroundAttributeName"; // color
    private const string HighlightKey = "kDLHighlightAttributeName"; // color
    private const string StrikeCountKey = "kDLStrikeCountAttributeName"; // int
    private const string StrikeColorKey = "kDLStrikeColorAttributeName"; // color
    private const string UnderlineStyleKey = "kDLUnderlineStyleAttributeName"; // enum
    private const string UnderlineColorKey = "kDLUnderlineColorAttributeName"; // color

    private static readonly string[] AllCustomAttributes = [BackgroundKey, HighlightKey, StrikeCountKey, StrikeColorKey, UnderlineStyleKey, UnderlineColorKey];

    private readonly ClientAttrMap _attrManager = new();
    private readonly FrameSetter _frameSetter;
    private readonly Color _black = Color.GetConstantColor(ColorConstants.Black);

    public TextFormattingPage(IWindowMethods windowMethods) : base(windowMethods)
    {
	    using var timesFont = Font.CreateWithName("Times New Roman", 40.0, new OptArgs());
	    using var timesItalic = timesFont.CreateCopyWithSymbolicTraits(0, new FontTraits { Italic = true }, new OptArgs()); // 0 = preserve size
	    
	    // can't use "use" with these now, they will be released if the other side doesn't retain them
	    // I understand why the local-only ones aren't being retained, but what about those passed directly
	    // into the remote attribute dictionary? my own dictionary-splitting run analysis implementation is failing to retain them?
	    // could be ...
	    // don't tell me we need .retain on opaques, as well - sigh
	    var magenta = Color.CreateGenericRGB(1, 0, 1, 1);
	    var alphaYellow = Color.CreateGenericRGB(1, 1, 0, 0.5);
	    var red = Color.CreateGenericRGB(1, 0, 0, 1);
	    var green = Color.CreateGenericRGB(0, 1, 0, 1);
	    var blue = Color.CreateGenericRGB(0, 0, 1, 1);
	    var yellow = Color.CreateGenericRGB(1, 1, 0, 1);
        
	    using var attrString = MutableAttributedString.Create(0); // 0 = amt of storage to reserve, no hint
	    attrString.ReplaceString(RangeZero, Text); // was: MakeRange(0, 0), not sure if that's the same, should be

	    var strLen = attrString.GetLength();
	    var fullRange = MakeRange(0, strLen);
        
	    // begin batch editing
	    attrString.BeginEditing();
	    
        // this was two different lines originally
        attrString.SetAttribute(fullRange, new AttributedStringOptions { ForegroundColor = _black, Font = timesFont });

        Drawing.Range range;

        range = StringFind(Text, "IDWriteTextFormat");
        attrString.SetAttribute(range, new AttributedStringOptions { Font = timesItalic });

        range = StringFind(Text, "IDWriteTextLayout");
        attrString.SetAttribute(range, new AttributedStringOptions { Font = timesItalic });

        range = StringFind(Text, "IDWriteTextFormat and IDWriteTextLayout objects");
        attrString.SetCustomAttribute(range, BackgroundKey, _attrManager.Insert(new ColorAttribute(magenta)));

        range = StringFind(Text, "the SetDrawingEffect method");
        attrString.SetCustomAttribute(range, HighlightKey, _attrManager.Insert(new ColorAttribute(alphaYellow)));

        range = StringFind(Text, "SetDrawingEffect");
        attrString.SetAttribute(range, new AttributedStringOptions { Font = timesItalic });
        
        // RBG strikethrough
        range = StringFind(Text, "RBG");
        attrString.SetAttribute(MakeRange(range.Location, 1), new AttributedStringOptions { ForegroundColor = red });
        attrString.SetAttribute(MakeRange(range.Location + 1, 1), new AttributedStringOptions { ForegroundColor = blue });
        attrString.SetAttribute(MakeRange(range.Location + 2, 1), new AttributedStringOptions { ForegroundColor = green });
        // strike count:
        attrString.SetCustomAttribute(range, StrikeCountKey, _attrManager.Insert(new IntAttribute(1)));
        
        // RGB
        range = StringFind(Text, "RGB");
        attrString.SetAttribute(MakeRange(range.Location, 1), new AttributedStringOptions { ForegroundColor = red });
        attrString.SetAttribute(MakeRange(range.Location + 1, 1), new AttributedStringOptions { ForegroundColor = green });
        attrString.SetAttribute(MakeRange(range.Location + 2, 1), new AttributedStringOptions { ForegroundColor = blue });
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Single)));
        attrString.SetCustomAttribute(range, UnderlineColorKey, _attrManager.Insert(new ColorAttribute(yellow)));
        
        range = StringFind(Text, " red");
        attrString.SetAttribute(range, new AttributedStringOptions { ForegroundColor = red });
        range = StringFind(Text, "green");
        attrString.SetAttribute(range, new AttributedStringOptions { ForegroundColor = green });
        range = StringFind(Text, "blue");
        attrString.SetAttribute(range, new AttributedStringOptions { ForegroundColor = blue });
        
        range = StringFind(Text, "double underline");
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Double)));
        
        range = StringFind(Text, "triple underline");
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Triple)));
        
        range = StringFind(Text, "single strikethrough");
        attrString.SetCustomAttribute(range, StrikeCountKey, _attrManager.Insert(new IntAttribute(1)));
        
        range = StringFind(Text, "double strikethrough");
        attrString.SetCustomAttribute(range, StrikeCountKey, _attrManager.Insert(new IntAttribute(2)));
        
        range = StringFind(Text, "triple strikethrough");
        attrString.SetCustomAttribute(range, StrikeCountKey, _attrManager.Insert(new IntAttribute(3)));
        
        range = StringFind(Text, "combinations");
        attrString.SetCustomAttribute(range, StrikeCountKey, _attrManager.Insert(new IntAttribute(2)));
        attrString.SetCustomAttribute(range, StrikeColorKey, _attrManager.Insert(new ColorAttribute(red)));
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Triple)));
        
        range = StringFind(Text, "thereof");
        attrString.SetCustomAttribute(range, StrikeCountKey, _attrManager.Insert(new IntAttribute(3)));
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Double)));
        attrString.SetCustomAttribute(range, UnderlineColorKey, _attrManager.Insert(new ColorAttribute(blue)));
        
        range = StringFind(Text, "overline");
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Overline)));
        attrString.SetCustomAttribute(range, UnderlineColorKey, _attrManager.Insert(new ColorAttribute(blue)));
        
        range = StringFind(Text, "squiggly (squiggly?) underline");
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Squiggly)));
        attrString.SetCustomAttribute(range, UnderlineColorKey, _attrManager.Insert(new ColorAttribute(blue)));
        
        range = StringFind(Text, "(squiggly?)");
        attrString.SetCustomAttribute(range, UnderlineColorKey, _attrManager.Insert(new ColorAttribute(red)));
        
        range = StringFind(Text, "IDWriteTextLayout");
        attrString.SetCustomAttribute(range, UnderlineStyleKey, _attrManager.Insert(new UnderlineStyleAttribute(UnderlineStyle.Squiggly)));
        attrString.SetCustomAttribute(range, UnderlineColorKey, _attrManager.Insert(new ColorAttribute(blue)));
        attrString.SetCustomAttribute(range, HighlightKey, _attrManager.Insert(new ColorAttribute(alphaYellow)));
        
        // end batch editing
        attrString.EndEditing();
        
        // framesetter
        _frameSetter = FrameSetter.CreateWithAttributedString(attrString.GetNormalAttributedString_REMOVEME()); // we need opaque inheritance!
    }
    
    public override void Render(DrawContext context, RenderArea area)
    {
	    var drawList = new DrawList(context);
	    
	    drawList.SetRGBFillColor(100 / 255.0, 149 / 255.0, 237 / 255.0, 1);
	    drawList.FillRect(MakeRect(0, 0, Width, Height));

	    drawList.SetTextMatrix(AffineTransformIdentity);

        // RECT ===========================
        var rect = MakeRect(0, 0, Width, Height);
        using var rectPath = Drawing.Path.CreateWithRect(rect, new OptArgs());
        using var frame = _frameSetter.CreateFrame(RangeZero, rectPath); // don't know what the final argument NULL could be (not implemented yet)
        
        // draw background color, underlines
        DrawFrameEffects(drawList, frame, rect, EffectLayer.Background, _black, _attrManager);
        
        // draw text + built-in CT effects
        drawList.DrawFrame(frame);
        // frame.Draw(context);
        
        // draw strikethroughs, highlights
        DrawFrameEffects(drawList, frame, rect, EffectLayer.Overlay, _black, _attrManager);
        
        drawList.Send();
    }

    private enum EffectLayer
    {
	    Background,
	    Overlay
    }

    private static void DrawFrameEffects(DrawList context, Frame frame, Rect rect, EffectLayer layer, Color defaultColor, ClientAttrMap attrMap)
    {
	    // really should just combine these into a single call, since origins requires checking the lines array internally
	    var lines = frame.GetLines();
	    var origins = frame.GetLineOrigins(RangeZero);

	    foreach (var (line, origin) in lines.Zip(origins, Tuple.Create))
	    {
		    // illustrate origins =================
		    context.SetRGBFillColor(1, 0, 0, 1);
		    context.FillRect(MakeRect(origin.X - 2, origin.Y - 2, 4, 4));
		    // end=================================

		    var lineTypoBounds = line.GetTypographicBounds();
		    
		    foreach (var run in line.GetGlyphRuns())
		    {
			    // TODO: add a custom map to the AttributedStringOptions?
			    // wish there was a way to maintain a server-side list of all custom keys, so we don't have to pass the AllCustomAttributes array every time
			    
			    var attrs = run.GetAttributes(AllCustomAttributes);
			    attrs.HasForegroundColor(out var fgColor);
			    attrs.HasFont(out var font);
			    attrs.HasCustom(out var customRaw);

			    var customMap = attrMap.GetMap(customRaw!); // guaranteed to exist (even if empty) because we provided a non-zero array to .GetAttributes
			    customMap.TryGetValue(BackgroundKey, out var bgColor);
			    customMap.TryGetValue(HighlightKey, out var highColor);
			    customMap.TryGetValue(StrikeCountKey, out var strikeCount);
			    customMap.TryGetValue(StrikeColorKey, out var strikeColor);
			    customMap.TryGetValue(UnderlineStyleKey, out var underStyle);
			    customMap.TryGetValue(UnderlineColorKey, out var underColor);

			    var runTypoBounds = run.GetTypographicBounds(RangeZero);
			    var runBounds = RectZero;
			    
			    // might want to pad these with user-definable pads?
			    runBounds.Size.Width = runTypoBounds.Width;
			    runBounds.Size.Height = runTypoBounds.Ascent + runTypoBounds.Descent;

			    var xOffset = 0.0;
			    var glyphRange = run.GetStringRange();
			    var status = run.GetStatus();
			    if (status.HasFlag(RunStatus.RightToLeft))
			    {
				    var (offs1, _) = line.GetLineOffsetForStringIndex(glyphRange.Location + glyphRange.Length);
				    xOffset = offs1;
			    }
			    else
			    {
				    var (offs1, _) = line.GetLineOffsetForStringIndex(glyphRange.Location);
				    xOffset = offs1;
			    }

			    runBounds.Origin.X = origin.X + xOffset;
			    runBounds.Origin.Y = origin.Y;
			    runBounds.Origin.Y -= runTypoBounds.Ascent;

			    if (runBounds.Size.Width > lineTypoBounds.Width)
			    {
				    runBounds.Size.Width = lineTypoBounds.Width;
			    }
			    
			    if (layer == EffectLayer.Background)
			    {
				    if (bgColor != null)
				    {
					    context.SetFillColorWithColor(bgColor.GetColor());
					    context.FillRect(runBounds);
				    }
				    if (underStyle != null)
				    {
					    var ulStyle = underStyle.GetUnderlineStyle();
					    var ulColor = 
						    underColor != null
						    ? underColor.GetColor() 
						    : fgColor ?? defaultColor;
					    context.SetStrokeColorWithColor(ulColor);

					    var thickness = font.GetUnderlineThickness();
					    context.SetLineWidth(thickness);

					    var y = origin.Y + font.GetUnderlinePosition();

					    if (ulStyle is >= UnderlineStyle.Single and <= UnderlineStyle.Triple)
					    {
						    context.MoveToPoint(runBounds.Origin.X, y);
						    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y);
						    context.StrokePath();
						    if (ulStyle >= UnderlineStyle.Double)
						    {
							    y += thickness * 2;
							    context.MoveToPoint(runBounds.Origin.X, y);
							    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y);
							    context.StrokePath();
							    if (ulStyle >= UnderlineStyle.Triple)
							    {
								    y += thickness * 2;
								    context.MoveToPoint(runBounds.Origin.X, y);
								    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y);
								    context.StrokePath();
							    }
						    }
					    } else if (ulStyle == UnderlineStyle.Overline)
					    {
						    y -= runTypoBounds.Ascent - thickness; // thickness hopefully being proportional to font size ...
						    context.MoveToPoint(runBounds.Origin.X, y);
						    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y);
						    context.StrokePath();
					    } else if (ulStyle == UnderlineStyle.Squiggly)
					    {
						    var amplitude = thickness;
						    var period = 5 * thickness;

						    for (var t = 0; t < runBounds.Size.Width; t++)
						    {
							    var px = runBounds.Origin.X + t;
							    var angle = Math.PI * 2 * (px % period) / period; // fmod
							    var py = y + Math.Sin(angle) * amplitude;
							    if (t == 0)
							    {
								    context.MoveToPoint(px, py);
							    }
							    else
							    {
								    context.AddLineToPoint(px, py);
							    }
						    }
						    context.StrokePath();
					    }
				    }
			    } else if (layer == EffectLayer.Overlay)
			    {
				    if (strikeCount != null)
				    {
					    var theCount = strikeCount.GetInt();
					    var useColor = strikeColor != null ? strikeColor.GetColor() : (fgColor ?? defaultColor);
					    context.SetStrokeColorWithColor(useColor);

					    var thickness = font.GetUnderlineThickness();
					    context.SetLineWidth(thickness);

					    var y = origin.Y - (runTypoBounds.Ascent / 4.0);
					    if (theCount is 1 or 3)
					    {
						    context.MoveToPoint(runBounds.Origin.X, y);
						    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y);
						    context.StrokePath();
					    }
					    if (theCount is 2 or 3)
					    {
						    var y2 = y - (thickness * (theCount - 1));
						    context.MoveToPoint(runBounds.Origin.X, y2);
						    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y2);
						    context.StrokePath();
						    y2 = y + (thickness * (theCount - 1));
						    context.MoveToPoint(runBounds.Origin.X, y2);
						    context.AddLineToPoint(runBounds.Origin.X + runBounds.Size.Width, y2);
						    context.StrokePath();
					    }
				    }
				    if (highColor != null)
				    {
					    context.SetFillColorWithColor(highColor.GetColor());
					    context.FillRect(runBounds);
				    }
			    }
		    }
	    }
    }
}
