**Temporização *One Shot* com Raspberry Pi Pico W**

O presente projeto utiliza o microcontrolador Raspberry Pi Pico W e a função *add_alarm_in_ms()* para ligar LEDs após acionamento de um botão. 
O sistema é configurado para alterar o estado dos LEDs funcionando como um ciclo de temporização *one shot*, isto é disparo único.

**Componentes Necessários**

- Microcontrolador Raspberry Pi Pico W;
- LED azul;
- LED vermelho;
- LED verde;
- Resistores de 330Ω;
- Botão *Pushbutton*;
- *Wokwi*.

**Funcionamento**

O sistema utiliza a função *add_alarm_in_ms()* para agendar temporizadores que alteram os estados dos LEDs a cada 3000 ms, ou seja 3 segundos.

O comportamento ocorre do seguinte modo:
- Quando o botão é pressionado, todos os LEDs são acesos simultaneamente.
- Em seguida, o LED verde apaga após 3 segudos.
- Posteriormente, o LED amarelo apaga transcorrido 3 segundos.
- E por fim, o LED azul apaga decorrido 3 segundos.

Deste modo, após a sequência completa, todos os LEDs são apagados e o ciclo termina.
É impotante citar que o botão não pode iniciar uma nova interação até que o ciclo de execução seja finalizado.

**Como Usar**

- Compile o código utilizando o VSCode.
- Carregue o código na placa BitDogLab.
- Pressione o botão A.
- A simulação também pode ser verificada no *diagram.json*, devido a integração com o *Wokwi*.

**Vídeo de funcionamento**

https://drive.google.com/drive/folders/1-9pVgkojia8EXkUnv-MwkPL24KXGVcmJ?usp=sharing
