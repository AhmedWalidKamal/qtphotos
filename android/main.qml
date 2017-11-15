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
    color: "#757575"

    property var selection: undefined
    property alias image: image
    property bool on: false

    function flipCropVisibility(enab) {
        homeButton.enabled = enab
        homeButton.visible = enab
        resetButton.enabled = enab
        resetButton.visible = enab
        doneButton.enabled = enab
        doneButton.visible = enab
        rotLeftButton.enabled = enab
        rotLeftButton.visible = enab
        rotRightButton.enabled = enab
        rotRightButton.visible = enab
        cropButton.enabled = enab
        cropButton.visible = enab
        doneCropButton.enabled = !enab
        doneCropButton.visible = !enab
        cancelCropButton.enabled = !enab
        cancelCropButton.visible = !enab
    }

    StackView {
        id: stack
        initialItem: homeView
        anchors.fill: parent
    }

    Item {
        id: homeView

        Pane {
            id: homePane
            anchors.fill: parent
            background: Image {
                id: backgroundImg
                anchors.fill: parent
                source: "icons/background.jpg"
            }
            ToolButton {
                id: openGalleryButton
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 100
                Image {
                    id: openGalleryImg
                    source: "icons/open.png"
                    width: 64
                    height: 64
                }
            }
        }
    }

    Item {
        id: mainView


        ToolBar {
            id: upperToolBar
            height: 50
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            background: Rectangle {color: "#00FFFFFF"}

            ToolButton {
                id: doneButton
                x: 552
                y: 10
                text: qsTr("")
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5

                Image {
                    id: doneImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/done.png"
                }

                onClicked: {
                    pixMap.save()
                    stack.pop()
                }
            }

            ToolButton {
                id: homeButton
                x: 0
                y: 10
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5

                Image {
                    id: homeImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/home.png"
                }

                onClicked: stack.pop()
            }

            ToolButton {
                id: resetButton
                x: 0
                text: qsTr("")
                anchors.top: parent.top
                anchors.topMargin: 5
                anchors.left: homeButton.right
                anchors.leftMargin: 0

                Image {
                    id: resetImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/reset.png"
                }

                onClicked: {
                    pixMap.reset()
                }
            }
        }

        Pane {
            id: pane
            anchors.top: upperToolBar.bottom
            anchors.topMargin: 20
            anchors.bottom: bottomToolBar.top
            anchors.bottomMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 25
            anchors.left: parent.left
            anchors.leftMargin: 25
            background: Rectangle {color: "#424242"}

            BusyIndicator {
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
                id: image
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
                        color: "#00A6F9"
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
                        color: "#00A6F9"
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
                        color: "#00A6F9"
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
                        color: "#00A6F9"
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
                        color: "#00A6F9"
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

        ToolBar {
            id: bottomToolBar
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 0
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            background: Rectangle {color: "#424242"}

            ToolButton {
                id: rotLeftButton
                y: 10
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - this.width) / 2 - this.width
                anchors.top: parent.top

                Image {
                    id: rotLeftImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/rotLeft.png"
                }

                onClicked: {

                }
            }

            ToolButton {
                id: cropButton
                y: 10
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - this.width) / 2
                anchors.top: parent.top

                Image {
                    id: cropImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/crop.png"
                }

                onClicked: {
                    if (!selection) {
                        console.log("CROP!")
                        selection = selectionComponent.createObject(boundingSelectionRect, {
                                                                "x": boundingSelectionRect.width / 4,
                                                                "y": boundingSelectionRect.height / 4,
                                                                "width": boundingSelectionRect.width / 2,
                                                                "height": boundingSelectionRect.height / 2})
                        flipCropVisibility(false)
                    }
                }
            }

            ToolButton {
                id: rotRightButton
                y: 10
                text: qsTr("")
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - this.width) / 2 + this.width
                anchors.top: parent.top

                Image {
                    id: rotRightImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/rotRight.png"
                }

                onClicked: {

                }
            }

            ToolButton {
                id: doneCropButton
                y: 10
                enabled: false
                visible: false
                text: qsTr("")
                anchors.left: parent.left
                anchors.top: parent.top

                Image {
                    id: doneCropImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/done.png"
                }

                onClicked: {
                    var imgHeight = image.sourceHeight * image.imgScale
                    var imgWidth = image.sourceWidth * image.imgScale

                    var cropX = selection.x * image.sourceWidth / imgWidth
                    var cropWidth = selection.width * image.sourceWidth / imgWidth

                    var marginY = (boundingSelectionRect.height - imgHeight) / 2

                    var cropY = (selection.y - marginY) * image.sourceHeight / imgWidth
                    var cropHeight = selection.height * image.sourceHeight / imgWidth

                    pixMap.crop(cropX, cropY, cropWidth, cropHeight)

                    selection.destroy()
                    flipCropVisibility(true)
                }
            }

            ToolButton {
                id: cancelCropButton
                y: 10
                enabled: false
                visible: false
                text: qsTr("")
                anchors.right: parent.right
                anchors.top: parent.top

                Image {
                    id: cancelCropImage
                    height: 32
                    width: 32
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "icons/cancel.png"
                }


                onClicked: {
                    selection.destroy()
                    flipCropVisibility(true)
                }
            }


        }


        Connections {
            target: openGalleryButton
            onClicked: {
                var s = BackEnd.openImage();
                if(s){
                    pixMap.clear();
                    pixMap.load(s);
                    console.log("Image loaded!");
                }
                stack.push(mainView)
            }
        }
    }
}
