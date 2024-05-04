#include "util.h"

dl_CGAffineTransform* dlOptionalTransform(std::optional<Drawing::AffineTransform>& t) {
    if (t.has_value()) {
        return (dl_CGAffineTransform*)&t.value();
    }
    return nullptr;
}
