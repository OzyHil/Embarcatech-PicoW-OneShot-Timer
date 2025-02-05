#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED 13   // LED vermelho
#define BLUE_LED 12  // LED azul
#define GREEN_LED 11 // LED verde
#define BUTTON_A 5   // Botão

volatile bool canPress = true; // Controle do botão
volatile uint8_t count = 0;

// Configura LEDs como saída
void SetOutputs(int pins[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        gpio_init(pins[i]);
        gpio_set_dir(pins[i], GPIO_OUT);
    }
}

// Função chamada pelo alarme para alternar LEDs
int64_t LEDUpdate(alarm_id_t id, void *user_data)
{
    if (count == 0)
    {
        gpio_put(GREEN_LED, true);
        gpio_put(BLUE_LED, true);
        gpio_put(RED_LED, true);
        add_alarm_in_ms(3000, LEDUpdate, NULL, false);
    }
    else if (count == 1)
    {
        gpio_put(GREEN_LED, false);
        add_alarm_in_ms(3000, LEDUpdate, NULL, false);
    }
    else if (count == 2)
    {
        gpio_put(BLUE_LED, false);
        add_alarm_in_ms(3000, LEDUpdate, NULL, false);
    }
    else if (count == 3)
    {
        gpio_put(RED_LED, false);
        count = -1;      // Reset para próximo ciclo
        canPress = true; // Permite novo acionamento do botão
    }

    count++; // Próximo estado
    return 0;
}

// Interrupção do botão (pressionado)
void HandleInterruption(uint gpio, uint32_t events)
{
    static uint32_t lastTime = 0;
    uint32_t currentTime = to_ms_since_boot(get_absolute_time());

    if (canPress && (currentTime - lastTime > 200))
    { // Debounce 200ms
        lastTime = currentTime;
        canPress = false;   // Bloqueia novos acionamentos até o ciclo dos LEDs terminar
        count = 0;          // Reinicia a sequência
        LEDUpdate(0, NULL); // Dispara a primeira mudança de LED
    }
}

int main()
{
    stdio_init_all();

    // Inicializa LEDs
    int led_pins[] = {RED_LED, BLUE_LED, GREEN_LED};
    SetOutputs(led_pins, sizeof(led_pins) / sizeof(led_pins[0]));

    // Inicializa botão e interrupção
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &HandleInterruption);

    // Loop infinito
    while (true)
    {
    }
}
