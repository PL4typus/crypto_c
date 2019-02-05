#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crypt.h"
#include <math.h>


/**
 *  * chiffrement utilisant cesar
 *   */
void cesar_crypt(int decallage, char * texte, char* chiffre)
{
  int i;
  for(i=0; (i<strlen(texte)) && (texte[i]!='\0');i++){
    if(texte[i]>='a' && texte[i] <= 'z'){
      chiffre[i] = texte[i] + decallage;
      if(chiffre[i] > 'z'){
        chiffre[i] = chiffre[i] -'z' +'a' -1;
      }
    }
    else if(texte[i] >= 'A' && texte[i] <= 'Z'){
      chiffre[i] = texte[i] + decallage;
      if(chiffre[i] > 'Z'){
        chiffre[i] = chiffre[i] - 'Z' + 'A' -1;
      }
    }
  }
}

/**
 *  * déchiffrement utilisant  cesar
 *   */
void cesar_decrypt(int decallage, char * texte, char* chiffre)
{
  int i;
  for(i=0; (i<strlen(texte)) && (texte[i]!='\0');i++){
    if(texte[i]>='a' && texte[i] <= 'z'){
      chiffre[i] = texte[i] - decallage;
      if(chiffre[i] < 'a'){
        chiffre[i] = chiffre[i] +'z' -'a' +1;
      }
    }
    else if(texte[i] >= 'A' && texte[i] <= 'Z'){
      chiffre[i] = texte[i] - decallage;
      if(chiffre[i] < 'A'){
        chiffre[i] = chiffre[i] + 'Z' - 'A' +1;
      }
    }
  }

}

void cesar_bruteforce(char* chiffre, char* clair){
  int i;
  for(i = 0;i<=25; i++){
    cesar_decrypt(i, chiffre, clair);
    printf("key = %i \t%s\n",i,clair);
  }
}


/**
 *  * chiffrement utilisant viginere
 *   */
void viginere_crypt(char * key, char * texte, char* chiffre)
{
  int i; 
  char key_i;
  char offset = 0; //offset for encryption in a given round
  for(i=0;i<strlen(texte) && texte[i]!='\0';i++){
    //if the key is shorter than text, repeats the key
    key_i=key[i%strlen(key)];

    //offset the value so thaat Aa=0 &  Zz=0
    if(key_i >= 'a' && key_i <='z'){
      key_i-='a';               
    }
    if(key_i >= 'A' && key_i <= 'Z'){
      key_i-='A';
    }

    offset = (texte[i] +  key_i);
    if( ((texte[i]>='a' && texte[i] <= 'z') && (offset > 'z' )) || ((texte[i]>='A' && texte[i] <= 'Z') && (offset > 'Z' )) ){
      offset-=26;
    }
    chiffre[i] = offset;

  }
}
/**
 *  * déchiffrement utilisant viginere
 *   */
void viginere_decrypt(char * key, char * texte, char* chiffre)
{
  int i; 
  char key_i;
  char offset = 0; //offset for encryption in a given round
  for(i=0;i<strlen(texte) && texte[i]!='\0';i++){
    //if the key is shorter than text, repeats the key
    key_i=key[i%strlen(key)];

    //offset the value so thaat Aa=0 &  Zz=0
    if(key_i >= 'a' && key_i <='z'){
      key_i-='a';               
    }
    if(key_i >= 'A' && key_i <= 'Z'){
      key_i-='A';
    }

    offset = (texte[i] -  key_i);
    if( ((texte[i]>='a' && texte[i] <= 'z') && (offset > 'z' )) || ((texte[i]>='A' && texte[i] <= 'Z') && (offset > 'Z' )) ){
      offset-=26;
    }
    else if( ((texte[i]>='a' && texte[i] <= 'z') && (offset < 'a' )) || ((texte[i]>='A' && texte[i] <= 'Z') && (offset < 'A' )) ){
      offset+=26;
    }

    chiffre[i] = offset;

  }

}

void viginere_bruteforce(char** dictionnary,int dic_size, char* texte, char* chiffre){
  int i;
  for(i=0;i<dic_size;i++){
    viginere_decrypt(dictionnary[i], texte, chiffre);
    printf("%s\t %s\n",dictionnary[i], chiffre);
  }
}

