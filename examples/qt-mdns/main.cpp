#include "mdnsdemo.h"

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>

namespace {

QByteArray normalizeType(const QString &text)
{
    QByteArray type = text.trimmed().toUtf8();
    if (type.isEmpty())
        return QByteArrayLiteral("_http._tcp.local.");
    if (!type.endsWith('.'))
        type.append('.');
    if (!type.endsWith("local."))
        type.append("local.");
    return type;
}

} // namespace

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("qt-mdns"));
    QCoreApplication::setApplicationVersion(QStringLiteral("1.0"));

    QCommandLineParser parser;
    parser.setApplicationDescription(
            QStringLiteral("Qt 5.14 mDNS 示例：用 QMdnsEngine 发布或发现局域网服务。"));
    parser.addHelpOption();
    parser.addVersionOption();

    const QCommandLineOption modeOption(
            QStringList() << QStringLiteral("m") << QStringLiteral("mode"),
            QStringLiteral("browse、publish 或 both，默认 both"),
            QStringLiteral("mode"),
            QStringLiteral("both"));
    const QCommandLineOption typeOption(
            QStringList() << QStringLiteral("t") << QStringLiteral("type"),
            QStringLiteral("服务类型，例如 _http._tcp.local."),
            QStringLiteral("type"),
            QStringLiteral("_http._tcp.local."));
    const QCommandLineOption nameOption(
            QStringList() << QStringLiteral("n") << QStringLiteral("name"),
            QStringLiteral("发布时的服务名"),
            QStringLiteral("name"),
            QStringLiteral("qt-mdns-demo"));
    const QCommandLineOption portOption(
            QStringList() << QStringLiteral("p") << QStringLiteral("port"),
            QStringLiteral("发布时的 TCP 端口"),
            QStringLiteral("port"),
            QStringLiteral("8080"));
    const QCommandLineOption secondsOption(
            QStringList() << QStringLiteral("s") << QStringLiteral("seconds"),
            QStringLiteral("运行秒数，0 表示一直运行到 Ctrl+C"),
            QStringLiteral("seconds"),
            QStringLiteral("0"));

    parser.addOption(modeOption);
    parser.addOption(typeOption);
    parser.addOption(nameOption);
    parser.addOption(portOption);
    parser.addOption(secondsOption);
    parser.process(app);

    QTextStream err(stderr);
    err.setCodec("UTF-8");

    const QString mode = parser.value(modeOption).trimmed().toLower();
    const bool browse = mode == QLatin1String("browse") || mode == QLatin1String("both");
    const bool publish = mode == QLatin1String("publish") || mode == QLatin1String("both");
    if (!browse && !publish) {
        err << "未知 mode: " << mode << "\n可选 browse、publish、both\n";
        return 2;
    }

    bool portOk = false;
    const uint port = parser.value(portOption).toUInt(&portOk);
    if (!portOk || port == 0 || port > 65535) {
        err << "端口必须是 1 到 65535\n";
        return 2;
    }

    bool secondsOk = false;
    const int seconds = parser.value(secondsOption).toInt(&secondsOk);
    if (!secondsOk || seconds < 0) {
        err << "seconds 必须是大于等于 0 的整数\n";
        return 2;
    }

    MdnsDemo demo(normalizeType(parser.value(typeOption)),
                  browse,
                  publish,
                  parser.value(nameOption).toUtf8(),
                  static_cast<quint16>(port));

    if (seconds > 0)
        QTimer::singleShot(seconds * 1000, &app, &QCoreApplication::quit);

    return app.exec();
}
