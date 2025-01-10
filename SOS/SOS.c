#include "pico/stdlib.h"


// Led da GPIO 13
#define LED_PIN 13


// Define os tempos pra cada caso
int ponto = 200; // duração ponto 0.2s
int traco = 800; // duração traço 0.8s

int gap = 125; // intervalo entre ponto e traço 0.125s
int intervalo = 250; // intervalo entre letras 0.25s

int reset = 3000; // reset 3s


// Função para piscar ponto com buzzer
void piscar_ponto() {
    gpio_put(LED_PIN, true);
    sleep_ms(ponto);
    gpio_put(LED_PIN, false);
    sleep_ms(gap);
}

// Função para piscar traço com buzzer
void piscar_traco() {
    gpio_put(LED_PIN, true);
    sleep_ms(traco);
    gpio_put(LED_PIN, false);
    sleep_ms(gap);
}


int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

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