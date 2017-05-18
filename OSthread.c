#include <windows.h>
#include <stdio.h>
#include <time.h>

#define M 40
#define K 60
#define N 40
#define SetThread 0
void Initialize(double(*A)[K],double(*B)[N],double(*C)[N]);
// structure for passsing data to therads
struct v
{
  int i; // row
  int j; // column       
};
       
double A[M][K];
double B[K][N];
double C[M][N];

DWORD WINAPI multiplyThread(LPVOID Param )
{
        // Create structure and assign data from param to it.
        struct v threadVal = *(struct v*)Param;
        free(Param);
        Param  = NULL;
        int a = threadVal.i;
        int b = threadVal.j;
        
        // cout << a << ' ' << b << endl;
        //Perform the matrix multiplication
        C[a][b]= 0;
        for(int i =0;i < K; i++)
        C[a][b] += A[a][i]*B[i][b];  
        
        return 0;
}
void SingleThread(struct v* Param )
{
        // Create structure and assign data from param to it.
        struct v threadVal = *Param;
        free(Param);
        Param  = NULL;
        int a = threadVal.i;
        int b = threadVal.j;
        
        // cout << a << ' ' << b << endl;
        //Perform the matrix multiplication
        C[a][b]= 0;
        for(int i =0;i < K; i++)
        C[a][b] += A[a][i]*B[i][b];  
        
        
}
int main()
{
    clock_t t1, t2;//timer
    t1 = clock();//timer
    DWORD ThreadId;
    HANDLE   ThreadHandle;
    
    Initialize(A,B,C);
    // printf array A
    /* printf("Array A is\n"); 
    for(int i= 0; i < M; i++ )
    {
     for( int j = 0; j < K; j++ )
        printf("%.2f ",A[i][j]);
     
     printf("\n");
    }
    
    printf("\n\n");
    
    // printf array B
    printf("Array B is\n"); 
    for(int i= 0; i < K; i++ )
    {
     for( int j = 0; j < N; j++ )
        printf("%.2f ",B[i][j]);
     
     printf("\n");
    }   
    */
    // create M * N worker threads
    for(int i= 0; i < M; i++ )
    {
     for( int j = 0; j < N; j++ )
     {      // allocate memory
           if(SetThread ) {
           struct v *data = (struct v *) malloc(sizeof(struct v) );
           data ->i = i;
           data ->j = j;
           // Create Thread to calculate value of matrix at row column
           ThreadHandle = CreateThread(
           NULL, // default security attributes 
           0, // default stack size
           multiplyThread, // thread function
           data, // parameter to thread function 
           0, // default creation flags
           &ThreadId); // returns the thread identifier
           }
           else if(!SetThread) {
              struct v *data = (struct v *) malloc(sizeof(struct v) );
              data ->i = i;
              data ->j = j;
                // cout << a << ' ' << b << endl;
                //Perform the matrix multiplication
              SingleThread(data);
                
                
           }
      /*
       if ( ThreadHandle != NULL )
       {
         // now wait for the thread to finish
         WaitForSingleObject(ThreadHandle,INFINITE);
        
         // close the thread handle
         CloseHandle(ThreadHandle);
       } 
       */        
     }
     printf("\n");
   }
   t2 = clock();  //timer
    printf("%lf\n", (t2-t1)/(double)(CLOCKS_PER_SEC)); //timer
    /*
   printf("Array A * B is\n"); 
   for(int i= 0; i < M; i++ )
   {
     for( int j = 0; j < N; j++ )
        printf("%d | %d | %.2f ",i,j,C[i][j]);
     
     printf("\n");
   }
   
   printf("\n");
   */
 
   
   system( "pause" );
   return 0;
}
void Initialize(double(*A)[K],double(*B)[N],double(*C)[N]) {
               for(int i = 0; i < 60 ; i ++) { for(int j = 0; j < 60; j++) {
                       if(i < 40)
                            A[i][j] = 2 * i + 4.8 * j ;
                       if(j < 40)        
                            B[i][j] = 1 + 3 * i - 6.9 * j ;
               }}
}
