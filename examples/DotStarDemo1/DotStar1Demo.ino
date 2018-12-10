/*------------------------------------------------------------------------
  Particle library to control Adafruit DotStar addressable RGB LEDs.

  Ported by gary@dcity.org for Particle Photon, Electron, Argon, Boron and Xenon
  version:
    1.0.0 - 12/9/2018 Original Release.

  Ported by Technobly for Spark Core, Particle Photon, P1, Electron,
  and RedBear Duo.

  ------------------------------------------------------------------------
  -- original header follows ---------------------------------------------
  ------------------------------------------------------------------------

 * Simple strand test for Adafruit Dot Star RGB LED strip.
 * This is a basic diagnostic tool, NOT a graphics demo...helps confirm
 * correct wiring and tests each pixel's ability to display red, green
 * and blue and to forward data down the line.  By limiting the number
 * and color of LEDs, it's reasonably safe to power a couple meters off
 * the VIN pin.  DON'T try that with other code!
 */

/* ======================= includes ================================= */


#include "dotstar1.h"

#define NUMPIXELS 72 // Number of LEDs in strip... 72 is used on the Adafruit DotStar Wing

//-------------------------------------------------------------------
// NOTE: If you find that the colors you choose are not correct,
// there is an optional 2nd argument (for HW SPI) and
// 4th arg. (for SW SPI) that you may specify to correct the colors.
//-------------------------------------------------------------------
// e.g. Adafruit_DotStar(NUMPIXELS, DOTSTAR_RGB);
// e.g. Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_RGB);
//
// DOTSTAR_RGB
// DOTSTAR_RBG
// DOTSTAR_GRB
// DOTSTAR_GBR (default)
// DOTSTAR_BRG
// DOTSTAR_BGR

//-------------------------------------------------------------------
// Here's how to control the LEDs from any two pins (Software SPI):
//-------------------------------------------------------------------
#define DATAPIN   D6
#define CLOCKPIN  D8
// Comment out the next line if using hardware SPI pins... leave uncommented if bit-banging the SPI
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

//-------------------------------------------------------------------
// Here's how to control the LEDs from SPI pins (Hardware SPI):
//-------------------------------------------------------------------
// Hardware SPI is a little faster, but must be wired to specific pins
// Core/Photon/P1/Electron = pin A5 for data, A3 for clock
// Argon/Boron/Xenon = pin MO for data, SCK for clock
// Comment out the next line if software bit banging SPI pins... leave uncommented if using the hardware the SPI
// Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS,DOTSTAR_BGR);

void setup() {
  strip.begin(); // Initialize pins for output
  strip.setBrightness(50);    // 0-255
  strip.show();  // Turn all LEDs off ASAP
}

// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)

void loop() {

  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(10);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

}
