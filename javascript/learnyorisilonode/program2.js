// learn you node
// console.log(process.argv);

var a = process.argv;

var strnums = a.slice(2, a.length);

var nums = strnums.map(function(n){
  return Number(n);
});


var sum = function(arr){
  var sum = 0;
  arr.forEach(function(elm){
    sum = sum + elm;
  });
  return sum;
};

console.log(sum(nums));
