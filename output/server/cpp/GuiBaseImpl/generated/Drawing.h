#pragma once

#include "../support/NativeImplServer.h"
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>

struct __Color; typedef struct __Color* Color;
struct __ColorSpace; typedef struct __ColorSpace* ColorSpace;
struct __Gradient; typedef struct __Gradient* Gradient;
struct __Path; typedef struct __Path* Path;
struct __DrawContext; typedef struct __DrawContext* DrawContext;
struct __AttributedString; typedef struct __AttributedString* AttributedString;
struct __MutableAttributedString; typedef struct __MutableAttributedString* MutableAttributedString;
struct __Font; typedef struct __Font* Font;
struct __Run; typedef struct __Run* Run;
struct __Line; typedef struct __Line* Line;
struct __Frame; typedef struct __Frame* Frame;
struct __FrameSetter; typedef struct __FrameSetter* FrameSetter;

struct AffineTransform {
    double a;
    double b;
    double c;
    double d;
    double tx;
    double ty;
};

// std::vector<std::string>

// std::vector<int64_t>

// std::map<std::string,int64_t>

struct AttributedStringOptions {
private:
    enum Fields {
        ForegroundColorField = 1,
        ForegroundColorFromContextField = 2,
        FontField = 4,
        StrokeWidthField = 8,
        StrokeColorField = 16,
        CustomField = 32
    };
    int32_t _usedFields = 0;
    Color _foregroundColor;
    bool _foregroundColorFromContext;
    Font _font;
    double _strokeWidth;
    Color _strokeColor;
    std::map<std::string,int64_t> _custom;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void AttributedStringOptions__push(AttributedStringOptions value, bool isReturn);
    friend AttributedStringOptions AttributedStringOptions__pop();
public:
    void setForegroundColor(Color value) {
        _foregroundColor = value;
        _usedFields |= Fields::ForegroundColorField;
    }
    bool hasForegroundColor(Color *value) {
        if (_usedFields & Fields::ForegroundColorField) {
            *value = _foregroundColor;
            return true;
        }
        return false;
    }
    void setForegroundColorFromContext(bool value) {
        _foregroundColorFromContext = value;
        _usedFields |= Fields::ForegroundColorFromContextField;
    }
    bool hasForegroundColorFromContext(bool *value) {
        if (_usedFields & Fields::ForegroundColorFromContextField) {
            *value = _foregroundColorFromContext;
            return true;
        }
        return false;
    }
    void setFont(Font value) {
        _font = value;
        _usedFields |= Fields::FontField;
    }
    bool hasFont(Font *value) {
        if (_usedFields & Fields::FontField) {
            *value = _font;
            return true;
        }
        return false;
    }
    void setStrokeWidth(double value) {
        _strokeWidth = value;
        _usedFields |= Fields::StrokeWidthField;
    }
    bool hasStrokeWidth(double *value) {
        if (_usedFields & Fields::StrokeWidthField) {
            *value = _strokeWidth;
            return true;
        }
        return false;
    }
    void setStrokeColor(Color value) {
        _strokeColor = value;
        _usedFields |= Fields::StrokeColorField;
    }
    bool hasStrokeColor(Color *value) {
        if (_usedFields & Fields::StrokeColorField) {
            *value = _strokeColor;
            return true;
        }
        return false;
    }
    void setCustom(std::map<std::string,int64_t> value) {
        _custom = value;
        _usedFields |= Fields::CustomField;
    }
    bool hasCustom(std::map<std::string,int64_t> *value) {
        if (_usedFields & Fields::CustomField) {
            *value = _custom;
            return true;
        }
        return false;
    }
};


enum class ColorConstants {
    White,
    Black,
    Clear
};


enum class ColorSpaceName {
    GenericGray,
    GenericRGB,
    GenericCMYK,
    GenericRGBLinear,
    AdobeRGB1998,
    SRGB,
    GenericGrayGamma2_2
};


