#include <stdio.h>
#include <string.h>

#define NODE_OFFSET 10
#define BUFFER_SIZE 5000

typedef struct node{
	char* name;
	int value;
	struct node* next;
} node_t;

void print_node(node_t n){
	printf("Name: %s \n", n.name);
	printf("Size: %d \n", n.value);
	printf("Next: %p \n", n.next);
}

int main() {

	node_t n1 = {.name = "James", .value = 300, .next = NULL};
	
	node_t n2 = n1;
	
	node_t n3;
	
	memcpy(&n3, &n2, sizeof(node_t));
	
	char buffer[BUFFER_SIZE];
	
	memcpy(buffer+NODE_OFFSET, &n3, sizeof(node_t));
	
	node_t *n4 = (node_t*)(buffer+NODE_OFFSET);
	
	print_node(n1);
	print_node(n2);
    print_node(n3);
    print_node(*n4);
    
    return 0;
}
