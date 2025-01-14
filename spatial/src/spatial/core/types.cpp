#include "spatial/core/types.hpp"

#include "duckdb/function/cast/cast_function_set.hpp"
#include "duckdb/parser/parsed_data/create_scalar_function_info.hpp"
#include "duckdb/parser/parsed_data/create_type_info.hpp"
#include "spatial/common.hpp"
#include "spatial/core/functions/common.hpp"

namespace spatial {

namespace core {

LogicalType GeoTypes::POINT_2D() {
	auto type = LogicalType::STRUCT({{"x", LogicalType::DOUBLE}, {"y", LogicalType::DOUBLE}});
	type.SetAlias("POINT_2D");
	return type;
}

LogicalType GeoTypes::POINT_3D() {
	auto type =
	    LogicalType::STRUCT({{"x", LogicalType::DOUBLE}, {"y", LogicalType::DOUBLE}, {"z", LogicalType::DOUBLE}});
	type.SetAlias("POINT_3D");
	return type;
}

LogicalType GeoTypes::POINT_4D() {
	auto type = LogicalType::STRUCT({{"x", LogicalType::DOUBLE},
	                                 {"y", LogicalType::DOUBLE},
	                                 {"z", LogicalType::DOUBLE},
	                                 {"m", LogicalType::DOUBLE}});
	type.SetAlias("POINT_4D");
	return type;
}

LogicalType GeoTypes::BOX_2D() {
	auto type = LogicalType::STRUCT({{"min_x", LogicalType::DOUBLE},
	                                 {"min_y", LogicalType::DOUBLE},
	                                 {"max_x", LogicalType::DOUBLE},
	                                 {"max_y", LogicalType::DOUBLE}});
	type.SetAlias("BOX_2D");
	return type;
}

LogicalType GeoTypes::LINESTRING_2D() {
	auto type = LogicalType::LIST(LogicalType::STRUCT({{"x", LogicalType::DOUBLE}, {"y", LogicalType::DOUBLE}}));
	type.SetAlias("LINESTRING_2D");
	return type;
}

LogicalType GeoTypes::POLYGON_2D() {
	auto type = LogicalType::LIST(
	    LogicalType::LIST(LogicalType::STRUCT({{"x", LogicalType::DOUBLE}, {"y", LogicalType::DOUBLE}})));
	type.SetAlias("POLYGON_2D");
	return type;
}

LogicalType GeoTypes::GEOMETRY() {
	auto blob_type = LogicalType(LogicalTypeId::BLOB);
	blob_type.SetAlias("GEOMETRY");
	return blob_type;
}

LogicalType GeoTypes::WKB_BLOB() {
	auto blob_type = LogicalType(LogicalTypeId::BLOB);
	blob_type.SetAlias("WKB_BLOB");
	return blob_type;
}

static void AddType(Catalog &catalog, ClientContext &context, LogicalType type, const char *name) {
	CreateTypeInfo type_info(name, std::move(type));
	type_info.temporary = true;
	type_info.internal = true;
	catalog.CreateType(context, type_info);
}

void GeoTypes::Register(ClientContext &context) {
	auto &catalog = Catalog::GetSystemCatalog(context);

	// POINT_2D
	AddType(catalog, context, GeoTypes::POINT_2D(), "POINT_2D");

	// POINT_3D
	AddType(catalog, context, GeoTypes::POINT_3D(), "POINT_3D");

	// POINT_4D
	AddType(catalog, context, GeoTypes::POINT_4D(), "POINT_4D");

	// LineString2D
	AddType(catalog, context, GeoTypes::LINESTRING_2D(), "LINESTRING_2D");

	// Polygon2D
	AddType(catalog, context, GeoTypes::POLYGON_2D(), "POLYGON_2D");

	// Box2D
	AddType(catalog, context, GeoTypes::BOX_2D(), "BOX_2D");

	// GEOMETRY
	AddType(catalog, context, GeoTypes::GEOMETRY(), "GEOMETRY");

	// WKB_BLOB
	AddType(catalog, context, GeoTypes::WKB_BLOB(), "WKB_BLOB");
}

} // namespace core

} // namespace spatial