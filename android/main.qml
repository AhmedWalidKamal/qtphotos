import QtQuick 2.7
import QtQuick.Controls 2.0

import QtQuick.Controls.Styles 1.4

ApplicationWindow {

    id: applicationWindow
    visible: true
    width: 600
    height: 320
    color: "#212121"
    title: qsTr("Hello World")

    ToolBar {
        id: toolBar
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        background: Rectangle {
            color: "#2D2D2D"
        }

        ToolButton {
            id: cropButton
            x: 552
            y: 10
            text: qsTr("")
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5

            Image {
                id: cropImage
                height: 35
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width: 32
                source: "icons/crop.png"
            }

            onClicked: console.log("CROP");
        }

        ToolButton {
            id: openButton
            y: 10
            text: qsTr("")
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 5

            Image {
                id: openImage
                height: 35
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                width: 32
                source: "icons/open.png"
            }

            onClicked: BackEnd.openImage();
        }

        ToolButton {
            id: saveButton
            text: qsTr("")
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.left: openButton.right
            anchors.leftMargin: 5

            Image {
                id: saveImage
                height: 32
                width: 32
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                source: "icons/save.png"
            }

            onClicked: console.log("SAVE")
        }
    }

    Label {
        id: imgLabel
        x: 283
        y: 151
        width: 500
        height: 100
        text: qsTr("")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

}
