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
        fprintf(fpt, "Product_ID,Product_Name,Product_Quantity,Product_Cost");
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
        fprintf(fpt, "Bill_ID,Customer_Name,Transaction_Datetime_Sec,Transaction_Datetime_Min,Transaction_Datetime_Hour,Transaction_Datetime_Day,Transaction_Datetime_Month,Transaction_Datetime_Year,Product_Quantity,Product_Price,Product_Cost");
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
        fprintf(fpt, "Transaction_ID,Product_ID,Product_Name,Product_Quantity,Product_Price,Product_Cost,Profit,Transaction_Datetime_Sec,Transaction_Datetime_Min,Transaction_Datetime_Hour,Transaction_Datetime_Day,Transaction_Datetime_Month,Transaction_Datetime_Year");
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
        fileClose(fpt);
    }
    else
    {
        struct Product checkPd = Product_Search(pd.product_id);
        if (checkPd.product_id < 0)
        {
            fpt = file_append_open(PRODUCT_FILE);
            fprintf(fpt, "\n%d,%s,%d,%lf", pd.product_id, pd.product_name, pd.product_quantity, pd.product_cost);
            fileClose(fpt);
            return 1;
        }
    }
    return 0;
}

// @docs - To add new POS to database
int new_POS(struct POS pos) // Fixed by MMA
{
    FILE *fpt;
    if (is_file_exists(POS_FILE) == 0)
    {
        fpt = file_write_open(POS_FILE);
        fprintf(fpt, "Bill_ID, Customer_Name, Transaction_Datetime_Sec, Transaction_Datetime_Min, Transaction_Datetime_Hour, Transaction_Datetime_Day, Transaction_Datetime_Month, Transaction_Datetime_Year, Product_Quantity , Product_Price, Product_Cost");
        fprintf(fpt, "\n%d,%s,%d,%d,%d,%d,%d,%d,%d,%lf,%lf", pos.bill_id, pos.customer_name, pos.transaction_datetime.tm_sec, pos.transaction_datetime.tm_min, pos.transaction_datetime.tm_hour, pos.transaction_datetime.tm_mday, pos.transaction_datetime.tm_mon, pos.transaction_datetime.tm_year, pos.product_quantity, pos.product_price, pos.product_cost);
        fileClose(fpt);
    }
    else
    {
        struct POS checkpos = POS_Search(pos.bill_id);
        if (checkpos.bill_id < 0)
        {
            fpt = file_append_open(POS_FILE);
            fprintf(fpt, "\n%d,%s,%d,%d,%d,%d,%d,%d,%d,%lf,%lf", pos.bill_id, pos.customer_name, pos.transaction_datetime.tm_sec, pos.transaction_datetime.tm_min, pos.transaction_datetime.tm_hour, pos.transaction_datetime.tm_mday, pos.transaction_datetime.tm_mon, pos.transaction_datetime.tm_year, pos.product_quantity, pos.product_price, pos.product_cost);
            fileClose(fpt);
            return 1;
        }
    }
    return 0;
}

