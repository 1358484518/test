#ifndef MDNSDEMO_H
#define MDNSDEMO_H

#include <QHash>
#include <QObject>
#include <QScopedPointer>

#include <qmdnsengine/browser.h>
#include <qmdnsengine/cache.h>
#include <qmdnsengine/hostname.h>
#include <qmdnsengine/provider.h>
#include <qmdnsengine/server.h>

namespace QMdnsEngine {
class Resolver;
class Service;
}

class MdnsDemo : public QObject
{
    Q_OBJECT

public:
    MdnsDemo(const QByteArray &type,
             bool browse,
             bool publish,
             const QByteArray &name,
             quint16 port,
             QObject *parent = nullptr);

private slots:
    void onServiceAdded(const QMdnsEngine::Service &service);
    void onServiceUpdated(const QMdnsEngine::Service &service);
    void onServiceRemoved(const QMdnsEngine::Service &service);

private:
    void watchHost(const QByteArray &hostname);

    QMdnsEngine::Server m_server;
    QMdnsEngine::Cache m_cache;
    QMdnsEngine::Hostname m_hostname;
    QScopedPointer<QMdnsEngine::Browser> m_browser;
    QScopedPointer<QMdnsEngine::Provider> m_provider;
    QHash<QByteArray, QMdnsEngine::Resolver *> m_resolvers;
};

#endif
