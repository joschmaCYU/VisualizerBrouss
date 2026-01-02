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
            text: qsTr("// This is a comment\nint x = 1 * 3 - 6 / 2 + 2\nstring str = \"Hello World!\"\n\nwhile(x) {\n  print(str)\n  x = x - 1\n}\n\nif (x) {\n  exit(20)\n} elif (1) {\n  exit(1)\n} else {\n  exit(0)\n}")
        }
    }

    Rectangle {
        id: toolBar
        width: parent.width; height: 30
        anchors.bottom: parent.bottom
        color: "gray"

        Row {
            spacing: 10
            anchors.centerIn: parent
            Button {
                text: "Tokenize"
                onClicked: {
                    var result = myBackend.tokens_str(txtarea.text)
                    txtarea.text = result
                }
            }
            Button {
                text: "Parse"
                onClicked: {
                    var result = myBackend.parse_str(txtarea.text)
                    txtarea.text = result
                }
            }
            Button {
                text: "Asembly"
                onClicked: {
                    var result = myBackend.assemble_str(txtarea.text)
                    txtarea.text = result
                }
            }
        }

    }
}