struct Point {
    double x;
    double y;
};

struct Size {
    double width;
    double height;
};

struct Rect {
    Point origin;
    Size size;
};

enum class PathDrawingMode {
    Fill,
    EOFill,
    Stroke,
    FillStroke,
    EOFillStroke
};

// std::vector<double>

enum GradientDrawingOptions {
    DrawsBeforeStartLocation = 1,
    DrawsAfterEndLocation = 2
};

struct DrawCommand {
public:
    enum class Tag {
        saveGState,
        restoreGState,
        setRGBFillColor,
        setRGBStrokeColor,
        setFillColorWithColor,
        fillRect,
        setTextMatrix,
        setTextPosition,
        beginPath,
        addArc,
        addArcToPoint,
        drawPath,
        setStrokeColorWithColor,
        strokeRectWithWidth,
        moveToPoint,
        addLineToPoint,
        strokePath,
        setLineDash,
        clearLineDash,
        setLineWidth,
        clip,
        clipToRect,
        translateCTM,
        scaleCTM,
        rotateCTM,
        concatCTM,
        addPath,
        fillPath,
        strokeRect,
        addRect,
        closePath,
        drawLinearGradient,
        drawFrame
    };
    const Tag tag;
    struct saveGState {
        static DrawCommand make() {
            DrawCommand ret{ Tag::saveGState };
            ret.saveGState = std::shared_ptr<saveGState>(new saveGState{  });
            return ret;
        }
    };
    struct restoreGState {
        static DrawCommand make() {
            DrawCommand ret{ Tag::restoreGState };
            ret.restoreGState = std::shared_ptr<restoreGState>(new restoreGState{  });
            return ret;
        }
    };
    struct setRGBFillColor {
        const double red;
        const double green;
        const double blue;
        const double alpha;
        static DrawCommand make(double red, double green, double blue, double alpha) {
            DrawCommand ret{ Tag::setRGBFillColor };
            ret.setRGBFillColor = std::shared_ptr<setRGBFillColor>(new setRGBFillColor{ red, green, blue, alpha });
            return ret;
        }
    };
    struct setRGBStrokeColor {
        const double red;
        const double green;
        const double blue;
        const double alpha;
        static DrawCommand make(double red, double green, double blue, double alpha) {
            DrawCommand ret{ Tag::setRGBStrokeColor };
            ret.setRGBStrokeColor = std::shared_ptr<setRGBStrokeColor>(new setRGBStrokeColor{ red, green, blue, alpha });
            return ret;
        }
    };
    struct setFillColorWithColor {
        const Color color;
        static DrawCommand make(Color color) {
            DrawCommand ret{ Tag::setFillColorWithColor };
            ret.setFillColorWithColor = std::shared_ptr<setFillColorWithColor>(new setFillColorWithColor{ color });
            return ret;
        }
    };
    struct fillRect {
        const Rect rect;
        static DrawCommand make(Rect rect) {
            DrawCommand ret{ Tag::fillRect };
            ret.fillRect = std::shared_ptr<fillRect>(new fillRect{ rect });
            return ret;
        }
    };
    struct setTextMatrix {
        const AffineTransform t;
        static DrawCommand make(AffineTransform t) {
            DrawCommand ret{ Tag::setTextMatrix };
            ret.setTextMatrix = std::shared_ptr<setTextMatrix>(new setTextMatrix{ t });
            return ret;
        }
    };
    struct setTextPosition {
        const double x;
        const double y;
        static DrawCommand make(double x, double y) {
            DrawCommand ret{ Tag::setTextPosition };
            ret.setTextPosition = std::shared_ptr<setTextPosition>(new setTextPosition{ x, y });
            return ret;
        }
    };
    struct beginPath {
        static DrawCommand make() {
            DrawCommand ret{ Tag::beginPath };
            ret.beginPath = std::shared_ptr<beginPath>(new beginPath{  });
            return ret;
        }
    };
    struct addArc {
        const double x;
        const double y;
        const double radius;
        const double startAngle;
        const double endAngle;
        const bool clockwise;
        static DrawCommand make(double x, double y, double radius, double startAngle, double endAngle, bool clockwise) {
            DrawCommand ret{ Tag::addArc };
            ret.addArc = std::shared_ptr<addArc>(new addArc{ x, y, radius, startAngle, endAngle, clockwise });
            return ret;
        }
    };
    struct addArcToPoint {
        const double x1;
        const double y1;
        const double x2;
        const double y2;
        const double radius;
        static DrawCommand make(double x1, double y1, double x2, double y2, double radius) {
            DrawCommand ret{ Tag::addArcToPoint };
            ret.addArcToPoint = std::shared_ptr<addArcToPoint>(new addArcToPoint{ x1, y1, x2, y2, radius });
            return ret;
        }
    };
    struct drawPath {
        const PathDrawingMode mode;
        static DrawCommand make(PathDrawingMode mode) {
            DrawCommand ret{ Tag::drawPath };
            ret.drawPath = std::shared_ptr<drawPath>(new drawPath{ mode });
            return ret;
        }
    };
    struct setStrokeColorWithColor {
        const Color color;
        static DrawCommand make(Color color) {
            DrawCommand ret{ Tag::setStrokeColorWithColor };
            ret.setStrokeColorWithColor = std::shared_ptr<setStrokeColorWithColor>(new setStrokeColorWithColor{ color });
            return ret;
        }
    };
    struct strokeRectWithWidth {
        const Rect rect;
        const double width;
        static DrawCommand make(Rect rect, double width) {
            DrawCommand ret{ Tag::strokeRectWithWidth };
            ret.strokeRectWithWidth = std::shared_ptr<strokeRectWithWidth>(new strokeRectWithWidth{ rect, width });
            return ret;
        }
    };
    struct moveToPoint {
        const double x;
        const double y;
        static DrawCommand make(double x, double y) {
            DrawCommand ret{ Tag::moveToPoint };
            ret.moveToPoint = std::shared_ptr<moveToPoint>(new moveToPoint{ x, y });
            return ret;
        }
    };
    struct addLineToPoint {
        const double x;
        const double y;
        static DrawCommand make(double x, double y) {
            DrawCommand ret{ Tag::addLineToPoint };
            ret.addLineToPoint = std::shared_ptr<addLineToPoint>(new addLineToPoint{ x, y });
            return ret;
        }
    };
    struct strokePath {
        static DrawCommand make() {
            DrawCommand ret{ Tag::strokePath };
            ret.strokePath = std::shared_ptr<strokePath>(new strokePath{  });
            return ret;
        }
    };
    struct setLineDash {
        const double phase;
        const std::vector<double> lengths;
        static DrawCommand make(double phase, std::vector<double> lengths) {
            DrawCommand ret{ Tag::setLineDash };
            ret.setLineDash = std::shared_ptr<setLineDash>(new setLineDash{ phase, lengths });
            return ret;
        }
    };
    struct clearLineDash {
        static DrawCommand make() {
            DrawCommand ret{ Tag::clearLineDash };
            ret.clearLineDash = std::shared_ptr<clearLineDash>(new clearLineDash{  });
            return ret;
        }
    };
    struct setLineWidth {
        const double width;
        static DrawCommand make(double width) {
            DrawCommand ret{ Tag::setLineWidth };
            ret.setLineWidth = std::shared_ptr<setLineWidth>(new setLineWidth{ width });
            return ret;
        }
    };
    struct clip {
        static DrawCommand make() {
            DrawCommand ret{ Tag::clip };
            ret.clip = std::shared_ptr<clip>(new clip{  });
            return ret;
        }
    };
    struct clipToRect {
        const Rect clipRect;
        static DrawCommand make(Rect clipRect) {
            DrawCommand ret{ Tag::clipToRect };
            ret.clipToRect = std::shared_ptr<clipToRect>(new clipToRect{ clipRect });
            return ret;
        }
    };
    struct translateCTM {
        const double tx;
        const double ty;
        static DrawCommand make(double tx, double ty) {
            DrawCommand ret{ Tag::translateCTM };
            ret.translateCTM = std::shared_ptr<translateCTM>(new translateCTM{ tx, ty });
            return ret;
        }
    };
    struct scaleCTM {
        const double scaleX;
        const double scaleY;
        static DrawCommand make(double scaleX, double scaleY) {
            DrawCommand ret{ Tag::scaleCTM };
            ret.scaleCTM = std::shared_ptr<scaleCTM>(new scaleCTM{ scaleX, scaleY });
            return ret;
        }
    };
    struct rotateCTM {
        const double angle;
        static DrawCommand make(double angle) {
            DrawCommand ret{ Tag::rotateCTM };
            ret.rotateCTM = std::shared_ptr<rotateCTM>(new rotateCTM{ angle });
            return ret;
        }
    };
    struct concatCTM {
        const AffineTransform transform;
        static DrawCommand make(AffineTransform transform) {
            DrawCommand ret{ Tag::concatCTM };
            ret.concatCTM = std::shared_ptr<concatCTM>(new concatCTM{ transform });
            return ret;
        }
    };
    struct addPath {
        const Path path;
        static DrawCommand make(Path path) {
            DrawCommand ret{ Tag::addPath };
            ret.addPath = std::shared_ptr<addPath>(new addPath{ path });
            return ret;
        }
    };
    struct fillPath {
        static DrawCommand make() {
            DrawCommand ret{ Tag::fillPath };
            ret.fillPath = std::shared_ptr<fillPath>(new fillPath{  });
            return ret;
        }
    };
    struct strokeRect {
        const Rect rect;
        static DrawCommand make(Rect rect) {
            DrawCommand ret{ Tag::strokeRect };
            ret.strokeRect = std::shared_ptr<strokeRect>(new strokeRect{ rect });
            return ret;
        }
    };
    struct addRect {
        const Rect rect;
        static DrawCommand make(Rect rect) {
            DrawCommand ret{ Tag::addRect };
            ret.addRect = std::shared_ptr<addRect>(new addRect{ rect });
            return ret;
        }
    };
    struct closePath {
        static DrawCommand make() {
            DrawCommand ret{ Tag::closePath };
            ret.closePath = std::shared_ptr<closePath>(new closePath{  });
            return ret;
        }
    };
    struct drawLinearGradient {
        const Gradient gradient;
        const Point startPoint;
        const Point endPoint;
        const uint32_t drawOpts;
        static DrawCommand make(Gradient gradient, Point startPoint, Point endPoint, uint32_t drawOpts) {
            DrawCommand ret{ Tag::drawLinearGradient };
            ret.drawLinearGradient = std::shared_ptr<drawLinearGradient>(new drawLinearGradient{ gradient, startPoint, endPoint, drawOpts });
            return ret;
        }
    };
    struct drawFrame {
        const Frame frame;
        static DrawCommand make(Frame frame) {
            DrawCommand ret{ Tag::drawFrame };
            ret.drawFrame = std::shared_ptr<drawFrame>(new drawFrame{ frame });
            return ret;
        }
    };
    std::shared_ptr<saveGState> saveGState;
    std::shared_ptr<restoreGState> restoreGState;
    std::shared_ptr<setRGBFillColor> setRGBFillColor;
    std::shared_ptr<setRGBStrokeColor> setRGBStrokeColor;
    std::shared_ptr<setFillColorWithColor> setFillColorWithColor;
    std::shared_ptr<fillRect> fillRect;
    std::shared_ptr<setTextMatrix> setTextMatrix;
    std::shared_ptr<setTextPosition> setTextPosition;
    std::shared_ptr<beginPath> beginPath;
    std::shared_ptr<addArc> addArc;
    std::shared_ptr<addArcToPoint> addArcToPoint;
    std::shared_ptr<drawPath> drawPath;
    std::shared_ptr<setStrokeColorWithColor> setStrokeColorWithColor;
    std::shared_ptr<strokeRectWithWidth> strokeRectWithWidth;
    std::shared_ptr<moveToPoint> moveToPoint;
    std::shared_ptr<addLineToPoint> addLineToPoint;
    std::shared_ptr<strokePath> strokePath;
    std::shared_ptr<setLineDash> setLineDash;
    std::shared_ptr<clearLineDash> clearLineDash;
    std::shared_ptr<setLineWidth> setLineWidth;
    std::shared_ptr<clip> clip;
    std::shared_ptr<clipToRect> clipToRect;
    std::shared_ptr<translateCTM> translateCTM;
    std::shared_ptr<scaleCTM> scaleCTM;
    std::shared_ptr<rotateCTM> rotateCTM;
    std::shared_ptr<concatCTM> concatCTM;
    std::shared_ptr<addPath> addPath;
    std::shared_ptr<fillPath> fillPath;
    std::shared_ptr<strokeRect> strokeRect;
    std::shared_ptr<addRect> addRect;
    std::shared_ptr<closePath> closePath;
    std::shared_ptr<drawLinearGradient> drawLinearGradient;
    std::shared_ptr<drawFrame> drawFrame;
};

