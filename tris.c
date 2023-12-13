#include <stdio.h>
#include <stdlib.h>
#define C 3
#define R 3

int mat[R][C];
int giocatore = 1;
int mosse;

void stampa_mat() {
	int i, j, k;
	printf("\n");
	for (i = 0, k = 0; i < R; i++) {
		printf("------------------------\n");
		for (j = 0; j < C; j++) {
			switch (mat[i][j]) {
				case 0:
					printf("   %c   |", '-'); //nel caso la casella sia a 0 (non ancora scelta)
					break;
				case 1:
					printf("   %c   |", 'X');
					break;
				case 2:
					printf("   %c   |", 'O');
					break;
			}
		}
		printf("\n");
		for (; k < (i + 1) * 3; k++) //stampa delle posizioni dei numeri della matrice (1,2,3...)
			printf("   %d   |", k + 1);
		printf("\n");
	}
	printf("------------------------\n");
}

void inserisci_valore() {
	int posCasella;
	printf("Inserisci numero casella: ");
	scanf("%d", &posCasella);

	if ((posCasella >= 1 && posCasella <= 9)) {
		if (posCasella >= 1 && posCasella <= 3 && mat[0][posCasella - 1] == 0) { //controllo che sia nella prima riga
			mat[0][posCasella - 1 ] = giocatore; //assegnazione in base al giocatore che sta giocando
			mosse++;
		} else if (posCasella >= 3 && posCasella <= 6 && mat[1][posCasella - 4] == 0) { //controllo che sia nella seconda riga
			mat[1][posCasella - 4] = giocatore;
			mosse++;
		} else if (posCasella >= 6 && posCasella <= 9 && mat[2][posCasella - 7] == 0) { //controllo che sia nella terza riga
			mat[2][posCasella - 7] = giocatore;
			mosse++;
		} else {
			printf("La casella e' occupata\n");
			inserisci_valore();
		}
	} else {
		printf("Hai inserito un valore sbagliato\n");
		inserisci_valore();
	}
}

int controllo() {
	int vincitore = 0;
	int i, j;
	int count1 = 0; //contatore "punti" primo giocatore
	int count2 = 0; //contatore "punti" secondo giocatore

	for (i = 0; i < R; i++) { //controllo per righe
		for (j = 0, count1 = 0, count2 = 0; j < C; j++) {
			if (mat[i][j] == 1)
				count1++;
			if (mat[i][j] == 2)
				count2++;
		}
		if (count1 == 3) vincitore = 1;
		if (count2 == 3) vincitore = 2;
	}

	for (i = 0, count1 = 0, count2 = 0; i < C && vincitore == 0; i++) { //controllo per colonne
		for (j = 0, count1 = 0, count2 = 0; j < R; j++) {
			if (mat[j][i] == 1)
				count1++;
			if (mat[j][i] == 2)
				count2++;
		}
		if (count1 == 3) vincitore = 1;
		if (count2 == 3) vincitore = 2;
	}

	for (i = 0, j = 0, count1 = 0, count2 = 0; i < R && vincitore == 0; i++, j++) { //controllo in diagonale da sinistra (
		if (mat[i][j] == 1)
			count1++;
		if (mat[i][j] == 2)
			count2++;
		if (count1 == 3) vincitore = 1;
		if (count2 == 3) vincitore = 2;
	}

	for (i = 0, j = C - 1, count1 = 0, count2 = 0; j >= 0 && vincitore == 0; i++, j--) { //controllo in diagonale da destra
		if (mat[i][j] == 1)
			count1++;
		if (mat[i][j] == 2)
			count2++;
		if (count1 == 3) vincitore = 1;
		if (count2 == 3) vincitore = 2;
	}
	return vincitore;
}

int main() {
	printf("--------\n");
	printf("| Tris |");
	printf("\n--------\nCreato da Enrico Officioso");

	int vincitore = 0;

	while (!controllo() && mosse < 9) {
		stampa_mat();
		inserisci_valore();
		if (mosse % 2 == 0) {
			giocatore = 1;
		} else {
			giocatore = 2;
		}

		vincitore = controllo();
		if (vincitore == 1) {
			stampa_mat();
			printf("Ha vinto il primo giocatore ( X )");
		} else if (vincitore == 2) {
			stampa_mat();
			printf("Ha vinto il secondo giocatore ( O )");
		}
	}
	if (vincitore == 0) {
		stampa_mat();
		printf("Non ha vinto nessuno");
	}

	return 0;
}
