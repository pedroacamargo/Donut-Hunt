<h3 align="center"><img src="https://github.com/pedroacamargo/Donut-Hunt/blob/main/imgs/DonutHunt.png"></img></h3> <hr>
<p>
  <strong>Donut Hunt</strong> - Roguelike desenvolvido em C, baseado somente em caracteres da tabela ASCII, onde o objetivo é sobreviver, passar os diferentes níveis e, talvez, achar o seu tão desejado donut. O jogo foi desenvolvido para a disciplina "Laboratórios de Algoritmia 1" do curso de Ciências da Computação na Universidade do Minho, onde <strong>Donut Hunt</strong> foi o projeto de finalização da UC.
</p>

<hr>

## 1. Objetivos mínimos
>&nbsp;
>* Fazer uma geração de mapas de forma aleatória, utilizando algum algoritmo de **procedural generation**
>* Fazer a movimentação do jogador com __WASD__ ou __ARROWS__
>* Fazer a iluminação (Visão do jogador)
>* Monstros
>
>&nbsp;

# 2. Features implementadas no jogo
## 2.1 Menus - [João Sousa](https://github.com/Sousini) & [Pedro Camargo](https://github.com/pedroacamargo)
### 2.1.1 Main Menu
Antes de começar a jogar, o usuário dispõe de um menu onde é possível ver as instruções, sair ou começar a jogar. Além disso, possui uma linda arte escrita "Donut Hunt", representada na imagem no começo do readme.

### 2.1.2 Side Menu
O side menu dispões de 3 áreas:
* **Stats** -> Aqui o jogador verá todos os status e estatísticas do jogo, até a sua morte.
* **Actions** -> Dá mais vida para o jogo, todo o histórico do que aconteceu aparecerá aqui. Caso você tenha visto um monstro, uma vinha, um item, o histórico de erosão de mapa, caminho bloqueado, dificuldade aumentada, etc.
* **Inventory** -> Parte mais importante do menu. Caso aperte __(Y)__, poderá ver todos os itens equipados nos slots de armor, sword e specialItem. Caso queira acessar um item, poderá ver tudo sobre o item equipado, seu nome, seu dano/defesa/buff, sua história, etc.


## 2.2 Map generation - [Pedro Camargo](https://github.com/pedroacamargo)
### 2.2.1 Backtracking procedural generation
This feature was fully implemented by **Pedro Camargo**, you can check the algorithm used and developed in **[Pedro Camargo](https://github.com/pedroacamargo/Procedural-Generation-Backtracking)**  repository.\
O algoritmo foi inspirado em backtracking, ou seja, a primeira sala será gerada (o spawn do player), após isso tentará ser criada outra sala em X direções, o algoritmo escolhe a melhor direção de todas as salas, junta tudo e conecta todas com portas aleatória, formando o mapa completo.

### 2.2.2 Vines
As vinhas cancelam a visão do jogador, mas podem ser sobrepostas. Caso queira tirar uma vinha do mapa basta andar sobre ela e a mesma sumirá.

### 2.2.3 Vine Rooms / Normal Rooms
Para dar mais randomização na geração de mapas, foram criados 2 tipos de salas:
* **Normal Rooms** -> Salas normais, quadradas, com dimensões de 10x4-19x9, possui 70% de chance de spawnar quando o mapa está gerando as salas e não possui vinhas no começo, somente poderá possuir vinhas devido à erosão de mapa. Além disso, possui 30% de chance de spawnar uma Normal Room junto com um item aleatório em seu interior.
* **Vine Rooms** -> Salas com vinhas, retangulares, com dimensões de 30x6-44x6, possui 30% de chance de spawnar quando o mapa está gerando as salas e em seu interior possui um vineCenter e vineWidth onde randomiza a posição e largura da geração das vinhas dentro da sala, além disso, podem ser geradas mais vinhas ao longo do jogo com a erosão de mapa. Existe uma chance de 70% de dentro de uma Vine Room, dentro das vinhas, nascer um item aleatório.

### 2.2.4 Map Erosion
De forma a deixar a permanência em um nível mais difícil, foi criado um sistema de erosão de mapa, de forma a forçar o jogador a descer de piso mais rapidamente. A cada 50 turnos do jogador, será randomizado um x/y do mapa para nascer vinhas, de forma que dificulte a locomoção do jogador e diminui a visibilidade das salas.

## 2.3 Brightness - [Tiago Machado](https://github.com/Maloco02)
### 2.3.1 Vision Radius
O player possui um raio de visão de 25 pixels, caso haja uma parede, vinha ou item, a luz não ultrapassará.
### 2.3.2 Colors
Foi através da iluminação que as cores começaram a ser desenvolvidas, sem a iluminação e cores o jogo seria totalmente diferente.\
Com as cores surgem 5 raridades de itens:
* Branca - Itens comuns
* Azul - Itens raros
* Amarelo - Itens muito raros
* Verde - Itens épicos
* Vermelho - Itens ultimate

## 2.4 Items - [Pedro Camargo](https://github.com/pedroacamargo) & [Bernardo Moniz](https://github.com/bernazyzz)
### 2.4.1



<p><samp>To create the ./play executable: <code><strong>make build</strong></code> or just <code><strong>make</strong></code></samp> <br>
<samp>To reset all files and delete the executable:  </samp><code><strong>make clean</strong></code> </p> 
