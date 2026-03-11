# Space Invaders Clone em C e SDL2

Um clone do clássico jogo arcade *Space Invaders*, desenvolvido do zero utilizando a linguagem C e a biblioteca gráfica SDL2. Este projeto foi criado com foco acadêmico e de aprimoramento técnico, servindo como uma aplicação prática de Estruturas de Dados e conceitos fundamentais de Desenvolvimento de Jogos.

## 🚀 O que aprendi com este projeto (Destaques Técnicos)

A construção deste jogo exigiu a implementação de sistemas dinâmicos e eficientes, sem o uso de "motores" prontos (como Unity ou Godot). Isso me permitiu aprofundar nos seguintes tópicos:

### 1. Estruturas de Dados Dinâmicas e Alocação de Memória

Em jogos, entidades como projéteis e inimigos são criadas e destruídas a todo instante. Para lidar com isso de forma otimizada:

* **Listas Duplamente Encadeadas (Projéteis):** Implementei uma lista duplamente encadeada para gerenciar as balas (tanto do jogador quanto dos inimigos). Isso permite inserção e remoção de elementos em tempo constante $O(1)$, evitando o custo de realocar grandes blocos de memória sempre que um tiro atinge o alvo ou sai da tela.
* **Array de Listas Encadeadas (Grade de Inimigos):** A "horda" de inimigos foi modelada como um array representando as colunas, onde cada índice aponta para uma lista encadeada contendo as naves. Essa estrutura facilitou a lógica de buscar os limites da horda (para inverter a direção do movimento ao bater na parede) e o processamento de animações individuais.
* **Gerenciamento Manual de Memória:** O ciclo de vida de cada *struct* foi cuidadosamente gerenciado através de ponteiros, usando chamadas de `malloc` e `free` (presentes nos métodos de destruição, como `destroy_bullet` e `destroy_enemy`).

### 2. Conceitos de Game Engine com SDL2

* **Game Loop e Delta Time:** A movimentação e as animações do jogo são multiplicadas pelo `delta_time` (o tempo percorrido entre os quadros). Isso garante que a física do jogo rode na mesma velocidade independente de o computador estar processando a 30 ou 144 FPS.
* **Renderização e Sprite Sheets:** O jogo lê *Sprite Sheets* de arquivos (ex: `enemy_moving.png`, `enemy_dying.png`) e utiliza o mapeamento e corte de retângulos (usando `SDL_Rect` em `SDL_RenderCopy`) para iterar sobre os quadros e criar as animações com tempos específicos.
* **Física Básica e Colisão AABB:** Implementação matemática de detecção de colisão *Axis-Aligned Bounding Box* (Caixa Delimitadora Alinhada aos Eixos) para detectar o impacto exato entre os retângulos de colisão das balas, do jogador e dos alienígenas.
* **Event Polling Contínuo:** O controle do jogador responde instantaneamente utilizando o processamento de estado contínuo do teclado (`SDL_GetKeyboardState`) aliado ao tratador de eventos (`SDL_PollEvent`).

## 🛠️ Ferramentas Utilizadas

O ambiente de desenvolvimento e build foi configurado visando as melhores práticas de C:

* **Linguagem:** C
* **Bibliotecas Gráficas:** SDL2, SDL2_image, SDL2_ttf
* **Compilador:** GCC com flags rigorosas (`-Werror`, `-Wall`, `-Wextra`, `-pedantic`) para garantir código seguro e limpo.
* **Build System:** `Makefile` customizado para automação.
* **Ferramentas de Análise:** Valgrind, utilizado para rastrear e prevenir vazamentos de memória (*memory leaks*).
* **Documentação:** Doxygen + Graphviz para geração de documentação automática e diagramas estruturais.


## 💻 Como Compilar e Executar

### Pré-requisitos

Certifique-se de ter um compilador C (como o GCC) e o `make` instalados. Além disso, é necessário ter as bibliotecas de desenvolvimento do SDL2 instaladas em seu sistema.
No Linux (Ubuntu/Debian), você pode instalar as dependências com:

```bash
sudo apt-get install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev valgrind

```

### Compilando o Jogo

Na raiz do projeto, utilize os comandos providenciados no `Makefile`:

1. Para compilar todos os arquivos fonte e gerar o executável `space_invaders`:
```bash
make all

```


2. Para compilar e executar o jogo automaticamente:
```bash
make run

```


3. Para rodar a análise de vazamento de memória com o Valgrind:
```bash
make val

```


4. Para limpar os arquivos objetos `.o` e os binários gerados:
```bash
make clean

```

## 📚 Como Gerar a Documentação

O código-fonte deste projeto está totalmente documentado seguindo o padrão **Doxygen**. O arquivo de configuração (`Doxyfile`) já está preparado para gerar uma página HTML navegável que inclui **diagramas UML e gráficos de dependência** de todas as estruturas do jogo.

### 1. Instalando os geradores

Para gerar a documentação completa com os gráficos, você precisará do Doxygen e do Graphviz instalados:

```bash
sudo apt-get install doxygen graphviz

```

### 2. Gerando os arquivos

Abra o terminal na raiz do projeto e execute o comando:

```bash
doxygen Doxyfile

```

*Isso lerá todos os arquivos `.c` e `.h` e criará uma pasta chamada `docs/` na raiz do projeto.*

### 3. Visualizando

Após a geração ser concluída, basta abrir o arquivo principal no seu navegador web preferido:

```bash
xdg-open docs/html/index.html

```

*(Ou navegue até a pasta `docs/html/` pelo seu gerenciador de arquivos e dê um duplo clique em `index.html`)*.
