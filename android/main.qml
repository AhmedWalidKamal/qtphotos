import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0

import QtQuick.Controls.Styles 1.4
ApplicationWindow {

    id: applicationWindow
    visible: true
    width: 600
    height: 320
    color: "#212121"
    property alias image: image
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

    Pane {
        id: pane
        anchors.top: toolBar.bottom
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 25
        anchors.left: parent.left
        anchors.leftMargin: 25

        background: Rectangle {
            color: "#2D2D2D"
        }


        ZoomableImage{
            id:image
            antialiasing: true

            anchors {
                fill: parent
                margins: 2
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: boundingSelectionTriangle
            color: "#00ffffff"
            anchors.fill: parent
            width: parent.width
            height: parent.height
            x: parent.x
            y: parent.y

            Rectangle {
                id: selectRect
                color: "#00ffffff"
                border.color: "#ff1f1f"
                width: 200
                height: 200
                Drag.active: dragArea.drag.active

                MouseArea {
                    id: dragArea
                    anchors.fill: parent
                    drag.target: parent
                    drag.minimumX: 0
                    drag.minimumY: 0
                    drag.maximumX: boundingSelectionTriangle.x + boundingSelectionTriangle.width - selectRect.width
                    drag.maximumY: boundingSelectionTriangle.y + boundingSelectionTriangle.height - selectRect.height
                }
            }

        }

    }

    Connections {
        target: openButton
        onClicked: {
            image.source = BackEnd.openImage()
            image.width = image.width
        }
    }

}

