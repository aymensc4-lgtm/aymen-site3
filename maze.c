#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>

#define ROWS 23
#define COLS 46

char map[ROWS][COLS] = {
   "#############################################",
   "#.P..........#......#.......#.........#.....#",
   "#.###.###.#.#.#####.#.#####.#.#######.#.###.#",
   "#.#.....#.#.#.....#.#.#.....#.#.....#.#...#.#",
   "#.##.##.#.#.#####.#.#.#.#####.#.###.#.###.#.#",
   "##....#.#.#.#...#.#.#.#.......#.#...#...#.#.#",
   "##.##.#.#.#.#.#.#.#.#.#########.#.#####.#.#.#",
   "#...#.#.#.#.#.#.#.#.#.........#.#.#.....#.#.#",
   "#.#.#.#.#.#.#.#.#.#.#########.#.#.#.#####.#.#",
   "#.#.#.#.#.#.#.#.#.#.........#.#.#.#.....#.#.#",
   "#.#.#.#.#.#.#.#.###########.#.#.#.#####.#.#.#",
   "#.#.#.#.#.#.#...............#.#.#.#...#.#.#.#",
   "#.#.#.#.#.#####################.#.#.#.#.#.#.#",
   "#.#.#.#.........................#.#.#.#.#.#.#",
   "#.#.#############################.#.#.#.#.#.#",
   "#.#.............#.................#.#.#.#.#.#",
   "#.###########.#.#.#################.#.#.#.#.#",
   "#...........#.#.#.................#.#.#.#.#.#",
   "###########.#.#.###############.#.#.#.#.#.#.#",
   "#...........#.#...............#.#.#.#.#.#.#.#",
   "#.#############.###########.#.#.#.#.#.#.#.#.#",
   "#...............#.........#*#.#.#.#.#.#.#.#.#",
   "#############################################",
};

int x, y;

void draw() {
    printf("\033[H\033[J"); // efface la console (simulateur web)
    for (int i = 0; i < ROWS; i++) {
        printf("%s\n", map[i]);
    }
    printf("\nUtilise les touches fléchées pour te déplacer. Appuie sur Q pour quitter.\n");
}

void movePlayer(int dx, int dy) {
    if (map[x + dx][y + dy] == '*') {
        printf("🎉 YOU WIN 🎉\n");
        emscripten_cancel_main_loop();
    } else if (map[x + dx][y + dy] != '#') {
        map[x][y] = '.';
        x += dx;
        y += dy;
        map[x][y] = 'P';
        draw();
    }
}

// Fonction appelée depuis JS
EMSCRIPTEN_KEEPALIVE
void handleInput(int keyCode) {
    if (keyCode == 81) { // Q
        printf("Bye!\n");
        emscripten_cancel_main_loop();
    }
    else if (keyCode == 37) movePlayer(0, -1); // gauche
    else if (keyCode == 39) movePlayer(0, +1); // droite
    else if (keyCode == 38) movePlayer(-1, 0); // haut
    else if (keyCode == 40) movePlayer(+1, 0); // bas
}

void gameLoop() {
    // boucle vide juste pour garder le jeu actif
}

int main() {
    // Trouver la position initiale du joueur
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == 'P') {
                x = i;
                y = j;
            }
        }
    }

    draw();
    emscripten_set_main_loop(gameLoop, 0, 1); // ✅ version C valide
    return 0;
}




