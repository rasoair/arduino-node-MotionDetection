const serialport = require("serialport");
const readline = require("@serialport/parser-readline");

let sp = new serialport.SerialPort({
  path : '/dev/cu.usbmodemXXXXX', //この表記はmacの場合。適宜自分のポート名に置き換えてください
  baudRate : 115200,
  parser : new readline.ReadlineParser({delimiter : "¥n"})
});

sp.on("open",() => {
  console.log("Serial Open");
})

sp.on("data", (input) => {
  let buffer = new Buffer.from(input,"utf8");
  let jsonData;
  try{
    jsonData = JSON.parse(buffer);
    if(jsonData.isDetected == 1){
      console.log("動きを検出したよ！");
    }else if(jsonData.isDetected == 0){
      console.log("監視中だよ！");
    }
  }catch(e){
    console.error();
    return;
  }
});