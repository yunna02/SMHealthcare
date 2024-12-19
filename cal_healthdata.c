//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

int calculatecal_L(const HealthData* health_data) { //calculate the calories left(intake, basal Metabolic rate, burned calories)
    return health_data->total_calories_intake - BASAL_METABOLIC_RATE - health_data->total_calories_burned;
	//return: how many calories are left
}


void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
	FILE* file = fopen(HEALTHFILEPATH, "w");  // Open file writing
	if (file == NULL) {
	    printf("There is no file for health data.\n");
		return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
	fprintf(file, "[Exercises] \n");
	for (int i = 0; i < health_data->exercise_count; i++) {
		fprintf(file, "%s - %d kcal\n", 
                health_data->exercises[i].exercise_name, 
                health_data->exercises[i].calories_burned_per_minute); // Write exercise details
    }
	fprintf(file, "Total calories burned: %d kcal\n\n", health_data->total_calories_burned); // Write total calories burned
    
    
    // ToCode: to save the chosen diet and total calories intake 
	fprintf(file, "\n[Diets]\n");
	for (int i = 0; i < health_data->diet_count; i++) {
        fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake); // Write diet details
    }
	fprintf(file, "Total calories intake: %d kcal\n\n", health_data->total_calories_intake); // Write total calorie intake



    // ToCode: to save the total remaining calrories
	int cal_L = calculatecal_L(health_data); // Save remaining calories
	fprintf(file, "[Total]\n");
	fprintf(file, "Basal metabolic rate: %d kcal\n", BASAL_METABOLIC_RATE); // Write basal Metabolic rate
	fprintf(file, "The remaining calories: %d kcal\n", cal_L); // Write remaining calories
    
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for (i = 0; i < health_data->exercise_count; i++) {
        printf("Exercise: %s, Calories burned: %d kcal\n",
               health_data->exercises[i].exercise_name,
               health_data->exercises[i].calories_burned_per_minute);
    }  // Print exercise details
	printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
	printf("============================= History of Diet =========================\n");
	for (i = 0; i < health_data->diet_count; i++) {
        printf("Food: %s, Calories intake: %d kcal\n",health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    } // Print diet details
	printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
	printf("Basal Metabolic Rate: 1300 kcal\n"); // Print basal metabolic rate
	printf("Total calories burned: %d kcal\n", health_data->total_calories_burned); // Print total calories burned
	printf("Total calories intake: %d kcal\n", health_data->total_calories_intake); // Print total calories intake
    
	int cal_L = calculatecal_L(health_data); // Calculate remaining calories
	printf("The remaining calories: %d kcal\n", cal_L); // Print remaining calories
	printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
	if (cal_L == 0) {
		printf("You have consumed all your calories for today!\n");
    } else if (cal_L < 0) {
		printf("[Warning] Too few calories!\n");
		if (health_data->total_calories_intake >= 2000) {
            printf("Your total calorie intake for today has reached your goal!\n");
        } else {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        }
		if (health_data->total_calories_intake > 2000) {
            printf("You have eaten more calories than planned today, but you have exercised too much!\n");
        }
    } else {
        printf("Please exercise for your health!\n");
		if (health_data->total_calories_intake >= 2000) {
            printf("Your total calorie intake for today has reached your goal!\n");
        } else {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        }
    }
    
	printf("=======================================================================\n");
}
