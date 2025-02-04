#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_BLUE 11 // Led azul
#define LED_PIN_RED 12 // Led vermelho
#define LED_PIN_GREEN 13 // Led verde
#define BUTTON_PIN 5 // Botão A

// Variáveis
int semaforo_estado = 0;
bool led_active = false;

// Função de callback chamada pelo temporizador
int64_t turn_off_callback(alarm_id_t id, void *user_data) {

    switch (semaforo_estado) {
        case 0: // Todos os LEDs acesos
            gpio_put(LED_PIN_BLUE, 1);
            gpio_put(LED_PIN_RED, 1);
            gpio_put(LED_PIN_GREEN, 1);
            semaforo_estado = 1; // Vai para o próximo estado (dois LEDs acesos)
            break;
        case 1: // Dois LEDs acesos
            gpio_put(LED_PIN_BLUE, 1);
            gpio_put(LED_PIN_RED, 1); 
            gpio_put(LED_PIN_GREEN, 0);
            semaforo_estado = 2; // Vai para o próximo estado (um LED aceso)
            break;
        case 2: // Um LED aceso
            gpio_put(LED_PIN_BLUE, 1); 
            gpio_put(LED_PIN_RED, 0); 
            gpio_put(LED_PIN_GREEN, 0);
            semaforo_estado = 3; // Vai para o estado (nenhum LED aceso)
            break;
        case 3: // Nenhum LED aceso
            gpio_put(LED_PIN_BLUE, 0); 
            gpio_put(LED_PIN_RED, 0);
            gpio_put(LED_PIN_GREEN, 0);
            semaforo_estado = 0;
            led_active = false; // Finaliza o ciclo, permitindo nova interação com o botão
            break;
        default:
            semaforo_estado = 0;
            break;
    }

    if (semaforo_estado != 0) {
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }

    return 0;
}

int main() {
    stdio_init_all();

    // Inicializa os pinos dos LEDs e os define como saída
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Inicializa o pino do botão e o define como entrada
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Resistor pull-up para o botão

    // Loop
    while (true) {
        // Verifica se o botão foi pressionado
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            // Atraso para debounce
            sleep_ms(50);

            if (gpio_get(BUTTON_PIN) == 0) {
                semaforo_estado = 0;
                led_active = true; 

                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }

        sleep_ms(10);
    }

    return 0;
}
