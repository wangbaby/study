const pm2 = require('pm2');

process.on('SIGINT', function () {
  console.log('---');
  pm2.killDaemon(function (err, data) {
    console.log(err, data);

    pm2.disconnect(function (err, data) {
      console.log(err, data);
      process.exit();
    });
  });
});

pm2.connect(function (err) {
  if (err) {
    console.error(err);
    process.exit(2);
  }

  pm2.start(
    {
      script: 'javascript/nodejs/third_library/pm2/app.js',
      instances: 4,
      exec_mode: 'cluster',
    },
    function (err, apps) {
      if (err) {
        console.error(err);
        return pm2.disconnect();
      }
    }
  );

  pm2.launchBus(function (err, pm2_bus) {
    pm2_bus.on('process:msg', function (packet) {
      console.log(packet);
    });
  });
});
