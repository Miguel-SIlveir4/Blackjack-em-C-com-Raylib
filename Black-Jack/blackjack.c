#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARTAS 11

typedef struct {
    int valor;
    char nome[3];
} Carta;

Carta comprarCarta() {
    int r = rand() % 13 + 1;
    Carta c;

    if (r == 1) {
        c.valor = 1;
        sprintf(c.nome, "A");
    } else if (r >= 2 && r <= 10) {
        c.valor = r;
        sprintf(c.nome, "%d", r);
    } else {
        c.valor = 10;
        if (r == 11) sprintf(c.nome, "J");
        else if (r == 12) sprintf(c.nome, "Q");
        else sprintf(c.nome, "K");
    }

    return c;
}

int calcularTotal(Carta mao[], int quantidade) {
    int total = 0;
    int ases = 0;
    for (int i = 0; i < quantidade; i++) {
        total += mao[i].valor;
        if (mao[i].valor == 1) ases++;
    }

    while (total <= 11 && ases > 0) {
        total += 10;
        ases--;
    }

    return total;
}

void desenharMao(Carta mao[], int quantidade, int x, int y, Color cor, bool esconderSegunda) {
    for (int i = 0; i < quantidade; i++) {
        DrawRectangle(x + i * 60, y, 50, 80, cor);

        const char* texto = (i == 1 && esconderSegunda) ? "?" : mao[i].nome;
        int larguraTexto = MeasureText(texto, 20);
        int posXTexto = x + i * 60 + (50 - larguraTexto) / 2;

        DrawText(texto, posXTexto, y + 30, 20, BLACK);
    }
}

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Blackjack");

    SetTargetFPS(60);
    srand(time(NULL));

    Carta maoJogador[MAX_CARTAS] = {0};
    Carta maoDealer[MAX_CARTAS] = {0};
    int qtdJogador = 0;
    int qtdDealer = 0;
    bool fimDeJogo = false;
    bool turnoJogador = true;
    const char* resultado = "";

    maoJogador[qtdJogador++] = comprarCarta();
    maoJogador[qtdJogador++] = comprarCarta();
    maoDealer[qtdDealer++] = comprarCarta();
    maoDealer[qtdDealer++] = comprarCarta();

    while (!WindowShouldClose()) {
        if (!fimDeJogo) {
            if (turnoJogador) {
                if (IsKeyPressed(KEY_H)) {
                    maoJogador[qtdJogador++] = comprarCarta();
                    if (calcularTotal(maoJogador, qtdJogador) > 21) {
                        resultado = "Você perdeu!";
                        fimDeJogo = true;
                    }
                } else if (IsKeyPressed(KEY_S)) {
                    turnoJogador = false;
                }
            } else {
                while (calcularTotal(maoDealer, qtdDealer) < 17) {
                    maoDealer[qtdDealer++] = comprarCarta();
                }

                int totalJogador = calcularTotal(maoJogador, qtdJogador);
                int totalDealer = calcularTotal(maoDealer, qtdDealer);

                if (totalDealer > 21 || totalJogador > totalDealer) {
                    resultado = "Você venceu!";
                } else if (totalJogador < totalDealer) {
                    resultado = "Você perdeu!";
                } else {
                    resultado = "Empate!";
                }

                fimDeJogo = true;
            }
        }

        BeginDrawing();
        ClearBackground(DARKGREEN);

        const char *titulo = "BLACKJACK";
        int tamanhoFonteTitulo = 40;
        int larguraTitulo = MeasureText(titulo, tamanhoFonteTitulo);
        DrawText(titulo, (larguraTela - larguraTitulo) / 2, 20, tamanhoFonteTitulo, WHITE);

        const char *instrucoes = "Pressione [H] para Comprar | [S] para Parar | [R] para Reiniciar";
        int tamanhoFonteInstr = 20;
        int larguraInstr = MeasureText(instrucoes, tamanhoFonteInstr);
        DrawText(instrucoes, (larguraTela - larguraInstr) / 2, 70, tamanhoFonteInstr, WHITE);

        desenharMao(maoJogador, qtdJogador, 100, 400, SKYBLUE, false);
        desenharMao(maoDealer, qtdDealer, 100, 150, RED, !fimDeJogo);

        DrawText("Jogador", 100, 370, 20, WHITE);
        DrawText("Dealer", 100, 120, 20, WHITE);

        if (fimDeJogo) {
            int larguraResultado = MeasureText(resultado, 30);
            DrawText(resultado, (larguraTela - larguraResultado) / 2, 300, 30, YELLOW);

            const char *msgReiniciar = "Pressione [R] para Reiniciar";
            int larguraReiniciar = MeasureText(msgReiniciar, 20);
            DrawText(msgReiniciar, (larguraTela - larguraReiniciar) / 2, 340, 20, LIGHTGRAY);

            if (IsKeyPressed(KEY_R)) {
                qtdJogador = qtdDealer = 0;
                maoJogador[qtdJogador++] = comprarCarta();
                maoJogador[qtdJogador++] = comprarCarta();
                maoDealer[qtdDealer++] = comprarCarta();
                maoDealer[qtdDealer++] = comprarCarta();
                fimDeJogo = false;
                turnoJogador = true;
                resultado = "";
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
