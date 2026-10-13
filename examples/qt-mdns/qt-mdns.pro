# Qt 5.14 mDNS example. Open this file in Qt Creator, or from this directory:
#   qmake qt-mdns.pro && make
# Run:
#   ./qt-mdns --help
#   ./qt-mdns --mode both --type _http._tcp.local. --name qt-mdns-demo --port 8080

!equals(QT_MAJOR_VERSION, 5) | lessThan(QT_MINOR_VERSION, 14): \
    error("This example targets Qt 5.14 or a newer Qt 5.")

QT += core network
QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle
TEMPLATE = app
TARGET = qt-mdns

QMDNS_ROOT = $$PWD/../../third_party/qmdnsengine

INCLUDEPATH += \
    $$PWD \
    $$QMDNS_ROOT/src/include \
    $$QMDNS_ROOT/src/src

DEPENDPATH += $$INCLUDEPATH

SOURCES += \
    main.cpp \
    mdnsdemo.cpp \
    $$QMDNS_ROOT/src/src/abstractserver.cpp \
    $$QMDNS_ROOT/src/src/bitmap.cpp \
    $$QMDNS_ROOT/src/src/browser.cpp \
    $$QMDNS_ROOT/src/src/cache.cpp \
    $$QMDNS_ROOT/src/src/dns.cpp \
    $$QMDNS_ROOT/src/src/hostname.cpp \
    $$QMDNS_ROOT/src/src/mdns.cpp \
    $$QMDNS_ROOT/src/src/message.cpp \
    $$QMDNS_ROOT/src/src/prober.cpp \
    $$QMDNS_ROOT/src/src/provider.cpp \
    $$QMDNS_ROOT/src/src/query.cpp \
    $$QMDNS_ROOT/src/src/record.cpp \
    $$QMDNS_ROOT/src/src/resolver.cpp \
    $$QMDNS_ROOT/src/src/server.cpp \
    $$QMDNS_ROOT/src/src/service.cpp

HEADERS += \
    mdnsdemo.h \
    qmdnsengine_export.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/abstractserver.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/browser.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/cache.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/hostname.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/prober.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/provider.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/resolver.h \
    $$QMDNS_ROOT/src/include/qmdnsengine/server.h \
    $$QMDNS_ROOT/src/src/browser_p.h \
    $$QMDNS_ROOT/src/src/cache_p.h \
    $$QMDNS_ROOT/src/src/hostname_p.h \
    $$QMDNS_ROOT/src/src/prober_p.h \
    $$QMDNS_ROOT/src/src/provider_p.h \
    $$QMDNS_ROOT/src/src/resolver_p.h \
    $$QMDNS_ROOT/src/src/server_p.h
