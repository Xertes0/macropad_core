#include <stdio.h>
#include "pico/stdlib.h"

#include <array>
#include <cstdint>

constexpr uint32_t SLEEP_MS{50};

constexpr std::array PIN_ARRAY {
	//0,2,4,6,8
	10,0,9,1,5,16,12,6,3,1 // 1
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
