//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r"); // Open the file read mode
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
     while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) {
        exercise_list_size++; // Read exercise information from the file line by line
        if (exercise_list_size >= MAX_EXERCISES) {   // Check maximum capacity is reached
            break; //stop reading
		}
    }

    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n"); 
	for (i = 0; i < exercise_list_size; i++) {
        printf("%d. %s (%d kcal/min)\n", i + 1, 
               exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute); // Display exercise list and calories burned per minute
    }
    printf("0. Exit\n");  //Provide an option to exit

    // ToCode: to enter the exercise to be chosen with exit option
	do {
        printf("Select an exercise by entering its number: ");
        scanf("%d", &choice); ////read user's choice
        if (choice == 0) return; // Exit if the user selects 0

        if (choice >= 1 && choice <= exercise_list_size) {
            // To enter the duration of the exercise
            printf("Enter the duration of the exercise (in min.): ");
            scanf("%d", &duration);


    // ToCode: to enter the selected exercise and total calcories burned in the health data
			int calories_burned = exercise_list[choice - 1].calories_burned_per_minute * duration;  // Calculate total calories burned
			
			//Store selected exercises info in health_data
			strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice - 1].exercise_name);
			health_data->exercises[health_data->exercise_count].calories_burned_per_minute = calories_burned;
			health_data->exercise_count++; 
            
            health_data->total_calories_burned += calories_burned; // Update total calories burned in health data
            printf("You chose %s for %d minutes (%d kcal burned)\n", exercise_list[choice - 1].exercise_name, duration, calories_burned);
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    } while (1);
}
