#include<stdio.h> 
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>
#include<unistd.h>

pthread_mutex_t m1;
sem_t st;
//static
 int i=1;int number = 0;
int c_generate;
void *num_generate()
{
  pthread_mutex_lock(&m1);
  srand(time(NULL));
    c_generate = (rand()%99) +1;
    //sleep(100);
    pthread_mutex_unlock(&m1);
   return NULL;
}
void *guess_part(){
  pthread_mutex_lock(&m1);
  printf("Your number: ");
  int num;
   scanf("%d",&num);
   fflush(stdin);
   if(num>0&&num<100)
   number = num;
  pthread_mutex_unlock(&m1);
   return NULL;

}
void *hints(){
   pthread_mutex_lock(&m1);
    printf("Enter the number between 1-100:\n");
   if(i==1){ 
      int h = 100 - c_generate;
      int s = c_generate/10 ;
      int r = h%10;
      printf("                                                   HINT: The number starts with %d\n",s);
      printf("                                                   HINT:  %d __ + __ %d  =  100\n",s,r);
      
      }
    else if(i==2){
         int arr[4] = {3,5,7,9};
      srand(time(NULL));
      int guess_cpu = rand()%4;
      int h1 = c_generate*arr[guess_cpu];
      int s1 = c_generate*(arr[guess_cpu] - 1);
      printf("                                                   The remainder in the division is the number\n");
      printf("                                                   HINT: %d / %d  ?\n", h1,s1);
      }
     
    else if (i==3){
        printf("                                                 HINT:\n");
        int prime=1,even=1;
       if(c_generate==1){
         printf("                                                The number is neither prime nor composite\n");
       }
       else if(c_generate%2){
           even = 0;int k;
           for( k=2;k<=c_generate/2;k++){
              if(c_generate%k == 0){
                prime = 0;
                break;
              }
           }
           if(prime){
             srand(time(NULL));
      int calc_cpu = rand()%500;
             srand(time(NULL));
      int number_cpu = rand()%10 + 1;
      int rem = calc_cpu - (c_generate*number_cpu); 
         printf("                                                 The number is odd as well as prime\n");
         printf("                                               HINT: (__ * %d) + %d = %d\n",number_cpu,rem,calc_cpu);
         
           }
         else{
         printf("                                                 The number is odd as well as composite\n");
         if(k<c_generate/2){
            int u;
           for(u=k+1;u<=c_generate/2;u++){
              if(c_generate%u == 0){
                break;
           }
         }
          if(u<=c_generate/2){
          if(u<c_generate/2){
            int v;
           for(v=u+1;v<=c_generate/2;v++){
              if(c_generate%v == 0){
                break;
           }
         }
         if(v<=c_generate/2){
         printf("                                                 The number is divisible by %d, %d, %d\n",k,u,v);
         }
         else{
         printf("                                                 The number is divisible by %d, %d\n",k,u);
         }
          }
          else{
         printf("                                                 The number is divisible by %d, %d\n",k,u);
          }
          }
          else{
         printf("                                                 The number is divisible only by %d\n",k);
          }
           }
           else{
         printf("                                                 The number is divisible only by %d\n",k);
           }
           }
        }
        else if(c_generate%2==0){
           even = 1;int k;
            for( k=3;k<=c_generate/2;k++){
              if(c_generate%k == 0){
                prime = 0;
                break;
              }
           }
           if(prime==1){
              srand(time(NULL));
      int calc_cpu = rand()%500;
             srand(time(NULL));
      int number_cpu = rand()%10 + 1;
      int rem = calc_cpu - (c_generate*number_cpu); 
         printf("                                                 The number is even as well as prime\n");
          if(rem>=0){
           printf("                                               HINT: (__ * %d) + %d = %d\n",number_cpu,rem,calc_cpu);
         }
         else{
           printf("                                               HINT: (__ * %d) - %d = %d\n",number_cpu,rem,calc_cpu);
         }
           }
           else{
         printf("                                                 The number is even as well as composite\n");
         if(k<c_generate/2){
            int u;
           for(u=k+1;u<=c_generate/2;u++){
              if(c_generate%u == 0){
                break;
           }
         }
          if(u<=c_generate/2){
          if(u<c_generate/2){
            int v;
           for(v=u+1;v<=c_generate/2;v++){
              if(c_generate%v == 0){
                break;
           }
         }
         if(v<=c_generate/2){
         printf("                                                 The number is divisible by %d, %d, %d\n",k,u,v);
         }
         else{
         printf("                                                 The number is divisible by %d, %d\n",k,u);
         }
          }
          else{
         printf("                                                 The number is divisible by %d, %d\n",k,u);
          }
          }
          else{
         printf("                                                 The number is divisible by 2 and %d\n",k);
          }
           }
           else{
         printf("                                                 The number is divisible by 2 and %d\n",k);
           }
           }
        }
        int divider = (c_generate/10)*10;
        printf("                                              The number can be from %d to %d\n",divider,divider+9);

     }
  else;
    pthread_mutex_unlock(&m1);
   return NULL;

}

void *timer(){
  sem_wait(&st);
   int t=10;
   printf("                                                      TIMER: 10 secs there \n");
   while(t>0){
     sleep(1);
      t--; 
   } 
    if(number==c_generate){
   printf("              WONDERFUL, IT'S RIGHT.....\n\n\n PRESS ENTER");
      }
      else if(((number!=0&&number!=c_generate)||number==0)){
        printf("         WAIT...THE CORRECT ANSWER IS : %d\n\n\n PRESS any number from 1 to 9 and then ENTER key....",c_generate);
      }
    
   sem_post(&st);
   return NULL;
}
int main(){
  pthread_t th1[3];
  pthread_t th2[3];
  pthread_t th3[3];
  pthread_t th4[3];
  sem_init(&st,0,1);
  pthread_mutex_init(&m1,NULL);

  
  printf("\n\n...................GUESS THE NUMBER GAME......................\n\n\n");

  for(int j=0;j<3;j++){
    
  pthread_create(&th1[j],NULL,&num_generate,NULL);
  pthread_create(&th2[j],NULL,&hints,NULL);
  pthread_create(&th3[j],NULL,&guess_part,NULL);
  sleep(1);
  pthread_create(&th4[j],NULL,&timer,NULL);
  getchar();
  pthread_join(th1[j],NULL);
  pthread_join(th2[j],NULL);
  pthread_join(th3[j],NULL);
  pthread_join(th4[j],NULL);
    i = i+1;
  
  }

  pthread_mutex_destroy(&m1);
  sem_destroy(&st);
  
  pthread_exit(NULL);
  
return 0;
}