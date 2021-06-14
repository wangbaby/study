function func(a, ...b) {
  console.log(a, b);
  console.log(arguments);
}

func(1, 2, 3);
