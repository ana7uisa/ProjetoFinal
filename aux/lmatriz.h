#ifndef LED_MATRIZ_H
#define LEd_MATRIZ_H

#include "hardware/pio.h"

#define pino_matriz 7
#define num_pixels 25

uint32_t rgb_matrix(double b, double r, double g);
void clear_leds(PIO pio, uint sm);
void leds_on(PIO pio, uint sm, double r, double g, double b);
void print_num(int caracter, PIO pio, uint sm);

#endif // LED_MATRIZ_H