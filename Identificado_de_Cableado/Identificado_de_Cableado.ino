#include <WiFi.h>

//Configuración de red
const char* ssid     = "HUAWEI P20 lite";
const char* password = "55029eb60de0";
WiFiServer server(80); //Servidor web

const int LED2 = 19;// aprobado
const int LED1 = 18;// aprobado
const int LED7 = 5;// aprobado
const int LED6 = 4;// aprobado
const int LED5 = 3;// aprobado
const int LED4 = 2;// aprobado
const int LED3 = 0;// aprobado
//Variables Cliente
char linebuf[80];
int charcount = 0;

void setup() {
  //Inicializamos el puerto sere
  Serial.begin(115200);

  //Configuramos los pines como salida.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);

  Serial.printf("Conectando a: %s\n", ssid);

  WiFi.begin(ssid, password);

  // Intentamos que se conecte a la red wifi
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando...");
    delay(2000);
  }

  Serial.print("Conectado.  ");
  Serial.print(" Dirección IP del módulo: ");
  Serial.println(WiFi.localIP());

  server.begin(); //Iniciamos el servidor web.

}

void loop() {
  // Esperamos a que se conecte un cliente
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo Cliente");
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;
    // Una petición http termina con línea en blanco.
    boolean currentLineIsBlank = true;


    while (client.connected()) {  //Mientras que el cliente está conectado
      if (client.available()) {   //Si se recibe algun dato del cliente.
        char c = client.read();
        Serial.write(c);
        //Lee caracter por caracter la petición http
        linebuf[charcount] = c;
        if (charcount < sizeof(linebuf) - 1) charcount++;
        // si se recibe un caracter de nueva línea (/n) y la siguiente línea
        // es una líne en blanco entonces la petición http ha terminado y podemos
        // responder al cliente

        if (c == '\n' && currentLineIsBlank) {
          // enviar un encabezado de respuesta http estándar
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // la conexión se cerrará después de completar la respuesta
          client.println();
          const char *html = R"====(
HTTP/1.1 200 OK

Content-Type: text/html

Connection: close

<!DOCTYPE HTML><html><head>
  <html lang="es" dir="ltr">
  <head>
<link href="https://unpkg.com/tailwindcss@^1.0/dist/tailwind.min.css" rel="stylesheet">

  <title>Identificador</title>
  </head>
  <body style= "background-color:#415a77;background-image:url('https://raw.githubusercontent.com/ramun9533/Pagina-de-Presentacion/main/fonddo.png')";>

<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">

<h1 style=\"width:500px;height:20px;color:#33285e;\"> Mi programa serio esp32 </h1>

<div class="flex w-full h-full justify-center content-center items-center">

<table>
<tr>
<td><p> SALIDA #1  </p>
  <td><a href=/"on1"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
    <a href=/"off1"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
  <td><p>SALIDA #2 </p>
    <td><a href=/"on2"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white" >ON</button></a>&nbsp;
      <a href=/"off2"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
    </tr>
<tr>
</tr>

<tr>
<td><p>SALIDA#3 </p>
<td><a href=\"#on3\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
  <a href=\"#off3\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
<td><p>SALIDA #4 </p>
  <td><a href=\"#on4\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button>
  </a>&nbsp;<a href=\"#off4\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
</tr>

<tr>
<td><p> SALIDA #1  </p>
  <td><a href="\on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
    <a href="\off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
  <td><p>SALIDA #2 </p>
    <td><a href="\on2\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white" >ON</button></a>&nbsp;
      <a href="\off2\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
    </tr>
<tr>
</tr>

<tr>
<td><p>SALIDA#3 </p>
<td><a href="\on3\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
  <a href="\off3\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
<td><p>SALIDA #4 </p>
  <td><a href="\on4\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button>
  </a>&nbsp;<a href="\off4\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
</tr>

<tr>
<td><p> SALIDA #5  </p>
  <td><a href="\on5\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
    <a href="\off5\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
  <td><p>SALIDA #6 </p>
    <td><a href="\on6\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white" >ON</button></a>&nbsp;
      <a href="\off6\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
</tr>
<tr>
</tr>

<tr>
<td><p>SALIDA #7 </p>
<td><a href="/on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
  <a href=\"off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
<td><p>SALIDA #8 </p>
  <td><a href=\"on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button>
  </a>&nbsp;<a href=\"off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
</tr>

<tr>
<td><p> SALIDA #9  </p>
  <td><a href=\"on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
    <a href=\"off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
  <td><p>SALIDA #10 </p>
    <td><a href=\"on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white" >ON</button></a>&nbsp;
      <a href=\"off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>

</tr>
<tr>
</tr>
<tr>
<td><p>SALIDA #11 </p>
<td><a href=\"on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button></a>&nbsp;
  <a href=\"off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
<td><p>SALIDA #12 </p>
  <td><a href=\"on1\"><button class="rounded bg-green-500 hover:bg-green-700 py-2 px-4 text-white">ON</button>
  </a>&nbsp;<a href=\"off1\"><button class="rounded bg-red-500 hover:bg-red-700 py-2 px-4 text-white">OFF</button></a></td></td>
</tr>
</table>
</div>

</body>

</html>

)====";
client.println(html); //jalo la pagina html por medio de: const char *html = R"====( 
          
          break;
        }

        if (c == '\n') {
          // Empieza una nueva línea
          currentLineIsBlank = true;
          if (strstr(linebuf, "GET /on1") > 0) {
            Serial.println("LED 1 ON");
            digitalWrite(LED1, HIGH);
          }
          else if (strstr(linebuf, "GET /off1") > 0) {
            Serial.println("LED 1 OFF");
            digitalWrite(LED1, LOW);
          }
          else if (strstr(linebuf, "GET /on2") > 0) {
            Serial.println("LED 2 ON");
            digitalWrite(LED2, HIGH);
          }
          else if (strstr(linebuf, "GET /off2") > 0) {
            Serial.println("LED 2 OFF");
            digitalWrite(LED2, LOW);
          }
          if (strstr(linebuf, "GET /on3") > 0) {
            Serial.println("LED 3 ON");
            digitalWrite(LED3, HIGH);
          }
          else if (strstr(linebuf, "GET /off3") > 0) {
            Serial.println("LED 3 OFF");
            digitalWrite(LED3, LOW);
          }

          if (strstr(linebuf, "GET /on4") > 0) {
            Serial.println("LED 4 ON");
            digitalWrite(LED4, HIGH);
          }
          else if (strstr(linebuf, "GET /off4") > 0) {
            Serial.println("LED 4 OFF");
            digitalWrite(LED4, LOW);
          }

          if (strstr(linebuf, "GET /on5") > 0) {
            Serial.println("LED 5 ON");
            digitalWrite(LED5, HIGH);
          }
          else if (strstr(linebuf, "GET /off5") > 0) {
            Serial.println("LED 5 OFF");
            digitalWrite(LED5, LOW);                  //Verificar salidas a partir de aqui
          }

          else if (strstr(linebuf, "GET /on6") > 0) {
            Serial.println("LED 6 ON");
            digitalWrite(LED6, HIGH);
          }
          else if (strstr(linebuf, "GET /off6") > 0) {
            Serial.println("LED 6 OFF");
            digitalWrite(LED6, LOW);
          }

          // Empieza una nueva línea
          currentLineIsBlank = true;
          memset(linebuf, 0, sizeof(linebuf));
          charcount = 0;
        } else if (c != '\r') {
          // Todavía queda un caracter en la línea actual
          currentLineIsBlank = false;
        }
      }
    }

    delay(1);  // Esperamos un poco para que el navegador reciba los datos.

    // Cerramos la conexión con el cliente
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
