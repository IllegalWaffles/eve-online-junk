#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

	srand(time(NULL));

	double INV_CHANCE;
	double *temp = &INV_CHANCE;
	
	printf("Enter the probability: ");
	scanf("%lf", temp);

	
	int NUM_RUNS = 100000000;
	int DATACORES_PER_RUN = 2;
	double roll;
	int successfulRuns = 0;
	
	printf("Calculating...\n");
	
	int i;
	for(i = 0; i < NUM_RUNS; i++){
		
		roll = ((rand() % 100)+1)/100.0;
		
		//printf("%lf\n", roll);
		
		if(roll <= INV_CHANCE)
			successfulRuns++;
		
	}
	
	int datacoresUsed = DATACORES_PER_RUN*NUM_RUNS;
	double avgCoresPerRun = (double)datacoresUsed/(double)successfulRuns;
		
	
	printf("Successful runs: %d\n", successfulRuns);
	printf("Number of cores used: %d\n", NUM_RUNS*DATACORES_PER_RUN);
	printf("Avg cores per run: %lf", avgCoresPerRun);
	
	
}
