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

void remove_new_line(char *word){
	int length;
	length = strlen(word);
	word[length-1] = '\0';
}

void write_data(FILE *file_pointer){
	char tmp_enter;
	memset(&new_employee, 0, sizeof(Node));
	printf("Employee ID : "); fgets(new_employee.emp_id, 10, stdin); remove_new_line(new_employee.emp_id);
	printf("First Name  : "); fgets(new_employee.first_name, 20, stdin); remove_new_line(new_employee.first_name);
	printf("Last Name   : "); fgets(new_employee.last_name, 20, stdin); remove_new_line(new_employee.last_name);
	printf("Gender      : "); fgets(new_employee.gender, 10, stdin); remove_new_line(new_employee.gender);
	printf("Age         : "); scanf("%d", &(new_employee.age)); scanf("%c", &tmp_enter);
	printf("Phone       : "); fgets(new_employee.phone, 13, stdin); remove_new_line(new_employee.phone);
	printf("Position    : "); fgets(new_employee.position, 20, stdin); remove_new_line(new_employee.position);
	printf("Salary      : "); scanf("%f", &(new_employee.salary)); scanf("%c", &tmp_enter);
	printf("Address     : "); fgets(new_employee.address, 100, stdin); remove_new_line(new_employee.address);
	fwrite(&new_employee, sizeof(Node), 1, file_pointer);
	if(ferror(file_pointer)){
		printf("Error in writing from file : data_emp.dat\n\n");
		exit(1);
	}
}

