#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	//real pwd is SECU
	char *entryPwd;
	entryPwd = malloc(50);
	printf("le mot de passe contient 4 lettres");
	scanf("%s", entryPwd);
	if(entryPwd[0] == 'S'){
		if(entryPwd[1] == 'E'){
				if(entryPwd[2] == 'C'){
					if(entryPwd[3] == 'U'){
						printf("Bon mot de passe, bienvenue");
						return 0;
					}
					
				}
			
			}
	}
	printf("mot de passe erroné\n");
	return-1;
}
