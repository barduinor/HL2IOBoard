// This is firmware for the Hermes Lite 2 IO board designed by Jim Ahlstrom, N2ADR. It is
//   Copyright (c) 2022-2023 James C. Ahlstrom <jahlstr@gmail.com>.
//   It is licensed under the MIT license. See MIT.txt.

// This firmware outputs the FT817 band voltage on J4 pin 8 and sets the band.

#include "../hl2ioboard.h"
#include "../i2c_registers.h"

// These are the major and minor version numbers for firmware. You must set these.
uint8_t firmware_version_major=1;
uint8_t firmware_version_minor=3;

int main()
{
	static uint8_t current_tx_fcode = 0;
	static bool current_is_rx = true;
	static uint8_t tx_band = 0;
	static uint8_t rx_band = 0;
	// uint8_t band, fcode;
	bool is_rx;
	// bool change_band;
	uint8_t i;

	stdio_init_all();
	configure_pins(false, true);
	configure_led_flasher();

	while (1) {	// Wait for something to happen
		sleep_ms(1);	// This sets the polling frequency.


		// Poll for a changed Tx band, Rx band and T/R change
		is_rx = gpio_get(GPIO13_EXTTR);		// true for receive, false for transmit
		if (current_is_rx != is_rx) {
			current_is_rx = is_rx;

			// Update TX state on GPIO10_Out5
			if (current_is_rx) {
				gpio_put(GPIO10_Out5, 0);
			} else {
				gpio_put(GPIO10_Out5, 1);
				}
		}

		// Poll for a changed Tx frequency. The new_tx_fcode is set in the I2C handler.
		if (current_tx_fcode != new_tx_fcode) {
			current_tx_fcode = new_tx_fcode;
			tx_band = fcode2band(current_tx_fcode);		// Convert the frequency code to a band code.
			xiegu_band_volts(tx_band); // Put the band voltage on J4 pin 8.
		}

		// Poll for a change in one of the twelve Rx frequencies. The rx_freq_changed is set in the I2C handler.
		if (rx_freq_changed) {
			rx_freq_changed = false;
			if (rx_freq_high == 0)
				rx_band = tx_band;
			else
				rx_band = fcode2band(rx_freq_high);	// Convert the frequency code to a band code.

			xiegu_band_volts(rx_band);
		}

	}
}