void add_new_data(){
	char answer;
	FILE *fp = fopen("data_emp.dat", "ab");
	if(!fp){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	printf("+-----------------------------+\n");
	printf("|         Add New Data        |\n");
	printf("+-----------------------------+\n");
	do{
		write_data(fp);
		printf("Add new contact complete!\n\n");
	 	printf("Add contact more? (Press any key or \'e\' to exit) : ");
	 	answer = getche();
		printf("\n\n");
	}while(tolower(answer) != 'e');
	fclose(fp);
}

void show_info(Node *head_ref){
	printf("+-----------------------------+\n");
	printf("|   %-6s   | %14s |\n", head_ref->emp_id, head_ref->position);
	printf("+-----------------------------+\n");
	printf("| First Name : %-14s |\n", head_ref->first_name);
	printf("| Last name  : %-14s |\n", head_ref->last_name);
	printf("| Gender     : %-14s |\n", head_ref->gender);
	printf("| Age        : %-3d years old  |\n", head_ref->age);
	printf("| Tel        : %-14s |\n", head_ref->phone);
	printf("| Address    : %-14s |\n", head_ref->address);
	printf("| Salary     : %-9.2f Bath |\n", head_ref->salary);
	printf("+-----------------------------+\n");
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

int read_data(Node **head_ref, FILE *file_pointer){
	int count = 0;
	Node *current, *prev;
	if(!file_pointer){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	*head_ref = NULL;
	while(fread(&new_employee, sizeof(Node), 1, file_pointer)){
		current = (Node*)malloc(sizeof(Node));
		prev = *head_ref;
		collect_data(current);
		if(!(*head_ref)){
			*head_ref = current;
		}else{
			while(prev->next){
				prev = prev->next;
			}
			prev->next = current;
		}
		if(ferror(file_pointer)){
			printf("Error in reading from file : data_emp.dat\n\n");
			exit(1);
		}
		count++;
	}
	return count;
}

void show_all_data(){
	int count;
	Node *head_ref;
	FILE *fp = fopen("data_emp.dat", "rb");
	if(count = read_data(&head, fp)){
		head_ref = head;
		printf("+-----------------------------+\n");
		printf("|          Found %3d          |\n", count);
		printf("+-----------------------------+\n");
		while(head_ref){
			show_info(head_ref);
			head_ref = head_ref->next;
		}
		printf("\n");
	}else{
		printf("It's empty!\n\n");
	}
	fclose(fp);
}

int search_by_id(Node **current, char key[10]){
	while(*current){
		if(!(strcmp((*current)->emp_id, key))){
			printf("%10sFound it!%10s\n", " ", " ");
			show_info(*current);
			printf("\n");
			return 1;
		}
		*current = (*current)->next;
	}
	printf("%10sNot Found!%10s\n\n", " ", " ");
	return 0;
}

void search_data(){
	char key[10];
	Node *current;
	FILE *fp = fopen("data_emp.dat", "rb");
	read_data(&head, fp);
	current = head;
	printf("+-----------------------------+\n");
	printf("|      Search Data By ID      |\n");
	printf("+-----------------------------+\n\n");
	printf("Enter id for search : "); fgets(key, 10, stdin); remove_new_line(key);
	printf("\n");
	search_by_id(&current, key);
	fclose(fp);
}

void get_data(Node *current, FILE *file_pointer){
	memset(&new_employee, 0, sizeof(Node));
	strcpy(new_employee.emp_id, current->emp_id);
	strcpy(new_employee.first_name, current->first_name);
	strcpy(new_employee.last_name, current->last_name);
	strcpy(new_employee.gender, current->gender);
	new_employee.age = current->age;
	strcpy(new_employee.phone, current->phone);
	strcpy(new_employee.position, current->position);
	new_employee.salary = current->salary;
	strcpy(new_employee.address, current->address);
	fwrite(&new_employee, sizeof(Node), 1, file_pointer);
	if(ferror(file_pointer)){
		printf("Error in writing from file : data_emp.dat\n\n");
		exit(1);
	}
}

void update_data(Node *head){
	FILE *fp = fopen("data_emp.dat", "wb");
	if(!fp){
		printf("Can't open this file : data_emp.dat\n");
		exit(1);
	}
	while(head){
		get_data(head, fp);
		head = head->next;
	}
	fclose(fp);
}

void delete_by_id(Node *head_ref, char key[10]){
	Node *prev;
	if(strcmp((head_ref)->emp_id, key)){
		while(strcmp((head_ref)->emp_id, key)){
			prev = head_ref;
			head_ref = (head_ref)->next;
		}
		prev->next = (head_ref)->next;
		free(head_ref);
	}else{
		head = (head_ref)->next;
		free(head_ref);
	}
}

void delete_data(){
	char key[10], answer;
	Node *current;
	FILE *fp = fopen("data_emp.dat", "rb");
	read_data(&head, fp);
	fclose(fp);
	current = head;
	printf("+-----------------------------+\n");
	printf("|         Delete Data         |\n");
	printf("+-----------------------------+\n");
	printf("Enter id for delete : "); fgets(key, 10, stdin); remove_new_line(key);
	printf("\n");
	if(!(search_by_id(&current, key))){
		return;
	}
	while(1){
		printf("Are you sure? (Y/N) : "); answer = getche(); printf("\n");
		if(toupper(answer) == 'Y'){
			current = head;
			delete_by_id(current, key);
			update_data(head);
			printf("Deleted complete!\n\n");
			break;
		}else if(toupper(answer) == 'N'){
			printf("\n");
			break;
		}else{
			printf("Please choose 'Y' or 'N' only!\n");
		}
	}
}

void edit_value(Node *current){
	char tmp_enter;
	printf("\n");
	printf("Enter new data : %s\n", current->emp_id);
	printf("First Name  : "); fgets(current->first_name, 20, stdin); remove_new_line(current->first_name);
	printf("Last Name   : "); fgets(current->last_name, 20, stdin); remove_new_line(current->last_name);
	printf("Gender      : "); fgets(current->gender, 10, stdin); remove_new_line(current->gender);
	printf("Age         : "); scanf("%d", &(current->age)); scanf("%c", &tmp_enter);
	printf("Phone       : "); fgets(current->phone, 13, stdin); remove_new_line(current->phone);
	printf("Position    : "); fgets(current->position, 20, stdin); remove_new_line(current->position);
	printf("Salary      : "); scanf("%f", &(current->salary)); scanf("%c", &tmp_enter);
	printf("Address     : "); fgets(current->address, 100, stdin); remove_new_line(current->address);
}

void edit_data(){
	char key[10], answer;
	Node *current;
	FILE *fp = fopen("data_emp.dat", "rb");
	read_data(&head, fp);
	current = head;
	printf("+-----------------------------+\n");
	printf("|           Edit Data         |\n");
	printf("+-----------------------------+\n");
	printf("Enter id for edit : "); fgets(key, 10, stdin); remove_new_line(key);
	printf("\n");
	if(!(search_by_id(&current, key))){
		return;
	}
	while(1){
		printf("Are you sure? (Y/N) : "); answer = getche(); printf("\n");
		if(toupper(answer) == 'Y'){
			edit_value(current);
			update_data(head);
			printf("\nEdit data complete!\n\n");
			break;
		}else if(toupper(answer) == 'N'){
			printf("\n");
			break;
		}else{
			printf("Please choose 'Y' or 'N' only!\n");
		}
	}
}

void export_2csv(){
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
	while(fread(&new_employee, sizeof(Node), 1, fp)){
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
	printf("Exporting...\n");
	printf("Exported file to .csv complete!\n\n");
	fclose(fp);
	fclose(fp_csv);
}

int main(){
	int choice=0;
	char tmp_choice;
	printf("+-----------------------------+\n");
	printf("|     Employee Management     |\n");
	printf("|           System            |\n");
	do{
		fflush(stdin);
		printf("+-----------------------------+\n");
		printf("|            Menu             |\n");
		printf("+-----------------------------+\n");
		printf("|  [1] Add new employee       |\n");
		printf("|  [2] Delete data            |\n");
		printf("|  [3] Edit data              |\n");
		printf("|  [4] Search data            |\n");
		printf("|  [5] Show all data          |\n");
		printf("|  [6] Export file to .csv    |\n");
		printf("|  [7] Exit program           |\n");
		printf("+-----------------------------+\n");
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
			case 6: export_2csv(); break;
			case 7: printf("Exiting the program..."); break;
			default: printf("Please select only number in 1-7\n\n");
		}
	} while(choice != 7);
	return 0;
}