#include "stockquotes.hpp"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

const QString gStockQuoteQueryAPI {"https://api.iextrading.com/1.0/stock/%1/quote"};
const QString gStockQuoteRetrieving {QObject::tr("Retrieving '%1' stock price ...")};
const QString gNetworkError {QObject::tr("Request failed with network error %1")};
const QString gStockQuoteResultAPI {QObject::tr("Stock '%1' last price is %2")};
const QString gStockQuoteErrorMessage {QObject::tr("Failed to retrieve stock price for '%1'")};

StockQuotes::StockQuotes(QObject *parent) : QObject(parent)
{
    connect(&mNetworkAccessManager, &QNetworkAccessManager::finished, this, &StockQuotes::onNetworkReply);
    connect(&mNetworkAccessManager, &QNetworkAccessManager::sslErrors,
            [&](QNetworkReply*,const QList<QSslError> &errors)
    {
        if ( errors.count() >0)
            mStockQuoteNotification.setQueryResult(gNetworkError.arg(errors.at(0).errorString()));
        else
            mStockQuoteNotification.setQueryResult(gNetworkError.arg(""));
    } );
}

void StockQuotes::queryStock(const QString &stockSymbol)
{
    try
    {
        mStockQuoteNotification.setQueryResult(gStockQuoteRetrieving.arg(stockSymbol));
        QString url {gStockQuoteQueryAPI.arg(stockSymbol)};
        auto networkRequest = QNetworkRequest(url);
        QStringList attributes { stockSymbol};
        networkRequest.setAttribute(QNetworkRequest::Attribute::User, QVariant(attributes ));
        QNetworkReply* networkReply = mNetworkAccessManager.get(networkRequest);

        connect(networkReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
                [&,stockSymbol](QNetworkReply::NetworkError code)
        {
            mStockQuoteNotification.setQueryResult(gNetworkError.arg(code));
        } );

    }
    catch(std::exception const & e)
    {
        qWarning() << "StockQuotes::queryStock exception: " << e.what();
    }
}

void StockQuotes::onNetworkReply(QNetworkReply *networkReply)
{
    if ( networkReply == nullptr)
        return;
    try
    {
        QStringList attributes = networkReply->request().attribute(QNetworkRequest::Attribute::User).toStringList();
        if ( attributes.isEmpty() )
            return;

        const QString stockSymbol { attributes[0]};
        if ( networkReply->error())
        {
            mStockQuoteNotification.setQueryResult(gStockQuoteErrorMessage.arg(stockSymbol));
        }
        else
        {
            const QString source { networkReply->readAll()};
            int begIndex = source.indexOf("latestPrice") + 13;
            int size = source.indexOf(",", begIndex) - begIndex;
            QStringRef extractedText(&source, begIndex, size);
            bool success;
            auto formattedPrice = extractedText.toString().toDouble(&success);
            if (success && formattedPrice > 0.0)
            {
                mStockQuoteNotification.setQueryResult(gStockQuoteResultAPI.arg(stockSymbol).arg(formattedPrice));
            }
            else
            {
                mStockQuoteNotification.setQueryResult(gStockQuoteErrorMessage.arg(stockSymbol));
            }
        }
    }
    catch(std::exception const & e)
    {
        qWarning() << "StockQuotes::onNetworkReply exception: " << e.what();
    }
    networkReply->deleteLater();
}
