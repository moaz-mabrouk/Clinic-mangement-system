#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"std_types.h"
#include"functions.h"
/*
 *NOTE: structure patient(data type) is defined in std_types.h*
 */
 
/*String used to define correct system password*/
#define pass "12345"
/*Initializing the head node*/
patient *head;
/*intialized a variable used to store input password from user 
 *assuming 10 char would be needed for any defined PASS above*/
extern u8 password[10];/*extern since it is originally in functions.c*/


int main()
{	/*Initializing Dummy HEAD node*/
	head=(patient*)malloc(sizeof(patient));
	head->first_name=(u8*)malloc(sizeof(u8));
	head->last_name=(u8*)malloc(sizeof(u8));
	head->gender=(u8*)malloc(sizeof(u8));
	head->age=0;
	head->id=0;
	head->next=NULL;
	
	/*To select User/Admin mode*/
	s8 mode=0;
	
	while(mode==0){
		/*Start by Scaning mode*/
		printf("--------------------------------\n");
		printf("Please choose mode: 1:Admin OR 2:User OR -1:EXIT->");
		scanf("%d",&mode);
		
		/*If Admin mode selected*/
		if (mode==1){
			printf("ENTER PASSWORD:");
			get_pass();
			u8 trials =1;/*number of trials given for inputing wrong password*/
			
			while (strcmp(password,pass) && trials<3 ){
				/*while for taking wrong password Three times maximum*/
				printf("WRONG password!!!\n");
				printf("Try again, You have %d Trials:",3-trials);
				get_pass();
				trials+=1;
			}
			/*If password is inputed thrice wrong mod=-1 
				breaks outmost while loop to exit system*/
			if(strcmp(password,pass))mode=-1;
			while(!strcmp(password,pass)){/*in case password is correct */
				printf("choose :\n");
				printf("1: Add patient \n");
				printf("2: Edit patient \n");
				printf("3: Reserve slot\n");
				printf("4: Cancel reservation\n");
				printf("0: EXIT ADMIN mode\n");
				printf("Your choice: ");
				mode=0;
				scanf("%d",&mode);
				
				switch(mode){
					case 1:
						add_patient();
						break;
					case 2:
						edit_patient();
						break;
					case 3:
						reserves_slot();
						break;
					case 4:
						cancel_reservation();
						break;
				}
				if(!mode)break;
			}	
		}
		else if(mode==2){/*in case USER mode*/
			while(1){
				mode=0;
				printf("choose :\n");
				printf("1: View patient records\n");
				printf("2: View reservations\n");
				printf("0: EXIT USER mode\n");
				printf("Your choice: ");
				scanf("%d",&mode);
				switch(mode){
					case 1:
						view_records();
						break;
					case 2:
						view_reservations();
						break;
				}
				if(!mode)break;
			}
		}
	}
	printf("*********************************SYSTEM IS SHUTTING DOWN*********************************");
}













