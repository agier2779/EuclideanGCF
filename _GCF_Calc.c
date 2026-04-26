/*Alex Gierich
takes in a changeable amount of integers and then returns the gcf between them 
using linked lists*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//function prototype
int euclid(int,int);

/*creates a new name for the user defined data type "Node", 
struct groups the variables "num" and the pointer "next" together*/
typedef struct Node {
	//holds the user input numbers
	int num;
	//pointer to struct Node
	struct Node *next;
	//set to true if the number has already been used
	bool used;
}Node; //shortens the declaration to just "Node"

//used to create a new node 
Node *make_node(int num){
	/*the malloc function reserves a block of memory and returns a 
	pointer to the beginning of the block*/
	Node *newNode = (Node*)malloc(sizeof(Node));
	/*sets the data of the node equal to the number passed in 
	(-> needed instead of . since its a pointer)*/
	newNode->num = num;
	/*sets the next pointer equal to NULL
	(-> needed instead of . since its a pointer)*/
	newNode->next = NULL;
	//returns node
	return newNode;
}

//used to insert a node at the end of linked list 
void insert(Node** head, int num){
	//variable declarations
	Node *end = *head;
	Node* newNode = make_node(num);
	//loops through the linked list until it reaches the end
	while(end->next != NULL){
		//sets the variable "end" equal to the next node
		end = end->next;
	}
	//sets the empty node equal to the newly created one
	end->next = newNode;
}

//sets the "used" element of the node equal to true so it doesn't get reused
void set_Used(Node** head, int num){
	//variable declaration
	Node *temp = *head;
	//continues till the end of the linked list
	while (temp != NULL){
		//executes once the number is found
		if (temp->num == num){
			//sets used equal to true so it doesn't get used again
			temp->used = true;
			//returns to the main code
			return;
		}
		//sets temp to the next node
		temp = temp->next;
	}
}

//prints the contents of the linked list sent over
void print(Node* list, int gcf){
	//first part of the display
	printf("The greatest common denominator of the set {");
	//continues until the last node is reached
	while (list->next != NULL){
		//prints the number held within the node
		printf("%d,", list->num);
		//moves to the next node in line
		list = list->next;
	}
	//prints the last node
	printf("%d} is: %d", list->num,gcf);
}

//main function
int main(void){
	//variable declarations
	int amount;
	int num;
	int gcf;
	int first;
	int second;
	Node* head;
	Node* temp;
	
	//prompts the user for how many integers they want to use
	printf("How many integers? (must be at least 2): ");
	//reads the input to the variable "amount"
	scanf("%d", &amount);
	
	//prompts the user for the first integer
	printf("Enter integer %d: ", 1);
	//reads the input to the variable "num"
	scanf("%d", &num);
	//creates the head node using the user input
	head = make_node(num);
	
	//continues until i is over to the number of integers the user needs
	for(int i = 2; i <= amount; i++){
		//prompts the user for the next integer
		printf("Enter integer %d: ", i);
		//reads the input to the variable "num"
		scanf("%d", &num);
		//calls the insert function to add a node to the head
		insert(&head, num);
	}
	//temp pointer used to manipulate the linked list
	temp = head;
	
	//cycles through the list
	while (temp != NULL){
		//executes if num is larger than first
		if (temp->num > first && temp->used != true){
			//sets first equal to the larger number
			first = temp->num;
		}
		//sets temp equal to the next node
		temp = temp->next;
	}
	//updates the used number in the list
	set_Used(&head, first);
	//resets temp to the new list
	temp = head;
	//cycles through the list
	while (temp != NULL){
		//executes if num is larger than second
		if (temp->num > second && temp->used != true){
			//sets second equal to the larger number
			second = temp->num;
		}
		//sets temp equal to the next node
		temp = temp->next;
	}
	//updates the used number in the list
	set_Used(&head, second);
	//find the gcf of the first two largest numbers in the list
	gcf = euclid(first, second);
	
	/*executes until i is equal to 2 less than the amount of ints used 
	(one gcf was already found so two numbers have already been accounted for*/
	for(int i = 0; i < amount - 2; i++){
		//sets temp equal to the new list
		temp = head;
		//resets the first variable to 0
		first = 0;
		//cycles through list
		while (temp != NULL){
			//executes if num is larger than first		
			if (temp->num > first && temp->used != true){
				//sets first equal to the larger number
				first = temp->num;
			}
			//sets temp equal to the next node
			temp = temp->next;
		}
		//updates the used number in the list
		set_Used(&head, first);
		//sets second equal to the previous gcf found
		second = gcf;
		//finds the new gcf 
		gcf = euclid(first, second);
	}
	print(head,gcf);
}

//function that calculates the greatest common factor of two integers
int euclid(int first, int second){
	//variable declarations
	int gcf;
	int remainder;
	int newRemain;
	
	//changes int to positive if negative
	if (first < 0){
		first *= -1;
	}
	//changes int to positive if negative
	else if( second < 0){
		second *= -1;
	}
	
	//executes if first is larger than second
	if (first > second){
		//sets the gcf equal to the lower number
		gcf = second;
		//gets the first remainder
		remainder = first - second;
	}
	//executes if second is larger than first
	else{
		//sets the gcf equal to the lower number
		gcf = first;
		//gets the first remainder
		remainder = second - first;
	}
	
	//continues until the remainder is 0
	while(remainder != 0){
		//executes if the remainder is less than the gcf
		if (gcf > remainder){
			//gets the new remainder
			newRemain = gcf - remainder;
			//sets the gcf equal to the old remainder
			gcf = remainder;
			//sets the old remainder equal to the newremainder
			remainder = newRemain;
		}
		//executes if the gcf is less than the remainder
		else{
			//gets the new remainder
			newRemain = remainder - gcf;
			//sets the old remainder equal to the new remainder, gcf does not change
			remainder = newRemain;
		}

	}
	//returns the gcf as an integer
	return gcf;
}
