# Projeto de Temporizador de Um Disparo - Acionamento de LEDs com Botão no Raspberry Pi Pico W

## Descrição
Este projeto foi desenvolvido por mim, Hilquias Rodrigues de Oliveira, para demonstrar o uso de temporizadores de um disparo (One Shot) no microcontrolador Raspberry Pi Pico W. O objetivo é acionar LEDs com base no clique de um botão, utilizando a função `add_alarm_in_ms()` do Pico SDK. O sistema segue um ciclo de transição onde os LEDs mudam de estado sequencialmente a cada 3 segundos após a pressão do botão.

## Funcionalidades
- Acionamento de LEDs azul, vermelho e verde com base no clique do botão.
- Transição entre estados a cada 3 segundos utilizando temporizadores de um disparo.
- Bloqueio de novos acionamentos até que o ciclo seja concluído.
- Opcional: Implementação de debounce por software para evitar falsos acionamentos do botão.

## Componentes Utilizados
- Raspberry Pi Pico W
- 3 LEDs (azul, vermelho e verde)
- 3 resistores de 330Ω
- 1 botão (pushbutton)

## Como Executar

### Requisitos
- Pico SDK instalado
- VS Code com extensões do Wokwi Simulator, Raspberry Pi Pico, CMake e C/C++

### Passos
1. Clone este repositório e abra a pasta do projeto no VS Code.
2. Realize a compilação.
3. Abra o arquivo `diagram.json` e execute a simulação no Wokwi.
4. Pressione o botão para iniciar o ciclo de acionamento dos LEDs.
