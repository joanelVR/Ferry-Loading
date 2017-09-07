/**********************************************************************
Program: Ferry Loading
Author: Joanel Vasquez
Date: 07/11/2016
Time spent: 10 hours (was trying to model the ferry as a linked list by 
					  having both left and right sides connected)
Purpose: The purpose of this program is to determine the amount of times 
		 that a ferry must cross a river in order to transport all the cars
		 from one side to the other.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	//1- create the handle and set it to NULL
	QUEUE hQueue_left = NULL;
	QUEUE hQueue_right = NULL;

	int c; //number of test cases.
	int l; //how long the ferry is in meters
	int m; //cars that arrive
	int car_length; //how long the cars are in centimeter
	int i, j;
	int river_count = 0, cars_total_length = 0;
	char direccion[10]; //direction where the cars are going
	Side state;

	//2- Init the handle
	hQueue_left = queue_init_default();
	if (hQueue_left == NULL)
	{
		printf("Couldn't allocate space for queue object.\n");
		exit(1);
	}

	hQueue_right = queue_init_default();
	if (hQueue_right == NULL)
	{
		printf("Couldn't allocate space for queue object.\n");
		exit(1);
	}

	//A - Ask for the number of cases
	scanf("%d", &c);
	clear_keyboard_buffer();

	//B - Evaluate the whole thing depending on the number of cases
	for (i = 0; i < c; i++)
	{
		//C - Each case beings with ferry length and amount of cars
		scanf("%d %d", &l, &m);
		clear_keyboard_buffer();
		l *= 100; //turns l to centimeters

		//D - For each car
		for (j = 0; j < m; j++)
		{
			//E - gets the direction and length 
			scanf("%d %s", &car_length, direccion);
			if (direccion[0] == 'l')
			{
				queue_enqueue(hQueue_left, car_length);
			}
			else
			{
				queue_enqueue(hQueue_right, car_length);
			}
		}

		river_count = 0;
		cars_total_length = 0;
		state = LEFT; //We start at the left side
		while (!queue_empty(hQueue_left) || !queue_empty(hQueue_right)) //While the ferry is not empty
		{
			if (state == LEFT)
			{
				cars_total_length = 0;
				while (!queue_empty(hQueue_left) && cars_total_length + queue_front(hQueue_left, NULL) <= l)
				{
					cars_total_length += queue_front(hQueue_left, NULL);
					queue_service(hQueue_left);
				}
				state = RIGHT;
				river_count++;
			}
			else
			{
				cars_total_length = 0;
				while (!queue_empty(hQueue_right) && cars_total_length + queue_front(hQueue_right, NULL) <= l)
				{
					cars_total_length += queue_front(hQueue_right, NULL);
					queue_service(hQueue_right);
				}
				state = LEFT;
				river_count++;
			}
		}
		printf("%d\n", river_count);
	}

	queue_destroy(&hQueue_right);
	queue_destroy(&hQueue_left);
	return 0;
}

//Saved program "Clear_keyboard_buffer"
//Will clear (eat up) everything up to the "new line" character 
void clear_keyboard_buffer(void)
{
	char c;

	//-------------------------------
	scanf("%c", &c);

	while (c != '\n')
	{
		scanf("%c", &c);
	}

}
