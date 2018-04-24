.pragma library

function boundingBox(object1) {
    var cR = object1.childrenRect
    var mapped = object1.mapToItem(object1.parent, cR.x, cR.y,
                                   cR.width, cR.height)
    return Qt.rect(mapped.x, mapped.y, mapped.width, mapped.height)
}

function intersect(object1, object2) {
    var r1 = boundingBox(object1)
    var r2 = boundingBox(object2)
    return (r1.x <= r2.x+r2.width &&   // r1.left <= r2.right
            r2.x <= r1.x+r1.width &&   // r2.left <= r1.right
            r1.y <= r2.y+r2.height &&  // r1.top <= r2.bottom
            r2.y <= r1.y+r1.height)    // r2.top <= r1.bottom
}
