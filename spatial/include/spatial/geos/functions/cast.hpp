#pragma once
#include "spatial/common.hpp"

namespace spatial {

namespace geos {

struct GeosCastFunctions {
	static void Register(ClientContext &context);
};

} // namespace geos

} // namespace spatial