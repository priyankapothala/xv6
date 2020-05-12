#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    assign_tickets(20);
    // write your own function here
    int i,k;
    const int loop=43000;
    for(i=0;i<loop;i++)
    {
        asm("nop"); //in order to prevent the compiler from optimizing the for loop
        for(k=0;k<loop;k++)
        {
            asm("nop");
        }
    }
    process_info();
    exit(); 
}