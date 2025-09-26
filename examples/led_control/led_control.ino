/**
 * ESP32 GPIO PCB - LED Control Example
 * 
 * This example demonstrates basic LED control using the ESP32 GPIO PCB.
 * It creates a simple pattern of LED flashing across all 16 GPIO pins.
 * 
 * Features demonstrated:
 * - Sequential LED control
 * - Pattern generation
 * - Serial output for debugging
 * - WiFi status indication
 * 
 * Hardware Setup:
 * - Connect LEDs to GPIO pins D0-D15 with appropriate resistors
 * - Power the board via USB-C or DC jack
 * - Monitor serial output at 115200 baud
 * 
 * Author: ESP32 GPIO PCB Project
 * Version: 1.0
 */

// GPIO Pin definitions (matches PCB layout)
const int GPIO_PINS[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26};
const int NUM_PINS = 16;

// Status LED pins
const int STATUS_LED_POWER = 27;
const int STATUS_LED_WIFI = 32;
const int STATUS_LED_ACTIVITY = 33;

// Pattern control variables
int currentPin = 0;
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 200; // milliseconds

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("ESP32 GPIO PCB - LED Control Example");
  Serial.println("=====================================");
  
  // Initialize status LEDs
  pinMode(STATUS_LED_POWER, OUTPUT);
  pinMode(STATUS_LED_WIFI, OUTPUT);
  pinMode(STATUS_LED_ACTIVITY, OUTPUT);
  
  digitalWrite(STATUS_LED_POWER, HIGH);   // Power LED always on
  digitalWrite(STATUS_LED_WIFI, LOW);     // WiFi LED off (no WiFi in this example)
  digitalWrite(STATUS_LED_ACTIVITY, LOW); // Activity LED starts off
  
  // Initialize all GPIO pins as outputs
  Serial.println("Initializing GPIO pins...");
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(GPIO_PINS[i], OUTPUT);
    digitalWrite(GPIO_PINS[i], LOW);
    Serial.printf("GPIO %d (Pin %d) - initialized\n", i, GPIO_PINS[i]);
  }
  
  Serial.println("\nStarting LED pattern...");
  Serial.println("Pattern: Sequential chase from D0 to D15");
  Serial.println("Speed: 200ms per step");
  Serial.println();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Update LED pattern every UPDATE_INTERVAL milliseconds
  if (currentTime - lastUpdate >= UPDATE_INTERVAL) {
    // Turn off all LEDs
    for (int i = 0; i < NUM_PINS; i++) {
      digitalWrite(GPIO_PINS[i], LOW);
    }
    
    // Turn on current LED
    digitalWrite(GPIO_PINS[currentPin], HIGH);
    
    // Update activity LED
    digitalWrite(STATUS_LED_ACTIVITY, HIGH);
    
    // Print status
    Serial.printf("LED Pattern: D%d (GPIO%d) ON\n", currentPin, GPIO_PINS[currentPin]);
    
    // Move to next LED
    currentPin = (currentPin + 1) % NUM_PINS;
    
    // Update timing
    lastUpdate = currentTime;
    
    // Turn off activity LED after short delay
    delay(50);
    digitalWrite(STATUS_LED_ACTIVITY, LOW);
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
}

/**
 * Alternative patterns you can try:
 * 
 * 1. Bounce Pattern:
 * - LED bounces back and forth between D0 and D15
 * 
 * 2. Binary Counter:
 * - Display binary numbers on LEDs (D0 = bit 0, D15 = bit 15)
 * 
 * 3. Random Pattern:
 * - Turn random LEDs on/off
 * 
 * 4. Breathing Pattern:
 * - All LEDs fade in and out together (requires PWM)
 * 
 * 5. Two-Dot Chase:
 * - Two LEDs chase each other around the circle
 * 
 * To implement these patterns, modify the main loop logic above.
 */