// std::vector<DrawCommand>


struct FontTraits {
private:
    enum Fields {
        ItalicField = 1,
        BoldField = 2,
        ExpandedField = 4,
        CondensedField = 8,
        MonospaceField = 16,
        VerticalField = 32
    };
    int32_t _usedFields = 0;
    bool _italic;
    bool _bold;
    bool _expanded;
    bool _condensed;
    bool _monospace;
    bool _vertical;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void FontTraits__push(FontTraits value, bool isReturn);
    friend FontTraits FontTraits__pop();
public:
    void setItalic(bool value) {
        _italic = value;
        _usedFields |= Fields::ItalicField;
    }
    bool hasItalic(bool *value) {
        if (_usedFields & Fields::ItalicField) {
            *value = _italic;
            return true;
        }
        return false;
    }
    void setBold(bool value) {
        _bold = value;
        _usedFields |= Fields::BoldField;
    }
    bool hasBold(bool *value) {
        if (_usedFields & Fields::BoldField) {
            *value = _bold;
            return true;
        }
        return false;
    }
    void setExpanded(bool value) {
        _expanded = value;
        _usedFields |= Fields::ExpandedField;
    }
    bool hasExpanded(bool *value) {
        if (_usedFields & Fields::ExpandedField) {
            *value = _expanded;
            return true;
        }
        return false;
    }
    void setCondensed(bool value) {
        _condensed = value;
        _usedFields |= Fields::CondensedField;
    }
    bool hasCondensed(bool *value) {
        if (_usedFields & Fields::CondensedField) {
            *value = _condensed;
            return true;
        }
        return false;
    }
    void setMonospace(bool value) {
        _monospace = value;
        _usedFields |= Fields::MonospaceField;
    }
    bool hasMonospace(bool *value) {
        if (_usedFields & Fields::MonospaceField) {
            *value = _monospace;
            return true;
        }
        return false;
    }
    void setVertical(bool value) {
        _vertical = value;
        _usedFields |= Fields::VerticalField;
    }
    bool hasVertical(bool *value) {
        if (_usedFields & Fields::VerticalField) {
            *value = _vertical;
            return true;
        }
        return false;
    }
};

