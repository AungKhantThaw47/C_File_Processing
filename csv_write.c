#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DataItem
{
    int id;
    char name[256];
    char email[256];
    char phone[256];
};

int main()
{
    FILE *fpt;
    char check;
    fpt = fopen("MyFile.csv", "w+");
    fprintf(fpt, "ID, Name, Email, Phone Number\n");
    do
    {
        struct DataItem *dt = malloc(sizeof(struct DataItem));
        printf("Enter your id: ");
        scanf("%d", &dt->id);
        printf("Enter your name(use _ instead of space): ");
        scanf("%s", &dt->name);
        printf("Enter your email: ");
        scanf("%s", &dt->email);
        // printf("Worked");
        printf("Enter your phone: ");
        scanf("%s", &dt->phone);
        // printf("Worked 2");
        
        fprintf(fpt, "%d, %s, %s, %s\n", dt->id, dt->name, dt->email, dt->phone);
        printf("Do you want to continue?(y/n): ");
        scanf("%c", &check);
        scanf("%c", &check);
    } while (check == 'y');

    // printf("work?");
    // int id = 34;
    // char name[] = "my name";
    // char email[] = "test@gmail.com";
    // char phone[] = "02020202";
    

    fclose(fpt);
    return 0;
}