/**
 * Created by anurag on 29/3/17.
 */
var addon = require('./build/Release/myAddon.node');

console.log(addon.sayHelloWorld());
console.log(addon.add(3,5));
console.log(addon.sortNode([8,1,5,25,4,85]));