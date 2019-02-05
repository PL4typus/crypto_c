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
  char* chiffre;
  char* dechiffre;
  char* chiffre_to_bf;
  FILE* f;
  char** dictionnary;

  printf("----------------   CESAR --------------\n");
  chiffre_to_bf = "carhzbabhygenzvpebfpbcvpfvyvpbibypnabpbavbfvf";
  printf("\nBruteforcing given sentence: %s\n",chiffre_to_bf);
  chiffre = (char *)malloc(8+strlen(chiffre_to_bf) * sizeof(char));
  dechiffre = (char *)malloc(8+strlen(chiffre_to_bf) * sizeof(char));
  strcpy(chiffre, chiffre_to_bf);
  cesar_bruteforce(chiffre, dechiffre);

  printf("----------------   VIGENRE --------------\n");
  chiffre_to_bf =  "no vveaqkac hs vbxijlbys c lfv owcu"

  fclose (pFile);  // ferme le flux et
  free(texte); // libère espace tampon
  return 0;
}
