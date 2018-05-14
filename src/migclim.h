/*###################################################################################################################### 
### migclim.h - Header file for the MigClim methods.
### ***********************************************
###
### Authors: Robin Engler and Wim Hordijk.
### Last modified: 16 Oct 2017.
######################################################################################################################*/


/* Header start: we use 'ifndef' to ensure that the header never gets defined/loaded twice (this prevents e.g. double
** declaration of static variables). If _MIGCLIM_H_ is already defined then the header is not read again. */
#ifndef _MIGCLIM_H_
#define _MIGCLIM_H_


/* Include files. */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <R.h>
#include <Rmath.h>


/* Define macros to be used thoughout the MigClim code. 
** UNIF01:         Draw a uniform random number in the range [0,1]. 
**                 Note: we are now using the function "unif_rand()" from the Rmath.h library. Originally MigClim
**                       was using the "rand()" C function (because 'random' doesn't work on Windows), but this 
**                       creates problems when trying to set the seed for the random number generator, as the 
**                       seed is then set for the original rand() function but when calling rand() the function 
**                       from R is used and the previously set seed is ignored. 
**                       #define UNIF01         ((double)rand () / RAND_MAX)  */
#define UNIF01         unif_rand()
#define WEAK_BARRIER   1        // Weak barrier type.
#define STRONG_BARRIER 2        // strong barrier type.
#define VERBOSE        true     // set to true to enable verbose mode.

/* Global variables (we just use many global var's here to avoid passing too many arguments all the time).
** Note that with the "extern" keywords, we are telling the compiler that variable exists, but we are not declaring
** it. These variables will still have to be declared in the .c file where they will be created.
**  -> nrRows: number of rows of input matrices used for the current MigClim run (all matrices have same size).
**  -> nrCols: number of columns of input matrices used for the current MigClim run (all matrices have same size).
**
**
**  -> singleKernelMode: boolean true/false indicating whether we are in "single kernel" (true) or 
**                       "multi kernel" (false) mode. Single kernel mode is the classic mode where the same
**                       dispersal kernel is used for all cells. Multi kernel mode is a mode where each pixel can
**                       have a custom kernel. In this case the user must pass a list of raster files as input, 
**                       where each raster file contains the probability of dispersal values for a given cell in
**                       the landscape for a given dispersal distance. Each raster file contains the values for
**                       a given dispersal distance. */
extern int          nrRows, nrCols, envChgSteps, dispSteps, dispDist, iniMatAge, fullMatAge, rcThreshold, 
                    barrierType, lddMinDist, lddMaxDist, noData, replicateNb;
extern float        *dispKernel; 
extern double       *propaguleProd, lddFreq, xllCorner, yllCorner, cellSize;
extern char         iniDist[128], hsMap[128], simulName[128], barrier[128];
extern bool         useBarrier, fullOutput, singleKernelMode;


/* Function prototypes. */
void mcMigrate           (char **paramFile, int *nrFiles);
bool mcSrcCell           (int i, int j, int **curState, int **pxlAge, int loopID, int habSuit, int **barriers);
int  mcUnivDispCnt       (int **habSuit);
void updateNoDispMat     (int **hsMat, int **noDispMat, int *noDispCount);
void mcFilterMatrix      (int **inMatrix, int **filterMatrix, bool filterNoData, bool filterOnes, bool insertNoData);
bool mcIntersectsBarrier (int snkX, int snkY, int srcX, int srcY, int **barriers);
int  mcInit              (char *paramFile);
int  readMat             (char *fName, int **mat);
int  readMatrixFloat     (char *fName, float *mat);
int  writeMat            (char *fName, int **mat);
void genClust            (int *nrow, int *ncol, int *ncls, int *niter, int *thrs, char **suitBaseName, 
                          char **barrBaseName, char **outBaseName, char **initFile);
void validate            (char **obsFileName, int *npts, char **simFileName, int *ncls, double *bestScore);



#endif  /* _MIGCLIM_H_ */
/*####################################################################################################################*/
