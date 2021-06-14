const _ = require('lodash');
let enemy = {
  // enemy health
  health: {
    current: 80,
    max: [1, 2, 3],
    healRate: {
      active: false,
      perTick: 5,
    },
  },

  // index values of targets
  targets: [2, 6, 8],
};

// can get plain old object properties like this
console.log(_.get(enemy, 'health.healRate.active')); // false
_.set(enemy, 'health.healRate.active', true);
console.log(_.get(enemy, 'health.healRate.active')); // false

// if it is an array I can and element get like this
// if I know the index
console.log(_.get(enemy, 'targets[2]')); // 8

// or like this
console.log(_.get(enemy, 'targets.2')); // 8

// default
console.log(
  _.get(enemy, 'health.healRate.overTime', {
    amount: 0,
    ticks: 0,
  })
); // {amount:0,ticks:0}
