# Magnetron

Corrida espacial arcade 2D — **Escape dos Asteróides**

---

## 🚀 Sobre o Jogo

Em **Magnetron**, o jogador comanda uma nave espacial em pistas no espaço, desviando de asteróides que surgem com velocidade e frequência crescentes ao longo das fases. As **5 melhores pontuações** são salvas automaticamente e exibidas na tela de **Fim de Jogo**.

---

## 👥 Equipe

<div align="center">

| Membro | E-mail |
| :---: | :---: |
| Arthur Santana de Andrade | **asa4@cesar.school** |
| Lucas Silva Moreira do Nascimento | **lsmn@cesar.school** |
| Matheus Trajano de Freitas | **mtf@cesar.school** |

</div>

---

## 🛠️ Tecnologias e Requisitos

<p align="center">
  <img src="https://img.shields.io/badge/Linguagem-C17-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Gráficos%20e%20Áudio-raylib-000000?style=for-the-badge&logo=raylib&logoColor=white" alt="raylib" />
  <img src="https://img.shields.io/badge/Build-Premake%20%2B%20Make-FF6B35?style=for-the-badge" alt="Premake + Make" />
  <img src="https://img.shields.io/badge/Plataformas-Windows%20%7C%20Linux%20%7C%20macOS-4C4C4C?style=for-the-badge" alt="Plataformas" />
</p>

<div align="center">

