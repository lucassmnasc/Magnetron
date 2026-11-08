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

## 🛠️ Tecnologias e Requisitos

<p align="center">
  <img src="https://img.shields.io/badge/Linguagem-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Gráficos-raylib-000000?style=for-the-badge&logo=raylib&logoColor=white" alt="raylib" />
  <img src="https://img.shields.io/badge/Build-Premake%20%2B%20Make-FF6B35?style=for-the-badge" alt="Premake + Make" />
  <img src="https://img.shields.io/badge/Plataformas-Windows%20%7C%20Linux%20%7C%20macOS-4C4C4C?style=for-the-badge" alt="Plataformas" />
</p>

<div align="center">
   
| 🧩 Item | 📌 Detalhe |
|---------|-----------|
| 💻 **Linguagem** | C |
| 🎨 **Biblioteca gráfica** | [raylib](https://github.com/raysan5/raylib) (licença zlib/libpng) |
| ⚙️ **Sistema de build** | Premake5 + Make (ou Visual Studio no Windows) |
| 🖥️ **Plataformas** | Windows, Linux e macOS |
| 🎓 **Contexto** | Projeto acadêmico, CESAR School, disciplina de PIF |

</div>

## 📁 Estrutura do Projeto

```
Magnetron/
├── README.md
├── Makefile
└── src/
    └── main.c
```

## 📦 Como Compilar e Executar

<details>
<summary><b>Acesse aqui para instalar e jogar</b> (clique para expandir)</summary>

O Magnetron usa a [raylib](https://github.com/raysan5/raylib). Na primeira geração do projeto, o Premake baixa o código-fonte da raylib, então é necessária uma **conexão com a internet** nessa etapa.

Primeiro, clone o repositório:

```bash
git clone https://github.com/lucassmnasc/Magnetron.git
cd Magnetron
```

> **Importante:** execute sempre o jogo a partir da **pasta raiz do projeto**. É de lá que ele lê a fonte em `resources/` e grava os recordes em `magnetron_scores.txt`.

### 🪟 Windows

**Pré-requisito:** [MinGW-W64](https://www.mingw-w64.org/) (com `mingw32-make` no PATH) **ou** Visual Studio 2022/2026 com o workload "Desenvolvimento para desktop com C++".

**Opção A: MinGW (linha de comando)**

```bat
build-MinGW-W64.bat
mingw32-make
bin\Debug\Magnetron.exe
```

O `.bat` gera os arquivos de build na pasta `build\`. Depois disso, `mingw32-make` compila e o `.exe` é executado.

**Opção B: Visual Studio**

1. Execute `build-VisualStudio2022.bat` (ou `build-VisualStudio2026.bat`).
2. Abra o arquivo `Magnetron.sln` gerado na raiz.
3. Defina **Magnetron** como projeto de inicialização e pressione **F5**.

### 🐧 Linux

**Dependências** (exemplo para Debian/Ubuntu):

```bash
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev \
  libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev \
  libwayland-dev libxkbcommon-dev
```

**Compilar e executar:**

```bash
cd build
chmod +x premake5      # só se o arquivo não tiver permissão de execução
./premake5 gmake
cd ..
make config=debug_x64
./bin/Debug/Magnetron
```

> No **WSL**, a janela do jogo exige o WSLg (Windows 11 ou WSL atualizado com `wsl --update`).

### 🍎 macOS

**Pré-requisito:** ferramentas de linha de comando da Apple:

```bash
xcode-select --install
```

**Compilar e executar:**

```bash
cd build
chmod +x premake5.osx  # só se o arquivo não tiver permissão de execução
./premake5.osx gmake
cd ..
make config=debug_arm64   # Macs com Apple Silicon (M1/M2/M3...)
# make config=debug_x64   # Macs com processador Intel
./bin/Debug/Magnetron
```

> Se o macOS bloquear o `premake5.osx` por segurança, abra **Ajustes do Sistema → Privacidade e Segurança** e permita a execução, depois rode o comando de novo.

### 🔁 Recompilando depois de alterar o código

Não é preciso rodar o Premake novamente, a menos que você adicione ou remova arquivos `.c`. Basta repetir o `make` (ou `mingw32-make` no Windows) e executar o jogo.

### 🚀 Versão otimizada (release)

Troque `debug` por `release` na configuração e o executável sai em `bin/Release/`:

```bash
make config=release_x64    # ou release_arm64 no Apple Silicon
./bin/Release/Magnetron
```

<div align="center">

| Tecla | Ação |
|-------|------|
| `W` | Mover para cima |
| `A` | Mover para a esquerda |
| `S` | Mover para baixo |
| `D` | Mover para a direita |
| `P` | Pressione para pausar |
| `ENTER ou ESPAÇO` | Pressione para iniciar o jogo |
| `R` | Pressione para jogar novamente |
| `ESC` | Sair do jogo |

</div>
</details>

## 📄 Licenças

Este projeto usa a biblioteca [raylib](https://github.com/raysan5/raylib), distribuída sob a licença zlib/libpng.
