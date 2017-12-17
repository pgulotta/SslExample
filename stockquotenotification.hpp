#pragma once

#include <QObject>
#include <QDebug>


class StockQuoteNotification : public QObject
{
Q_OBJECT
Q_PROPERTY(QString queryResult READ queryResult WRITE setQueryResult NOTIFY queryResultChanged)

signals:
    void queryResultChanged(QString queryResult);

public slots:
    void setQueryResult(QString queryResult)
    {
        if (m_queryResult == queryResult)
            return;

        m_queryResult = queryResult;
        emit queryResultChanged(m_queryResult);
    }

public:
    QString queryResult() const
    {
        return m_queryResult;
    }

private:
    QString m_queryResult;
};
