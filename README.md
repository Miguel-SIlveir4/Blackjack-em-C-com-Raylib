🎰 Blackjack em C com Raylib

Este é um projeto simples do jogo Blackjack (21) desenvolvido em C, utilizando a biblioteca gráfica Raylib para exibir cartas, textos e controles na tela.

O objetivo é demonstrar lógica de programação, estruturas, arrays, aleatoriedade e interação com o teclado dentro de um projeto visual.


🃏 Funcionalidades


Compra de cartas aleatórias com valores reais do Blackjack

Cálculo automático do valor da mão, incluindo tratamento de Ás (1 ou 11)

Sistema completo de turnos: jogador ➜ dealer

Dealer compra automaticamente até atingir 17

Exibição gráfica das cartas e textos usando Raylib

Sistema de vitória, derrota e empate

Reinício da partida com um toque de tecla


🎮 Controles

H	Comprar carta (Hit)
S	Parar jogada (Stand)
R	Reiniciar o jogo
ESC	Fechar o programa

🖥️ Como o jogo funciona

➤ Jogador

Começa com duas cartas.

Pode comprar cartas (H) até parar ou estourar 21.

Se ultrapassar 21, perde automaticamente.

➤ Dealer

Compra automaticamente até atingir 17 ou mais.

Caso ultrapasse 21, o jogador vence.

➤ Resultados possíveis

Você venceu!

Você perdeu!

Empate!

🗂️ Estrutura do Código

Principais funções:
Carta comprarCarta()

Gera uma carta aleatória entre A, 2–10, J, Q, K.

int calcularTotal(...)

Calcula o total da mão com suporte ao Ás como 1 ou 11.

desenharMao(...)

Desenha cartas na tela como retângulos com texto.

📦 Como compilar

🔧 Dependências

Raylib instalada no sistema

Compilador C (GCC recomendado)

🔨 Comando de compilação

(Windows + MinGW):

gcc blackjack.c -o blackjack -lraylib -lopengl32 -lgdi32 -lwinmm

Linux:

gcc blackjack.c -o blackjack -lraylib -lm -lpthread -ldl -lrt -lX11
