#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv){
  if(argc < 2){
    printf("Usage: ./caesar message\n");
    return 1;
  }
  char* msg_to_decrypt =malloc(sizeof(char)*strlen("carhzbabhygenzvpebfpbcvpfvyvpbibypnabpbavbfvf"));
  strcpy(msg_to_decrypt,"carhzbabhygenzvpebfpbcvpfvyvpbibypnabpbavbfvf");
  char* msg = argv[1];
  int key = atoi(argv[2]); 

  if(key <= 25 || key >= 0){ 
    char* enc_msg = caesar(msg, key);
    printf("\n%s\n",enc_msg);
    printf("\n%s\n",dec_caesar(enc_msg,key));
    bruteforce(msg_to_decrypt);  
  }else{
    return 1;
  }
  return 0;
}
