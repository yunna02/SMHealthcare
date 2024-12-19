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

// Function prototype for calculating remaining calories
int calculatecal_L(const HealthData* health_data);

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH);
    loadDiets(DIETFILEPATH); 


    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
		int cal_L = calculatecal_L(&health_data); // Calculate remaining calories ('cal_L' represents 'calories are left')
	
		// If remaining calories are zero, exit the system
		if (cal_L == 0){
			printf("You have consumed all your calories for today! \n");
			saveData(HEALTHFILEPATH, &health_data); // Save data before exiting
			printf("=======================================================================\n");
			printf("System is exiting...\n");
			return 0; // Exit the system
		} 
		
		//Display menu
		printf("\n=======================================================================\n");
        printf("[Healthcare Management Systems] \n");
        printf("1. Exercise \n");
        printf("2. Diet \n");
        printf("3. Show logged information \n");
        printf("4. Exit \n");
        printf("Select the desired number: ");
        scanf("%d", &choice); //user's choice read
        printf("=======================================================================\n");
    
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1: //Input Exercise and Save data
            	inputExercise(&health_data); //Add selected exercise, calculate calories burned to health data
				saveData(HEALTHFILEPATH, &health_data); //Store updated health data
                break;
                
            case 2: //Input Diets and Save data
            	inputDiet(&health_data); //Adds selected food's calories to health data
				saveData(HEALTHFILEPATH, &health_data); //Store updated health data
                break;
                
            case 3: //Output health data
            	printHealthData(&health_data); //Watch exercise, diet, and remaining calories.
                break;
                
            case 4: //Exit
            	saveData(HEALTHFILEPATH, &health_data); //Save health data before exiting.
				printf("Exit the system.\n");
				printf("=======================================================================\n");
                return 0;
                
            default: //Handle Invalid input
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (1); // Continue until pick to exit(4) or Remaining calories = 0
    
	
	return 0;
}
