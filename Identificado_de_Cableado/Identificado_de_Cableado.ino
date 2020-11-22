
#include <WiFi.h>

//Configuración de red
const char* ssid     = "HUAWEI P20 lite";
const char* password = "55029eb60de0";

WiFiServer server(80); //Servidor web

const int LED24 = 33;
const int LED23 = 32;
const int LED22 = 27;
const int LED21 = 26;
const int LED20 = 25;
const int LED19 = 23;
const int LED18 = 22;
const int LED17 = 21;
const int LED2 = 19;// aprobado
const int LED1 = 18;// aprobado
const int LED16 = 17;
const int LED15 = 16;
const int LED14 = 15;
const int LED13 = 14;// problemas, espejea el GPIO 18
const int LED12 = 13; // problemas, espejea el GPIO 18
const int LED11 = 12; // problemas, espejea el GPIO 18
const int LED10 = 10; // problemas de conexion, posiblemente sea de comunicacion
const int LED9 = 9; // problemas de conexion, posiblemente sea de comunicacion
const int LED8 = 5;// aprobado
const int LED7 = 4;// aprobado
const int LED6 = 3;// aprobado
const int LED5 = 2;// aprobado
//const int LED4 = 1; // problemas de conexion, posiblemente sea de comunicacion
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
  //pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LED11, OUTPUT);
  pinMode(LED12, OUTPUT);
  pinMode(LED13, OUTPUT);
  pinMode(LED14, OUTPUT);
  pinMode(LED15, OUTPUT);
  pinMode(LED16, OUTPUT);
  pinMode(LED17, OUTPUT);
  pinMode(LED18, OUTPUT);
  pinMode(LED19, OUTPUT);
  pinMode(LED20, OUTPUT);
  pinMode(LED21, OUTPUT);
  pinMode(LED22, OUTPUT);
  pinMode(LED23, OUTPUT);
  pinMode(LED24, OUTPUT);


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
          client.println("<!DOCTYPE HTML><html><head>");
          client.println("<body style=\"background-color:#050200;\">"); //fondo negro
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1 style=\"width:500px;height:20px;color:#33285e;\">Mi programa serio esp32 </h1>"); // color de encabezado
          client.println("<p style=\"color:#14c923\">LED #1 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #3 <a href=\"on3\"><button>ON</button></a>&nbsp;<a href=\"off3\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #4 <a href=\"on4\"><button>ON</button></a>&nbsp;<a href=\"off4\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #5 <a href=\"on5\"><button>ON</button></a>&nbsp;<a href=\"off5\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #6 <a href=\"on6\"><button>ON</button></a>&nbsp;<a href=\"off6\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #7 <a href=\"on7\"><button>ON</button></a>&nbsp;<a href=\"off7\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #8 <a href=\"on8\"><button>ON</button></a>&nbsp;<a href=\"off8\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #9 <a href=\"on9\"><button>ON</button></a>&nbsp;<a href=\"off9\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #10 <a href=\"on10\"><button>ON</button></a>&nbsp;<a href=\"off10\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #11 <a href=\"on11\"><button>ON</button></a>&nbsp;<a href=\"off11\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #12 <a href=\"on12\"><button>ON</button></a>&nbsp;<a href=\"off12\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #13 <a href=\"on13\"><button>ON</button></a>&nbsp;<a href=\"off13\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #14 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #15 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #16 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #17 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #18 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #19 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #20 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #21 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #22 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #23 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #24 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          
          
          
          client.println("</html>");
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
          else if (strstr(linebuf, "GET /on7") > 0) {
            Serial.println("LED 7 ON");
            digitalWrite(LED7, HIGH);
          }
          else if (strstr(linebuf, "GET /off7") > 0) {
            Serial.println("LED 7 OFF");
            digitalWrite(LED7, LOW);
          }
          
          
          else if (strstr(linebuf, "GET /on8") > 0) { //GPIO5
            Serial.println("LED 8 ON");
            digitalWrite(LED8, HIGH);
          }
          else if (strstr(linebuf, "GET /off8") > 0) {
            Serial.println("LED 8 OFF");
            digitalWrite(LED8, LOW);
          }
          
          
          else if (strstr(linebuf, "GET /on13") > 0) { //GPIO14
            Serial.println("LED 13 ON");
            digitalWrite(LED13, HIGH);
          }
          else if (strstr(linebuf, "GET /off13") > 0) {
            Serial.println("LED 13 OFF");
            digitalWrite(LED13, LOW);
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
