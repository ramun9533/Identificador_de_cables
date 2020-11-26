
#include <WiFi.h>

//Configuración de red
const char* ssid     = "HUAWEI P20 lite";
const char* password = "55029eb60de0";

WiFiServer server(80); //Servidor web

int Led[24] = {1, 2, 3, 4, 5, 6, 7 , };
int CantidadLed = 24;
char linebuf[80];
int charcount = 0;

void setup() {
  //Inicializamos el puerto sere
  Serial.begin(115200);

  for (int i = 0; i < CantidadLed; i++) {
    pinMode(Led[i], OUTPUT);
  }


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

          for (int i = 0; i < CantidadLed; i++) {

            Serial.print("< p style = \"color:#14c923\">LED #")
            Serial.print(i + 1);
            Serial.print("<a href=\"on");
            Serial.print(i + 1);
            Serial.print("\"><button>ON</button></a>&nbsp;<a href=\"off");
            Serial.print(i + 1);
            Serial.print("\"><button>OFF</button></a></p>");

          }


          client.println("</html>");
          break;
        }

        if (c == '\n') {
          // Empieza una nueva línea
          currentLineIsBlank = true;

          String TextoBaseOn = "GET /on";
          String TextoBaseOff = "GET /off";
          for (int i = 0; i < CantidadLed; i++) {
            String TextoOn = TextoBaseOn + i;
            String TextoOff = TextoBaseOff + i;
            if (strstr(linebuf, TextoOn) > 0) {
              Serial.print("LED ");
              Serial.print(i);
              Serial.print(" ON");
              digitalWrite(Led[i], HIGH);
            } else if (strstr(linebuf, TextoOff) > 0) {
              Serial.print("LED ");
              Serial.print(i);
              Serial.print(" OFF");
              digitalWrite(Led[i], LOW);
            }
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
