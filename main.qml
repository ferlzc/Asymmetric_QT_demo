import QtQuick.Controls 2.2
import QtQuick 2.2
import QtCharts 2.2
import Realtime 1.0

Item {
    id: item1
    visible: true
    width: 800
    height: 480

    Realtime {
        id: realtime
    }

    Timer {
        id: timer
        property int index: 0
        running: true
        repeat: true
        interval: 100
        onTriggered: {
            realtime.update();

            console.log(
                        "x: " + realtime.accX +
                        " y: " + realtime.accY +
                        " z: " + realtime.accZ );
            accx.append(index,realtime.accX);
            accy.append(index,realtime.accY);
            accz.append(index,realtime.accZ);

            index++;
            axisX.min++;
            axisX.max++;
        }
    }

    ChartView {
        id: chartview
        animationOptions: ChartView.NoAnimation
        theme: ChartView.ChartThemeDark
        antialiasing: true
        anchors.fill: parent

        ValueAxis {
            id: axisX
            min: -5
            max: 5
        }

        ValueAxis {
            id: axisY
            min: -20
            max: 20
        }

        LineSeries {
            id: accx
            name: "accx"
            axisY: axisY
            axisX: axisX
        }
        LineSeries {
            id: accy
            name: "accy"
            axisY: axisY
            axisX: axisX
        }
        LineSeries {
            id: accz
            name: "accz"
            axisY: axisY
            axisX: axisX
        }
    }

    Text {
        x: 630
        y: 427
        width: 144
        height: 19
        color: "#ffffff"
        text: SOFTWARE_VERSION
        font.bold: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 34
        z: 10
    }
}
