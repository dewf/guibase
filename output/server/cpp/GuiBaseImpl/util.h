#pragma once

#include "generated/Drawing.h"
#include "deps/opendl/source/opendl.h"
#include "deps/opendl/deps/CFMinimal/source/CF/CFMisc.h" // for exceptions

#include <optional>

#define STRUCT_CAST(t, v) *((t*)&v)

dl_CGAffineTransform* dlOptionalTransform(std::optional<Drawing::AffineTransform>& t);
