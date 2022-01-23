#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include"std_types.h"
/*******************************************************/
/*******global variable to hold user password input*****/
/*******************************************************/
u8 password[10]="\0";


/*******************************************************/
/*******importing global node head from other file******/
/*******************************************************/
extern patient *head;


/*******************************************************/
/*******Array used to Store ID's with reservation*******/
/*******************************************************/
/*6th element used as a flag for noreservations*/
u32 reserves_id[6]={0};


/*******************************************************/
/************Used to simplfy printing process***********/
/*******************************************************/
const u8 slots[6][30]={"2PM to 2:30PM ",
"2:30PM to 3PM ",
"3PM to 3:30PM ",
"3:30PM to 4PM ",
"4PM to 4:30PM ",
"Sorry No free slots available"};


/*******************************************************/
/****************Function to scan a String**************/
/*******************************************************/
void scan_string(u8 **string){
	/*to take a string input with unknown size 
	and allocate its size based on input size 
	30 characters*/
	*string=(u8*)malloc(sizeof(u8));
	
	/*temporary variable to store actual input*/
	u8 temp[30];
	fflush(stdin);
	scanf("%s",temp);
	fflush(stdin);
	u32 i=0;
	for(i=0; temp[i]!='\0'; i++){
		/*copying elements of temp to actual string 
		and allocating size based on input size*/
		string[0][i]=temp[i];
		*string=(u8*)realloc(*string,sizeof(u8)*(i+2));
	}
	string[0][i]='\0';/*adding the NULL characters at string last element */
}