// @docs - To add new Sale to database
int new_Sale(struct Sale sale) // Fixed by MMA
{
    FILE *fpt;
    if (is_file_exists(SALE_FILE) == 0)
    {
        fpt = file_write_open(SALE_FILE);
        fprintf(fpt, "Transaction_ID,Product_ID,Product_Name,Product_Quantity,Product_Price,Product_Cost,Profit,Transaction_Datetime_Sec,Transaction_Datetime_Min,Transaction_Datetime_Hour,Transaction_Datetime_Day,Transaction_Datetime_Month,Transaction_Datetime_Year");
        printf("Header ok\n");
        fprintf(fpt, "\n%d,%d,%s,%d,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d", sale.transaction_id, sale.product_id, sale.product_name, sale.product_quantity, sale.product_price, sale.product_cost, sale.profit, sale.transaction_datetime.tm_sec, sale.transaction_datetime.tm_min, sale.transaction_datetime.tm_hour, sale.transaction_datetime.tm_mday, sale.transaction_datetime.tm_mon, sale.transaction_datetime.tm_year);
        printf("Data ok?\n");
        fileClose(fpt);
    }
    else
    {
        struct Sale checksale = Sale_Search(sale.transaction_id);
        if (sale.product_id < 0)
        {
            fpt = file_append_open(SALE_FILE);
            fprintf(fpt, "\n%d,%d,%s,%d,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d", sale.transaction_id, sale.product_id, sale.product_name, sale.product_quantity, sale.product_price, sale.product_cost, sale.profit, sale.transaction_datetime.tm_sec, sale.transaction_datetime.tm_min, sale.transaction_datetime.tm_hour, sale.transaction_datetime.tm_mday, sale.transaction_datetime.tm_mon, sale.transaction_datetime.tm_year);
            fileClose(fpt);
            return 1;
        }
    }
    return 0;
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

            fprintf(tmpFile, "%d,%s,%d,%lf\n", InPd.product_id, InPd.product_name, InPd.product_quantity, InPd.product_cost);
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

// @docs - To Update one row of POS database using POS Bill ID
int POS_Update(struct POS InPos)
{
    FILE *fpt;
    FILE *tmpFile;
    struct POS tempPos;
    int state = 0;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(POS_FILE, "r");
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

        if (foundID == InPos.bill_id)
        {
            fprintf(fpt, "\n%d,%s,%d,%d,%d,%d,%d,%d,%d,%lf,%lf", InPos.bill_id, InPos.customer_name, InPos.transaction_datetime.tm_sec, InPos.transaction_datetime.tm_min, InPos.transaction_datetime.tm_hour, InPos.transaction_datetime.tm_mday, InPos.transaction_datetime.tm_mon, InPos.transaction_datetime.tm_year, InPos.product_quantity, InPos.product_price, InPos.product_cost);
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
    remove(POS_FILE);
    rename("tmp", POS_FILE);
    return state;
}

// @docs - To Update one row of POS database using POS Bill ID
int Sale_Update(struct Sale InSale)
{
    FILE *fpt;
    FILE *tmpFile;
    struct Sale tempSale;
    int state = 0;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(SALE_FILE, "r");
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

        if (foundID == InSale.product_id)
        {
            fprintf(fpt, "\n%d,%d,%s,%d,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d", InSale.transaction_id, InSale.product_id, InSale.product_name, InSale.product_quantity, InSale.product_price, InSale.product_cost, InSale.profit, InSale.transaction_datetime.tm_sec, InSale.transaction_datetime.tm_min, InSale.transaction_datetime.tm_hour, InSale.transaction_datetime.tm_mday, InSale.transaction_datetime.tm_mon, InSale.transaction_datetime.tm_year);
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
    remove(POS_FILE);
    rename("tmp", POS_FILE);
    return state;
}

// @docs - To Delete one row of Product database using Product ID
struct Product Product_Delete(int id)
{
    FILE *fpt;
    FILE *tmpFile;
    struct Product pd;
    struct Product tempPd;
    pd.product_id = -1;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(PRODUCT_FILE, "r");
    if (NULL == fpt)
    {
        printf("file can't be opened \n");
    }
    char line[1024];
    fgets(line, 1024, fpt);
    fprintf(tmpFile, "%s", line);
    while (fgets(line, 1024, fpt))
    {
        
        char TempLine[1024];
        strcpy(TempLine, line);
        printf("%s",TempLine);
        printf("Len %lu\n",strlen(TempLine));
        int foundID = atoi(strtok(line, ","));

        char *tmp = strdup(line);

        if (foundID == id)
        {
            printf("Found\n");
            pd.product_id = foundID;
            strcpy(pd.product_name, strtok(NULL, ","));
            pd.product_quantity = atoi(strtok(NULL, ","));
            pd.product_cost = atof(strtok(NULL, ","));
        }
        else
        {
            // TempLine[strlen(TempLine)-1]='\0';
            // printf("\n%s",TempLine);
            // fprintf(tmpFile, "\n%s", TempLine);
            fputs(TempLine,tmpFile);
        }
        free(tmp);
    }
    fclose(fpt);
    fclose(tmpFile);
    // remove(PRODUCT_FILE);
    rename(PRODUCT_FILE,"old");
    rename("tmp", PRODUCT_FILE);
    return pd;
};

// @docs - To Delete one row of Product database using Product ID
struct POS POS_Delete(int id)
{
    FILE *fpt;
    FILE *tmpFile;
    struct POS pos;
    struct POS tempPos;
    pos.bill_id = -1;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(POS_FILE, "r");
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

            pos.bill_id = foundID;
            strcpy(pos.customer_name, strtok(NULL, ","));
            pos.transaction_datetime.tm_sec = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_min = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_hour = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_mday = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_mon = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_year = atoi(strtok(NULL, ","));
            pos.product_quantity = atoi(strtok(NULL, ","));
            pos.product_price = atof(strtok(NULL, ","));
            pos.product_cost = atof(strtok(NULL, ","));
        }
        else
        {
            fprintf(tmpFile, "%s", TempLine);
        }
        free(tmp);
    }
    fclose(fpt);
    fclose(tmpFile);
    remove(POS_FILE);
    rename("tmp", POS_FILE);
    return pos;
};

// @docs - To Delete one row of Product database using Product ID
struct Sale Sale_Delete(int id)
{
    FILE *fpt;
    FILE *tmpFile;
    struct Sale sale;
    struct Sale tempSale;
    sale.transaction_id = -1;

    char ch;
    tmpFile = file_write_open("tmp");
    fpt = fopen(SALE_FILE, "r");
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
            sale.transaction_id = foundID;
            sale.product_id = atoi(strtok(NULL, ","));
            strcpy(sale.product_name, strtok(NULL, ","));
            sale.product_quantity = atoi(strtok(NULL, ","));
            sale.product_price = atof(strtok(NULL, ","));
            sale.product_cost = atof(strtok(NULL, ","));
            sale.profit = atof(strtok(NULL, ","));

            sale.transaction_datetime.tm_sec = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_min = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_hour = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_mday = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_mon = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_year = atoi(strtok(NULL, ","));
        }
        else
        {
            fprintf(tmpFile, "%s", TempLine);
        }
        free(tmp);
    }
    fclose(fpt);
    fclose(tmpFile);
    remove(SALE_FILE);
    rename("tmp", SALE_FILE);
    return sale;
};

