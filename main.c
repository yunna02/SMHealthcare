//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

// Function prototype for inputExercise
void inputExercise(HealthData* health_data);

// Function prototype for inputDiet
void inputDiet(HealthData* health_data);



int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH); 


    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	int goal_cal_balance = DAILY_CALORIE_GOAL - BASAL_METABOLIC_RATE + health_data.total_calories_intake - health_data.total_calories_burned;

    	if (goal_cal_balance == 0){
            printf("You have consumed all your calories for today! \n");
            saveData(HEALTHFILEPATH, &health_data); // Save data before exiting
            printf("=======================================================================\n");
            printf("System is exiting...\n");
            break; // Exit the system
		} 
		
		printf("\n=======================================================================\n");
        printf("[Healthcare Management Systems] \n");
        printf("1. Exercise \n");
        printf("2. Diet \n");
        printf("3. Show logged information \n");
        printf("4. Exit \n");
        printf("Select the desired number: ");
        scanf("%d", &choice);
        printf("=======================================================================\n");
    
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data);
    			saveData(HEALTHFILEPATH, &health_data); 
                break;
                
            case 2:
            	inputDiet(&health_data);
    			saveData(HEALTHFILEPATH, &health_data);
                break;
                
            case 3:
            	printHealthData(&health_data);
                break;
                
            case 4:
            	saveData(HEALTHFILEPATH, &health_data);
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                return 0;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (1);
    
	return 0;
}
