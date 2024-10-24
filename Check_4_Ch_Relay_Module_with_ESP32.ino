// ESP32 4-Channel Relay Module Test
// Pins for relay control
const int RELAY_1 = 26;  // Connect relay IN1 to GPIO26
const int RELAY_2 = 27;  // Connect relay IN2 to GPIO27
const int RELAY_3 = 14;  // Connect relay IN3 to GPIO14
const int RELAY_4 = 12;  // Connect relay IN4 to GPIO12

// Array to store relay pins for easier iteration
const int relayPins[] = {RELAY_1, RELAY_2, RELAY_3, RELAY_4};
const int NUM_RELAYS = 4;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Relay Test Starting...");
  
  // Initialize all relay pins as outputs
  for(int i = 0; i < NUM_RELAYS; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);  // Start with relays OFF (HIGH for active LOW relay modules)
  }
  
  delay(1000);  // Initial delay for stability
}

void loop() {
  // Test 1: Sequential relay activation
  Serial.println("\nTest 1: Sequential Relay Activation");
  sequentialTest();
  
  // Test 2: All relays on/off
  Serial.println("\nTest 2: All Relays On/Off");
  allRelayTest();
  
  // Test 3: Binary counter pattern
  Serial.println("\nTest 3: Binary Counter Pattern");
  binaryCounterTest();
  
  delay(5000);  // Wait before starting next test cycle
}

// Function to test relays one at a time
void sequentialTest() {
  for(int i = 0; i < NUM_RELAYS; i++) {
    Serial.print("Activating Relay ");
    Serial.println(i + 1);
    
    digitalWrite(relayPins[i], LOW);   // Turn ON
    delay(1000);
    digitalWrite(relayPins[i], HIGH);  // Turn OFF
    delay(500);
  }
}

// Function to test all relays simultaneously
void allRelayTest() {
  Serial.println("All relays ON");
  for(int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relayPins[i], LOW);
  }
  delay(2000);
  
  Serial.println("All relays OFF");
  for(int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relayPins[i], HIGH);
  }
  delay(1000);
}

// Function to create binary counting pattern with relays
void binaryCounterTest() {
  for(int counter = 0; counter < 16; counter++) {
    for(int relay = 0; relay < NUM_RELAYS; relay++) {
      bool relayState = bitRead(counter, relay);
      digitalWrite(relayPins[relay], !relayState);  // Inverse logic for active LOW
    }
    delay(1000);
  }
  
  // Turn all relays off after test
  for(int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relayPins[i], HIGH);
  }
}
