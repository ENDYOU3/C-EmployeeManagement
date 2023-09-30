#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

typedef struct Node{
	char emp_id[10];
	char first_name[20];
	char last_name[20];
	char gender[10];
	char phone[13];
	char position[20];
	char address[100];
	int age;
	float salary;
	struct Node *next;
}Node;
Node new_employee;
Node *head = NULL;

//main function
void delete_data();
void edit_data();
void import_2csv();

void remove_new_line(char *word){
	int length;
	length = strlen(word);
	word[length-1] = '\0';
}

void write_data(FILE *file_pointer){
	char tmp_enter;
	Node *new_data = (Node*)malloc(sizeof(Node));
	printf("Employee ID : "); fgets(new_employee.emp_id, 10, stdin); remove_new_line(new_employee.emp_id);
	printf("First Name  : "); fgets(new_employee.first_name, 20, stdin); remove_new_line(new_employee.first_name);
	printf("Last Name   : "); fgets(new_employee.last_name, 20, stdin); remove_new_line(new_employee.last_name);
	printf("Gender      : "); fgets(new_employee.gender, 10, stdin); remove_new_line(new_employee.gender);
	printf("Age         : "); scanf("%d", &(new_employee.age)); scanf("%c", &tmp_enter);
	printf("Phone       : "); fgets(new_employee.phone, 13, stdin); remove_new_line(new_employee.phone);
	printf("Position    : "); fgets(new_employee.position, 20, stdin); remove_new_line(new_employee.position);
	printf("Salary      : "); scanf("%f", &(new_employee.salary)); scanf("%c", &tmp_enter);
	printf("Address     : "); fgets(new_employee.address, 100, stdin); remove_new_line(new_employee.address);
	fwrite(&new_employee, sizeof(new_employee), 1, file_pointer);
	if(ferror(file_pointer)){
		printf("Error in writing from file : data_emp.dat\n\n");
		exit(1);
	}
}

void add_new_data(){
	char answer;
	FILE *fp = fopen("data_emp.dat", "ab");
	if(fp == NULL){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	printf("+----------------------------+\n");
	printf("|        Add New Data        |\n");
	printf("+----------------------------+\n");
	do{
		write_data(fp);
		printf("Add new contact complete!\n\n");
	 	printf("Add contact more (Press any key) or Exit home (Press \'e\') : ");
	 	answer = getche();
		printf("\n\n");
	}while(tolower(answer) != 'e');
	fclose(fp);
}

void show_info(Node *head_ref){
	printf("+----------------------------+\n");
	printf("| %-7s | %16s |\n", head_ref->emp_id, head_ref->position);
	printf("+----------------------------+\n");
	printf("| Name    : %-17s|\n", strcat(strcat(head_ref->first_name, " "), head_ref->last_name));
	printf("| Gender  : %-16s |\n", head_ref->gender);
	printf("| Age     : %-3d years old %2s |\n", head_ref->age, " ");
	printf("| Tel     : %-16s |\n", head_ref->phone);
	printf("| Address : %-16s |\n", head_ref->address);
	printf("| Salary  : %-9.2f Bath %2s|\n", head_ref->salary, " ");
	printf("+----------------------------+\n");
}

void collect_data(Node *head_ref){
	strcpy(head_ref->emp_id, new_employee.emp_id);
	strcpy(head_ref->first_name, new_employee.first_name);
	strcpy(head_ref->last_name, new_employee.last_name);
	strcpy(head_ref->gender, new_employee.gender);
	head_ref->age = new_employee.age;
	strcpy(head_ref->phone, new_employee.phone);
	strcpy(head_ref->position, new_employee.position);
	head_ref->salary = new_employee.salary;
	strcpy(head_ref->address, new_employee.address);
	head_ref->next = NULL;
}

int read_data(){
	int count=0;
	Node *new_node, *last;
	FILE *fp = fopen("data_emp.dat", "rb");
	head = NULL;
	if(fp == NULL){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);	
	}
	while(fread(&new_employee, sizeof(Node), 1, fp)){
		new_node = (Node*)malloc(sizeof(Node));
		last = head;
		collect_data(new_node);
		if(head == NULL){
			head = new_node;
		}else{
			while(last->next != NULL){
				last = last->next;
			}
			last->next = new_node;
		}
		if(ferror(fp)){
			printf("Error in reading from file : data_emp.dat\n\n");
			exit(1);
		}
		count++;
	}
	fclose(fp);
	return count;
}

void show_all_data(){
	int count;
	count = read_data();
	if(count != 0){
		printf("+----------------------------+\n");
		printf("|         Found %3d          |\n", count);
		printf("+----------------------------+\n");
		while(head != NULL){
			show_info(head);
			head = head->next;
		}
		printf("\n");
	}else{
		printf("It's empty!\n");
	}
}

void search_data(){
	int count;
	char key[10];
	Node *current ;
	printf("+----------------------------+\n");
	printf("|     Search Data By ID      |\n");
	printf("+----------------------------+\n\n");
	printf("Enter id for search : "); fgets(key, 10, stdin); remove_new_line(key);
	printf("\n");
	count = read_data();
	current = head;
	while(current != NULL){
		if(strcmp(current->emp_id, key) == 0){
			printf("+----------------------------+\n");
			printf("|         Found it!          |\n");
			printf("+----------------------------+\n");
			show_info(current);
			printf("\n");
			break;
		}
		current = current->next;
	}
	printf("Not Found!\n\n");
}

