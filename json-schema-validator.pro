CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = lib
TARGET = json-schema-validator
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
CONFIG += c++17

QT = core

SOURCES +=  src/json-patch.cpp \
			src/json-schema-draft7.json.cpp \
			src/json-uri.cpp \
			src/json-validator.cpp \
			src/qt-json-validator.cpp \
			src/string-format-check.cpp

