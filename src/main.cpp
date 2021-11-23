#include <stdio.h>
#include "pico/stdlib.h"

#include <array>

constexpr uint32_t SLEEP_MS{50};

constexpr std::array PIN_ARRAY {
	0,2,4,6,8
};

auto
main() -> int
{
	stdio_init_all();

	for(auto const &pin : PIN_ARRAY) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_up(pin);
	}

	while(true) {
		for(auto const &pin : PIN_ARRAY) {
			auto const status = !static_cast<bool>(gpio_get(pin));
			if(status) {
				printf("%i\n", pin, status);
			}
		}
		sleep_ms(SLEEP_MS);
	}
	return 0;
}
