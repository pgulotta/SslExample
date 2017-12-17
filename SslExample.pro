TEMPLATE = app

QT += quick

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    stockquotes.cpp

HEADERS += \
    stockquotes.hpp \
    stockquotenotification.hpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =


unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/android/libs/openssl/armeabi-v7a/libcrypto.so \
        $$PWD/android/libs/openssl/armeabi-v7a/libssl.so
}

message(Source directory = $$PWD)
message(ANDROID_TARGET_ARCH = $$ANDROID_TARGET_ARCH)
message(ANDROID_EXTRA_LIBS = $$ANDROID_EXTRA_LIBS)


