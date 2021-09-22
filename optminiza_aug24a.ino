
#include <WiFi.h>

//Configuración de red
const char* ssid     = "*****";
const char* password = "******";

WiFiServer server(80); //Servidor web

#define LED1  18  //Pines de cada LED
#define LED2  19
#define LED7  5// aprobado
#define LED6  4// aprobado
#define LED5  3// aprobado
#define LED4  2// aprobado
#define LED3  0// aprobado
int i;
//Variables Cliente
char linebuf[80]; //aparta ochenta caracteres para la variable linebuf
int charcount=0; //se inicializa contador "charcount"en cero

void setup() {
  //Inicializamos el puerto serie
  Serial.begin(115200);

  //Configuramos los pines como salida.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  
 Serial.printf("Conectando a: %s\n", ssid); //lee el string (cadena de char) de la variable "ssid"
 
  WiFi.begin(ssid, password);
  
  // Intentamos que se conecte a la red wifi
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando...");
    delay(2000);    //espera 2 segundos
  }
  Serial.print("Conectado.  ");
  Serial.print(" Dirección IP del módulo: ");
  Serial.println(WiFi.localIP()); //imprime por puerto serial que IP tiene el dispositivo
  
  server.begin(); //Iniciamos el servidor web.
}
void loop() {
  // Esperamos a que se conecte un cliente
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nuevo Cliente");
    memset(linebuf,0,sizeof(linebuf)); //memset se encarga de llenar los espacios que le sobran a la variable "linebuf" con "0"
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
        // si se recibe un caracter de nueva línea (/n) y la siguiente línea  (se refier a "\" de "<a href=\"on") ?
        // es una líne en blanco entonces la petición http ha terminado y podemos
        // responder al cliente
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header,enviar un encabezado de respuesta http estándar
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response/ la conexión se cerrará después de completar la respuesta
          client.println();
          //client.println("<!DOCTYPE HTML><html><head>");
          //client.println("<body style=\"background-color:#0066aa;\">");
          //client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          //client.println("<h1 style=\"width:500px;height:20px;color:#ffffff;\">Tutorial Web Server ESP32 </h1>");
          //client.println();
          const char *html = R"====(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
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
			"display: inline-block";
			padding: 20px 15px;
			text-decoration: none;
			text-shadow: 0 1px 0 rgba(255,255,255,0.3);
			box-shadow: 0 1px 1px rgba(0,0,0,0.3);
		}

		.btn-green{
			/*color: white;*/
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
		"#tabla"{
    "margin: auto;"
}

	</style>
</head>
<body>
    <header>Identificador ESP32 V1.2</header>
    <td>)====";
client.println(html);
         // for(int i=1;i<=12;i++) //secuancia de impresion de botones
         // {
           client.println(" <p> SALIDA ");
          client.println(i);
          client.println ("</p></a>");
          client.println ("<a href=/on"" class=""btn btn-green");
          client.println(i);
          client.println("\"><button>ON</button></a><a href=/off"" class=""btn btn-red");
          client.println(i);
          client.println("\"><button>OFF</button></a></p>");
       
         // }
          client.println("</html>");
          break;
        }
        
        if (c == '\n') {
          // Empieza una nueva línea
          currentLineIsBlank = true;
         
          
          if (strstr(linebuf,"GET /on1") > 0){ //GET es una delas opciones en que html envia datos al servidor, en este caso el server es el esp32
            
            
            Serial.println("LED 1 ON");
            
            
            digitalWrite(LED1, HIGH); //enciende el LED1
          
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
