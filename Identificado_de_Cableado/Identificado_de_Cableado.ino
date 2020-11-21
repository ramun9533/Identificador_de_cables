
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
const int LED2 = 19;  
const int LED1 = 18;
const int LED16 = 17;  
const int LED15 = 16;
const int LED14 = 15;  
const int LED13 = 14;
const int LED12 = 13;  
const int LED11 = 12;
const int LED10 = 10;  
const int LED9 = 9;
const int LED8 = 5;  
const int LED7 = 4;
const int LED6 = 3;  
const int LED5 = 2;
const int LED4 = 1;  
const int LED3 = 0;
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
          // enviar un encabezado de respuesta http estándar
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // la conexión se cerrará después de completar la respuesta
          client.println();
          client.println("<!DOCTYPE HTML><html><head>");
          client.println("<body style=\"background-color:#aa4c00;\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1 style=\"width:500px;height:20px;color:#ffffff;\">Mi programa serio esp32 </h1>");
          client.println("<p style=\"color:#ffffff\">LED #1 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p style=\"color:#ffffff\">LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
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
