CONFIG(debug, debug|release) {
	MODE = debug
}
CONFIG(release, debug|release) {
	MODE = release
}


TEMPLATE = app
TARGET = qt-json-validation-example
DESTDIR = $$MODE
OBJECTS_DIR = $$MODE/objects
MOC_DIR = $$MODE/moc
CONFIG += c++17 console
QT = core


INCLUDEPATH += ../src
LIBS += ../$$MODE/libjson-schema-validator.a

SOURCES += main.cpp

RESOURCES += resources.qrc

