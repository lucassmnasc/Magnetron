# Magnetron

Corrida espacial arcade 2D: pilote sua nave por uma chuva de asteroides e tente
percorrer a maior distância possível.

## 🚀 Sobre o Jogo

Em **Magnetron**, desvie de asteroides em velocidade crescente, proteja seu casco
e bata seu recorde de distância. O jogo é feito em C com raylib e não precisa de
arquivos de imagem ou áudio externos.

O código está dividido por responsabilidade: `nave.c` cuida do movimento e do
desenho da nave, `obstaculos.c` cria e atualiza os asteroides, e `colisao.c`
verifica os impactos.

## Conceitos de C usados no projeto

- **Structs e ponteiros:** `Nave`, `Obstaculo`, `CampoAsteroides` e `Placar`
  agrupam os dados do jogo; as funções recebem ponteiros para atualizar esses
  dados sem copiar as estruturas.
- **Alocação dinâmica e lista encadeada:** cada asteroide é criado com `malloc`
  e ligado ao próximo pelo campo `prox`. Asteroides que saem da tela ou são
  reiniciados são liberados com `free`.
- **Matriz:** `ocupacao[8][6]` representa oito setores verticais e seis colunas
  do campo. Ela conta asteroides por setor e evita gerar um novo asteroide em
  uma coluna que já está ocupada na parte superior.
- **Arquivos:** o jogo lê e grava os cinco melhores resultados em
  `magnetron_scores.txt`, no diretório de trabalho usado para iniciar o jogo.

## 🎮 Como Jogar

| Tecla | Ação |
|-------|------|
| `W` / `↑` | Mover para cima |
| `A` / `←` | Mover para a esquerda |
| `S` / `↓` | Mover para baixo |
| `D` / `→` | Mover para a direita |
| `P` | Pausar / continuar |
| `R` | Reiniciar após o fim de jogo |
| `ESC` | Sair do jogo |

Você tem três pontos de casco. Depois de uma colisão, a nave fica brevemente
invulnerável para permitir que você se afaste dos asteroides.

## 🛠️ Tecnologias e Requisitos

- **Linguagem:** C
- **Biblioteca gráfica:** [raylib](https://github.com/raysan5/raylib) (licença zlib/libpng)
- **Contexto:** Projeto acadêmico (CESAR School — disciplina de PIF)

## 📦 Como Compilar e Executar

1. A primeira geração do projeto baixa o código-fonte da raylib com Premake,
   então é necessária uma conexão com a internet.
2. Clone o repositório:
   ```bash
   git clone https://github.com/lucassmnasc/Magnetron.git
   cd Magnetron
   ```
3. Gere os arquivos de compilação para sua plataforma usando Premake e compile:
   ```bash
   cd build
   ./premake5.osx gmake
   cd ..
   make config=debug_x64
   ```
   No Linux, use `./premake5 gmake` no lugar de `./premake5.osx`; em Macs Intel,
   use `make config=debug_x64`. Em Macs com Apple Silicon, use
   `make config=debug_arm64`.
4. Execute:
   ```bash
   ./bin/Debug/Magnetron
   ```
   Os recordes são salvos no arquivo `magnetron_scores.txt` nesse diretório.

> Em WSL, a janela do jogo exige o WSLg (Windows 11 ou WSL atualizado com `wsl --update`).

## 📁 Estrutura do Projeto

```
Magnetron/
├── README.md
└── src/
    ├── main.c
    ├── nave.c / nave.h
    ├── obstaculos.c / obstaculos.h
    ├── colisao.c / colisao.h
    └── recordes.c / recordes.h
```


## 👥 Equipe

- Lucas Silva Moreira do Nascimento
- Matheus Trajano de Freitas
- Arthur Santana de Andrade

## 📄 Licenças

Este projeto usa a biblioteca [raylib](https://github.com/raysan5/raylib), distribuída sob a licença zlib/libpng.
