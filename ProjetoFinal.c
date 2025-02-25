#include <stdio.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "pio_matriz.pio.h"
#include "./aux/lmatriz.h"
#include "./aux/num.h"
#include "./aux/ssd1306.h"
#include "./aux/font.h"
#include "hardware/pwm.h"

/* 
 * SEMÁFORO COM RASPBERRY PI PICO
 * 
 * Este projeto implementa um semáforo completo utilizando:
 * - LEDs RGB para indicação de cores (vermelho, amarelo, verde)
 * - Display OLED para mensagens de texto
 * - Matriz de LEDs para contagem regressiva
 * - Buzzer para sinalização sonora durante o estado verde
 *
 * O semáforo possui três estados:
 * 1. Vermelho (3s): Proibida a passagem
 * 2. Amarelo (3s): Atenção
 * 3. Verde (6s): Permitida a passagem (com sinal sonoro)
 */

// Definição dos pinos utilizados
#define LED_R 13         // Pino do LED vermelho
#define LED_G 11         // Pino do LED verde
#define LED_B 12         // Pino do LED azul
#define BUZZER 21        // Pino do buzzer
#define I2C_INTERFACE i2c1  // Interface I2C para o display
#define DISPLAY_ADDR 0x3C   // Endereço I2C do display OLED
#define PIN_SDA 14       // Pino de dados I2C
#define PIN_SCL 15       // Pino de clock I2C

// Variáveis globais
volatile int estado = 0;                   // Estado atual do semáforo (0=vermelho, 1=amarelo, 2=verde)
struct repeating_timer semaforo_timer;     // Timer para controle do semáforo
ssd1306_t display;                         // Estrutura para controle do display OLED
PIO pio = pio0;                            // Controlador PIO para a matriz de LEDs
uint sm = 0;                               // State machine do PIO

/**
 * Configura um pino para operar em modo PWM
 * @param pin Número do pino
 * @param freq Frequência desejada (Hz)
 * @param duty_c Ciclo de trabalho (0-10000)
 */
void set_pwm_pin(uint pin, uint freq, uint duty_c) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_config config = pwm_get_default_config();
    float div = (float)clock_get_hz(clk_sys) / (freq * 10000);
    pwm_config_set_clkdiv(&config, div);
    pwm_config_set_wrap(&config, 10000); 
    pwm_init(slice_num, &config, true); 
    pwm_set_gpio_level(pin, duty_c); 
}

/**
 * Desativa o modo PWM de um pino
 * @param pin Número do pino
 */
void disable_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_SIO);
    gpio_put(pin, 0);
}

/**
 * Função principal para controle do semáforo
 * Gerencia os três estados, atualiza LEDs, display OLED e matriz
 * @param t Ponteiro para timer (não utilizado diretamente)
 * @return true para continuar o timer, false para interromper
 */
bool controlar_semaforo(struct repeating_timer *t) {
    
    switch (estado) {
        case 0: // Vermelho - Proibido passar
            // Desliga todos os LEDs e buzzer primeiro
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 0);
            gpio_put(LED_B, 0);
            disable_pwm(BUZZER);
            
            // Configura para o estado vermelho
            gpio_put(LED_R, 1);
            
            // Atualiza o display
            ssd1306_fill(&display, false);
            ssd1306_draw_string(&display, "Proibido a", 5, 20);
            ssd1306_draw_string(&display, "passagem", 5, 40);
            ssd1306_send_data(&display);

            // Configura o contador regressivo na matriz de LEDs
            for(int i = 3; i > 0; i--){
                print_num(i, pio, sm);
                sleep_ms(1000);
            }
            clear_leds(pio, sm);
            
            // Muda para o próximo estado após 3 segundos
            estado = 1;
            return true;
            
        case 1: // Amarelo - Atenção
            // Configura para o estado amarelo (vermelho + verde = amarelo)
            gpio_put(LED_R, 1);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 0);
            
            // Atualiza o display
            ssd1306_fill(&display, false);
            ssd1306_draw_string(&display, "Atencao!", 5, 20);
            ssd1306_send_data(&display);

            // Configura o contador regressivo na matriz de LEDs
            for(int i = 3; i > 0; i--){
                print_num(i, pio, sm);
                sleep_ms(1000);
            }
            clear_leds(pio, sm);
            
            // Muda para o próximo estado após 3 segundos
            estado = 2;
            return true;
            
        case 2: // Verde - Permitido passar
            // Configura para o estado verde
            gpio_put(LED_R, 0);
            gpio_put(LED_G, 1);
            gpio_put(LED_B, 0);
            
            // Ativa o buzzer com tom de 300Hz
            set_pwm_pin(BUZZER, 300, 300);
            
            // Atualiza o display
            ssd1306_fill(&display, false);
            ssd1306_draw_string(&display, "Permitido a", 5, 20);
            ssd1306_draw_string(&display, "passagem", 5, 40);
            ssd1306_send_data(&display);

            // Configura o contador regressivo (mais longo - 6 segundos)
            for(int i = 6; i > 0; i--){
                print_num(i, pio, sm);
                sleep_ms(1000);
            }
            clear_leds(pio, sm);
                       
            // Volta para o estado vermelho após 6 segundos
            estado = 0;
            return true;
            
        default:
            return false;
    }
}

/**
 * Configura todo o hardware necessário para o semáforo
 * - Pinos GPIO para LEDs e buzzer
 * - Interface I2C para display OLED
 * - Inicializa o display OLED
 */
void configurar_hardware() {
    // Inicializa os pinos de LED
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Inicializa o I2C para o display OLED
    i2c_init(I2C_INTERFACE, 400 * 1000);  // 400 kHz
    gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SDA);
    gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_SCL);

    // Inicializa o display OLED
    ssd1306_init(&display, WIDTH, HEIGHT, false, DISPLAY_ADDR, I2C_INTERFACE);
    ssd1306_config(&display);
    ssd1306_fill(&display, false);
    ssd1306_send_data(&display);
}

/**
 * Função principal
 * Inicializa hardware, configura o PIO para a matriz de LEDs
 * e mantém o semáforo em ciclo constante
 */
int main() {
    // Inicializa o programa PIO para controlar a matriz de LEDs
    uint deslocamento = pio_add_program(pio, &pio_matriz_program);
    pio_matriz_program_init(pio, sm, deslocamento, pino_matriz);

    // Inicializa o sistema
    stdio_init_all();
    configurar_hardware();

    // Inicia o semáforo no estado 0 (vermelho)
    controlar_semaforo(NULL);
    
    // Loop principal - monitora e atualiza o semáforo
    while (true) {
        printf("Semaforo em operacao - Estado: %d\n", estado);
        sleep_ms(1000);
        
        // Atualiza o estado do semáforo
        controlar_semaforo(NULL);
    }
    
    return 0;
}