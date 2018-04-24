{
    "step": function(current) {
        // helper function to get random integer in [min, max)
        function getRandomInt(min, max) {
          return Math.floor(Math.random() * (max - min)) + min;
        }
        // select a random move
        return {
            x: current.pos().x + getRandomInt(-1, 2),
            y: current.pos().y + getRandomInt(-1, 2),
        }
    }
}
