#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypt.h" 

#define BUF_SIZE 64

int compte_ligne(FILE* fichier){
  int c;
  int nLignes = 0;
  int c2 = '\0';

  while((c=fgetc(fichier)) != EOF)
  {
    if(c=='\n')
      nLignes++;
    c2 = c;
  }
  /* Ici, c2 est gal au caractre juste avant le EOF. */
  if(c2 == '\n')
    nLignes--; /* Dernire ligne non finie */
  fseek(fichier,0,SEEK_SET);
  return nLignes;
}


char** fill_dictionnary(FILE* pFile,int lsize){
  int i;
  char** dictionnary = malloc(lsize*sizeof(char*));
  for(i=0;i<lsize;i++){
    dictionnary[i]=malloc(BUF_SIZE*sizeof(char));
    fscanf(pFile,"%s\n",dictionnary[i]);
  }
  return dictionnary;
}


/**
 *  *
 *   * Usage : xor_crypt key input_file output_file
 *    *
 *     */
int main(int argc, char *argv[]){
  char* chiffre;
  char* dechiffre;
  char* chiffre_to_bf;
  FILE* pFile;
  int lsize;
  char** dictionnary;

  pFile = fopen( argv[1] , "rb");
  if (pFile == NULL) return 1;

  lsize = compte_ligne(pFile);

  dictionnary =  fill_dictionnary(pFile,lsize);


  printf("----------------   CESAR --------------\n");
  chiffre_to_bf = "carhzbabhygenzvpebfpbcvpfvyvpbibypnabpbavbfvf";
  printf("\nBruteforcing given sentence: %s\n",chiffre_to_bf);
  chiffre = (char *)malloc(8+strlen(chiffre_to_bf) * sizeof(char));
  dechiffre = (char *)malloc(8+strlen(chiffre_to_bf) * sizeof(char));
  strcpy(chiffre, chiffre_to_bf);
  cesar_bruteforce(chiffre, dechiffre);

  printf("----------------   VIGENRE --------------\n");
  chiffre_to_bf =  "novveaqkachsvbxijlbysclfvowcu";
  printf("\nBruteforcing given sentence: %s\n",chiffre_to_bf);
  chiffre = (char *)malloc(8+strlen(chiffre_to_bf) * sizeof(char));
  dechiffre = (char *)malloc(8+strlen(chiffre_to_bf) * sizeof(char));
  strcpy(chiffre, chiffre_to_bf);

  viginere_bruteforce(dictionnary,lsize,chiffre,dechiffre);

  fclose (pFile);  // ferme le flux et
  return 0;
}
