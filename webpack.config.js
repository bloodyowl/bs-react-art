const path = require('path');

module.exports = {
  entry: {
    demo: './lib/js/src/example.js',
  },
  resolve: {
    alias: {
      "react-art": "bloodyowl-react-art"
    },
  },
  output: {
    path: path.join(__dirname, 'bundledOutputs'),
    filename: '[name].js',
  },
};
