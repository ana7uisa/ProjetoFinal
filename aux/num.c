#include "num.h"
#include "lmatriz.h"
#include "pico/stdlib.h"

// Número 0
void num0(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5 
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5);
        int coluna = i % 5;
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 1
void num1(PIO pio, uint sm) {
    double frame[25] = {
        0.0, 0.0, 0.5, 0.0, 0.0,  
        0.0, 0.5, 0.5, 0.0, 0.0,  
        0.0, 0.0, 0.5, 0.0, 0.0,  
        0.0, 0.0, 0.5, 0.0, 0.0,  
        0.0, 0.5, 0.5, 0.5, 0.0   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 2
void num2(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.0,  
        0.5, 0.5, 0.5, 0.5, 0.5   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 3
void num3(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 4
void num4(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.0   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 5
void num5(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.0,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 6
void num6(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.0,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 7
void num7(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.0, 0.5, 0.0, 0.0, 0.0,  
        0.0, 0.0, 0.5, 0.0, 0.0,  
        0.0, 0.0, 0.0, 0.5, 0.0   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 8
void num8(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}

// Número 9
void num9(PIO pio, uint sm) {
    double frame[25] = {
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.5, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5,  
        0.0, 0.0, 0.0, 0.0, 0.5,  
        0.5, 0.5, 0.5, 0.5, 0.5   
    };

    for (int i = 0; i < 25; i++) {
        int linha = 4 - (i / 5); 
        int coluna = i % 5; 
        pio_sm_put_blocking(pio, sm, rgb_matrix(frame[linha * 5 + coluna], frame[linha * 5 + coluna], frame[linha * 5 + coluna]));  
    }
}