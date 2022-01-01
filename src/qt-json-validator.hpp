#pragma once
#include <QString>


namespace JsonValidator
{
bool validate(const QString &jsonSchema, const QString &jsonToValidate, QString *errorMsg = nullptr);
}

