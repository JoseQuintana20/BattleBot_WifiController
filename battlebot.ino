#include <WiFi.h>

// Configuración de la red WiFi en modo AP (Access Point)
const char* ssid = "Karonte";
const char* password = "123456789";

// Pines para los motores y relay
#define LEFT_ENA 13
#define LEFT_IN1 26
#define LEFT_IN2 14
#define RIGHT_ENA 33
#define RIGHT_IN1 23
#define RIGHT_IN2 21  // Pin para RIGHT_IN2 cambiado a 21
#define RELAY_PIN 18  // Pin para controlar el relay

// Pin del LED indicador
#define LED_INDICATOR 2  // Usaremos el pin D2 para el LED azul

// Configuración del servidor web en el puerto 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Configuración de los pines de los motores
  pinMode(LEFT_ENA, OUTPUT);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_ENA, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  
  // Configuración del pin del relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Comienza en estado desactivado (lógica inversa)

  // Configuración del pin del LED como salida
  pinMode(LED_INDICATOR, OUTPUT);
  digitalWrite(LED_INDICATOR, LOW);  // Apagar LED al inicio

  // Configuración de la ESP32 en modo AP (Access Point)
  Serial.println();
  Serial.println("Configurando punto de acceso...");
  WiFi.softAP(ssid, password);

  // Encender el LED indicador para señalar que la red está activa
  digitalWrite(LED_INDICATOR, HIGH);

  // Imprimir la dirección IP del punto de acceso
  Serial.print("Punto de acceso iniciado. Dirección IP: ");
  Serial.println(WiFi.softAPIP());

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor iniciado");
}

// Funciones de movimiento
void moveForward() {
  analogWrite(LEFT_ENA, 255);
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(RIGHT_ENA, 255);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}

void moveBackward() {
  analogWrite(LEFT_ENA, 255);
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  analogWrite(RIGHT_ENA, 255);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, HIGH);
}

void turnLeft() {
  analogWrite(LEFT_ENA, 255);
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  analogWrite(RIGHT_ENA, 255);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);
}

void turnRight() {
  analogWrite(LEFT_ENA, 255);
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(RIGHT_ENA, 255);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, HIGH);
}

void stopMotors() {
  analogWrite(LEFT_ENA, 0);
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(RIGHT_ENA, 0);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);
}

