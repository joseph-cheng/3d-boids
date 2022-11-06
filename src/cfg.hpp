#pragma once

#include "status.hpp"
#include <cstdint>
typedef struct Config {
    uint32_t num_boids;
} Config_t;

Status_t parse_cmd(int argc, char *argv[], Config_t *dest);

void print_usage(const char *prog_name);

