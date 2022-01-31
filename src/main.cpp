#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include <array>
#include <cstdint>

constexpr uint32_t SLEEP_MS{50};

constexpr std::array PIN_ARRAY {
	19,4,2,0,10,8,6,16,14,12 // 0,1,2...9
};

auto
main() -> int
{
#ifdef PICO_DEFAULT_LED_PIN
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	gpio_put(PICO_DEFAULT_LED_PIN, 1);
#endif

	stdio_init_all();

	for(auto const& pin : PIN_ARRAY) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_up(pin);
	}

	std::array<char, PIN_ARRAY.size()+1> buffer{};
	buffer.fill('\0');

	bool all_down = true;
	while(true) {
		all_down = true;
		for(size_t i=0; auto const& pin : PIN_ARRAY) {
			auto const status = !static_cast<bool>(gpio_get(pin));
			buffer[i] = status?'1':'0';
			if(!status) {
				all_down = false;
			}
			i++;
		}
		if(all_down) {
			reset_usb_boot(0,0);
		}
		printf("%s\n", buffer.data());
		sleep_ms(SLEEP_MS);
	}
	return 0;
}
