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

        //        Label {
        //            id: imgLabel
        //            x: 246
        //            y: 94
        //            text: qsTr("")
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            anchors.verticalCenter: parent.verticalCenter
        //        }
        PinchArea {
            id: pinchArea
            anchors.fill: parent
            pinch.target: image
            pinch.minimumRotation: -360
            pinch.maximumRotation: 360
            pinch.minimumScale: 0.1
            pinch.maximumScale: 10
            pinch.dragAxis: Pinch.XAndYAxis
            ScrollView {
                anchors.fill: parent
                Image {
                    id: image
                    source: ""
                    antialiasing: true
                    fillMode: Image.PreserveAspectFit

                    transform: Translate { y: transformY*visibleImg.scale; x: transformX*visibleImg.scale }
                    //                            anchors {
                    //                                fill: parent
                    //                                margins: 2
                    //                                horizontalCenter: parent.horizontalCenter
                    //                                verticalCenter: parent.verticalCenter
                    //                            }

                }
            }


            //            Rectangle {
            //                id: borderRect
            //                color: "#2D2D2D"
            //                clip: true
            //                anchors {
            //                    fill: parent
            //                    margins: 2
            //                }


            //            }
        }

        DropArea {
//            property int prevX: 0
//            property int prevY: 0
            anchors.fill: parent
//            entered: {
//                prevX = selectRect.x
//                prevY = selectRect.y
//            }


//            positionChanged: {
//                var deltaX = selectRect.x - prevX;
//                selectRect.x += deltaX;
//                prevX = selectRect.x - deltaX;

//                var deltaY = selectRect.y - prevY;
//                selectRect.y += deltaY;
//                prevY = selectRect.y - deltaY;
//            }

            Rectangle {
                id: selectRect
                color: "#00ffffff"
                anchors.fill: parent
                border.color: "#ff1f1f"
//                Drag.YAxis
            }
        }
    }
    Connections {
        target: openButton
        onClicked: image.source = BackEnd.openImage()
    }

    //    Rectangle {
    //        id: cropArea
    //        color: "#05f5f5f5"
    //        anchors.bottom: parent.bottom
    //        anchors.bottomMargin: 35
    //        anchors.top: parent.top
    //        anchors.topMargin: 85
    //        anchors.left: parent.left
    //        anchors.leftMargin: 200
    //        anchors.right: parent.right
    //        anchors.rightMargin: 200
    //        visible: true
    //        border.color: "#bdbdbd"
    //    }


}
