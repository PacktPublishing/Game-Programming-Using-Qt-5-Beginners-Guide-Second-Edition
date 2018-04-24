{
    "init": function() {
        console.log("init!");
        // example of using killed signal
        field.entities().forEach(function(entity) {
            entity.killed.connect(function() {
               console.log("entity was killed!", entity.team(), entity.pos());
            });
        });
    },
    "step": function(current) {
        // helper function that returns the square of the distance
        // between pos1 and pos2
        function sq_distance(pos1, pos2) {
            return Math.pow(pos1.x - pos2.x, 2) +
                   Math.pow(pos1.y - pos2.y, 2);
        }
        // helper function that clamps value to [min, max] interval
        function clamp(value, min, max) {
          if (value < min) {
            return min;
          }
          if (value > max) {
            return max;
          }
          return value;
        }
        var currentPos = current.pos();
        var chosenPos;
        var closestAllyPos;
        // search for an enemy to kill and for the closest ally
        field.entities().forEach(function(entity) {
            if (entity === current) {
                return; // skip self
            }
            var pos = entity.pos();
            if (entity.team() === current.team()) {
                // search for closest ally
                if (!closestAllyPos || sq_distance(currentPos, pos) <
                                       sq_distance(currentPos, closestAllyPos)) {
                    closestAllyPos = pos;
                }
            } else {
                // check if we can kill an enemy
                var dx = Math.abs(pos.x - currentPos.x);
                var dy = Math.abs(pos.y - currentPos.y);
                if (dx < 2 && dy < 2) {
                    chosenPos = entity.pos();
                }
            }
        });

        if (chosenPos) {
            // we found an entity to kill
            return chosenPos;
        } else if (closestAllyPos) {
            // move away from the closest ally
            var x = currentPos.x + Math.sign(currentPos.x - closestAllyPos.x);
            var y = currentPos.y + Math.sign(currentPos.y - closestAllyPos.y);
            return {
                x: clamp(x, 0, field.size().width - 1),
                y: clamp(y, 0, field.size().height - 1)
            };
        } else {
            // no allies :(
            return currentPos;
        }
    }
}