struct OptArgs {
private:
    enum Fields {
        TransformField = 1
    };
    int32_t _usedFields = 0;
    AffineTransform _transform;
protected:
    int32_t getUsedFields() {
        return _usedFields;
    }
    friend void OptArgs__push(OptArgs value, bool isReturn);
    friend OptArgs OptArgs__pop();
public:
    void setTransform(AffineTransform value) {
        _transform = value;
        _usedFields |= Fields::TransformField;
    }
    bool hasTransform(AffineTransform *value) {
        if (_usedFields & Fields::TransformField) {
            *value = _transform;
            return true;
        }
        return false;
    }
};


// std::vector<Line>

// std::vector<Point>

struct Range {
    int64_t location;
    int64_t length;
};

struct TypographicBounds {
    double width;
    double ascent;
    double descent;
    double leading;
};

// std::vector<TypographicBounds>

// std::vector<AttributedStringOptions>

// std::vector<Range>

enum RunStatus {
    NoStatus = 0,
    RightToLeft = 1,
    NonMonotonic = 2,
    HasNonIdentityMatrix = 4
};

// std::vector<uint32_t>

// std::vector<Size>

// std::vector<Rect>

struct RunInfo {
    AttributedStringOptions attrs;
    Range sourceRange;
    uint32_t status;
    Rect bounds;
    TypographicBounds typoBounds;
};

