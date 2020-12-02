#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>


// MAC address and IP address for this *particular* Ethernet Shield!
// MAC address is printed on the shield
// IP address is an available address you choose on your subnet where the switcher is also present:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };	
IPAddress ip(10, 1, 2, 34);				


// Include ATEM library and make an instance:
#include <ATEM.h>

// Connect to an ATEM switcher on this address and using this local port:
// The port number is chosen randomly among high numbers.
ATEM AtemSwitcher(IPAddress(10, 1, 2, 68), 51707); 



void setup() { 

    // Set up pins for 
  pinMode(7, INPUT);  // Cut
  pinMode(2, INPUT);  // Select 1 for Preview
  pinMode(3, INPUT);  // Select 2 for Preview
  pinMode(4, OUTPUT);  // LED: 1 is on Program (Tally)
  pinMode(5, OUTPUT);  // LED: 2 is on Program (Tally)
    
  // Start the Ethernet, Serial (debugging) and UDP:
  Ethernet.begin(mac,ip);
  Serial.begin(9600);  

  // Initialize a connection to the switcher:
  AtemSwitcher.serialOutput(true);
  AtemSwitcher.connect();
}


void loop() {
    // Check for packets, respond to them etc. Keeping the connection alive!
  AtemSwitcher.runLoop();
  


    // Write the Tally LEDS:
  digitalWrite(4, AtemSwitcher.getProgramTally(1));
  digitalWrite(5, AtemSwitcher.getProgramTally(2));


  
}
