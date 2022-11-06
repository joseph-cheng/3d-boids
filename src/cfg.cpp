#include "cfg.hpp"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


void print_usage(const char *prog_name) {
    printf("Usage: %s -n [num boids]\n", prog_name);
}

Status_t parse_cmd(int argc, char *argv[], Config_t *dest) {
    if (dest == NULL) {
        fprintf(stderr, "Passed NULL dest pointer to parse_cmd\n");
        return STATUS_FAIL;
    }
    int opt;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                dest->num_boids = atoi(optarg);
                break;
            default:
                print_usage(argv[0]);
                return STATUS_FAIL;
        }
    }
    return STATUS_SUCCESS;
}
