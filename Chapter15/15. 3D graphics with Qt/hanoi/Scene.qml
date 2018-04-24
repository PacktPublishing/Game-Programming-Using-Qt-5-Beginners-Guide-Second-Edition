import Qt3D.Core 2.10
import Qt3D.Render 2.10
import Qt3D.Input 2.0
import Qt3D.Extras 2.10
import QtQuick 2.10

Entity {
    id: sceneRoot
    property variant rods: []
    property variant sourceRod

    Entity {
        components: [
            DiffuseSpecularMaterial {
                id: foundationMaterial
                ambient: "#444"
            },
            CuboidMesh {},
            Transform {
                scale3D: Qt.vector3d(40, 1, 40)
            }
        ]
    }

    DiskAnimation { id: diskAnimation }
    SequentialAnimation {
        id: invalidModeAnimation
        ColorAnimation {
            target: foundationMaterial
            property: "ambient"
            to: "#a00"
            duration: 300
        }
        ColorAnimation {
            target: foundationMaterial
            property: "ambient"
            to: "#444"
            duration: 300
        }
    }
    Component.onCompleted: {
        // load components from other files
        var rodComponent = Qt.createComponent("Rod.qml");
        if(rodComponent.status !== Component.Ready) {
            console.log(rodComponent.errorString());
            return;
        }
        var diskComponent = Qt.createComponent("Disk.qml");
        if(diskComponent.status !== Component.Ready) {
            console.log(diskComponent.errorString());
            return;
        }

        var setupRod = function(i) {
            var rod = rodComponent.createObject(sceneRoot, { index: i });
            rod.clicked.connect(function() {
                rodClicked(rod);
            });
            return rod;
        }

        // create rods        
        for(var i = 0; i < 3; i++) {
            rods.push(setupRod(i));
        }
        var startingRod = rods[0];
        // create disks
        for(i = 0; i < 8; i++) {
            var disk = diskComponent.createObject(sceneRoot, { index: i });
            disk.pos = Qt.vector3d(startingRod.pos.x, 8 - i, startingRod.pos.z);
            startingRod.disks.unshift(disk);
        }

    }
    function rodClicked(rod) {
        if (diskAnimation.running) { return; }
        if (rod.isSourceRod) {
            rod.isSourceRod = false;
            sourceRod = null;
        } else if (!sourceRod) {
            if (rod.disks.length > 0) {
                rod.isSourceRod = true;
                sourceRod = rod;
            } else {
                console.log("no disks on this rod");
                invalidModeAnimation.start();
            }
        } else {
            var targetRod = rod;
            if (targetRod.disks.length > 0 &&
                targetRod.disks[targetRod.disks.length - 1].index <
                sourceRod.disks[sourceRod.disks.length - 1].index)
            {
                console.log("invalid move");
                invalidModeAnimation.start();
            } else {
                var disk = sourceRod.disks.pop();
                targetRod.disks.push(disk);
                diskAnimation.rod1Pos = sourceRod.pos;
                diskAnimation.rod2Pos = targetRod.pos;
                diskAnimation.startY = disk.pos.y;
                diskAnimation.finalY = targetRod.disks.length;
                diskAnimation.target = disk;
                diskAnimation.start();
            }
            sourceRod.isSourceRod = false;
            sourceRod = null;
        }
    }

}
