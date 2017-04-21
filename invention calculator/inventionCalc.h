#ifndef __INV_CALC__
#define __INV_CALC__

#ifdef __WIN32__
	#define clear() do{system("cls");}while(0)
#else
	#define clear() do{system("clear");}while(0)
#endif

#define NUM_INVENTION_RUNS 10000000

#ifdef DEBUG
	#define debug(S, ...)   do{fprintf(stderr, KMAG "DEBUG: %s:%s:%d " KNRM S,   __FILE__, __extension__ __FUNCTION__, __LINE__, __VA_ARGS__  );}while(0)
#else
	#define debug(S, ...)
#endif

#ifdef INFO
	#define info(S, ...)    do{fprintf(stderr, KBLU "INFO: %s:%s:%d " KNRM S,    __FILE__, __extension__ __FUNCTION__, __LINE__, __VA_ARGS__  );}while(0)
#else
	#define info(S, ...)
#endif

#ifdef COLOR
	#define KNRM "\x1B[0m"
	#define KMAG "\x1B[1;35m"
	#define KBLU "\x1B[1;34m"
#else
	#define KNRM
	#define KMAG
	#define KBLU
#endif

// Each decryptor has these values. Initializer is below
typedef struct decryptor {

    char name[60];
    float decryptProb;
    int decryptRuns;
    float decryptCost;

} Decryptor;

void printDecryptorStats(Decryptor,int);
int initializeData();
void printTableHeader();
void printHR();

#endif
