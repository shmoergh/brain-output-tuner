#include <pico/stdlib.h>
#include <stdio.h>

#include "brain-common/brain-common.h"
#include "brain-io/audio-cv-out.h"
#include "brain-ui/button.h"
#include "brain-ui/leds.h"

using brain::io::AudioCvOut;
using brain::io::AudioCvOutChannel;
using brain::ui::Leds;

int main() {
	stdio_init_all();

	int voltage = 0;
	AudioCvOut g_dac;
	Leds leds;

	brain::ui::Button buttonDown = brain::ui::Button(BRAIN_BUTTON_1, 50, 500);
	brain::ui::Button buttonUp = brain::ui::Button(BRAIN_BUTTON_2, 50, 500);
	buttonDown.init();
	buttonUp.init();

	sleep_ms(1000);

	// Reset all LEDs to off
	printf("Resetting all LEDs to OFF\n");
	leds.init();
	leds.off_all();
	sleep_ms(200);

	// Setup button callbacks
	buttonDown.set_on_release([&]() {
		int nextVoltage = voltage - 1;
		if (nextVoltage < 0) {
			nextVoltage = 10;
		}
		voltage = nextVoltage;
	});

	buttonUp.set_on_release([&]() {
		int nextVoltage = voltage + 1;
		if (nextVoltage > 10) {
			nextVoltage = 0;
		}
		voltage = nextVoltage;
	});

	// Init DAC
	if (!g_dac.init()) {
		printf("DAC init failed\n");
	}

	// Set DC coupling on both outputs
	printf("Setting DC coupling on both outputs\n");
	g_dac.set_coupling(
		brain::io::AudioCvOutChannel::kChannelA, brain::io::AudioCvOutCoupling::kDcCoupled);
	g_dac.set_coupling(
		brain::io::AudioCvOutChannel::kChannelB, brain::io::AudioCvOutCoupling::kDcCoupled);

	sleep_ms(1000);

	// Set voltage output to 10V
	printf("Setting output voltage to 10V on both outputs\n");
	g_dac.set_voltage(brain::io::AudioCvOutChannel::kChannelA, float(voltage));
	g_dac.set_voltage(brain::io::AudioCvOutChannel::kChannelB, float(voltage));

	printf("Setting all LEDs to ON\n");
	leds.startup_animation();

	while (true) {
		buttonDown.update();
		buttonUp.update();
		g_dac.set_voltage(brain::io::AudioCvOutChannel::kChannelA, float(voltage));
		g_dac.set_voltage(brain::io::AudioCvOutChannel::kChannelB, float(voltage));

		// Set LED (binary) to actual voltage
		leds.set_from_mask(voltage);
	}

	return 0;
}
