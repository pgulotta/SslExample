import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import StockQuoteNotification 1.0

ApplicationWindow {
    readonly property bool isAndroid: Qt.platform.os === "android"

    visible: true
    width: isAndroid ? Screen.width : Screen.width * .25
    height: isAndroid ? Screen.height : Screen.height * .3
    title: qsTr("SSL Example")

    ColumnLayout {
        spacing: 20
        anchors.margins: spacing
        anchors.fill: parent
        Text {
            id: resultTextId
            width: parent.width
            Layout.alignment: Qt.AlignHCenter
            textFormat: Text.RichText
            font.pointSize: 18
            color: "blue"

            StockQuoteNotification {
                queryResult: StockQuote.queryResult
                onQueryResultChanged: resultTextId.text = queryResult
            }
        }
        Text {
            text: "Press stock symbol to display latest price"
            width: parent.width
            Layout.alignment: Qt.AlignHCenter
            textFormat: Text.RichText
            font.pointSize: 14
        }
        GridView {
            id: stockSymbolsId
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: stockSymbolsModelId
            delegate: Rectangle {
                height: 80
                width: 100
                Button {
                    text: symbol
                    height: 60
                    width: 80
                    anchors.centerIn: parent
                    onClicked: StockQuoteQuery.queryStock(text)
                }
            }
        }

        ListModel {
            id: stockSymbolsModelId
            ListElement {
                symbol: "ABT"
            }
            ListElement {
                symbol: "CAG"
            }
            ListElement {
                symbol: "FB"
            }
            ListElement {
                symbol: "KR"
            }
            ListElement {
                symbol: "MSFT"
            }
            ListElement {
                symbol: "PG"
            }
            ListElement {
                symbol: "QQQ"
            }
            ListElement {
                symbol: "T"
            }
            ListElement {
                symbol: "UPS"
            }
            ListElement {
                symbol: "XRX"
            }
        }
    }
}
