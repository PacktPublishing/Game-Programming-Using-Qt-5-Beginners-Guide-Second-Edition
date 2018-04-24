.import "collisions.js" as Collisions

var coins = []

coins.collisionsWith = function(player) {
  var collisions = []
  for(var index = 0; index < coins.length; ++index) {
    var obj = this[index]
    if(Collisions.intersect(player, obj)) collisions.push(obj)
  }
  return collisions
}

coins.remove = function(obj) {
  var arr = Array.isArray(obj) ? obj : [ obj ]
  var L = arr.length
  var idx, needle
  while(L && this.length) {
    needle = arr[--L]
    idx = this.indexOf(needle)
    if(idx !== -1) { this.splice(idx, 1) }
  }
  return this
}
