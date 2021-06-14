# for ... in

循环遍历对象自身的和继承的可枚举属性（不含 symbol 属性）

# Object.keys

返回一个数组，包含对象自身的（不含继承的）所有可枚举属性（不含 symbol 属性）

# Object.getOwnPropertyNames

返回一个数组，包含对象自身的所有属性（包含不可枚举属性，但是不包含 symbol 属性）

# Object.getOwnPropertySymbols

返回一个数组，包含对象自身的所有 Symbol 属性

# Reflect.ownKeys

返回一个数组，包含对象的所有属性，不管是否可枚举还是是否是 symbol 属性
