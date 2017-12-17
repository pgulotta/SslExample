#pragma once

#include "stockquotenotification.hpp"
#include <QObject>
#include <QStringList>
#include <QNetworkAccessManager>

class StockQuotes : public QObject
{
Q_OBJECT

signals:

public slots:
    void onNetworkReply(QNetworkReply *networkReply);

public:
    explicit StockQuotes(QObject *parent = nullptr);

    Q_INVOKABLE void queryStock(const QString& stockSymbol);

    StockQuoteNotification* stockQuoteNotification()
    {
        return &mStockQuoteNotification;
    }

private:
    QNetworkAccessManager mNetworkAccessManager;
    StockQuoteNotification mStockQuoteNotification;
};


