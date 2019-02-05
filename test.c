#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypt.h" 

/**
 *  *
 *   * Usage : xor_crypt key input_file output_file
 *    *
 *     */
int main(int argc, char *argv[]){
	FILE* pFile;
	long lsize;
	char* texte;
	char* chiffre;
	char* dechiffre;
	int size;

	pFile = fopen( argv[1] , "rb");
	if (pFile == NULL) return 1;

	fseek (pFile, 0 , SEEK_END);  // Obtient la taille du fichier
	lsize = ftell (pFile);
	rewind (pFile);

	texte = (char*) malloc (lsize+1);   //Alloue mémoire pour le tampon, de la taille du fichier
	if (texte ==  NULL) return 2;

	fread (texte, 1, lsize, pFile); // copie fichier vers tampon
	texte[lsize]='\0';
        
	size = (strlen(texte)+7)/8;


	chiffre = (char *)malloc(8+strlen(texte) * sizeof(char));
	dechiffre = (char *)malloc(8+strlen(texte) * sizeof(char));
	printf("----------------   CESAR --------------\n");
	cesar_crypt(2, texte,chiffre);
	printf("'%s'\n",chiffre);
	cesar_decrypt(2, chiffre, dechiffre);
	printf("'%s'\n",dechiffre);
	printf("%s\n", strcmp(texte, dechiffre)==0?"ok":"NON");


	chiffre = (char *)malloc(8+strlen(texte) * sizeof(char));
	dechiffre = (char *)malloc(8+strlen(texte) * sizeof(char));
	printf("----------------   VIGENRE --------------\n");
	viginere_crypt("abc", texte,chiffre);
	viginere_decrypt("abc", chiffre, dechiffre);
	printf("'%s'\n",chiffre);
	printf("'%s'\n",dechiffre);
	printf("%s\n", strcmp(texte, dechiffre)==0?"ok":"NON");

	fclose (pFile);  // ferme le flux et
	free(texte); // libère espace tampon

	return 0;
}