// std::vector<RunInfo>

// std::vector<std::vector<RunInfo>>

struct LineInfo {
    Point origin;
    TypographicBounds lineTypoBounds;
    std::vector<RunInfo> runs;
};

// std::vector<LineInfo>



struct GradientStop {
    double location;
    double red;
    double green;
    double blue;
    double alpha;
};

// std::vector<GradientStop>


enum LineBoundsOptions {
    ExcludeTypographicLeading = 1,
    ExcludeTypographicShifts = 2,
    UseHangingPunctuation = 4,
    UseGlyphPathBounds = 8,
    UseOpticalBounds = 16
};

// std::vector<Run>

// std::tuple<double,double>





extern const AffineTransform AffineTransformIdentity;

Color Color_createGenericRGB(double red, double green, double blue, double alpha);
Color Color_getConstantColor(ColorConstants which);
void Color_dispose(Color _this);
ColorSpace ColorSpace_createWithName(ColorSpaceName name);
ColorSpace ColorSpace_createDeviceGray();
void ColorSpace_dispose(ColorSpace _this);
Gradient Gradient_createWithColorComponents(ColorSpace space, std::vector<GradientStop> stops);
void Gradient_dispose(Gradient _this);
Path Path_createWithRect(Rect rect, OptArgs optArgs);
Path Path_createWithEllipseInRect(Rect rect, OptArgs optArgs);
Path Path_createWithRoundedRect(Rect rect, double cornerWidth, double cornerHeight, OptArgs optArgs);
void Path_dispose(Path _this);
void DrawContext_saveGState(DrawContext _this);
void DrawContext_restoreGState(DrawContext _this);
void DrawContext_setRGBFillColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_setRGBStrokeColor(DrawContext _this, double red, double green, double blue, double alpha);
void DrawContext_setFillColorWithColor(DrawContext _this, Color color);
void DrawContext_fillRect(DrawContext _this, Rect rect);
void DrawContext_setTextMatrix(DrawContext _this, AffineTransform t);
void DrawContext_setTextPosition(DrawContext _this, double x, double y);
void DrawContext_beginPath(DrawContext _this);
void DrawContext_addArc(DrawContext _this, double x, double y, double radius, double startAngle, double endAngle, bool clockwise);
void DrawContext_addArcToPoint(DrawContext _this, double x1, double y1, double x2, double y2, double radius);
void DrawContext_drawPath(DrawContext _this, PathDrawingMode mode);
void DrawContext_setStrokeColorWithColor(DrawContext _this, Color color);
void DrawContext_strokeRectWithWidth(DrawContext _this, Rect rect, double width);
void DrawContext_moveToPoint(DrawContext _this, double x, double y);
void DrawContext_addLineToPoint(DrawContext _this, double x, double y);
void DrawContext_strokePath(DrawContext _this);
void DrawContext_setLineDash(DrawContext _this, double phase, std::vector<double> lengths);
void DrawContext_clearLineDash(DrawContext _this);
void DrawContext_setLineWidth(DrawContext _this, double width);
void DrawContext_clip(DrawContext _this);
void DrawContext_clipToRect(DrawContext _this, Rect clipRect);
void DrawContext_translateCTM(DrawContext _this, double tx, double ty);
void DrawContext_scaleCTM(DrawContext _this, double scaleX, double scaleY);
void DrawContext_rotateCTM(DrawContext _this, double angle);
void DrawContext_concatCTM(DrawContext _this, AffineTransform transform);
void DrawContext_addPath(DrawContext _this, Path path);
void DrawContext_fillPath(DrawContext _this);
void DrawContext_strokeRect(DrawContext _this, Rect rect);
void DrawContext_addRect(DrawContext _this, Rect rect);
void DrawContext_closePath(DrawContext _this);
void DrawContext_drawLinearGradient(DrawContext _this, Gradient gradient, Point startPoint, Point endPoint, uint32_t drawOpts);
void DrawContext_batchDraw(DrawContext _this, std::vector<DrawCommand> commands);
void DrawContext_dispose(DrawContext _this);
AttributedString AttributedString_create(std::string s, AttributedStringOptions opts);
void AttributedString_dispose(AttributedString _this);
int64_t MutableAttributedString_getLength(MutableAttributedString _this);
void MutableAttributedString_replaceString(MutableAttributedString _this, Range range, std::string str);
void MutableAttributedString_beginEditing(MutableAttributedString _this);
void MutableAttributedString_endEditing(MutableAttributedString _this);
void MutableAttributedString_setAttribute(MutableAttributedString _this, Range range, AttributedStringOptions attr);
void MutableAttributedString_setCustomAttribute(MutableAttributedString _this, Range range, std::string key, int64_t value);
AttributedString MutableAttributedString_getNormalAttributedString_REMOVEME(MutableAttributedString _this);
MutableAttributedString MutableAttributedString_create(int64_t maxLength);
void MutableAttributedString_dispose(MutableAttributedString _this);
Font Font_createCopyWithSymbolicTraits(Font _this, double size, FontTraits newTraits, OptArgs optArgs);
double Font_getAscent(Font _this);
double Font_getDescent(Font _this);
double Font_getUnderlineThickness(Font _this);
double Font_getUnderlinePosition(Font _this);
Font Font_createFromFile(std::string path, double size, OptArgs optArgs);
Font Font_createWithName(std::string name, double size, OptArgs optArgs);
void Font_dispose(Font _this);
AttributedStringOptions Run_getAttributes(Run _this, std::vector<std::string> customKeys);
TypographicBounds Run_getTypographicBounds(Run _this, Range range);
Range Run_getStringRange(Run _this);
uint32_t Run_getStatus(Run _this);
void Run_dispose(Run _this);
TypographicBounds Line_getTypographicBounds(Line _this);
Rect Line_getBoundsWithOptions(Line _this, uint32_t opts);
void Line_draw(Line _this, DrawContext context);
std::vector<Run> Line_getGlyphRuns(Line _this);
std::tuple<double,double> Line_getOffsetForStringIndex(Line _this, int64_t charIndex);
Line Line_createWithAttributedString(AttributedString str);
void Line_dispose(Line _this);
void Frame_draw(Frame _this, DrawContext context);
std::vector<Line> Frame_getLines(Frame _this);
std::vector<Point> Frame_getLineOrigins(Frame _this, Range range);
std::vector<LineInfo> Frame_getLinesExtended(Frame _this, std::vector<std::string> customKeys);
void Frame_dispose(Frame _this);
FrameSetter FrameSetter_createWithAttributedString(AttributedString str);
Frame FrameSetter_createFrame(FrameSetter _this, Range range, Path path);
void FrameSetter_dispose(FrameSetter _this);
