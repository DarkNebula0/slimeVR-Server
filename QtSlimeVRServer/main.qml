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
        y: 59
        width: 164
        height: 24
        text: qsTr("Pair Trackers")
        anchors.horizontalCenterOffset: -183
        anchors.horizontalCenter: parent.horizontalCenter
        flat: false
        onClicked: _gui.pairTracker()
    }

    Button {
        id: button_connect_bridge
        y: 100
        width: 164
        height: 24
        text: qsTr("Connect to bridge")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -183
        enabled: (_gui?.nBridgeState ?? 0) !== 1
        flat: false
        onClicked: _gui.connectToBridge()
    }

    Text {
        id: text1
        x: 324
        y: 51
        color: "#ffffff"
        text: qsTr("Bridge Status:")
        font.pixelSize: 12
    }

    Text {
        id: text_bridge_state
        x: 409
        y: 51
        color: "#ffffff"
        text: [qsTr("Disconnected"), qsTr("Connected"), qsTr("Error")][_gui?.nBridgeState ?? 0]
        font.pixelSize: 12
    }

    View3D {
        id: view3D
        y: 206
        width: 281
        height: 255
        anchors.horizontalCenterOffset: 1
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
                    id: hmd
                    index: 0
                    skeletonRoot: qmlskeleton

                    Joint {
                        id: head

                        Joint {
                            id: neck

                            Joint {
                                id: chest

                                Joint {
                                    id: waist

                                    Joint {
                                        id: hip

                                        Joint {
                                            id: leftHip

                                            Joint {
                                                id: leftKnee

                                                Joint {
                                                    id: leftAnkle

                                                    Joint {
                                                        id: leftFoot

                                                        Joint {
                                                            id: leftFootTracker
                                                        }
                                                    }
                                                }

                                                Joint {
                                                    id: leftKneeTracker
                                                }
                                            }
                                        }

                                        Joint {
                                            id: rightHip

                                            Joint {
                                                id: rightKnee

                                                Joint {
                                                    id: rightAnkle

                                                    Joint {
                                                        id: rightFoot

                                                        Joint {
                                                            id: rightFootTracker
                                                        }
                                                    }
                                                }

                                                Joint {
                                                    id: rightKneeTracker
                                                }
                                            }
                                        }

                                        Joint {
                                            id: waistTracker
                                        }
                                    }
                                }

                                Joint {
                                    id: chestTracker
                                }
                            }
                        }
                    }

                }

                Joint {
                    id: leftHand

                    Joint {
                        id: leftWrist

                        Joint {
                            id: leftElbow

                            Joint {
                                id: leftElbowTracker
                            }
                        }
                    }
                }

                Joint {
                    id: rightHand
                    Joint {
                        id: rightWrist
                        Joint {
                            id: rightElbow

                            Joint {
                                id: rightElbowTracker
                            }
                        }
                    }
                }
            }
        }
        environment: sceneEnvironment
    }
}
