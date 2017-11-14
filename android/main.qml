import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0

import QtQuick.Controls.Styles 1.4

import com.qPhotosAndroid.types 1.0
ApplicationWindow {

    id: applicationWindow
    visible: true
    width: 600
    height: 320
    color: "#212121"
    property alias image: image
    property var selection: undefined
    property bool on: false
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

            onClicked: {
                if (!selection) {
                    console.log("CROP")

                    selection = selectionComponent.createObject(boundingSelectionRect, {
                                                                    "x": boundingSelectionRect.width / 4,
                                                                    "y": boundingSelectionRect.height / 4,
                                                                    "width": boundingSelectionRect.width / 2,
                                                                    "height": boundingSelectionRect.width / 2})
                }
            }
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

        BusyIndicator{
            id: busyBackGround
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -70
            running: on
            // platformStyle: BusyIndicatorStyle { size: "large" }
            z:10
        }

        Pixmap {
            id: pixMap
        }

        ZoomableImage {
            id:image
            antialiasing: true
            source: pixMap.data

            anchors {
                fill: parent
                margins: 2
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            onStatusChanged: {
                if(image.status==Image.Ready)
                    on = false;
                else
                    on = true;
            }

        }

        Rectangle {
            id: boundingSelectionRect
            color: "#00ffffff"
            anchors.fill: parent
            width: parent.width
            height: parent.height
            x: parent.x
            y: parent.y
        }

        Component {
            id: selectionComponent

            Rectangle {
                id: selCompRect
                border {
                    width: 2
                    color: "lightslategray"
                }
                color: "#354682B4"

                property int rulersSize: 18

                MouseArea {
                    anchors.fill: parent
                    drag {
                        target: parent
                        minimumX: 0
                        minimumY: 0
                        maximumX: parent.parent.width - parent.width
                        maximumY: parent.parent.height - parent.height
                        smoothed: true
                    }
                }

                Rectangle {
                    //left resizer
                    width: rulersSize
                    height: rulersSize
                    radius: rulersSize
                    color: "lightslategray"
                    anchors.horizontalCenter: parent.left
                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea {
                        anchors.fill: parent
                        drag {target: parent; axis: Drag.XAxis}
                        onMouseXChanged: {
                            if (drag.active) {
                                if (selCompRect.x + mouseX >= boundingSelectionRect.x) {
                                    selCompRect.width = selCompRect.width - mouseX
                                    selCompRect.x = selCompRect.x + mouseX
                                    if (selCompRect.width < 30)
                                        selCompRect.width = 30
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    //right resizer
                    width: rulersSize
                    height: rulersSize
                    radius: rulersSize
                    color: "lightslategray"
                    anchors.horizontalCenter: parent.right
                    anchors.verticalCenter: parent.verticalCenter

                    MouseArea {
                        anchors.fill: parent
                        drag {target: parent; axis: Drag.XAxis}
                        onMouseXChanged: {
                            if (drag.active) {
                                if (selCompRect.x + selCompRect.width + mouseX <= boundingSelectionRect.x + boundingSelectionRect.width) {
                                    selCompRect.width = selCompRect.width + mouseX
                                    if (selCompRect.width < 30)
                                        selCompRect.width = 30
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    //Upper resizer
                    width: rulersSize
                    height: rulersSize
                    radius: rulersSize
                    x: parent.x / 2
                    y: 0
                    color: "lightslategray"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.top

                    MouseArea {
                        anchors.fill: parent
                        drag {target: parent; axis: Drag.YAxis}
                        onMouseYChanged: {
                            if (drag.active) {
                                if (selCompRect.y + mouseY >= boundingSelectionRect.y) {
                                    selCompRect.height = selCompRect.height - mouseY
                                    selCompRect.y = selCompRect.y + mouseY
                                    if (selCompRect.height < 30)
                                        selCompRect.height = 30
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    //bottom resizer
                    width: rulersSize
                    height: rulersSize
                    radius: rulersSize
                    x: parent.x / 2
                    y: parent.y
                    color: "lightslategray"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.bottom

                    MouseArea {
                        anchors.fill: parent
                        drag {target: parent; axis: Drag.YAxis}
                        onMouseYChanged: {
                            if (drag.active) {
                                if (selCompRect.y + selCompRect.height + mouseY <= boundingSelectionRect.y + boundingSelectionRect.height) {
                                    selCompRect.height = selCompRect.height + mouseY
                                    if (selCompRect.height < 30)
                                        selCompRect.height = 30
                                }
                            }
                        }
                    }
                }
            }
        }

    }

    Connections {
        target: openButton
        onClicked: {
            var s = BackEnd.openImage();
            if(s){
                pixMap.clear();
                pixMap.load(s);
                console.log("Image loaded!");
            }
        }
    }

}
