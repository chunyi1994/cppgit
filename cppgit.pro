TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lz

INCLUDEPATH += /usr/local/include

QMAKE_CXXFLAGS += -std=c++1z

SOURCES += \
    src/object/object.cc \
    src/object/object.cc \
    src/vendor/sha1/sha1.cc \
    src/main.cc

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
    src/object/zlibs.h \
    src/object/hash.h \
    src/errors/errors.h \
    src/object/commit.h \
    src/object/hash.h \
    src/object/object.h \
    src/object/object_test.h \
    src/object/zlibs.h \
    src/utils/times.h \
    src/vendor/sha1/sha1.h

