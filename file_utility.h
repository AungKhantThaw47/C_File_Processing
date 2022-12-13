/* file_utility.h */
#include<stdio.h>
#include "model.h"
extern FILE *file_write_open(char fileName[255]);
extern FILE *file_read_open(char fileName[255]);
extern void Product_initialize();
extern void POS_initialize();
extern void Sale_initiaize();
extern int new_Product(struct Product pd);
extern int new_POS(struct POS pos);
extern int new_Sale(struct Sale sale);
extern int Product_Update(struct Product InPd);
extern struct Product Product_Delete(int id);
extern struct Product Product_Search(int id);
extern void fileClose(FILE *fpt);
extern int is_file_exists(const char *fname);
extern void Display_Product(struct Product pd);
extern void Display_POS(struct POS pos);