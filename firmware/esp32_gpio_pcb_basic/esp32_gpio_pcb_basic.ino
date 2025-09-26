/**
 * ESP32 GPIO PCB - Basic GPIO Control Example
 * 
 * This example demonstrates basic GPIO control functionality for the ESP32 GPIO PCB.
 * Features:
 * - Digital output control for 16 GPIO pins
 * - LED status indicators
 * - Serial command interface
 * - WiFi connectivity with web interface
 * 
 * Hardware:
 * - ESP32-WROOM-32 module
 * - 16 GPIO expansion pins
 * - Status LEDs
 * - USB-C programming interface
 * 
 * Author: ESP32 GPIO PCB Project
 * Version: 1.0
 * Date: 2024
 */

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// GPIO Pin Definitions
const int GPIO_PINS[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26};
const int NUM_GPIO_PINS = sizeof(GPIO_PINS) / sizeof(GPIO_PINS[0]);

// Status LED Pins
const int STATUS_LED_POWER = 27;
const int STATUS_LED_WIFI = 32;
const int STATUS_LED_ACTIVITY = 33;

// GPIO States
bool gpio_states[NUM_GPIO_PINS] = {false};

// WiFi Configuration
const char* ssid = "ESP32_GPIO_PCB";
const char* password = "gpio123456";

// Web Server
WebServer server(80);

// Function Prototypes
void setupGPIO();
void setupWiFi();
void setupWebServer();
void handleRoot();
void handleGPIOControl();
void handleGPIOStatus();
void handleNotFound();
void processSerialCommand();
void updateStatusLEDs();
void toggleGPIO(int pin, bool state);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("ESP32 GPIO PCB - Initializing...");
  
  // Initialize GPIO pins
  setupGPIO();
  
  // Initialize WiFi
  setupWiFi();
  
  // Initialize Web Server
  setupWebServer();
  
  Serial.println("System ready!");
  Serial.println("Commands:");
  Serial.println("  SET <pin> <state>  - Set GPIO pin state (pin: 0-15, state: 0/1)");
  Serial.println("  GET <pin>          - Get GPIO pin state");
  Serial.println("  STATUS             - Show all GPIO states");
  Serial.println("  RESET              - Reset all GPIOs to LOW");
  Serial.println();
}

void loop() {
  server.handleClient();
  processSerialCommand();
  updateStatusLEDs();
  delay(10);
}

void setupGPIO() {
  Serial.println("Initializing GPIO pins...");
  
  // Initialize status LEDs
  pinMode(STATUS_LED_POWER, OUTPUT);
  pinMode(STATUS_LED_WIFI, OUTPUT);
  pinMode(STATUS_LED_ACTIVITY, OUTPUT);
  
  digitalWrite(STATUS_LED_POWER, HIGH);  // Power LED always on
  digitalWrite(STATUS_LED_WIFI, LOW);
  digitalWrite(STATUS_LED_ACTIVITY, LOW);
  
  // Initialize GPIO pins
  for (int i = 0; i < NUM_GPIO_PINS; i++) {
    pinMode(GPIO_PINS[i], OUTPUT);
    digitalWrite(GPIO_PINS[i], LOW);
    gpio_states[i] = false;
  }
  
  Serial.printf("Initialized %d GPIO pins\n", NUM_GPIO_PINS);
}

void setupWiFi() {
  Serial.println("Setting up WiFi Access Point...");
  
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  
  Serial.println("WiFi Access Point created");
  Serial.printf("SSID: %s\n", ssid);
  Serial.printf("Password: %s\n", password);
  Serial.printf("IP Address: %s\n", IP.toString().c_str());
  
  digitalWrite(STATUS_LED_WIFI, HIGH);
}