// @docs - To Search one row of Product database using Product ID
struct Product Product_Search(int id)
{
    FILE *fpt;
    struct Product pd;
    pd.product_id = -1;

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

struct POS POS_Search(int id) // Fixed by MMA
{
    FILE *fpt;
    struct POS pos;
    pos.bill_id = -1;

    char ch;
    fpt = fopen(POS_FILE, "r");
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
            pos.bill_id = foundID;
            strcpy(pos.customer_name, strtok(NULL, ","));
            pos.transaction_datetime.tm_sec = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_min = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_hour = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_mday = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_mon = atoi(strtok(NULL, ","));
            pos.transaction_datetime.tm_year = atoi(strtok(NULL, ","));
            pos.product_quantity = atoi(strtok(NULL, ","));
            pos.product_price = atof(strtok(NULL, ","));
            pos.product_cost = atof(strtok(NULL, ","));
            free(tmp);
            break;
        }
        free(tmp);
    }
    fclose(fpt);
    return pos;
}

struct Sale Sale_Search(int id) // Fixed By MMA
{
    FILE *fpt;
    struct Sale sale;
    sale.product_id = -1;

    char ch;
    fpt = fopen(SALE_FILE, "r");
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
            sale.transaction_id = foundID;
            sale.product_id = atoi(strtok(NULL, ","));
            strcpy(sale.product_name, strtok(NULL, ","));
            sale.product_quantity = atoi(strtok(NULL, ","));
            sale.product_price = atof(strtok(NULL, ","));
            sale.product_cost = atof(strtok(NULL, ","));
            sale.profit = atof(strtok(NULL, ","));
            sale.transaction_datetime.tm_sec = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_min = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_hour = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_mday = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_mon = atoi(strtok(NULL, ","));
            sale.transaction_datetime.tm_year = atoi(strtok(NULL, ","));
            free(tmp);
            break;
        }
        free(tmp);
    }
    fclose(fpt);
    return sale;
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