document.querySelector('#msg').innerHTML = '<h1>Hello, World</h1>';

const run = (f,g,h) => {
  return (x) => {
    return h(g(f(x)));
  };
};

const printMessage = run(addToDom('msg'), h1, echo);

printMessage('Hello World');


[0,1,2,3,4,5,6,7,8,9,10].map((num) => Math.pow(num, 2));
