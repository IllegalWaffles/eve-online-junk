#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct decryptor {

                char name[60];
                float decryptProb;
                float decryptCost;
                int decryptRuns;

} Decryptor;

Decryptor initializeDecryptor(int);
void printDecryptorStats(Decryptor,int,int);


int main(){

	srand(time(NULL));

	int inventionRuns;
	printf("Enter number of invention runs:");
        scanf(" %d", &inventionRuns);
        printf("\n");
	
	int finished;

	do{

		system("clear");

		printf("Choose a decryptor -\n0 - No Decryptor\n1 - Accelerant\n");
		printf("2 - Attainment\n3 - Augmentation\n4 - Optimized Attainment\n");
		printf("5 - Optimized Augmentation\n6 - Parity\n7 - Process\n8 - Symmetry\n");
		printf("9 - Display Stats For All\n>");

		int decryptorType;
		scanf("%d", &decryptorType);

		Decryptor decryptorUsed;

		if(decryptorType == 9){

			int i;			
			for(i = 0; i < 9; i++){

				decryptorUsed = initializeDecryptor(i);
				printDecryptorStats(decryptorUsed, inventionRuns,0);

			}
			
			printf("\n\nAgain? [0/1]:");
			scanf(" %d", &finished);
			continue;

		}
		

		decryptorUsed = initializeDecryptor(decryptorType);
		
		printDecryptorStats(decryptorUsed, inventionRuns,1);

		printf("\n\nAgain? [0/1]:");
		scanf(" %d", &finished);

	}while(finished);

	return 0;

}

Decryptor initializeDecryptor(int type){

        Decryptor ret;

        switch(type){

                case 0:
		default:
			strcpy(ret.name, "No Decryptor");
                        ret.decryptProb = 0;
                        ret.decryptRuns = 0;
                        ret.decryptCost = 0;
                break;
		case 1:
			strcpy(ret.name, "Accelerant Decryptor");
			ret.decryptProb = .20;
			ret.decryptRuns = 1;
			ret.decryptCost = 326001.00;
		break;
		case 2:
			strcpy(ret.name, "Attainment Decryptor");
			ret.decryptProb = .8;
			ret.decryptRuns = 4;
			ret.decryptCost = 2433000.52;
		break;
		case 3:
			strcpy(ret.name, "Agumentation Decryptor");
			ret.decryptProb = -.4;
			ret.decryptRuns = 9;
			ret.decryptCost = 816055.61;			
		break;
		case 4:
			strcpy(ret.name, "Optimized Attainment Decryptor");
			ret.decryptProb = .9;
			ret.decryptRuns = 2;
			ret.decryptCost = 3176002.08;			
		break;
		case 5:
			strcpy(ret.name, "Optimized Augmentation Decryptor");
			ret.decryptProb = -.1;
			ret.decryptRuns = 7;
			ret.decryptCost = 5005000.21;
		break;
		case 6:
			strcpy(ret.name, "Parity Decryptor");
			ret.decryptProb = .5;
			ret.decryptRuns = 3;
			ret.decryptCost = 1012114.25;			
		break;
		case 7:
			strcpy(ret.name, "Process Decryptor");
			ret.decryptProb = .1;
			ret.decryptRuns = 0;
			ret.decryptCost = 420003.59;
		break;
		case 8:
			strcpy(ret.name, "Symmetry Decryptor");
			ret.decryptProb = 0;
			ret.decryptRuns = 2;
			ret.decryptCost = 323000.02;		
		break;


        }


        return ret;

}

//Print stats for a single decryptor
void printDecryptorStats(Decryptor decryptor, int inventionRuns, int verbose){
	
	//BASE VALUES
	const int baseRunsPerCopy = 1;
	const float baseInventionProbability = .43;
	/////////////

	//PRICES AND PROFITS
	const int numDatacore1 = 2;
	const int numDatacore2 = 2;
	const float datacore1cost =  89991.00;
	const float datacore2cost = 118991.76;
	/////////////

	//TEMP VARS
	register int successfulJobs = 0;
	int totalRuns = 0;
	/////////////

	int finished = 0;

	//CALCULATED VALUES
	int finalRunsPerCopy = baseRunsPerCopy + decryptor.decryptRuns;
	float finalInventionProbability = baseInventionProbability * (decryptor.decryptProb+1);
	/////////////

	if(verbose)printf("\nCalc Invention Success Probability:%.2f\n", finalInventionProbability);

	successfulJobs = 0;
	register int c;
	for(c = 0; c < inventionRuns; c++){

		successfulJobs = (rand() % 100)/100.0 <= finalInventionProbability?successfulJobs+1:successfulJobs;

	}

	if(verbose)printf("Total Invention Runs:%d\nSuccessful Jobs:%d\n", inventionRuns, successfulJobs);

	int totalSuccessfulRuns = successfulJobs*finalRunsPerCopy;
	if(verbose)printf("Total Successful Runs:%d\n\n", totalSuccessfulRuns);

	float inventionCost = ((datacore1cost*(float)numDatacore1 + datacore2cost*(float)numDatacore2) + decryptor.decryptCost) * inventionRuns;
	if(verbose)printf("Average invention cost per manufacturing job:%.2f\n", inventionCost/(float)totalSuccessfulRuns);	

	if(!verbose)printf("Name: %-33s - %11.2f\n", decryptor.name, inventionCost/(float)totalSuccessfulRuns);


}

