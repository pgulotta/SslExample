#include <QtGui>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "stockquotes.hpp"
#include "stockquotenotification.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QObject::connect(&app, &QGuiApplication::lastWindowClosed, &app, &QGuiApplication::quit);

    QQmlApplicationEngine engine;

    StockQuotes stockquotes;
    auto rootContext = engine.rootContext();
    qmlRegisterType<StockQuoteNotification>("StockQuoteNotification",1,0,"StockQuoteNotification");
    rootContext->setContextProperty("StockQuoteQuery",&stockquotes);
    rootContext->setContextProperty("StockQuote", stockquotes.stockQuoteNotification());
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
