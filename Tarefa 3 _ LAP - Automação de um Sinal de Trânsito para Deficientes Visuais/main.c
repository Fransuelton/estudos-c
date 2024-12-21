#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definindo os pinos de leds, buzzer e botão
#define LED_G 11
#define LED_Y 4
#define LED_R 0
#define LED_GP 15
#define BUZZER_PIN 28
#define BUTTON_PIN 27

// Definindo os delays default de cada led
#define DEFAULT_DELAY_G 8000
#define DEFAULT_DELAY_Y 2000
#define DEFAULT_DELAY_R 10000

// Definindo a frequência de som do buzzer em Hz
#define BUZZER_FREQUENCY 100

// Definição de uma função para inicializar o PWM no pino do buzzer
void pwm_init_buzzer(uint pin) {
  // Configurar o pino como saída de PWM
  gpio_set_function(pin, GPIO_FUNC_PWM);

  // Obter o slice do PWM associado ao pino
  uint slice_num = pwm_gpio_to_slice_num(pin);

  // Configurar o PWM com frequência desejada
  pwm_config config = pwm_get_default_config();
  pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
  pwm_init(slice_num, &config, true);

  // Iniciar o PWM no nível baixo
  pwm_set_gpio_level(pin, 0);
}

// Definição de uma função para emitir um beep com duração especificada
void beep(uint pin, uint duration_ms) {
  // Obter o slice do PWM associado ao pino
  uint slice_num = pwm_gpio_to_slice_num(pin);

  // Configurar o duty cycle para 50% (ativo)
  pwm_set_gpio_level(pin, 2048);

  // Temporização
  sleep_ms(duration_ms);

  // Desativar o sinal PWM (duty cycle 0)
  pwm_set_gpio_level(pin, 0);

  // Pausa entre os beeps
  sleep_ms(100); // Pausa de 100ms
}

void initial_leds_state();

int main() {
  stdio_init_all();

  // Inicializando os Leds
  gpio_init(LED_G);
  gpio_init(LED_Y);
  gpio_init(LED_R);
  gpio_init(LED_GP);

  // Definindo os Leds como saída
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_set_dir(LED_Y, GPIO_OUT);
  gpio_set_dir(LED_G, GPIO_OUT);
  gpio_set_dir(LED_GP, GPIO_OUT);

  // Configuração do GPIO para o botão como entrada com pull-up
  gpio_init(BUTTON_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);
  gpio_pull_up(BUTTON_PIN);

  // Configuração do GPIO para o buzzer como saída
  gpio_init(BUZZER_PIN);
  gpio_set_dir(BUZZER_PIN, GPIO_OUT);

  // Inicializar o PWM no pino do buzzer
  pwm_init_buzzer(BUZZER_PIN);

  while (true) {

    initial_leds_state();

    // Verifica o estado do botão
    if (gpio_get(BUTTON_PIN) == 0) {  // Botão pressionado (nível lógico baixo)

      gpio_put(LED_Y, 1);
      sleep_ms(5000);
      gpio_put(LED_Y, 0);

      gpio_put(LED_R, 1);
      gpio_put(LED_GP, 1);
      beep(BUZZER_PIN, 15000); // Bipe de 15s + Buzzer ligado

      gpio_put(LED_R, 0);
      gpio_put(LED_GP, 0);
    }
  }
  return 0;
}

// Função para controlar o estado inicial dos leds
void initial_leds_state() {
  gpio_put(LED_G, 1);
  sleep_ms(DEFAULT_DELAY_G);
  gpio_put(LED_G, 0);

  gpio_put(LED_Y, 1);
  sleep_ms(DEFAULT_DELAY_Y);
  gpio_put(LED_Y, 0);

  gpio_put(LED_R, 1);
  sleep_ms(DEFAULT_DELAY_R);
  gpio_put(LED_R, 0);

  // Durante esse sleep o botão pode ser pressionado para que o pedestre atravesse
  sleep_ms(100);
};