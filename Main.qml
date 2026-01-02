import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ScrollView {
        id: view
        anchors.fill: parent

        TextArea {
            id: txtarea

            width: 640
            height: 480
            text: qsTr("exit(1 * 3 - 6 / 2 + 2)")
        }
    }

    Rectangle {
        id: toolBar
        width: parent.width; height: 30
        anchors.bottom: parent.bottom
        color: "gray"

        Button {
            text: "Clear"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10

            onClicked: {
                txtarea.text = myBackend.deleteFile(txtarea.text);
                txtarea.readOnly = false
            }
        }

        Row {
            spacing: 10
            anchors.centerIn: parent
            Button {
                text: "Tokenize"
                onClicked: {
                    txtarea.text = myBackend.checkFile(txtarea.text);
                    var result = myBackend.tokens_str(txtarea.text)
                    txtarea.text = result
                    txtarea.readOnly = true
                }
            }
            Button {
                text: "Parse"
                onClicked: {
                    txtarea.text = myBackend.checkFile(txtarea.text);
                    var result = myBackend.parse_str(txtarea.text)
                    txtarea.text = result
                    txtarea.readOnly = true;
                }
            }
            Button {
                text: "Asembly"
                onClicked: {
                    txtarea.text = myBackend.checkFile(txtarea.text);
                    var result = myBackend.assemble_str(txtarea.text)
                    txtarea.text = result
                    txtarea.readOnly = true;
                }
            }
        }

    }
}

