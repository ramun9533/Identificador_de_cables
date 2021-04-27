
#include <WiFi.h>

//Configuración de red
const char* ssid     = "HUAWEI P20 lite";
const char* password = "55029eb60de0";

WiFiServer server(80); //Servidor web

const int LED2 = 19;// aprobado
const int LED1 = 18;// aprobado
const int LED8 = 5;// aprobado
const int LED7 = 4;// aprobado
const int LED6 = 3;// aprobado
const int LED5 = 2;// aprobado
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
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);

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
          //       client.println("<html lang="en"dir="ltr"> " );
          client.println(" <head> ");
          client.println("<link href='https://unpkg.com/tailwindcss@^2/dist/tailwind.min.css' rel='stylesheet'> ");

//   client.println(" <meta charset="utf-8">");
          client.println(" <title>Identificador</title>");
          client.println("</head>");
          client.println(" <body>");

          client.println("  </body>");
          client.println("</html>"); 
          
          
          client.println("<body style=\"background-color:#050200;\">"); //fondo negro
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1 style=\"width:500px;height:20px;color:#33285e;\">Mi programa serio esp32 </h1>"); // color de encabezado
       //   <p style=\"color:#6c757d\">LED #1 <a href=\"on1\"><button class="py-2 px-4 bg-Gray-500 text-white font-semibold rounded-lg shadow-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo-400 focus:ring-opacity-75">ON</button>
//  <p style=\"color:#14c923\">LED #1 <a href=\"on1\"><button class="py-2 px-4 bg-Gray-500 text-white font-semibold rounded-lg shadow-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo400 focus:ring-opacity-75">OFF</button>
          client.println("<p style=\"color:#6c757d\">LED #1 <a href=\"on1\"><button class="py-2 px-4 bg-Gray-500 text-white font-semibold rounded-lg shadow-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo-400 focus:ring-opacity-75">ON</button>");
          client.println("<p style=\"color:#6c757d\">LED #1 <a href=\"on1\"><button class="py-2 px-4 bg-Gray-500 text-white font-semibold rounded-lg shadow-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo-400 focus:ring-opacity-75">ON</button>");
          client.println("<p style=\"color:#6c757d\">LED #2 <a href=\"on2\"><button class="py-2 px-4 bg-Gray-500 text-white font-semibold rounded-lg shadow-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo-400 focus:ring-opacity-75">ON</button>");
          client.println("<p style=\"color:#6c757d\">LED #2 <a href=\"on2\"><button class="py-2 px-4 bg-Gray-500 text-white font-semibold rounded-lg shadow-md hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-indigo-400 focus:ring-opacity-75">ON</button>");
          
          client.println("<p style=\"color:#14c923\">LED #3 <a href=\"on3\"><button>ON</button></a>&nbsp;<a href=\"off3\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #5 <a href=\"on5\"><button>ON</button></a>&nbsp;<a href=\"off5\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #6 <a href=\"on6\"><button>ON</button></a>&nbsp;<a href=\"off6\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #7 <a href=\"on7\"><button>ON</button></a>&nbsp;<a href=\"off7\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#14c923\">LED #8 <a href=\"on8\"><button>ON</button></a>&nbsp;<a href=\"off8\"><button>OFF</button></a></p>");
          
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

            if (strstr(linebuf, "GET /on5") > 0) {
            Serial.println("LED 5 ON");
            digitalWrite(LED5, HIGH);
          }
          else if (strstr(linebuf, "GET /off5") > 0) {
            Serial.println("LED 5 OFF");
            digitalWrite(LED5, LOW);
          }

            if (strstr(linebuf, "GET /on6") > 0) {
            Serial.println("LED 6 ON");
            digitalWrite(LED6, HIGH);
          }
          else if (strstr(linebuf, "GET /off6") > 0) {
            Serial.println("LED 6 OFF");
            digitalWrite(LED6, LOW);
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
