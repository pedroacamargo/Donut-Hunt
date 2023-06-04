<h3 align="center"><img src="https://github.com/pedroacamargo/Donut-Hunt/blob/main/imgs/DonutHunt.png"></img></h3> <hr>
<p>
  <strong>Donut Hunt</strong> - Roguelike desenvolvido em C, baseado somente em caracteres da tabela ASCII, onde o objetivo é sobreviver, passar os diferentes níveis e, talvez, achar o seu tão desejado donut. O jogo foi desenvolvido para a disciplina "Laboratórios de Algoritmia 1" do curso de Ciências da Computação na Universidade do Minho, onde <strong>Donut Hunt</strong> foi o projeto final.
</p>

<hr>

# Index

- [1. Objetivos Minimos](https://github.com/pedroacamargo/Donut-Hunt/#1-objetivos-minimos)
- [2. Features](https://github.com/pedroacamargo/Donut-Hunt/#2.-features-implementadas-no-jogo)
  - [2.1.1 Main Menu](https://github.com/pedroacamargo/Donut-Hunt/#211-main-menu)
  - [2.1.2 Side Menu](https://github.com/pedroacamargo/Donut-Hunt/#212-side-menu)
  - [2.2.1 Backtracking Procedural Generation](https://github.com/pedroacamargo/Donut-Hunt/#221-backtracking-procedural-generation)
  - [2.2.2 Vines](https://github.com/pedroacamargo/Donut-Hunt/#222-vines)
  - [2.2.3 Vine Rooms | Normal Rooms](https://github.com/pedroacamargo/Donut-Hunt/#223-vine-rooms--normal-rooms)
  - [2.3.1 Vision Radius](https://github.com/pedroacamargo/Donut-Hunt/#231-vision-radius)
  - [2.3.2 Colors](https://github.com/pedroacamargo/Donut-Hunt/#232-colors)
  - [2.4.1 Item Types](https://github.com/pedroacamargo/Donut-Hunt/#241-item-types)
  - [2.4.2 Item Spawn Chances](https://github.com/pedroacamargo/Donut-Hunt/#242-item-spawn-chances)
  - [2.4.3 Backpack](https://github.com/pedroacamargo/Donut-Hunt/#243-backpack)
  - [2.5.1 Monster Types & Spawn Rate](https://github.com/pedroacamargo/Donut-Hunt/#251-monster-types--spawn-rate)
  - [2.5.2 Monster Stats](https://github.com/pedroacamargo/Donut-Hunt/#252-monster-stats)
- [3. How To Install](https://github.com/pedroacamargo/Donut-Hunt/#3-how-to-install)
- [4. Contributors](https://github.com/pedroacamargo/Donut-Hunt/#4-contributors)



# 1. Objetivos minimos
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
### 2.4.1 Item Types
Existem 3 tipos de itens:
* **Armor** -> Vai te dar armadura, quando os monstros tentarem hitar o player, caso você tenha armadura, irá reduzir a armadura ao invés da vida. Caso o jogador não possua uma armadura, a vida irá reduzir.
* **Sword** -> Aumenta o dano do jogador.
* **Aneis** -> Dão variados bônus.
Existem 10 itens de cada tipo

### 2.4.2 Item spawn chances
Nas Normal Rooms, existe 30% de chance de spawnar um item variado. Nas Vine Rooms, existe 70% de chance de spawnar um item variado dentro das vinhas.\
**A raridade dos itens quando spawnados é crescente** -> Lvl 1 - 4, raridade 1 - 3. Lvl 4 - 8, raridade 2 - 4. Lvl 9-15, raridade 3 - 5. Lvl > 15, raridade 5.\
Os itens estarão presentes no mapa como '?'.

### 2.4.3 Backpack
O jogo possui um sistema de mochila. Quando o player passa por um '?', um item aleatório daquela raridade irá aparecer na mochila, para equipar basta pressionar **(ENTER)**. Na mochilá conseguirá ver o gasto da armadura, caso queira destruir a armadura gasta, pressione **(T)**. Para movimentar dentro da mochila, utilize o **(A)** ou **(D)**. 

## 2.5 Monsters - [Pedro Camargo](https://github.com/pedroacamargo) & [Tiago Machado](https://github.com/Maloco02)
### 2.5.1 Monster Types & Spawn Rate
Existem três tipos de monstros: **Esqueletos, Goblins e Dragões**.\
* **Esqueletos** -> 95% Pisos 1 - 4 | 70% Pisos 5 - 9 | 50% Pisos 10 - 14 | 30% Pisos > 15
* **Goblins** -> 5% Pisos 1 - 4 | 25% Pisos 5 - 9 | 40% Pisos 10 - 14 | 30% Pisos > 15
* **Dragões** -> 0% Pisos 1 - 4 | 5% Pisos 5 - 9 | 10% Pisos 10 - 14 | 40% Pisos > 15

### 2.5.2 Monsters Stats

<table align="center">
  <tr><th>Monster</th><th>Char</th><th>Life</th><th>Damage</th></tr>
  <tr align="center"><td>Skeleton</td><td>'S'</td><td>50</td><td>5</td></tr>
  <tr align="center"><td>Goblin</td><td>'G'</td><td>75</td><td>10</td></tr>
  <tr align="center"><td>Dragon</td><td>'D'</td><td>500</td><td>50</td></tr>
</table>

# 3. How to install
## 3.1 Clone o repositório para algum diretório local
>&nbsp;
>```cmd
>> git clone https://github.com/pedroacamargo/Donut-Hunt
>```
>&nbsp;

## 3.2 Tenha certeza que você tem o ncurses instalado
>&nbsp;
>```cmd
> Ubuntu
>> sudo apt-get install libncurses5-dev libncursesw5-dev
>
> Arch Linux based distros
>> sudo pacman -S ncurses
>```
>&nbsp;

## 3.3 Instale o jogo e jogue
>&nbsp;
>```cmd
>> make
>> ./play
>```
>&nbsp;

# 4. Contributors

<table>
<tr>
 <th><strong><a href="https://github.com/pedroacamargo">Pedro Camargo</a></strong></th>
 <th><strong><a href="https://github.com/Sousini">João Sousa</a></strong></th>
 <th><strong><a href="https://github.com/Maloco02">Tiago Machado</a></strong></th>
 <th><strong><a href="https://github.com/bernazyzz">Bernardo Moniz</a></strong></th>
</tr>
<tr>
 <td align="center"><img src="https://avatars.githubusercontent.com/u/98715404?s=400&u=1d27a23534700cfa2fb02fc716db89b023abb54d&v=4" width="150"></td>
  <td align="center"><img src="https://avatars.githubusercontent.com/u/116192076?v=4" width="150"></td>
  <td align="center"><img src="https://avatars.githubusercontent.com/u/115084153?v=4" width="150"></td>
  <td align="center"><img src="https://avatars.githubusercontent.com/u/114089668?v=4" width="150"></td>
</tr>
</table>
