#include "node.h"
#include <stdlib.h>
//#include <stdio.h> debug
#include <string.h>

/* Debugging only
void			show_node(Node *start)
{
	Node	*p;

	p = start;
	while (p != NULL)
	{
		printf("%lu, %s, %s, %hhu", p->data.reg_num, p->data.model, p->data.category, p->data.loaned);
		printf("  ->  ");
		p = p->next;
	}
	printf("\n");
}
*/

/* Creates a new node and returns it */
Node			*new_node(Car car)
{
	Node	*p;

	p = malloc(sizeof(Node) + 1);
	p->data = car;
	p->next = NULL;
	return (p);
}

/* Adds a new node at the beginning of the list */
void			unshift_node(Node **start, Car car)
{
	Node	*p;

	if (*start == NULL)
		*start = new_node(car);
	else
	{
		p = new_node(car);
		p->next = *start;
		*start = p;
	}
}

/* Adds a new node at the end of the list */
void			push_node(Node **start, Car car)
{
	Node	*p;
	Node	*t;

	if (*start == NULL)
		*start = new_node(car);
	else
	{
		p = new_node(car);
		t = *start;
		while (t->next != NULL)
			t = t->next;
		t->next = p;
	}
}

/* Edits a node */
void			edit_node(Node **start, Car car)
{
	Node *p;

	p = *start;
	while (p != NULL)
	{
		if (p->data.reg_num == car.reg_num)
		{
			strcpy(p->data.model, car.model);
			strcpy(p->data.category, car.category);
			break;
		}
		p = p->next;
	}
}

/* Checks if the node exists, 1 - exists, else 0 */
int				node_exists(Node *start, Car car)
{
	Node *p;

	p = start;
	while (p != NULL)
	{
		if (p->data.reg_num == car.reg_num)
			return (1);
		p = p->next;
	}
	return (0);
}

/* Clears the list "start" */
void			clear_list(Node **start)
{
	Node	*p;
	
	while (*start != NULL)
	{
		p = *start;
		*start = (*start)->next;
		free(p);
	}
}

/* Changes the loan status of the car and returns the new status */
unsigned char	loan_car(Node **start, unsigned long reg_num)
{
	Node *p;

	p = *start;
	while (p != NULL)
	{
		if (p->data.reg_num == reg_num)
		{
			p->data.loaned = !p->data.loaned;
			return (p->data.loaned);
		}
		p = p->next;
	}
	return (42); //Big problem if reached here.
}

/* Creates a new list and returns it, the list is sorted by model */
Node			*sort_by_model(Node *start)
{
	Node			*p;
	Node			*new_list = NULL;
	unsigned char	sorted = 0;
	
	p = start;
	while (p != NULL)
	{
		push_node(&new_list, p->data);
		p = p->next;
	}
	while (!sorted)
	{
		p = new_list;
		sorted = 1;
		
		if (p != NULL)
		{
			if (p->next != NULL)
			{
				if (strcmp(p->data.model, p->next->data.model) > 0)
				{
					Node	*temp = p;
					
					new_list = p->next;
					temp->next = new_list->next;
					new_list->next = temp;
					sorted = 0;
				}
				else
				{
					while (p->next->next != NULL)
					{
						if (strcmp(p->next->data.model, p->next->next->data.model) > 0)
						{
							Node	*temp = p->next;
							
							p->next = temp->next;
							temp->next = p->next->next;
							p->next->next = temp;
							sorted = 0;
						}
						p = p->next;
					}
				}
			}
		}
	}
	return (new_list);
}

/* Creates a new list and returns it, the list is sorted by category */
Node			*sort_by_category(Node *start)
{
	Node			*p;
	Node			*new_list = NULL;
	unsigned char	sorted = 0;
	
	p = start;
	while (p != NULL)
	{
		push_node(&new_list, p->data);
		p = p->next;
	}
	while (!sorted)
	{
		p = new_list;
		sorted = 1;
		if (p != NULL)
		{
			if (p->next != NULL)
			{
				if (strcmp(p->data.category, p->next->data.category) > 0)
				{
					Node	*temp = p;
					
					new_list = p->next;
					temp->next = new_list->next;
					new_list->next = temp;
					sorted = 0;
				}
				else
				{
					while (p->next->next != NULL)
					{
						if (strcmp(p->next->data.category, p->next->next->data.category) > 0)
						{
							Node	*temp = p->next;
							
							p->next = temp->next;
							temp->next = p->next->next;
							p->next->next = temp;
							sorted = 0;
						}
						p = p->next;
					}
				}
			}
		}
	}
	return (new_list);
}