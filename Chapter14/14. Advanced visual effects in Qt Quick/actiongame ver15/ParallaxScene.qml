import QtQuick 2.9

Item {
  id: root
  property int currentPos
  x: -currentPos*(root.width - root.parent.width)/width
}

