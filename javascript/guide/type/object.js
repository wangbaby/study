/**
 * Object
 */

// Object.keys
{
  const obj = {
    a: 1,
    b: 2,
    [Symbol('obj')]: 'obj',
  };

  console.log(Object.keys(obj));

  // Object.getOwnPropertyNames

  console.log(Object.getOwnPropertyNames(obj));

  // Object.getOwnPropertySymbols

  console.log(Object.getOwnPropertySymbols(obj));
}

/**
 * Object.prototype
 */

console.log(Object.getOwnPropertyNames(Object.prototype));

// hasOwnProperty
function Base() {}

Object.assign(Base.prototype, {
  a: 1,
});

console.log(Object.getOwnPropertyNames(Base.prototype));

function Derived() {
  this.b = 2;
}

Derived.prototype.__proto__ = Base.prototype;
{
  const obj = new Derived();
  for (const key in obj) {
    console.log(obj[key]);
  }

  for (const key in obj) {
    if (obj.hasOwnProperty(key)) {
      console.log(key, obj[key]);
    }
  }
}
