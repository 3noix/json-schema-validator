#include "qt-json-validator.hpp"
#include "json-schema.hpp"
using nlohmann::json;
using nlohmann::json_schema::json_validator;


namespace JsonValidator
{
bool validate(const QString &jsonSchema, const QString &jsonToValidate, QString *errorMsg)
{
	json jsonSchema2;
	try {
		jsonSchema2 = json::parse(jsonSchema.toStdString());
	}
	catch (std::exception &e) {
		if (errorMsg) {*errorMsg = QString{"Fail to parse schema: "} + e.what();}
		return false;
	}

	json jsonToValidate2;
	try {
		jsonToValidate2 = json::parse(jsonToValidate.toStdString());
	}
	catch (std::exception &e) {
		if (errorMsg) {*errorMsg = QString{"Fail to parse content: "} + e.what();}
		return false;
	}

	// process the schema
	json_validator validator;
	try {
		validator.set_root_schema(jsonSchema2);
	}
	catch (const std::exception &e) {
		if (errorMsg) {*errorMsg = QString{"At schema validation step: "} + e.what();}
		return false;
	}

	// validate wrt the schema
	try {
		auto defaultPatch = validator.validate(jsonToValidate2);
		return true;
	}
	catch (const std::exception &e) {
		if (errorMsg) {*errorMsg = e.what();}
		return false;
	}
}
}

