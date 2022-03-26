import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 6.2
import QtQuick3D

Window {
    id: window
    visible: true
    color: "#222222"
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button {
        id: button_pair_tracker
        y: 66
        width: 164
        height: 24
        text: qsTr("Pair Trackers")
        anchors.horizontalCenter: parent.horizontalCenter
        flat: false
        onClicked: _gui.buttonClicked()
    }

    View3D {
        id: view3D
        y: 110
        width: 355
        height: 331
        anchors.horizontalCenter: parent.horizontalCenter
        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
            }

            PerspectiveCamera {
                id: camera
                z: 350
            }

            Model {
                id: cylinder
                x: 0
                source: "#Cylinder"
                eulerRotation.z: _gui?.test.z ?? 0
                eulerRotation.y: _gui?.test.y ?? 0
                eulerRotation.x: _gui?.test.x ?? 0
                materials: cylinderMaterial
                DefaultMaterial {
                    id: cylinderMaterial
                    diffuseColor: "#4aee45"
                }
            }

            Skeleton {
                id: qmlskeleton
                Joint {
                    id: joint0
                    index: 0
                    skeletonRoot: qmlskeleton
                    Joint {
                        id: joint1
                        index: 1
                        skeletonRoot: qmlskeleton
                    }
                    Joint {
                        id: joint2
                        index: 2
                        skeletonRoot: qmlskeleton
                    }

                }
            }
        }
        environment: sceneEnvironment
    }
}
