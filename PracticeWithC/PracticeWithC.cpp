/// https://www.youtube.com/watch?v=LuR-54fQrA0

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
	int data;
	struct node* next;
} node;

typedef void(*callback)(node* data);

/*
create a new node
initialize the data and next field

return the newly created node
*/
node* create(int data, node* next)
{
	node* new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL)
	{
		printf("Error creating a new node.\n");
		exit(0);
	}
	new_node->data = data;
	new_node->next = next;

	return new_node;
}

/*
add a new node at the beginning of the list
*/
node* prepend(node* head, int data)
{
	node* new_node = create(data, head);
	head = new_node;
	return head;
}

/*
add a new node at the end of the list
*/
node* append(node* head, int data)
{
	if (head == NULL)
		return NULL;
	/* go to the last node */
	node *cursor = head;
	while (cursor->next != NULL)
		cursor = cursor->next;

	/* create a new node */
	node* new_node = create(data, NULL);
	cursor->next = new_node;

	return head;
}

/*
insert a new node after the prev node
*/
node* insert_after(node *head, int data, node* current)
{
	if (head == NULL || current == NULL)
		return NULL;
	/* find the prev node, starting from the first node*/
	/*node *cursor = head;
	while (cursor != current)
		cursor = cursor->next;

	if (cursor != NULL)
	{*/
	//node* new_node = create(data, cursor->next);
	//node* new_node = create(data, current->next);
	////cursor->next = new_node;
	//current->next = new_node;
	current->next = create(data, current->next);
	return head;
	/*}
	else
	{
		return NULL;
	}*/
}

/*
insert a new node before the nxt node
*/
node* insert_before(node *head, int data, node* current)
{
	if (current == NULL || head == NULL)
		return NULL;

	if (head == current)
	{
		head = prepend(head, data);
		return head;
	}

	/* find the prev node, starting from the first node*/
	node *cursor = head;
	while (cursor != NULL)
	{
		if (cursor->next == current)
			break;
		cursor = cursor->next;
	}

	if (cursor != NULL)
	{
		node* new_node = create(data, cursor->next);
		cursor->next = new_node;
		return head;
	}
	else
	{
		return NULL;
	}
}

/*
traverse the linked list
*/
void traverse(node* head, callback f)
{
	node* cursor = head;
	while (cursor != NULL)
	{
		f(cursor);
		cursor = cursor->next;
	}
	printf("null");
}
/*
remove node from the front of list
*/
node* remove_front(node* head)
{
	if (head == NULL)
		return NULL;
	node *front = head;
	head = head->next;
	front->next = NULL;
	/* is this the last node in the list */
	if (front == head)
		head = NULL;
	free(front);
	return head;
}

/*
remove node from the back of the list
*/
node* remove_back(node* head)
{
	if (head == NULL)
		return NULL;

	node *cursor = head;
	node *back = NULL;
	while (cursor->next != NULL)
	{
		back = cursor;
		cursor = cursor->next;
	}

	if (back != NULL)
		back->next = NULL;

	/* if this is the last node in the list*/
	if (cursor == head)
		head = NULL;

	free(cursor);

	return head;
}

/*
remove a node from the list
*/
node* remove_any(node* head, node* nd)
{
	if (nd == NULL)
		return NULL;
	/* if the node is the first node */
	if (nd == head)
		return remove_front(head);

	/* if the node is the last node */
	if (nd->next == NULL)
		return remove_back(head);

	/* if the node is in the middle */
	node* cursor = head;
	while (cursor != NULL)
	{
		if (cursor->next == nd)
			break;
		cursor = cursor->next;
	}

	if (cursor != NULL)
	{
		node* tmp = cursor->next;
		cursor->next = tmp->next;
		tmp->next = NULL;
		free(tmp);
	}
	return head;

}
/*
display a node
*/
void display(node* n)
{
	if (n != NULL)
		//printf("%d ", n->data);
		printf("%d-->", n->data);
	else
		printf("NULL");
}

/*
Search for a specific node with input data

return the first matched node that stores the input data,
otherwise return NULL
*/
node* search(node* head, int data)
{

	node *cursor = head;
	while (cursor != NULL)
	{
		if (cursor->data == data)
			return cursor;
		cursor = cursor->next;
	}
	return NULL;
}

/*
remove all element of the list
*/
void dispose(node *head)
{
	node *cursor, *tmp;

	if (head != NULL)
	{
		cursor = head->next;
		head->next = NULL;
		while (cursor != NULL)
		{
			tmp = cursor->next;
			free(cursor);
			cursor = tmp;
		}
	}
}
/*
return the number of elements in the list
*/
int count(node *head)
{
	node *cursor = head;
	int c = 0;
	while (cursor != NULL)
	{
		c++;
		cursor = cursor->next;
	}
	return c;
}
/*
sort the linked list using insertion sort
*/
node* insertion_sort(node* head)
{
	node *x, *y, *e;

	x = head;
	head = NULL;

	while (x != NULL)
	{
		e = x;
		x = x->next;
		if (head != NULL)
		{
			if (e->data > head->data)
			{
				y = head;
				while ((y->next != NULL) && (e->data > y->next->data))
				{
					y = y->next;
				}
				e->next = y->next;
				y->next = e;
			}
			else
			{
				e->next = head;
				head = e;
			}
		}
		else
		{
			e->next = NULL;
			head = e;
		}
	}
	return head;
}

/*
reverse the linked list
*/
node* reverse(node* head)
{
	node* prev = NULL;
	node* current = head;
	node* next;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}
