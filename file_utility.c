/* file_utility.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utility.h"
#include "model.h"
#include "env.h"

void String_Token_Check()
{
    // char str[80] = "Product_ID, Product_Name, Product_Quantity, Product_Coste";
    char str[80] = "12, product_one, 34, 23.000000";
    const char s[2] = ",";
    char *token;

    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while (token != NULL)
    {
        printf("%s\n", token);

        token = strtok(NULL, s);
    }
}

const char *getfield(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

FILE *file_write_open(char fileName[255])
{
    FILE *fpt;
    fpt = fopen(fileName, "w+");
    return fpt;
}

FILE *file_read_open(char fileName[255])
{
    FILE *fpt;
    fpt = fopen(fileName, "r");
    return fpt;
}

FILE *file_append_open(char fileName[255])
{
    FILE *fpt;
    fpt = fopen(fileName, "a");
    return fpt;
}

void Product_initialize()
{
    FILE *fpt;
    if (is_file_exists(PRODUCT_FILE) == 0)
    {
        fpt = file_write_open(PRODUCT_FILE);
        fprintf(fpt, "Product_ID, Product_Name, Product_Quantity, Product_Cost");
    }
    fileClose(fpt);
}

void POS_initialize()
{
    FILE *fpt;
    if (is_file_exists(POS_FILE) == 0)
    {
        fpt = file_write_open(POS_FILE);
        fprintf(fpt, "Bill_ID, Customer_Name, Transaction_Datetime_Sec, Transaction_Datetime_Min, Transaction_Datetime_Hour, Transaction_Datetime_Day, Transaction_Datetime_Month, Transaction_Datetime_Year, Product_Quantity , Product_Price, Product_Cost");
    }
    fileClose(fpt);
}

void Sale_initiaize()
{
    FILE *fpt;
    if (is_file_exists(SALE_FILE) == 0)
    {
        fpt = file_write_open(SALE_FILE);
        fprintf(fpt, "Product_ID, Product_Name, Product_Quantity, Product_Price, Product_Cost, Profit, Transaction_Datetime_Sec, Transaction_Datetime_Min, Transaction_Datetime_Hour, Transaction_Datetime_Day, Transaction_Datetime_Month, Transaction_Datetime_Year");
    }
    fileClose(fpt);
}

int new_Product(struct Product pd)
{
    FILE *fpt;
    if (is_file_exists(PRODUCT_FILE) == 0)
    {
        fpt = file_write_open(PRODUCT_FILE);
        fprintf(fpt, "Product_ID,Product_Name,Product_Quantity,Product_Cost");
        fprintf(fpt, "\n%d,%s,%d,%lf", pd.product_id, pd.product_name, pd.product_quantity, pd.product_cost);
    }
    else
    {
        struct Product checkPd = Product_Search(pd.product_id);
        if (checkPd.product_id == NULL)
        {
            // printf("This is new\n");
            fpt = file_append_open(PRODUCT_FILE);
            fprintf(fpt, "\n%d,%s,%d,%lf", pd.product_id, pd.product_name, pd.product_quantity, pd.product_cost);
            fileClose(fpt);
            return 1;
        }
    }
    fileClose(fpt);
    return 0;
}

int new_POS(struct POS pos)
{
    FILE *fpt;
    if (is_file_exists(POS_FILE) == 0)
    {
        fpt = file_write_open(POS_FILE);
        fprintf(fpt, "Bill_ID, Customer_Name, Transaction_Datetime_Sec, Transaction_Datetime_Min, Transaction_Datetime_Hour, Transaction_Datetime_Day, Transaction_Datetime_Month, Transaction_Datetime_Year, Product_Quantity , Product_Price, Product_Cost");
        fprintf(fpt, "\n%d, %s, %d, %d, %d, %d, %d, %d, %d, %lf, %lf", pos.bill_id, pos.customer_name, pos.transaction_datetime.tm_sec, pos.transaction_datetime.tm_min, pos.transaction_datetime.tm_hour, pos.transaction_datetime.tm_mday, pos.transaction_datetime.tm_mon, pos.transaction_datetime.tm_year, pos.product_quantity, pos.product_price, pos.product_cost);
    }
    else
    {
        fpt = file_append_open(POS_FILE);
        fprintf(fpt, "\n%d, %s, %d, %d, %d, %d, %d, %d, %d, %lf, %lf", pos.bill_id, pos.customer_name, pos.transaction_datetime.tm_sec, pos.transaction_datetime.tm_min, pos.transaction_datetime.tm_hour, pos.transaction_datetime.tm_mday, pos.transaction_datetime.tm_mon, pos.transaction_datetime.tm_year, pos.product_quantity, pos.product_price, pos.product_cost);
    }
    fileClose(fpt);
    return 1;
}

int new_Sale(struct Sale sale)
{
    FILE *fpt;
    if (is_file_exists(SALE_FILE) == 0)
    {
        fpt = file_write_open(SALE_FILE);
        fprintf(fpt, "Product_ID, Product_Name, Product_Quantity, Product_Price, Product_Cost, Profit, Transaction_Datetime_Sec, Transaction_Datetime_Min, Transaction_Datetime_Hour, Transaction_Datetime_Day, Transaction_Datetime_Month, Transaction_Datetime_Year");
        fprintf(fpt, "\n%d, %s, %d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", sale.product_id, sale.product_name, sale.product_quantity, sale.product_price, sale.product_cost, sale.profit, sale.transaction_datetime.tm_sec, sale.transaction_datetime.tm_min, sale.transaction_datetime.tm_hour, sale.transaction_datetime.tm_mday, sale.transaction_datetime.tm_mon, sale.transaction_datetime.tm_year);
    }
    else
    {
        fpt = file_append_open(SALE_FILE);
        fprintf(fpt, "\n%d, %s, %d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", sale.product_id, sale.product_name, sale.product_quantity, sale.product_price, sale.product_cost, sale.profit, sale.transaction_datetime.tm_sec, sale.transaction_datetime.tm_min, sale.transaction_datetime.tm_hour, sale.transaction_datetime.tm_mday, sale.transaction_datetime.tm_mon, sale.transaction_datetime.tm_year);
    }
    fileClose(fpt);
    return 1;
}

int Product_Update(struct Product InPd){
    FILE *fpt;
    FILE *tmpFile;
    struct Product tempPd;
    int state = 0;
    // printf("Product Delete\n");
    char ch;
    // Opening file in reading mode
    tmpFile = file_write_open("tmp");
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    // Printing what is written in file
    // character by character using loop.
    char line[1024];
    while (fgets(line, 1024, fpt))
    {
        // printf("Working\n");
        // printf("%s", line);
        char TempLine[1024];
        strcpy(TempLine, line);
        int foundID = atoi(strtok(line, ","));

        char *tmp = strdup(line);
        // printf("Product ID: %d\n", foundID);
        if (foundID == InPd.product_id)
        {
            // printf("Found\n");
            // Display_Product(InPd);
            // printf("%d,%s,%d,%lf", InPd.product_id, InPd.product_name, InPd.product_quantity, InPd.product_cost);
            fprintf(tmpFile, "%d,%s,%d,%lf", InPd.product_id, InPd.product_name, InPd.product_quantity, InPd.product_cost);
            state = 1;
        }
        else
        {
            // printf("Else\n");
            // printf("%s", TempLine);
            fprintf(tmpFile, "%s", TempLine);
        }
        free(tmp);
    }
    fclose(fpt);
    fclose(tmpFile);
    remove(PRODUCT_FILE);
    rename("tmp",PRODUCT_FILE);
    return state;
}

struct Product Product_Delete(int id)
{
    FILE *fpt;
    FILE *tmpFile;
    struct Product pd;
    struct Product tempPd;
    pd.product_id = NULL;
    // printf("Product Delete\n");
    char ch;
    // Opening file in reading mode
    tmpFile = file_write_open("tmp");
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    // Printing what is written in file
    // character by character using loop.
    char line[1024];
    while (fgets(line, 1024, fpt))
    {
        // printf("Working\n");
        // printf("%s", line);
        char TempLine[1024];
        strcpy(TempLine, line);
        int foundID = atoi(strtok(line, ","));

        char *tmp = strdup(line);
        // printf("Product ID: %d\n", foundID);
        if (foundID == id)
        {
            // printf("Found\n");
            pd.product_id = foundID;
            strcpy(pd.product_name, strtok(NULL, ","));
            pd.product_quantity = atoi(strtok(NULL, ","));
            pd.product_cost = atof(strtok(NULL, ","));
            // Display_Product(pd);
        }
        else
        {
            fprintf(tmpFile, "%s", TempLine);
        }
        free(tmp);
    }
    fclose(fpt);
    fclose(tmpFile);
    remove(PRODUCT_FILE);
    rename("tmp",PRODUCT_FILE);
    return pd;
};

struct Product Product_Search(int id)
{
    FILE *fpt;
    struct Product pd;
    pd.product_id = NULL;
    // printf("Product Search\n");
    char ch;
    // Opening file in reading mode
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    // Printing what is written in file
    // character by character using loop.
    char line[1024];
    while (fgets(line, 1024, fpt))
    {
        // printf("%s", line);
        int foundID = atoi(strtok(line, ","));

        char *tmp = strdup(line);
        // printf("Product ID: %d\n", foundID);
        if (foundID == id)
        {
            // printf("Found\n");
            pd.product_id = foundID;
            strcpy(pd.product_name, strtok(NULL, ","));
            pd.product_quantity = atoi(strtok(NULL, ","));
            pd.product_cost = atof(strtok(NULL, ","));
            // Display_Product(pd);
            free(tmp);
            break;
        }
        free(tmp);
    }
    fclose(fpt);
    return pd;
}

void fileClose(FILE *fpt)
{
    fclose(fpt);
}

int is_file_exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void Display_Product(struct Product pd)
{
    printf("Product");
    printf("Product ID: %d\nProduct Name: %s\nProduct Quantity: %d\nProduct Cost: %lf\n", pd.product_id, pd.product_name, pd.product_quantity, pd.product_cost);
}
void Display_POS(struct POS pos)
{
    printf("Bill ID: %d\nCustomer Name: %s\nTime: %s\nProduct Quantity: %d\nProduct Price: %lf\nProduct Cost: %lf\n", pos.bill_id, pos.customer_name, asctime(&pos.transaction_datetime), pos.product_quantity, pos.product_price, pos.product_cost);
}