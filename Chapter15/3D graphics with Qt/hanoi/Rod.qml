import Qt3D.Core 2.10
import Qt3D.Render 2.10
import Qt3D.Extras 2.10

Entity {
    id: rod
    property int index
    property bool isSourceRod: false
    readonly property alias pos: transform.translation
    property var disks: []
    signal clicked()

    components: [
        CylinderMesh {
            id: mesh
            radius: 0.5
            length: 9
            slices: 30
        },
        DiffuseSpecularMaterial {
            ambient: {
                if (isSourceRod) {
                    return picker.containsMouse? "#f44" : "#f11";
                } else {
                    return picker.containsMouse? "#484" : "#111";
                }
            }
        },
        Transform {
            id: transform
            translation: {
                var radius = 8;
                var step = 2 * Math.PI / 3;
                return Qt.vector3d(radius * Math.cos(index * step),
                                   mesh.length / 2 + 0.5,
                                   radius * Math.sin(index * step));

            }
        },
        ObjectPicker {
            id: picker
            hoverEnabled: true
            onClicked: rod.clicked()
        }
    ]

}
