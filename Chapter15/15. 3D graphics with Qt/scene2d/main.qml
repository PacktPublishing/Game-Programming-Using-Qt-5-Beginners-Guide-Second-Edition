import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.10
import QtQuick 2.10
import QtQuick.Scene2D 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Entity {
    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                clearColor: "black"
                camera: Camera {
                    id: camera
                    projectionType: CameraLens.PerspectiveProjection
                    fieldOfView: 45
                    nearPlane : 0.1
                    farPlane : 1000.0
                    position: Qt.vector3d(0.0, 40.0, -40.0)
                    upVector: Qt.vector3d(0.0, 1.0, 0.0)
                    viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
                }
            }
            pickingSettings.pickMethod: PickingSettings.TrianglePicking
        },
        InputSettings {}
    ]

    FirstPersonCameraController {
        camera: camera
    }
    Entity {
        id: cube
        components: [
            CuboidMesh {},
            TextureMaterial {
                texture: texture
            },
            Transform {
                scale: 10
                rotationY: checkBox2.checked ? 45 : 0
            },
            ObjectPicker {
                hoverEnabled: true
                dragEnabled: true
            }
        ]
    }
    Entity {
        id: plane
        components: [
            PlaneMesh {
                mirrored: true
            },
            TextureMaterial {
                texture: texture
            },
            Transform {
                translation: checkBox3.checked ? Qt.vector3d(-20, 0, 0) : Qt.vector3d(20, 0, 0)
                scale: 10
                rotationX: 90
                rotationY: 180
                rotationZ: 0
            },
            ObjectPicker {
                hoverEnabled: true
                dragEnabled: true
            }

        ]
    }

    Scene2D {
        output: RenderTargetOutput {
            attachmentPoint: RenderTargetOutput.Color0
            texture: Texture2D {
                id: texture
                width: 200
                height: 200
                format: Texture.RGBA8_UNorm
            }
        }
        entities: [cube, plane]

        Rectangle {
            color: checkBox1.checked? "#ffa0a0" : "#a0a0ff"
            width: texture.width
            height: texture.height
            ColumnLayout {
                CheckBox {
                    id: checkBox1
                    text: "Toggle color"
                }
                CheckBox {
                    id: checkBox2
                    text: "Toggle cube"
                }
                CheckBox {
                    id: checkBox3
                    checked: true
                    text: "Toggle plane"
                }
            }
        }
    }



}

