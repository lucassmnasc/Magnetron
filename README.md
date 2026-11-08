# Magnetron

Corrida espacial - **Escape dos Asteróides**

## 🚀 Sobre o Jogo

Em **Magnetron**, o jogador comanda uma nave espacial em pistas no espaço. Utilizando mecânicas em 2D, a nave precisa ir desviando dos asteróides ao longo do caminho, eles vem de forma aleatória conforme vão passando as fases do jogo. O objetivo é simples: o jogador precisa ir desviando dos asteróides pelo máximo de fases que conseguir, os 5 primeiros aparecerão na tela de "Fim de Jogo". O jogo é inspirado em um design retrô, com uma pegada divertida e fácil de jogar por qualquer um! **Entre e se divirta**!

## 👥 Equipe

<div align="center">

| Membro | E-mail |
| :---: | :---: |
| Arthur Santana de Andrade | **asa4@cesar.school** |
| Lucas Silva Moreira do Nascimento | **lsmn@cesar.school** |
| Matheus Trajano de Freitas | **mtf@cesar.school** |

</div>

## 🎮 Como Jogar

<div align="center">

| Tecla | Ação |
|-------|------|
| `W` | [Mover para cima] |
| `A` | [Mover para a esquerda] |
| `S` | [Mover para baixo] |
| `D` | [Mover para a direita] |
| `ESC` | Sair do jogo |

</div>

## 🛠️ Tecnologias e Requisitos

- **Linguagem:** C
- **Biblioteca gráfica:** [raylib](https://github.com/raysan5/raylib) (licença zlib/libpng)
- **Contexto:** Projeto acadêmico (CESAR School — disciplina de PIF)

## 📦 Como Compilar e Executar

1. Instale a raylib seguindo o guia oficial: <https://github.com/raysan5/raylib/wiki>
2. Clone o repositório:
   ```bash
   git clone https://github.com/lucassmnasc/Magnetron.git
   cd Magnetron
   ```
3. Compile:
   ```bash
   [COLE AQUI O SEU COMANDO OU USE: make]
   ```
4. Execute:
   ```bash
   ./magnetron
   ```

> Em WSL, a janela do jogo exige o WSLg (Windows 11 ou WSL atualizado com `wsl --update`).

## 📁 Estrutura do Projeto

```
Magnetron/
├── README.md
├── Makefile
└── src/
    └── main.c
```

## 📄 Licenças

Este projeto usa a biblioteca [raylib](https://github.com/raysan5/raylib), distribuída sob a licença zlib/libpng.
