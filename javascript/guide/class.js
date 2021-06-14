/* eslint-disable max-classes-per-file */
class Base {
  constructor() {
    this.year = 2021;
  }
}

class Derived extends Base {
  constructor() {
    super();
    this.name = 'wang';
  }
}

const d1 = new Derived();
console.log(d1.name, d1.year);