/*******************************************************/
/**********Add a patient to the linked list*************/
/*******************************************************/
void add_patient(void){
	/*start by creating a new node and filling its information */
	patient *new_patient=(patient*)malloc(sizeof(patient));
	new_patient->next=NULL;
	printf("--------------------------------------------------\n");
	printf("*************Fill patient information*************\n");
	printf("First name: ");
	scan_string(&(new_patient->first_name));
	printf("Last name: ");
	scan_string(&(new_patient->last_name));
	printf("Gender [male/female]: ");
	scan_string(&(new_patient->gender));
	printf("Age: ");
	scanf("%d",&new_patient->age);
	fflush(stdin);
	printf("ID: ")	;
	scanf("%d",&new_patient->id);
	
	/*use a while loop to check no repeated ID 
	and raise a flag if false*/
	patient *ptr=head;
	bool flag=0;
	while(ptr!=NULL){
		if(ptr->id==new_patient->id){
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	if (flag){
		/*if entered ID already exists 
		start by freeing all deallocated elements first 
		then deallocating the node*/
		free(new_patient->first_name);
		free(new_patient->last_name);
		free(new_patient->gender);
		free(new_patient);
		printf("ID already exists!!\n");
		printf("New patient entry NOT added\n");
	}else{
		/*if ID is not repeated 
		then search for last node and 
		connecting created node patient 
		right after it*/
		ptr=head;
		while(ptr->next!=NULL ){
			ptr=ptr->next;
		}
		ptr->next=new_patient;
		printf("New Patient entry added SUCCESSFULLY\n");
		
	}
	printf("--------------------------------------------------\n");

}


/*******************************************************/
/**************Edit a patient record********************/
/*******************************************************/
void edit_patient(void){
	fflush(stdin);
	printf("--------------------------------\n");
	u32 id =0;
	printf("Please Enter ID: ");
	scanf("%d",&id);
	
	/*check if entered ID exists in database*/
	patient *ptr =head;
	bool flag=0;
	while(ptr!=NULL){
		if(id==ptr->id){
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	if(!flag){/*if ID doesnt exist*/
		printf("Patient ID dont exist!!\n");
		printf("Terminating process\n");
	}
	while(flag){/*IF ID exists remain offer different edit options*/
		/*stay in edit mode unless 0 is entered*/
		printf("*************EDIT patient*************\n");
		printf("What do you want to Edit?\n");
		printf("1: First name \n");
		printf("2: Second name \n");
		printf("3: Gender \n");
		printf("4: Age \n");
		printf("0: Exit editing mode\n");
		printf("Your choice: ");
		u8 choice=0;
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter new first name: ");
				free(ptr->first_name);
				scan_string(&(ptr->first_name));
				break;
			case 2:
				printf("Enter new last name: ");
				free(ptr->last_name);
				scan_string(&(ptr->last_name));
				break;
			case 3:
				printf("Enter new gender: ");
				free(ptr->gender);
				scan_string(&(ptr->gender));
				break;
			case 4:
				printf("Enter new Age: ");
				scanf("%d",&ptr->age);
				break;
			case 0:
				printf("Exiting Edit mode\n");
				flag=0;
				break;
			default :
				/*if input is not shown in options*/
				printf("Incorrect choice Input\n");
				printf("Please try again");	
		}
	}
	printf("--------------------------------\n");
}


/*******************************************************/
/**************Function to reserve a slot***************/
/*******************************************************/
void reserves_slot(void){
	printf("--------------------------------\n");
	u32 id =0;
	printf("Please Enter ID: ");
	scanf("%d",&id);
	/*check if ID exists */
	patient *ptr =head;
	bool flag=0;
	while(ptr!=NULL){
		if(id==ptr->id){
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	/*check if ID had previous reservations
	if so, termenate process*/
	bool prev_reservation=0;
	for(u32 i=0; i<5; i++){
		if(reserves_id[i]==id){
			prev_reservation=1;
			break;
		}
	}
	
	if(flag && !reserves_id[5] && !prev_reservation){
		/*There is available slots && ID exists && ID had no reservations already*/
		printf("*************Available slots are*************\n");
		for(u32 i=0; i<5; i++ ){/*print slot if no id is in its corrosponding element*/
			if(reserves_id[i]==0){
				printf("Slot %d--> %s\n",i+1,slots[i]);
			}
		}
		printf("Choose a Slot: ");
		u32 choice=0;
		scanf("%d",&choice);
		
		/*Check If chosen slot is actually empty*/
		if(reserves_id[choice-1]==0){
			reserves_id[choice-1]=id;
		}else {
			printf("INVALID SLOT CHOICE!!!\n");
		}
		
		/*Check if all slots are reserved, if so: reserves_id 6th element 
		is set to 1 to show all slots are full*/
		for(u32 i=0; i<5; i++){
			if(!reserves_id[i]){
				reserves_id[5]=0;
				break;
			}else{
				reserves_id[5]=1;
			}
		}
	}
	else if(ptr==NULL){/*IF ID doesnt Exist*/
		printf("Patient ID dont exist!!\n");
		printf("Terminating process\n");
	}
	else if (reserves_id[5]){/*IF all slots are reserved*/
		printf("%s\n",slots[5]);
	}else{
		/*If there areavailable slots and the ID already had a reserved slot*/ 
		printf("This patient already had a reservation \nPlease cancel old reservation first before reserving again \n");
	} 
	printf("--------------------------------\n");
}


/*******************************************************/
/************Function to cancel a reseration************/
/*******************************************************/
void cancel_reservation(void){
	printf("--------------------------------\n");
	u32 id =0;
	printf("Please Enter ID: ");
	scanf("%d",&id);
	
	/*Check if ID exists*/
	patient *ptr=head;
	bool flag= 0;
	while (ptr!=NULL){
		if(id==ptr->id){
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	
	
	if(flag){/*if id exists */
		flag=0;
		for (u8 i=0; i<5; i++){
			/*check if ID had a reservation and delete it*/
			if (id==reserves_id[i]){
				flag=1;
				reserves_id[i]=0;
				reserves_id[5]=0;
				break;
			}
		}
		if(flag){
			/*If ID has a reservation */
			printf("Reservation cancelled successfully\n");
		}else{
			printf("This ID has no reservations!!!\n");
		}
	}else{/*IF ID doesnt exist in nodes*/
		printf("INVALID ID!!!");
	}
	printf("--------------------------------\n");
	
}


/*******************************************************/
/****************Function t print records***************/
void view_records(void){
	printf("--------------------------------\n");
	u32 id =0;
	printf("Please Enter ID: ");
	scanf("%d",&id);
	
	/*Check if ID Exists and find its nodes*/
	patient *ptr =head;
	bool flag=0;
	while (ptr!=NULL){
		if(ptr->id==id){
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	if (flag){/*If ID Exists */
		printf("*************Patient Information*************\n");
		printf("First name : %s\n",ptr->first_name);
		printf("Last name: %s\n",ptr->last_name);
		printf("Gender: %s\n",ptr->gender);
		printf("Age: %d\n",ptr->age);
		printf("ID: %d\n",ptr->id);
		u8 i=0;
		/*Check if it has a reservation and print it*/
		for (i=0; i<5; i++){
			if(id==reserves_id[i])
				break;
		}
		if(i<5)
			printf("Patient have reservation from %s\n",slots[i]);
		else
			printf("Patient have no reservations\n");
	}else{
		printf("ID does not EXIST!!!\n");
	}
	printf("--------------------------------\n");

}
/*-----------------------------------------------------*/
void view_reservations(void){
	printf("--------------------------------\n");
	printf("*************Reservations*************\n");
	for(u8 i=0; i<5; i++){
		/*print reservation with a Zero value crossponding to the ID*/
		if(reserves_id[i])
			printf("From %s : Patient ID (%d)\n",slots[i],reserves_id[i]);
	}
	printf("--------------------------------\n");
	
}
/*-----------------------------------------------------*/
void get_pass(void){/*handles taking password input with increaption from user*/
	password[0]='\0';
	u8 ch;
	u8 i=0;
	fflush(stdin);
	
	while(i<10){
		
		ch=getch();
		if (ch==13){/*If ch is enter(13 in ascii)*/
			break;
		}else if (ch==32 || ch==9){/*If ch is tab or space then ignore it*/
			continue;
		}else if (ch==8 && i>0){
			/*Only true if cursor is not at position 0*/
			
			/*If ch is backspace then move cursor back 
			overwrite * to  space and move back again
			and decrease position counter*/
			i--;
			printf("\b \b");
		}else if (ch!=8) {
			/*IF ch is a normal character then add to 
			global var password and display a * for encription then increase counter position*/
			password[i]=ch;
			i++;
			printf("*");
		}
	}
	printf("\n");
	password[i]='\0';/*set last character as null*/
	fflush(stdin);/*clear buffer*/
}
/*-----------------------------------------------------*/
















