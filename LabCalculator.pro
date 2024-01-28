QT += quick

VERSION = 1.0.0.1

QMAKE_TARGET_COMPANY = Hapooga Co
QMAKE_TARGET_PRODUCT = Lab Calculator
QMAKE_TARGET_DISCRIPTION = Lab Calculator
QMAKE_TARGET_COPYRIGHT = Kliuev Mikhail

SOURCES += \
        chemicalequivalentcontroller.cpp \
        evaluator.cpp \
        formulaparser.cpp \
        inputcontroller.cpp \
        main.cpp \
        periodictable.cpp \
        qmladapter.cpp

resources.files = \
main.qml \
MyTopPanel.qml \
MySwip.qml \
MyPageCaption.qml \
MyInputItem.qml \
MyRadioButtonInputItem.qml \
MyInputItemVertical.qml

resources.prefix = /$${TARGET}

RESOURCES += resources \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

DISTFILES +=

HEADERS += \
    chemicalequivalentcontroller.h \
    evaluator.h \
    expressionTree.h \
    formulaparser.h \
    inputcontroller.h \
    periodictable.h \
    qmladapter.h
