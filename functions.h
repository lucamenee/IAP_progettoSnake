/**
 * @file functions.h
 * @author Luca Meneghetti
 * @brief Funzioni utilizzate nel progetto snake
 * @date 30/01/2023
 */

/**
 * Controlla se lo snake e' finito in un vicolo ceco
 * @param x, y (le coordinat dello snake), *lab, righe, colonne
 * @return true / false
 */
bool isCieco(int x, int y, char *lab, int righe, int colonne) {
    if ((*(lab + (y - 1) * colonne + x) == '.' || *(lab + (y - 1) * colonne + x) == '#') &&
        (*(lab + (y + 1) * colonne + x) == '.' || *(lab + (y + 1) * colonne + x) == '#') &&
        (*(lab + y * colonne + x - 1) == '.' || *(lab + y * colonne + x - 1) == '#') &&
        (*(lab + y * colonne + x + 1) == '.' || *(lab + y * colonne + x + 1) == '#')) {
            return true;
        } else {
            return false;
        }
}


/**
 * Stampa a schermo il labirinto
 * @param *lab, righe, colonne
 * @return void
 */
void printLab(char *lab, int righe, int colonne) {
    for (int i = 0; i < righe; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("%c", *(lab + i * colonne + j));
        }
        printf("\n");
    }
}
