#ifndef __XRANC_SB_API_H
#define __XRANC_SB_API_H
#include <cstddef>
#include <stdint.h>
size_t cell_config_request(uint8_t *buffer, size_t buf_size);
void cell_config_response(uint8_t *buffer, size_t buf_size);
#endif
