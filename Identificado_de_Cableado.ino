
#include <WiFi.h>

//Configuración de red
const char* ssid     = "RED_TUTOELECTRO";
const char* password = "tutoelectro123";

WiFiServer server(80); //Servidor web

const int LED1 = 18;  //Pines de cada LED
const int LED2 = 19;

//Variables Cliente
char linebuf[80];
int charcount=0;

void setup() {
  //Inicializamos el puerto sere
  Serial.begin(115200);

  //Configuramos los pines como salida.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  
 Serial.printf("Conectando a: %s\n", ssid);
 
  WiFi.begin(ssid, password);
  
  // Intentamos que se conecte a la red wifi
  while(WiFi.status() != WL_CONNECTED) {
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
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    // Una petición http termina con línea en blanco.
    boolean currentLineIsBlank = true;

    
    while (client.connected()) {  //Mientras que el cliente está conectado
      if (client.available()) {   //Si se recibe algun dato del cliente.
        char c = client.read();
        Serial.write(c);  
        //Lee caracter por caracter la petición http
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        // si se recibe un caracter de nueva línea (/n) y la siguiente línea 
        // es una líne en blanco entonces la petición http ha terminado y podemos
        // responder al cliente
       
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML><html><head>");
          client.println("<body style=\"background-color:#324851;\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1 style=\"width:500px;height:20px;color:#86ac41;\">Tutorial Web Server ESP32 </h1>");
          client.println("<p style="color:#7da3a1">LED #1 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style="color:#7da3a1">LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("</html>");
          break;
        }
        
        if (c == '\n') {
          // Empieza una nueva línea
          currentLineIsBlank = true;
          if (strstr(linebuf,"GET /on1") > 0){
            Serial.println("LED 1 ON");
            digitalWrite(LED1, HIGH);
          }
          else if (strstr(linebuf,"GET /off1") > 0){
            Serial.println("LED 1 OFF");
            digitalWrite(LED1, LOW);
          }
          else if (strstr(linebuf,"GET /on2") > 0){
            Serial.println("LED 2 ON");
            digitalWrite(LED2, HIGH);
          }
          else if (strstr(linebuf,"GET /off2") > 0){
            Serial.println("LED 2 OFF");
            digitalWrite(LED2, LOW);
          }
          // Empieza una nueva línea
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
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
