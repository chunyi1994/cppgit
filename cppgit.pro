TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lz

INCLUDEPATH += /usr/local/include

QMAKE_CXXFLAGS += -std=c++1z

#QMAKE_CXXFLAGS += -Werror
#QMAKE_CXXFLAGS +=  -Wno-unused-parameter
#QMAKE_CXXFLAGS +=  -Wno-unused-function
#QMAKE_CXXFLAGS +=  -Wno-unused-variable
#QMAKE_CXXFLAGS +=  -Wunused-private-field


SOURCES += \
    src/object/object.cc \
    src/vendor/sha1/sha1.cc \
    src/main.cc \
    src/object/commit.cc \
    src/object/hash.cc \
    src/object/zlibs.cc \
    src/object/tree.cc \
    src/object/commit.cc \
    src/object/hash.cc \
    src/object/object.cc \
    src/object/tree.cc \
    src/object/zlibs.cc \
    src/vendor/sha1/sha1.cc \
    src/main.cc \
    src/storer/file_storer.cc \
    src/object/commit.cc \
    src/object/hash.cc \
    src/object/object.cc \
    src/object/tree.cc \
    src/object/zlibs.cc \
    src/storer/file_storer.cc \
    src/vendor/sha1/sha1.cc \
    src/main.cc \
    src/repository/repository.cc \
    src/repository/branch.cc \
    src/storer/file_storer.cc \
    src/storer/file/file_storer.cc

DISTFILES += \
    README.md \
    src/CMakeLists.txt \
    CMakeLists.txt \
    src/vendor/CMakeLists.txt \
    src/errors/CMakeLists.txt \
    src/object/CMakeLists.txt

INCLUDEPATH += /usr/local/include


HEADERS += \
    src/object/object.h \
    src/errors/errors.h \
    src/object/commit.h \
    src/object/object_test.h \
    src/vendor/sha1/sha1.h \
    src/object/zlibs.h \
    src/object/hash.h \
    src/object/zlibs.h \
    src/utils/times.h \
    src/utils/buffer.h \
    src/object/commit_test.h \
    src/object/tree.h \
    src/object/tree_test.h \
    src/utils/strings.h \
    src/errors/errors.h \
    src/object/commit.h \
    src/object/commit_test.h \
    src/object/hash.h \
    src/object/object.h \
    src/object/object_test.h \
    src/object/tree.h \
    src/object/tree_test.h \
    src/object/zlibs.h \
    src/storer/storer.h \
    src/utils/buffer.h \
    src/utils/strings.h \
    src/utils/times.h \
    src/vendor/sha1/sha1.h \
    src/errors/errors.h \
    src/object/commit.h \
    src/object/commit_test.h \
    src/object/hash.h \
    src/object/object.h \
    src/object/object_test.h \
    src/object/tree.h \
    src/object/tree_test.h \
    src/object/zlibs.h \
    src/repository/repository.h \
    src/storer/storer.h \
    src/utils/buffer.h \
    src/utils/strings.h \
    src/utils/times.h \
    src/vendor/sha1/sha1.h \
    src/repository/branch.h \
    src/storer/storer.h \
    src/storer/file/file_storer.h

