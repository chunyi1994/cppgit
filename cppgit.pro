TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lz

INCLUDEPATH += /usr/local/include

QMAKE_CXX = g++
QMAKE_CXXFLAGS += -std=c++17


SOURCES += \
    src/main.cc \
    src/object/object.cc \
    src/vendor/sha1/sha1.cc

DISTFILES += \
    README.md \
    src/CMakeLists.txt \
    CMakeLists.txt \
    src/vendor/CMakeLists.txt

INCLUDEPATH += /usr/local/include


HEADERS += \
    src/object/object.h \
    src/errors/errors.h \
    src/object/commit.h \
    src/object/object_test.h \
    src/vendor/sha1/sha1.h \
    src/object/zlibs.h

