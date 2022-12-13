#include<time.h>
#include<stdio.h>

int main(){
    struct tm xmas = { 0, 0, 0, 24, 11, 116 };
    
    time_t rawtime = mktime(&xmas);
    
    if (rawtime == -1) {
        
         puts("The mktime() function failed");   
         return 1;
    }
    
    printf("The Unix time for Xmas is: %ld\n", rawtime);
}