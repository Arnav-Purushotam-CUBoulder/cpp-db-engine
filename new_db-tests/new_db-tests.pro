TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15

QMAKE_CXXFLAGS += -O2 -fPIC

SOURCES += \
        dbmanagement-tests.cpp \
        encodedvalue-tests.cpp \
        hashedvalue-tests.cpp \
        hashing-tests.cpp \
        key-tests.cpp \
        keyvalue-bug-tests.cpp \
        keyvalue-tests.cpp \
        performance-tests.cpp \
        query-tests.cpp

include(../new_db/Defines.pri)

macx:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../new_db/ -lnew_db
else:macx:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../new_db/ -lnew_db

HEADERS += \
    catch.hpp \
    tests.h

HH = ../../highwayhash

INCLUDEPATH += include $${HH}
