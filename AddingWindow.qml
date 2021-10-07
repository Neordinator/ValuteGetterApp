import QtQuick
import QtQuick.Window
import QtQuick.Controls
import VG 0.1

Window {
    id: root
    minimumWidth: 360
    minimumHeight: 420
    color: "black"
    title: qsTr("Valute Getter")
    Component.onCompleted: {
        close()
    }
    ListModel {
        id: notAddedValutesModel
        function insertElement(currentIndex, charCode, name){
            insert(count, { "currentIndex": currentIndex, "charCode": charCode, "name": name })
        }
    }
    Connections {
        target: vG
        function onValuteChecked(currentIndex, charCode, name){
            notAddedValutesModel.insertElement(currentIndex, charCode, name)
        }
    }
    Component {
        id: notAddedComponent
        Button {
            width: 120
            height: 20 + notAddedComponentCharName.height
            Column {
                width: parent.width
                height: parent.height
                Text {
                    width: parent.width
                    id: notAddedComponentCharCode
                    text: qsTr(model.charCode)
                    color: "black"
                    horizontalAlignment: Text.AlignHCenter
                }
                Text {
                    width: parent.width
                    id: notAddedComponentCharName
                    text: qsTr(model.name)
                    color: "black"
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    horizontalAlignment: Text.AlignHCenter
                }
            }
            onClicked: {
                valuteModel.insert(valuteModel.count, {"currentIndex": currentIndex, "name": name, "charCode": charCode, "value": vG.countCourse(currentIndex)})
                vG.setIsAddedByIndex(currentIndex, true)
                notAddedValutesModel.clear()
                root.close()
            }
        }
    }
    Rectangle {
        id: notAddedValutesRect
        color: "black"
        x: 1
        y: 1
        width: root.width - 2
        height: root.height - 2
        GridView{
            id: notAddedValutesGrid
            x: 1
            y: 1
            anchors.margins: 10
            width: notAddedValutesRect.width - 2
            height: notAddedValutesRect.height - 22
            cellWidth: 120
            cellHeight: 60
            model: notAddedValutesModel
            delegate: notAddedComponent
        }
        Button {
            text: "Cancel"
            x: 1
            y: notAddedValutesGrid.height
            width: notAddedValutesRect.width - 2
            height: 20
            onClicked: {
                notAddedValutesModel.clear()
                root.close()
            }
        }
    }
}
