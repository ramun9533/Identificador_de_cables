
const char* ssid_1     = "xxxx";
const char* password_1 = "xxxx";
const char* ssid_2     = "ZTE Blade A5 2020";
const char* password_2 = "ac0a96172796";

const String Pagina =  R"====(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Botón con CSS</title>
<head>
  <h1 id="main-container">ESP32</h1>

  <style  >
    body{
 background-color:#415a77;
      /* background-color: #436C94; */
      font-family: Arial;
    }
    #main-container{
      padding-top: 20px;
      text-align: center;
    }

    .btn{
      border-radius: 35px;
      display: inline-block;
      padding: 20px 15px;
      text-decoration: none;
      text-shadow: 0 1px 0 rgba(255,255,255,0.3);
      box-shadow: 0 1px 1px rgba(0,0,0,0.3);
    }

    .btn-green{
      color: white;
      background-color: #3CC93F;
    }
    .btn-green:hover{
      background-color: #ffffff;
    }
    .btn-green:active{
      background-color: #29962A;
    }

    .btn-red{
      color: white;
      background-color: #E34242;
    }
    .btn-red:hover{
      background-color: #C43535;
    }
    .btn-red:active{
      background-color: #A62828;
    }
    #tabla{
    margin: auto;
}
#tabla1{
    margin: auto;
}
  
  :root {
  --main-bg-color: #422261;
  --face: #422261;
}

* {
  border: 5px solid red;
  margin: 0px;
  padding: 0px;
  box-sizing: border-box;
}

body {
  display: flex; 
  justify-content: center;
  align-items: center;
  height: 100vh;
  background-color: var(--main-bg-color);
}
.pumpkin {
  position: relative;
  height: 300px;
  width: 170px;
  background-color: #f8931f;
  border-radius: 28% 72% 33% 67% / 21% 83% 17% 79% ;
  transform: rotate(13deg);
  box-shadow:
    -80px 5px 0px -2px #f8931f,   /*BS 1*/
    -40px 4px 0px -1px #fbb03b,   /*BS 2*/
    40px -15px 0px  0px #f87700,  /*BS 3*/
    80px -35px 0px -2px #f8931f;  /*BS 4*/

}
.stem {
  position: relative;
  bottom: 180px;
  background-color: #8cc63e;
  left: 210px;
  z-index: -1;
  width: 75px;
  height: 150px;
  transform: rotate(30deg);
  border-radius: 58% 42% 69% 31% / 44% 100% 0% 56% ;
}
.stem::before {
  content: '';
  border: 20px solid red;
  position: absolute;
  top: 0px;
  left: 50px;
  width: 100px;
  height: 100px;
  background-color: var(--main-bg-color);
  clip-path: circle(50% at 50% 50%);
}
.face {
  width: 75px;
  height: 30px;
  background-color: var(--face);
  position: relative;
  left: 60px;
  bottom: 40px;
  transform: rotate(10deg);
  z-index: 1;
  border-radius: 
    100% 0% 50% 50% / 0% 0% 100% 100%;
}
.face::after {
  content: '';
  position: absolute;
  background-color: var(--face);
  top: -25px;
  left: 120px;
  width: 75px;
  height: 30px;
  transform: rotate(-20deg);
  border-radius: 
    100% 0% 50% 50% / 0% 0% 100% 100%;
}
.face::before {
  content: '';
  position: absolute;
  top: 75px;
  left: 15px;
  background-color: var(--face);
  transform: rotate(-10deg);
  width: 200px;
  height: 50px;
  clip-path: polygon(0% 35%, 17% 2%, 21% 37%, 31% 17%, 36% 32%, 49% 6%, 63% 34%, 86% 8%, 85% 30%, 100% 30%, 94% 60%, 79% 98%, 66% 62%, 63% 94%, 53% 76%, 42% 100%, 31% 62%, 17% 96%, 14% 66%);
}
  * {
border: 1px solid red;
}
.face::before {
  animation-name: pulse;
  animation-duration: 1.5s;
  animation-iteration-count: infinite;
}
@keyframes pulse {
  0% {transform: scale(1) rotate(-10deg);}
  50% {transform: scale(1.1) rotate(-10deg);}
  100% {transform: scale(1) rotate(-10deg);}
}

  </style>
</head>
<body  style= "background-color:#415a77;>
  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
  <h1  id="table1" align="center"> Mi programa serio esp32 </h1>
  
  
  
  <div >
  <table id="tabla" >
  <tr>
  <td><p> SALIDA #1  </p>
    <td><a  href="on1" class="btn btn-green" style ="color:#000000";>ON</button></a>&nbsp;
    <a  href="off1" class="btn btn-red" style ="color:#000000";>OFF</button></a></td></td>
    <td><p>SALIDA #2 </p>
    <td><a href="#" class="btn btn-green" style ="color:#000000"; >ON</button></a>&nbsp;
      <a href="#" class="btn btn-red" style ="color:#000000";>OFF</button></a></td></td>
    </tr>
   </table>
   </div>
  <div class="stem"></div>
<div class="face"></div>
<div class="pumpkin"></div>

  


</body>
</html>
)====";