/*
display the menu
*/
void menu()
{
	printf("\n11.Create Subset from a Set\n");
	printf("--- C Linked List Demonstration --- \n\n");
	printf("0.menu\n");
	printf("1.prepend an element\n");
	printf("2.append an element\n");
	printf("3.search for an element\n");
	printf("4.insert after an element\n");
	printf("5.insert before an element\n");
	printf("6.remove front node\n");
	printf("7.remove back node\n");
	printf("8.remove any node\n");
	printf("9.sort the list\n");
	printf("10.Reverse the linked list\n");
	printf("12.Check if linked list is palindrome\n");
	printf("-1.quit\n");
}

char string[50], n;
void subset(int, int, int);

void subset(int start, int index, int num_sub)
{
	int i, j;
	if (index - start + 1 == num_sub)
	{
		if (num_sub == 1)
		{
			for (i = 0; i < n; i++)
				printf("%c\n", string[i]);
		}
		else
		{
			for (j = index; j < n; j++)
			{
				for (i = start; i < index; i++)
					printf("%c", string[i]);
				printf("%c\n", string[j]);
			}
			if (start != n - num_sub)
				subset(start + 1, start + 1, num_sub);
		}
	}
	else
	{
		subset(start, index + 1, num_sub);
	}
}

void showNode()
{
	int val = 2;
	printf("\n| %d ||-->", val);
}

/*
check if palindrome linked list
*/
bool isPalindrome(node* head)
{
	node* temp = head;
	int listLength = 1;
	while (temp->next != NULL)
	{
		temp = temp->next;
		listLength++;
	}

	int midL = 0;
	int m = listLength % 2;
	int d = listLength / 2;
	if (m == 0)
		midL = d;
	else
		midL = d + 1;

	//temp = head;
	node* midH = head;
	int i = 1;
	while (i <= midL)
	{
		midH = midH->next;
		i++;
	}
	//return midH;

	node* prev = NULL;
	node* current = midH;
	node* next;
	while (current != NULL && temp != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	midH = prev;
	//return midH;

	temp = head;
	while (temp->next != NULL && midH->next != NULL)
	{
		if (temp->data != midH->data)
			return false;
		else
		{
			temp = temp->next;
			midH = midH->next;
		}
	}

	return true;
	//return head;
}

void printPowerSet(char *set, int set_size)
{
	/*set_size of power set of a set with set_size
	n is (2**n -1)*/
	unsigned int pow_set_size = pow(2, set_size);
	int counter, j;

	/*Run from counter 000..0 to 111..1*/
	for (counter = 0; counter < pow_set_size; counter++)
	{
		for (j = 0; j < set_size; j++)
		{
			/* Check if jth bit in the counter is set
			If set then pront jth element from set */
			if (counter & (1 << j))
				printf("%c", set[j]);
		}
		printf("\n");
	}
}

int main()
{
	int command = 0;
	int data;

	node* head = NULL;
	node* tmp = NULL;
	callback disp = display;

	menu();
	while (1)
	{
		printf("\nEnter a command(0-10,-1 to quit):");
		scanf_s("%d", &command);

		if (command == -1)
			break;
		switch (command)
		{
		case 0:
			menu();
			break;
		case 1:
			printf("Please enter a number to prepend:");
			scanf_s("%d", &data);
			head = prepend(head, data);
			traverse(head, disp);
			break;
		case 2:
			printf("Please enter a number to append:");
			scanf_s("%d", &data);
			head = append(head, data);
			traverse(head, disp);
			break;
		case 3:
			printf("Please enter a number to search:");
			scanf_s("%d", &data);
			tmp = search(head, data);
			if (tmp != NULL)
			{
				printf("Element with value %d found.", data);
			}
			else
			{
				printf("Element with value %d not found.", data);
			}
			break;
		case 4:
			printf("Enter the element value where you want to insert after:");
			scanf_s("%d", &data);
			tmp = search(head, data);
			if (tmp != NULL)
			{
				printf("Enter the element value to insert after:");
				scanf_s("%d", &data);
				head = insert_after(head, data, tmp);
				if (head != NULL)
					traverse(head, disp);
			}
			else
			{
				printf("Element with value %d not found.", data);
			}
			break;
		case 5:
			printf("Enter the element value where you want to insert before:");
			scanf_s("%d", &data);
			tmp = search(head, data);
			if (tmp != NULL)
			{
				printf("Enter the element value to insert before:");
				scanf_s("%d", &data);
				head = insert_before(head, data, tmp);

				if (head != NULL)
					traverse(head, disp);
			}
			else
			{
				printf("Element with value %d not found.", data);
			}
			break;
		case 6:
			head = remove_front(head);
			if (head != NULL)
				traverse(head, disp);
			break;
		case 7:
			head = remove_back(head);
			if (head != NULL)
				traverse(head, disp);
			break;
		case 8:
			printf("Enter the element value to remove:");
			scanf_s("%d", &data);
			tmp = search(head, data);
			if (tmp != NULL)
			{
				remove_any(head, tmp);
				if (head != NULL)
					traverse(head, disp);
			}
			else
			{
				printf("Element with value %d not found.", data);
			}
			break;
		case 9:
			head = insertion_sort(head);
			if (head != NULL)
				traverse(head, disp);
			break;
		case 10:
			head = reverse(head);
			if (head != NULL)
				traverse(head, disp);
			break;
		case 11:
			int i, len;
			printf("Enter the len of main set : ");
			scanf_s("%d", &len);
			printf("Enter the elements of main set : ");
			scanf_s("%s", string, sizeof(string));
			n = len;
			printf("The subsets are :\n");
			printPowerSet(string, n);
			/*for (i = 1; i <= n; i++)
				subset(0, 0, i);*/
			break;
		case 12:
			if (isPalindrome(head))
				printf("List is palindrome.");
			else
				printf("List is not palindrome.");
			break;
		}
	}
	dispose(head);
	return 0;
}