int main(){
	int choice=0;
	char tmp_choice;
	printf("##############################\n");
	printf("# Employee Management System #\n");
	printf("##############################\n");
	do{
		fflush(stdin);
		printf("+----------------------------+\n");
		printf("|            Menu            |\n");
		printf("+----------------------------+\n");
		printf("|  [1] Add new data          |\n");
		printf("|  [2] Delete data           |\n");
		printf("|  [3] Edit data             |\n");
		printf("|  [4] Search data           |\n");
		printf("|  [5] Show all data         |\n");
		printf("|  [6] Import file in .csv   |\n");
		printf("|  [7] Exit program          |\n");
		printf("+----------------------------+\n");
		printf("Select menu : ");
		tmp_choice = getche();
		choice = atoi(&tmp_choice);
		printf("\n\n");
		switch(choice){
			case 1: add_new_data(); break;
			case 2:	delete_data(); break;
			case 3: edit_data(); break;
			case 4: search_data(); break;
			case 5: show_all_data(); break;
			case 6: import_2csv(); break;
			case 7: printf("Exiting the program..."); break;
			default: printf("Please select only number in 1-7\n\n");
		}
	} while(choice != 7);
	return 0;
}

void delete_data(){
	int record=0, count=0;
	char answer;
	char num_record[5];
	FILE *fp = fopen("data_emp.dat", "rb+");
	if(fp==NULL){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	printf("+----------------------------+\n");
	printf("|        Delete Data         |\n");
	printf("+----------------------------+\n");
	// view_all_emp(fp, &record, &count, 0);
	printf("\n");
	if(count != 0){
		while(1){
			printf("Are you sure delete contact (y/n) : ");
			answer = getche();
			printf("\n");
			if(toupper(answer) == 'Y'){
				printf("Enter record number for delete : "); fgets(num_record, 5, stdin);
				if(atoi(num_record) < 1 || atoi(num_record) > record){
					printf("Not found!\n");
				}else{
					fseek(fp, (atoi(num_record)-1)*sizeof(new_employee), SEEK_SET);
					strcpy(new_employee.emp_id, "\0");
					fwrite(&new_employee, sizeof(new_employee), 1, fp);
					if(ferror(fp)){
						printf("Error in writer from file : data_emp.dat\n\n");
						exit(1);
					}else{
						printf("Delete record : %d complete!\n",atoi(num_record));
					}
					break;
				}
			}else if(toupper(answer) == 'N'){
				printf("\n");
				break;
			}else{
				printf("Please enter Y or N only!\n");
			}
		}
	}else{
		printf("All contact already to delete!\n");
	}
	fclose(fp);
}

void edit_data(){
	char answer;
	char id[10];
	FILE *fp = fopen("data_emp.dat", "rb+");
	if(fp == NULL){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	printf("+----------------------------+\n");
	printf("|          Edit Data         |\n");
	printf("+----------------------------+\n\n");
	printf("Enter id for edit : "); fgets(id, 10, stdin);
	remove_new_line(id);
	while(fread(&new_employee, sizeof(new_employee), 1, fp) == 1){
		if(strcmp(id, new_employee.emp_id) == 0){
			printf("\nCurrent data!\n");
			// read_data();			
			printf("Are you sure for edit data (Y/N) : ");
			answer = getche();
			printf("\n");
			if(toupper(answer) == 'Y'){
				fseek(fp, ftell(fp)-sizeof(new_employee), SEEK_SET);
				printf("\nFill in information\n");
				write_data(fp);
				printf("\nEdit employee id %s complete!\n\n", new_employee.emp_id);
				break;
			}else if(toupper(answer) == 'N'){
				printf("\n");
				break;
			}else{
				printf("Please enter Y or N only!\n");
			}
		}
		if(feof(fp)){
			break;
		}
	}
	if(strcmp(id, new_employee.emp_id) != 0){
		printf("\nNot found!\n\n");
	}
	fclose(fp);
}

void import_2csv(){
	FILE *fp = fopen("data_emp.dat", "rb");
	FILE *fp_csv = fopen("data_emp.csv", "w");
	if(fp == NULL){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	if(fp_csv == NULL){
		printf("Can't open this file : data_emp.csv\n");
		exit(1);
	}
	fprintf(fp_csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "EmployeeID","FirstName", "LastName", "Gender", "Age", "Phone", "Position", "Salary", "Address");
	while(fread(&new_employee, sizeof(new_employee), 1, fp) == 1){
		if(ferror(fp)){
			printf("Error in reading from file : context.dat\n\n");
			exit(1);
		}
		if(feof(fp)){
			break;
		}							
		fprintf(fp_csv, "%s,%s,%s,%s,%d,%s,%s,%f,%s\n", new_employee.emp_id, new_employee.first_name, new_employee.last_name, new_employee.gender, new_employee.age, new_employee.phone, new_employee.position, new_employee.salary, new_employee.address);
		if(ferror(fp_csv)){
			printf("Error in writing from file : context.csv\n\n");
			exit(1);
		}
	}
	printf("Importing...\n");
	printf("Import file to .csv complete!\n\n");
	fclose(fp);
	fclose(fp_csv);
}

/*
fix function delete
fix function edit
*/