void setupWebServer() {
  server.on("/", handleRoot);
  server.on("/gpio/control", HTTP_POST, handleGPIOControl);
  server.on("/gpio/status", HTTP_GET, handleGPIOStatus);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("Web server started on port 80");
}

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 GPIO PCB Control</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; background: #f0f0f0; }
        .container { max-width: 800px; margin: 0 auto; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        h1 { color: #333; text-align: center; }
        .gpio-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 10px; margin: 20px 0; }
        .gpio-item { padding: 15px; border: 1px solid #ddd; border-radius: 5px; text-align: center; }
        .gpio-on { background: #4CAF50; color: white; }
        .gpio-off { background: #f44336; color: white; }
        button { padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-size: 16px; }
        .btn-on { background: #4CAF50; color: white; }
        .btn-off { background: #f44336; color: white; }
        .status { margin: 10px 0; padding: 10px; background: #e7f3ff; border-left: 4px solid #2196F3; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 GPIO PCB Control Panel</h1>
        <div class="status">
            <strong>Status:</strong> Connected | <strong>Device:</strong> ESP32 GPIO PCB v1.0
        </div>
        <div class="gpio-grid" id="gpioGrid">
            <!-- GPIO controls will be loaded here -->
        </div>
        <div style="text-align: center; margin: 20px 0;">
            <button onclick="resetAll()" style="background: #ff9800; color: white;">Reset All</button>
            <button onclick="refreshStatus()" style="background: #2196F3; color: white;">Refresh</button>
        </div>
    </div>

    <script>
        function toggleGPIO(pin, currentState) {
            const newState = currentState ? 0 : 1;
            fetch('/gpio/control', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ pin: pin, state: newState })
            })
            .then(response => response.json())
            .then(data => {
                if (data.success) {
                    refreshStatus();
                } else {
                    alert('Error: ' + data.message);
                }
            });
        }

        function resetAll() {
            for (let i = 0; i < 16; i++) {
                fetch('/gpio/control', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ pin: i, state: 0 })
                });
            }
            setTimeout(refreshStatus, 500);
        }

        function refreshStatus() {
            fetch('/gpio/status')
            .then(response => response.json())
            .then(data => {
                const grid = document.getElementById('gpioGrid');
                grid.innerHTML = '';
                for (let i = 0; i < 16; i++) {
                    const state = data.states[i];
                    const item = document.createElement('div');
                    item.className = 'gpio-item ' + (state ? 'gpio-on' : 'gpio-off');
                    item.innerHTML = `
                        <h3>GPIO ${i}</h3>
                        <p>Pin: ${data.pins[i]}</p>
                        <p>State: ${state ? 'HIGH' : 'LOW'}</p>
                        <button onclick="toggleGPIO(${i}, ${state})" class="${state ? 'btn-off' : 'btn-on'}">
                            ${state ? 'Turn OFF' : 'Turn ON'}
                        </button>
                    `;
                    grid.appendChild(item);
                }
            });
        }

        // Load initial status
        refreshStatus();
        
        // Auto-refresh every 5 seconds
        setInterval(refreshStatus, 5000);
    </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleGPIOControl() {
  if (server.hasArg("plain")) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, server.arg("plain"));
    
    int pin = doc["pin"];
    int state = doc["state"];
    
    if (pin >= 0 && pin < NUM_GPIO_PINS) {
      toggleGPIO(pin, state == 1);
      server.send(200, "application/json", "{\"success\":true,\"message\":\"GPIO updated\"}");
      
      // Activity LED blink
      digitalWrite(STATUS_LED_ACTIVITY, HIGH);
      delay(50);
      digitalWrite(STATUS_LED_ACTIVITY, LOW);
    } else {
      server.send(400, "application/json", "{\"success\":false,\"message\":\"Invalid pin number\"}");
    }
  } else {
    server.send(400, "application/json", "{\"success\":false,\"message\":\"No data received\"}");
  }
}

void handleGPIOStatus() {
  DynamicJsonDocument doc(2048);
  JsonArray states = doc.createNestedArray("states");
  JsonArray pins = doc.createNestedArray("pins");
  
  for (int i = 0; i < NUM_GPIO_PINS; i++) {
    states.add(gpio_states[i]);
    pins.add(GPIO_PINS[i]);
  }
  
  String response;
  serializeJson(doc, response);
  server.send(200, "application/json", response);
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not Found");
}

void processSerialCommand() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase();
    
    if (command.startsWith("SET ")) {
      int firstSpace = command.indexOf(' ');
      int secondSpace = command.indexOf(' ', firstSpace + 1);
      
      if (firstSpace > 0 && secondSpace > 0) {
        int pin = command.substring(firstSpace + 1, secondSpace).toInt();
        int state = command.substring(secondSpace + 1).toInt();
        
        if (pin >= 0 && pin < NUM_GPIO_PINS) {
          toggleGPIO(pin, state == 1);
          Serial.printf("GPIO %d set to %s\n", pin, state ? "HIGH" : "LOW");
        } else {
          Serial.println("Error: Invalid pin number");
        }
      } else {
        Serial.println("Error: Invalid SET command format");
      }
    }
    else if (command.startsWith("GET ")) {
      int pin = command.substring(4).toInt();
      if (pin >= 0 && pin < NUM_GPIO_PINS) {
        Serial.printf("GPIO %d state: %s\n", pin, gpio_states[pin] ? "HIGH" : "LOW");
      } else {
        Serial.println("Error: Invalid pin number");
      }
    }
    else if (command == "STATUS") {
      Serial.println("GPIO Status:");
      for (int i = 0; i < NUM_GPIO_PINS; i++) {
        Serial.printf("  GPIO %2d (Pin %2d): %s\n", i, GPIO_PINS[i], gpio_states[i] ? "HIGH" : "LOW");
      }
    }
    else if (command == "RESET") {
      for (int i = 0; i < NUM_GPIO_PINS; i++) {
        toggleGPIO(i, false);
      }
      Serial.println("All GPIOs reset to LOW");
    }
    else {
      Serial.println("Unknown command");
    }
  }
}

void updateStatusLEDs() {
  // WiFi LED - blink if clients connected
  static unsigned long lastBlink = 0;
  static bool wifiLedState = false;
  
  if (WiFi.softAPgetStationNum() > 0) {
    if (millis() - lastBlink > 500) {
      wifiLedState = !wifiLedState;
      digitalWrite(STATUS_LED_WIFI, wifiLedState ? HIGH : LOW);
      lastBlink = millis();
    }
  } else {
    digitalWrite(STATUS_LED_WIFI, HIGH);
  }
}

void toggleGPIO(int pin, bool state) {
  if (pin >= 0 && pin < NUM_GPIO_PINS) {
    gpio_states[pin] = state;
    digitalWrite(GPIO_PINS[pin], state ? HIGH : LOW);
  }
}