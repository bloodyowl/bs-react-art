const path = require("path");

module.exports = {
  entry: {
    demo: "./lib/js/src/example.js"
  },
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: "[name].js"
  }
};