| 🧩 Item | 📌 Detalhe |
|---------|-----------|
| 💻 **Linguagem** | C (C17) |
| 🎨 **Biblioteca gráfica e áudio** | [raylib](https://github.com/raysan5/raylib) (licença zlib/libpng) |
| ⚙️ **Sistema de build** | Premake5 + Make (ou Visual Studio no Windows) |
| 🖥️ **Plataformas** | Windows, Linux e macOS |
| 🎓 **Contexto** | Projeto acadêmico — CESAR School (disciplina de PIF) |

</div>

---

## ✨ Funcionalidades

- **Movimentação 2D:** controle da nave com `WASD` ou `Setas`, animação de propulsão e limites de tela.
- **Fases progressivas:** pontuação por distância, mudança de fase a cada 20 segundos e geração controlada por matriz de ocupação `8x6`.
- **Vidas e invulnerabilidade:** 3 vidas no HUD e `1,35s` de invulnerabilidade após colisão.
- **Áudio integrado:** efeitos sonoros em `.wav` para propulsão (`nave.wav`), meteoros (`meteoro.wav`) e perda de vida (`perdeu_vida.wav`).
- **Top 5 recordes:** salvamento automático das 5 maiores pontuações em `magnetron_scores.txt`.
- **Visual retrô:** pixel art por código, estrelas animadas, *scanlines* CRT e fonte **Press Start 2P**.

<details>
<summary><b>🎮 Ver Controles</b></summary>

<br>

| Tecla | Ação |
|-------|------|
| `W` / `↑` | Mover para cima |
| `A` / `←` | Mover para a esquerda |
| `S` / `↓` | Mover para baixo |
| `D` / `→` | Mover para a direita |
| `ENTER` ou `ESPAÇO` | Iniciar o jogo |
| `P` | Pausar / continuar |
| `R` | Reiniciar após Fim de Jogo |
| `ESC` | Sair do jogo |

</details>

---

## 📁 Estrutura do Projeto

<details>
<summary><b>Clique para expandir a árvore de arquivos</b></summary>

```
Magnetron/
├── .vscode/
│   ├── launch.json                 # Configurações de debug (GDB / LLDB)
│   ├── settings.json               # Configurações do editor
│   └── tasks.json                  # Tarefas de build (Windows, Linux e macOS)
├── build/
│   ├── premake5.lua                # Script de geração dos arquivos de build
│   ├── premake5                    # Premake5 (Linux)
│   ├── premake5.exe                # Premake5 (Windows)
│   └── premake5.osx                # Premake5 (macOS)
├── resources/
│   ├── Press_Start_2P/
│   │   ├── OFL.txt
│   │   └── PressStart2P-Regular.ttf
│   └── sounds/
│       ├── meteoro.wav
│       ├── nave.wav
│       └── perdeu_vida.wav
├── src/
│   ├── colisao.c / colisao.h       # Detecção de colisão nave x asteróides
│   ├── estilo.h                    # Paleta de cores do jogo
│   ├── main.c                      # Loop principal, HUD, estados e telas
│   ├── nave.c / nave.h             # Movimentação, desenho e hitbox da nave
│   ├── obstaculos.c / obstaculos.h # Lista encadeada e matriz 8x6 dos asteróides
│   ├── recordes.c / recordes.h     # Leitura e gravação do Top 5
│   └── sons.c / sons.h             # Gerenciamento e disparo dos efeitos sonoros
├── Makefile
├── Magnetron.make
├── raylib.make
├── build-MinGW-W64.bat
├── build-VisualStudio2022.bat
├── build-VisualStudio2026.bat
└── README.md
```

</details>

---

## 📦 Como Compilar e Executar

Na primeira geração do projeto, o Premake baixa o código-fonte da [raylib](https://github.com/raysan5/raylib), então é necessária **conexão com a internet** nessa etapa.

```bash
git clone https://github.com/lucassmnasc/Magnetron.git
cd Magnetron
```

> **Dica:** execute sempre o jogo a partir da **pasta raiz do projeto** para carregar `resources/` e salvar `magnetron_scores.txt` no local correto.

<details>
<summary><b>⚡ Via VS Code (Windows, Linux e macOS)</b></summary>

<br>

1. Abra a pasta `Magnetron` no **VS Code**.
2. Pressione **`Ctrl+Shift+B`** (Windows/Linux) ou **`Cmd+Shift+B`** (macOS) para rodar **`build debug`**.
3. Pressione **`F5`** para compilar e iniciar com o depurador.

</details>

<details>
<summary><b>🪟 Windows (MinGW-W64 ou Visual Studio)</b></summary>

<br>

**Pré-requisitos:** [MinGW-W64](https://www.mingw-w64.org/) (`mingw32-make.exe` no `PATH`) **ou** Visual Studio 2022/2026 com *"Desenvolvimento para desktop com C++"*.

**Opção A — MinGW-W64:**

```bat
build-MinGW-W64.bat
mingw32-make config=debug_x64
bin\Debug\Magnetron.exe
```

*(Sem usar o `.bat`:)*

```bat
cd build
premake5.exe gmake
cd ..
mingw32-make config=debug_x64
bin\Debug\Magnetron.exe
```

**Opção B — Visual Studio:**

1. Execute `build-VisualStudio2022.bat` (ou `build-VisualStudio2026.bat`).
2. Abra `Magnetron.sln`, defina **Magnetron** como projeto de inicialização e pressione **F5**.

</details>

<details>
<summary><b>🐧 Linux</b></summary>

<br>

**Dependências (Debian/Ubuntu):**

```bash
sudo apt update
sudo apt install build-essential git libasound2-dev libx11-dev libxrandr-dev \
  libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev \
  libwayland-dev libxkbcommon-dev
```

**Compilar e executar:**

```bash
cd build
chmod +x premake5
./premake5 gmake
cd ..
make config=debug_x64
./bin/Debug/Magnetron
```

> No **WSL**, a janela gráfica exige o **WSLg** (Windows 11 ou WSL atualizado com `wsl --update`).

</details>

<details>
<summary><b>🍎 macOS (Apple)</b></summary>

<br>

**Pré-requisito:**

```bash
xcode-select --install
```

**Compilar e executar:**

```bash
cd build
chmod +x premake5.osx
./premake5.osx gmake
cd ..
make config=debug_arm64   # Apple Silicon (M1/M2/M3/M4)
# make config=debug_x64   # Processador Intel
./bin/Debug/Magnetron
```

> Caso o macOS bloqueie o `premake5.osx`, libere em **Ajustes do Sistema → Privacidade e Segurança** e execute novamente.

</details>

<details>
<summary><b>🚀 Recompilação e Build Release</b></summary>

<br>

- **Após alterar arquivos `.c`/`.h` existentes:** não precisa rodar o Premake de novo — basta executar `make` (ou `mingw32-make`).
- **Versão otimizada (`bin/Release/`):**

```bash
make config=release_x64    # Linux / Windows (MinGW) / macOS Intel
make config=release_arm64  # macOS Apple Silicon
./bin/Release/Magnetron
```

</details>

---

## 📄 Licenças

- [raylib](https://github.com/raysan5/raylib) — licença **zlib/libpng**.
- **Press Start 2P** — licença **SIL Open Font License** ([OFL.txt](resources/Press_Start_2P/OFL.txt)).
