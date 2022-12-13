/* file_utility.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utility.h"
#include "model.h"
#include "env.h"

void String_Token_Check()
{
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

// @docs - To Open file with Write mode using file name
FILE *file_write_open(char fileName[255])
{
    FILE *fpt;
    fpt = fopen(fileName, "w+");
    return fpt;
}

// @docs - To Open file with Read mode using file name
FILE *file_read_open(char fileName[255])
{
    FILE *fpt;
    fpt = fopen(fileName, "r");
    return fpt;
}

// @docs - To Open file with Append mode using file name
FILE *file_append_open(char fileName[255])
{
    FILE *fpt;
    fpt = fopen(fileName, "a");
    return fpt;
}

// @docs - To initialize Product database
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

// @docs - To initialize POS database
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

// @docs - To initialize Sale database
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

// @docs - To add new Product to database
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
            fpt = file_append_open(PRODUCT_FILE);
            fprintf(fpt, "\n%d,%s,%d,%lf", pd.product_id, pd.product_name, pd.product_quantity, pd.product_cost);
            fileClose(fpt);
            return 1;
        }
    }
    fileClose(fpt);
    return 0;
}

// @docs - To add new POS to database
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

// @docs - To add new Sale to database
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

// @docs - To Update one row of Product database using Product ID
int Product_Update(struct Product InPd)
{
    FILE *fpt;
    FILE *tmpFile;
    struct Product tempPd;
    int state = 0;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    char line[1024];
    while (fgets(line, 1024, fpt))
    {
        char TempLine[1024];
        strcpy(TempLine, line);
        int foundID = atoi(strtok(line, ","));

        char *tmp = strdup(line);

        if (foundID == InPd.product_id)
        {

            fprintf(tmpFile, "%d,%s,%d,%lf", InPd.product_id, InPd.product_name, InPd.product_quantity, InPd.product_cost);
            state = 1;
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
    rename("tmp", PRODUCT_FILE);
    return state;
}

// @docs - To Delete one row of Product database using Product ID
struct Product Product_Delete(int id)
{
    FILE *fpt;
    FILE *tmpFile;
    struct Product pd;
    struct Product tempPd;
    pd.product_id = NULL;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    char line[1024];
    while (fgets(line, 1024, fpt))
    {

        char TempLine[1024];
        strcpy(TempLine, line);
        int foundID = atoi(strtok(line, ","));

        char *tmp = strdup(line);

        if (foundID == id)
        {

            pd.product_id = foundID;
            strcpy(pd.product_name, strtok(NULL, ","));
            pd.product_quantity = atoi(strtok(NULL, ","));
            pd.product_cost = atof(strtok(NULL, ","));
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
    rename("tmp", PRODUCT_FILE);
    return pd;
};

// @docs - To Search one row of Product database using Product ID
struct Product Product_Search(int id)
{
    FILE *fpt;
    struct Product pd;
    pd.product_id = NULL;

    char ch;
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    char line[1024];
    while (fgets(line, 1024, fpt))
    {

        int foundID = atoi(strtok(line, ","));
        char *tmp = strdup(line);

        if (foundID == id)
        {
            pd.product_id = foundID;
            strcpy(pd.product_name, strtok(NULL, ","));
            pd.product_quantity = atoi(strtok(NULL, ","));
            pd.product_cost = atof(strtok(NULL, ","));
            free(tmp);
            break;
        }
        free(tmp);
    }
    fclose(fpt);
    return pd;
}

// @docs - To Close file after every operation
void fileClose(FILE *fpt)
{
    fclose(fpt);
}

// @docs - To Check if file already exists or not
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

// @docs - To Display Product Data
void Display_Product(struct Product pd)
{
    printf("Product");
    printf("Product ID: %d\nProduct Name: %s\nProduct Quantity: %d\nProduct Cost: %lf\n", pd.product_id, pd.product_name, pd.product_quantity, pd.product_cost);
}

void Display_POS(struct POS pos)
{
    printf("Bill ID: %d\nCustomer Name: %s\nTime: %s\nProduct Quantity: %d\nProduct Price: %lf\nProduct Cost: %lf\n", pos.bill_id, pos.customer_name, asctime(&pos.transaction_datetime), pos.product_quantity, pos.product_price, pos.product_cost);
}