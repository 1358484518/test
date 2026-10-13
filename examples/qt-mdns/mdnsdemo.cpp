#include "mdnsdemo.h"

#include <QHostAddress>
#include <QMap>
#include <QTextStream>

#include <qmdnsengine/resolver.h>
#include <qmdnsengine/service.h>

namespace {

QTextStream &out()
{
    static QTextStream stream(stdout);
    stream.setCodec("UTF-8");
    return stream;
}

void printService(const char *tag, const QMdnsEngine::Service &service)
{
    out() << tag << " " << service.name()
          << " type=" << service.type()
          << " host=" << service.hostname()
          << " port=" << service.port() << "\n";

    const QMap<QByteArray, QByteArray> attributes = service.attributes();
    for (QMap<QByteArray, QByteArray>::const_iterator it = attributes.cbegin();
         it != attributes.cend(); ++it) {
        out() << "    " << it.key() << "=" << it.value() << "\n";
    }
    out().flush();
}

} // namespace

MdnsDemo::MdnsDemo(const QByteArray &type,
                   bool browse,
                   bool publish,
                   const QByteArray &name,
                   quint16 port,
                   QObject *parent)
    : QObject(parent),
      m_hostname(&m_server)
{
    if (browse) {
        m_browser.reset(new QMdnsEngine::Browser(&m_server, type, &m_cache));
        connect(m_browser.data(), &QMdnsEngine::Browser::serviceAdded,
                this, &MdnsDemo::onServiceAdded);
        connect(m_browser.data(), &QMdnsEngine::Browser::serviceUpdated,
                this, &MdnsDemo::onServiceUpdated);
        connect(m_browser.data(), &QMdnsEngine::Browser::serviceRemoved,
                this, &MdnsDemo::onServiceRemoved);
        out() << "browsing " << type << "\n";
        out().flush();
    }

    if (publish) {
        QMdnsEngine::Service service;
        service.setName(name);
        service.setType(type);
        service.setPort(port);
        service.addAttribute("txtvers", "1");
        service.addAttribute("app", "qt-mdns");

        m_provider.reset(new QMdnsEngine::Provider(&m_server, &m_hostname));
        m_provider->update(service);

        connect(&m_hostname, &QMdnsEngine::Hostname::hostnameChanged,
                this, [](const QByteArray &hostname) {
            out() << "hostname " << hostname << "\n";
            out().flush();
        });

        out() << "publishing " << name << " type=" << type << " port=" << port << "\n";
        out().flush();
    }
}

void MdnsDemo::onServiceAdded(const QMdnsEngine::Service &service)
{
    printService("+", service);
    watchHost(service.hostname());
}

void MdnsDemo::onServiceUpdated(const QMdnsEngine::Service &service)
{
    printService("~", service);
    watchHost(service.hostname());
}

void MdnsDemo::onServiceRemoved(const QMdnsEngine::Service &service)
{
    printService("-", service);
}

void MdnsDemo::watchHost(const QByteArray &hostname)
{
    if (hostname.isEmpty() || m_resolvers.contains(hostname))
        return;

    QMdnsEngine::Resolver *resolver =
            new QMdnsEngine::Resolver(&m_server, hostname, &m_cache, this);
    m_resolvers.insert(hostname, resolver);
    connect(resolver, &QMdnsEngine::Resolver::resolved,
            this, [hostname](const QHostAddress &address) {
        out() << "  addr " << hostname << " " << address.toString() << "\n";
        out().flush();
    });
}
