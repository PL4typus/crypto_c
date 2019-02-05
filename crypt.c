#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crypt.h"
#include "encrypt.h"
#include <math.h>

/**
 *  * chiffrement utilisant le ou exclusif
 *   */
void xor_crypt(char * key, char * texte, char* chiffre)
{
    int i;
    for(i=0; (i<strlen(texte)) && (texte[i]!='\0');i++){
        chiffre[i] = texte[i] ^ key[i%strlen(key)]; //Key repeat if it is < size of text
    }
    chiffre[strlen(texte)]='\0';
}

/**
 *  * dÈchiffrement utilisant le ou exclusif
 *   */
void xor_decrypt(char * key, char * texte, char* chiffre)
{
	xor_crypt(key,texte,chiffre); //xor_crypt = xor_decrypt
}

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
 *  * dÈchiffrement utilisant  cesar
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
 *  * dÈchiffrement utilisant viginere
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
        chiffre[i] = offset;

    }
    
}

/**
 *  * chiffrement utilisant des
 *   */
void des_crypt(char * key, char * texte, char* chiffre, int size)
{
    int i;
    //chiffrement du premier bloc
    des_encipher((const unsigned char*)texte,(unsigned char*)chiffre,(const unsigned char*)key);
    for(i=1; i< size; i++){
        //chiffrement des blocs suivants
        des_encipher((const unsigned char*)texte+(i*8),(unsigned char*)chiffre+(i*8),NULL);
    }
        
}



/**
 *  * dÈchiffrement utilisant des
 *   */
void des_decrypt(char * key, char * chiffre, char* dechiffre, int size)
{
    int i;
    //DÈchiffrement du premier bloc
    des_decipher((const unsigned char*)chiffre,(unsigned char*)dechiffre,(const unsigned char*)key);
    for(i=1;i<size;i++){
        //dechiffrement des blocs suivants (toutes les 8 "cases")
        des_decipher((const unsigned char*)chiffre+(i*8),(unsigned char*)dechiffre+(i*8),NULL);
    }
}

/**
 *  * chiffrement utilisant 3des
 *   */
void tripledes_crypt(char * key1, char * key2, char * texte, char* chiffre,int size)
{
    char * chiffre_temp;
    //on chiffre une fois avec key1
    des_crypt(key1,texte,chiffre,size);
    chiffre_temp = chiffre;
    //AprËs on dechiffre chiffre avec la key2
    des_decrypt(key2,chiffre,chiffre_temp,size);
    //finalement on chiffre le rÈsultat avec la key1
    des_crypt(key1,chiffre_temp,chiffre,size);

}


/**
 *  * dÈchiffrement utilisant 3des
 *   */
void tripledes_decrypt(char* key1, char* key2, char* chiffre, char* dechiffre, int size)
{
    char* chiffre_temp=dechiffre;
    //On dechiffre une premiËre fois avec key1
    des_decrypt(key1,chiffre,dechiffre,size);
    //puis on rechiffre avec key2
    des_crypt(key2,dechiffre,chiffre_temp,size);
    //Et enfin on dechiffre avec la key1 ‡ nouveau. 
    des_decrypt(key1,chiffre_temp,dechiffre,size);

}


/****************************************************************
 *                                                               *
 *  -------------------------- modexp -------------------------  *
 *                                                               *
 ****************************************************************/

static Huge modexp(Huge a, Huge b, Huge n) {
	
	Huge               y;
	
	/****************************************************************
	 *                                                               *
	 *  Calcule (pow(a, b) % n) avec la mÈthode du carrÈ binaire     *
	 *  et de la multiplication.                                     *
	 *                                                               *
	 ****************************************************************/
	
	y = 1;
	
	while (b != 0) {
		
		/*************************************************************
		 *                                                            *
		 *  Pour chaque 1 de b, on accumule dans y.                   *
		 *                                                            *
		 *************************************************************/
		
		if (b & 1)
			y = (y * a) % n;
		
		/*************************************************************
		 *                                                            *
		 *  …lÈvation de a au carrÈ pour chaque bit de b.             *
		 *                                                            *
		 *************************************************************/
		
		a = (a * a) % n;
		
		/*************************************************************
		 *                                                            *
		 *  On se prÈpare pour le prochain bit de b.                  *
		 *                                                            *
		 *************************************************************/
		
		b = b >> 1;
		
	}
	
	return y;
	
}


/**
 * Transforme une chaine de caractère en chaine d'entier
 */
void texttoint(char * texte, char* chiffre, int size){
	*chiffre='\0';
	int tmp;
	int i;
	for(i=0;i<size;i++){		
	    // on ajoute 10 pour éviter le problème de disparition du 0 devnt les entiers entre 1 et 9 (01 a 09)
		// ceci évite de découper le texte en bloc de taille < n et de les normaliser ensuite
		tmp=(*(texte+i)-'a'+10);
		sprintf(chiffre+strlen(chiffre),"%d%c",tmp,'\0');
	}
}

/**
 * Transforme une chaine d'entier en chaine de caractère
 */ 
void inttotext(char * texte, char* chiffre){
	*chiffre='\0';
	int tmp=0;
	while((*texte) != '\0'){	
	    // lettre de l'alphabet (0..25 correspond pour nous à 10..35)	
		if(10*tmp+(*(texte)-'0') > 36){
		    // on déduit donc 10 pour obtenir la bonne lettre dans l'alphabet
			sprintf(chiffre+strlen(chiffre),"%c%c",tmp+'a'-10, '\0');
			tmp=0;
		}
		tmp=10*tmp+(*(texte)-'0');
		texte++;
	}
}

/**
 * Chiffrement RSA
 */
void rsa_crypt(int e, int n, char * texte, char* chiffre, int size)
{
    int tmp;
	Huge buf=0;
	char* pt;
	char* btmp = (char *)malloc(strlen(texte) * sizeof(char)); 
	
	texttoint(texte,btmp,size);
	pt = btmp;
	*chiffre='\0';
	while((*pt) != '\0'){
		tmp=*pt-'0';
		if(10*buf + tmp >= n){
		    // on utilise le $ comme séparateur de bloc
			sprintf(chiffre+strlen(chiffre),"%ld$%c",modexp(buf,e,n),'\0');
			buf=0;
		}
		buf=10*buf+tmp;
		pt++;
	}
	sprintf(chiffre+strlen(chiffre),"%ld$%c",modexp(buf,e,n),'\0');
	printf("\n");
}

/**
 * Déchiffrement RSA
 */
void rsa_decrypt(int d, int n, char * texte, char* chiffre)
{
	int tmp;
	char* pt=texte;
	char* tmpc= (char *)malloc(strlen(texte) * sizeof(char)); 
	Huge buf=0;
	
	*tmpc='\0';
	while((*pt) != '\0'){
		// on utilise le $ comme séparateur de bloc
	    if((*pt) == '$'){
			sprintf(tmpc+strlen(tmpc),"%ld%c", modexp(buf,d,n),'\0');
			buf=0;
		}else{
			tmp=*pt-'0';
			buf=10*buf+tmp;
		}
		pt++;
	}
	sprintf(tmpc+strlen(tmpc),"%ld%c",modexp(buf,d,n),'\0');
	
	inttotext(tmpc,chiffre);
}


