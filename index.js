const testAddon = require('./build/Release/testaddon.node');

console.log("The square root is: " + testAddon.mysqrt(16));

module.exports = testAddon;