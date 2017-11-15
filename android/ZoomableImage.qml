import QtQuick 2.7

Flickable {
    id: flickable

    clip: true
    contentHeight: imageContainer.height
    contentWidth: imageContainer.width
    onHeightChanged: image.calculateSize()

    property alias source: image.source
    property alias status: image.status
    property alias progress: image.progress
    property alias paintedWidth: image.paintedWidth
    property alias paintedHeight: image.paintedHeight
    property alias sourceWidth: image.sourceSize.width
    property alias sourceHeight: image.sourceSize.height
    property alias containerWidth: imageContainer.width
    property alias containerHeight: imageContainer.height

    property real dragX: 0
    property real dragY: 0

    property string remoteSource: ''
    property string localSource: ''

    signal swipeLeft()
    signal swipeRight()
    signal imageClicked();

    Item {
        id: imageContainer
        width: Math.max(image.width * image.scale, flickable.width)
        height: Math.max(image.height * image.scale, flickable.height)

        Image {
            id: image
            property real prevScale
            smooth: !flickable.movingVertically
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            cache: false
            function calculateSize() {
                scale = Math.min(flickable.width / width, Math.min(flickable.height / height, pinchArea.lastScale)) * 0.98;
                pinchArea.minScale = scale;
                prevScale = Math.min(scale, 1);
                console.log(scale);
            }
            onScaleChanged: {
                if ((width * scale) > flickable.width) {
                    var xoff = (flickable.width / 2 + flickable.contentX) * scale / prevScale;
                    flickable.contentX = xoff - flickable.width / 2;
                }
                if ((height * scale) > flickable.height) {
                    var yoff = (flickable.height / 2 + flickable.contentY) * scale / prevScale;
                    flickable.contentY = yoff - flickable.height / 2;
                }
                prevScale = scale;
            }
            onStatusChanged: {
                if(image.status==Image.Ready){
                   //image.sourceChanged();
                   calculateSize();
                   image.rotation = 0;
                }
            }
        }
    }
    PinchArea {
        id: pinchArea
        property real minScale:  0.1
        property real lastScale: 1.0
        anchors.fill: parent
        pinch.target: image
        pinch.minimumRotation: -360
        pinch.maximumRotation: 360
        pinch.minimumScale: minScale
        pinch.maximumScale: 10
        onPinchFinished: flickable.returnToBounds()
        pinch.dragAxis: Pinch.XAndYAxis

        MouseArea {
            anchors.fill : parent
            scrollGestureEnabled: false
            property bool doubleClicked: false
            property bool swipeDone: false
            property int startX
            property int startY
            property real startScale: pinchArea.minScale
            Timer {
                id: clickTimer
                interval: 350
                running: false
                repeat:  false
                onTriggered: {
                    //                if (!parent.swipeDone) {
                    //                    showAlt = !showAlt
                    //                }
                    parent.swipeDone = false
                }
            }
            onDoubleClicked: {
                clickTimer.stop()
                mouse.accepted = true
                if (image.scale > pinchArea.minScale) {
                    image.scale = pinchArea.minScale
                    flickable.returnToBounds()
                } else {
                    image.scale = 2.0
                }
            }
            onClicked: {
                // There's a bug in Qt Components emitting a clicked signal
                // when a double click is done.
                clickTimer.start()
                imageClicked();
            }
            onPressed: {
                startX = (mouse.x / image.scale)
                startY = (mouse.y / image.scale)
                startScale = image.scale
            }
            onReleased: {
                if (image.scale === startScale) {
                    var deltaX = (mouse.x / image.scale) - startX
                    dragX += deltaX
                    var deltaY = (mouse.y / image.scale) - startY
                    dragY += deltaY
                    // Swipe is only allowed when we're not zoomed in
                    if (image.scale == pinchArea.minScale &&
                            (Math.abs(deltaX) > 50 || Math.abs(deltaY) > 50)) {
                        swipeDone = true
                        if (deltaX > 30) {
                            flickable.swipeRight()
                        } else if (deltaX < -30) {
                            flickable.swipeLeft()
                        }
                    }
                }
            }
        }
    }

}