void loop() {
  // Espera un cliente que se conecte
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Espera hasta que el cliente envíe algunos datos
  Serial.println("Nuevo cliente conectado");
  while (!client.available()) {
    delay(1);
  }

  // Lee la solicitud del cliente
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Procesa la solicitud y ejecuta la acción correspondiente
  if (request.indexOf("/adelante_start") != -1) {
    moveForward();
  }
  if (request.indexOf("/atras_start") != -1) {
    moveBackward();
  }
  if (request.indexOf("/izquierda_start") != -1) {
    turnLeft();
  }
  if (request.indexOf("/derecha_start") != -1) {
    turnRight();
  }
  if (request.indexOf("/stop") != -1) {
    stopMotors();
  }
  if (request.indexOf("/relay_on") != -1) {
    digitalWrite(RELAY_PIN, LOW);  // Activa el relay (0 lógico)
  }
  if (request.indexOf("/relay_off") != -1) {
    digitalWrite(RELAY_PIN, HIGH);   // Desactiva el relay (1 lógico)
  }

  // Genera la página HTML de respuesta
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>Control de Auto BattleBot</title>");
  // Meta viewport para hacer que el diseño sea responsive
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<style>");
  client.println("body { display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; font-family: Arial, sans-serif; background-color: #f4f4f9; }");
  client.println(".container { text-align: center; width: 90%; max-width: 400px; padding: 20px; background: #ffffff; border-radius: 15px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2); }");
  client.println("h1 { font-size: 24px; margin: 0 0 20px; padding: 10px; background: #4CAF50; color: white; border-radius: 10px; box-shadow: inset 0 -2px 8px rgba(0, 0, 0, 0.2); }");
  client.println(".controls { display: grid; grid-template-columns: 1fr 1fr 1fr; grid-template-rows: 1fr 1fr 1fr; grid-gap: 10px; }");
  client.println(".button { aspect-ratio: 1 / 1; width: 100%; border-radius: 50%; background-color: #4CAF50; border: none; cursor: pointer; box-shadow: 0 4px 6px rgba(0, 0, 0, 0.2); transition: all 0.2s ease-in-out; }");
  client.println(".button:active { background-color: #45a049; transform: scale(0.95); }");
  client.println(".switch-label { display: block; font-size: 18px; font-weight: bold; margin-top: 20px; color: #333; }");
  client.println(".switch { width: 60px; height: 30px; position: relative; display: inline-block; }");
  client.println(".switch input { display: none; }");
  client.println(".slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: green; transition: .4s; border-radius: 15px; }"); // Desactivado (Verde)
  client.println(".slider:before { position: absolute; content: \"\"; height: 26px; width: 26px; left: 2px; bottom: 2px; background-color: white; transition: .4s; border-radius: 50%; }");
  client.println("input:checked + .slider { background-color: red; }"); // Activado (Rojo)
  client.println("input:checked + .slider:before { transform: translateX(28px); }");
  client.println("@media (max-width: 320px) { .button { height: 50px; } }");
  client.println("</style>");
  client.println("<script>");
  client.println("let intervalId;");
  client.println("function startCommand(command) {");
  client.println("  if (intervalId) clearInterval(intervalId);");
  client.println("  intervalId = setInterval(() => { fetch(command); }, 100);");
  client.println("}");
  client.println("function stopCommand() {");
  client.println("  if (intervalId) clearInterval(intervalId);");
  client.println("  intervalId = null;");
  client.println("  fetch('/stop');");
  client.println("}");
  client.println("function toggleRelay() {");
  client.println("  let relayState = document.getElementById('relaySwitch').checked;");
  client.println("  fetch(!relayState ? '/relay_on' : '/relay_off');");  // Invertimos el comando
  client.println("}");
  client.println("</script></head>");
  client.println("<body><div class=\"container\">");
  client.println("<h1>Control de Karonte</h1>");

  // Controles del carro en cruz
  client.println("<div class=\"controls\">");
  client.println("<div></div>");  // Espacio vacío
  client.println("<button class=\"button\" onmousedown=\"startCommand('/adelante_start')\" onmouseup=\"stopCommand()\" ontouchstart=\"startCommand('/adelante_start')\" ontouchend=\"stopCommand()\"></button>");  // Arriba
  client.println("<div></div>");  // Espacio vacío
  client.println("<button class=\"button\" onmousedown=\"startCommand('/izquierda_start')\" onmouseup=\"stopCommand()\" ontouchstart=\"startCommand('/izquierda_start')\" ontouchend=\"stopCommand()\"></button>");  // Izquierda
  client.println("<div></div>");  // Centro vacío
  client.println("<button class=\"button\" onmousedown=\"startCommand('/derecha_start')\" onmouseup=\"stopCommand()\" ontouchstart=\"startCommand('/derecha_start')\" ontouchend=\"stopCommand()\"></button>");  // Derecha
  client.println("<div></div>");  // Espacio vacío
  client.println("<button class=\"button\" onmousedown=\"startCommand('/atras_start')\" onmouseup=\"stopCommand()\" ontouchstart=\"startCommand('/atras_start')\" ontouchend=\"stopCommand()\"></button>");  // Abajo
  client.println("<div></div>");  // Espacio vacío
  client.println("</div>");

  // Interruptor para el relay
  client.println("<label class=\"switch-label\">Relay:</label>");
  client.println("<label class=\"switch\">");
  client.println("<input type=\"checkbox\" id=\"relaySwitch\" onchange=\"toggleRelay()\" checked>");  // Iniciar en activo
  client.println("<span class=\"slider\"></span>");
  client.println("</label>");

  client.println("</div></body></html>");

  delay(1);
  Serial.println("Cliente desconectado");
}