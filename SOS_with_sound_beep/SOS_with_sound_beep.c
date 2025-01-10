#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Buzzers 
#define BUZZER_A 21
#define BUZZER_B 10

// Led 
#define LED_PIN 13

// Define os tempos para cada caso
int ponto = 200; // duração ponto 0.2s
int traco = 800; // duração traço 0.8s

int gap = 125; // intervalo entre ponto e traço 0.125s
int intervalo = 250; // intervalo entre letras 0.25s

int reset = 3000; // reset 3s


// Função para configurar o PWM nos pinos do buzzer
void configurar_pwm(uint gpio, int freq_hz, float duty_cycle) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice_num, 4.0f); 

    uint16_t wrap = 125000000 / freq_hz - 1; 
    pwm_set_wrap(slice_num, wrap);
    
    uint16_t level = wrap * duty_cycle; 
    pwm_set_gpio_level(gpio, level);
}

// Função para ligar o PWM no pino do buzzer
void ligar_pwm(uint gpio){
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_enabled(slice_num, true);
}

// Função para parar o PWM no pino do buzzer
void parar_pwm(uint gpio) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_enabled(slice_num, false);
}

// Função para piscar ponto com LED e buzzer com frequência e volume
void piscar_ponto() {
    gpio_put(LED_PIN, true);
    ligar_pwm(BUZZER_A);
    ligar_pwm(BUZZER_B);

    sleep_ms(ponto); 

    gpio_put(LED_PIN, false);
    parar_pwm(BUZZER_A);
    parar_pwm(BUZZER_B);

    sleep_ms(gap);
}

// Função para piscar traço com LED e buzzer com frequência e volume
void piscar_traco() {
    gpio_put(LED_PIN, true);
    ligar_pwm(BUZZER_A);
    ligar_pwm(BUZZER_B);

    sleep_ms(traco);

    gpio_put(LED_PIN, false);
    parar_pwm(BUZZER_A);
    parar_pwm(BUZZER_B);

    sleep_ms(gap);
}

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUZZER_A);
    gpio_init(BUZZER_B);

    // Configura os buzzers a 100hz a 20% do volume
    configurar_pwm(BUZZER_A, 100, 0.8); 
    configurar_pwm(BUZZER_B, 100, 0.8);

    while (true) {
        // S
        piscar_ponto();
        piscar_ponto();
        piscar_ponto();
        sleep_ms(intervalo);

        // O
        piscar_traco();
        piscar_traco();
        piscar_traco();
        sleep_ms(intervalo);

        // S
        piscar_ponto();
        piscar_ponto();
        piscar_ponto();
        sleep_ms(intervalo);

        sleep_ms(reset);
    }
}