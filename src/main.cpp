#include <stdio.h>
#include "pico/stdlib.h"

#include <array>
#include <cstdint>

constexpr uint32_t SLEEP_MS{50};

constexpr std::array PIN_ARRAY {
	15,4,2,0,10,8,6,16,14,12
};

auto
main() -> int
{
	stdio_init_all();

	for(auto const& pin : PIN_ARRAY) {
		gpio_init(pin);
		gpio_set_dir(pin, GPIO_IN);
		gpio_pull_up(pin);
	}

	char buffer[PIN_ARRAY.size()+1] = {'\0'};
	while(true) {
		for(size_t i=0; auto const& pin : PIN_ARRAY) {
			auto const status = !static_cast<bool>(gpio_get(pin));
			buffer[i] = status?'1':'0';
			i++;
		}
		printf("%s\n", buffer);
		sleep_ms(SLEEP_MS);
	}
	return 0;
}
