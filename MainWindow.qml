import QtQuick
import QtQuick.Window
import QtQuick.Controls
import VG 0.1

ApplicationWindow  {
    id: root
    minimumWidth: 360
    minimumHeight: 420
    visible: true
    title: qsTr("Valute Getter")
    ValuteGetter {
        id: vG
    }
    Connections {
        target: vG
        function onDigitsGlobalCompare(){
            vG.setUserNominal(nominalValue.storedDouble)
        }
    }
    Column {
        id: nominalInfo
        x: 1
        width: 150//root.width / 2 - 2
        height:  + nominalName.height

        Text {
            id: nominalName
            text: qsTr("Российский Рубль")
            color: "black"
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            horizontalAlignment: Text.AlignHCenter
        }
        Row {
            width: parent.width
            Text {
                id: nominalCharCode
                text: qsTr("RUR")
                font.pixelSize: 16
                color: "black"
                horizontalAlignment: Text.AlignHCenter
            }
            ToolSeparator {
                spacing: 5
            }
            TextField {
                id: nominalValue
                text: qsTr("100.00")
                font.pixelSize: 14
                color: "black"
                horizontalAlignment: Text.AlignHCenter
                validator: RegularExpressionValidator { regularExpression: /^\d*\.{0,1}\d+$/ }// { regularExpression: /^-?\d*\.{0,1}\d+$/ }

                property double storedDouble

                Component.onCompleted: {
                    storedDouble = parseFloat(text.toString())
                }
                onTextChanged: {
                    vG.setUserNominal(storedDouble)
                }
                onTextEdited: {
                    storedDouble = parseFloat(text.toString())
                }
            }
        }
    }
    ListModel {
        id: valuteModel
        /*ListElement { currentIndex: 5, charCode: BYN, name: "Белорусский Рубль" }*/
    }
    Component {
        id: valuteInfo
        Column {
            x: 1
            width: listView.width - 2 //root.width / 2 - 2
            Connections {
                target: vG
                function onDigitsCompare(){
                    nominalValue.text = qsTr(vG.countCourse(currentIndex))
                }
            }
            Text {
                id: nominalName
                width: parent.width
                text: qsTr(model.name)
                color: "black"
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                horizontalAlignment: Text.AlignHCenter
            }
            Row {
                width: parent.width
                Text {
                    id: nominalValue
                    text: qsTr(value.toString())
                    font.pixelSize: 16
                    color: "black"
                    horizontalAlignment: Text.AlignJustify
                    //validator: RegularExpressionValidator { regularExpression: /^-?\d*\.{0,1}\d+$/ }
                }
                ToolSeparator {
                    spacing: 5
                }
                Text {
                    id: nominalCharCode
                    text: qsTr(model.charCode)
                    font.pixelSize: 16
                    color: "black"
                    horizontalAlignment: Text.AlignRight
                }
                ToolSeparator {
                    spacing: 5
                }
                Button {
                    text: "Remove"
                    x: parent.width - width
                    onClicked: {
                        vG.setIsAddedByIndex(currentIndex, false)
                        valuteModel.remove(index)
                    }
                }
            }
        }
    }
    ScrollView {
        id: scrollView
        x: nominalInfo.width + 2
        width: root.width - x - 1
        height: root.height - 22
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AsNeeded
        ListView {
            id: listView
            model: valuteModel
            delegate: valuteInfo
        }
    }
    AddingWindow{
        id: addingWindow
    }
    Button {
        text: "Add"
        x: scrollView.x
        y: scrollView.height
        onClicked: {
            vG.constructNotAddedValutesGrid()
            addingWindow.show()
        }
    }
}
