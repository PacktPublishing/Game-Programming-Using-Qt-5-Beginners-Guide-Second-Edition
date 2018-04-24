import Qt3D.Core 2.10
import Qt3D.Render 2.10
import Qt3D.Extras 2.10

Entity {
    property int index
    property alias pos: transform.translation
    components: [
        DiffuseSpecularMaterial {
            ambient: Qt.hsla(index / 8, 1, 0.5)
        },

        Mesh {
            source: "qrc:/obj/disk" + index + ".obj"
        },
        Transform {
            id: transform
        }

/* to use torus mesh instead of obj files, replace Mesh and Transform
   component with the following code:

        TorusMesh {
            minorRadius: 1.1
            radius: 2.5 + 1 * index
            rings: 80
        },
        Transform {
            id: transform
            rotationX: 90
            scale: 0.45
        }*/
    ]
}

