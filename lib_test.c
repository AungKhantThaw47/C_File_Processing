#include<stdio.h>
#include "file_utility.h"
#include<string.h>
#include "model.h"
#include "env.h"

int main(){
    // FILE *testFp;
    // struct POS *pos;
    // printf("worked 4\n");
    // pos->bill_id = 1;
    // printf("worked 5\n");
    // strcpy(pos->customer_name,"tester");
    // printf("worked 6\n");
    // pos->product_cost = 10;
    // pos->product_price = 20;
    // pos->product_quantity = 11;
    // time_t t;
    // t = time(NULL);
    // pos->transaction_datetime = *localtime(&t);
    struct Product pd;

    pd.product_id = 12;
    strcpy(pd.product_name,"product_one");
    pd.product_quantity = 34;
    pd.product_cost = 23;
    new_Product(pd);

    pd.product_id = 10;
    strcpy(pd.product_name,"product_two");
    pd.product_quantity = 31;
    pd.product_cost = 98;
    new_Product(pd);

    pd.product_id = 43;
    strcpy(pd.product_name,"product_three");
    pd.product_quantity = 22;
    pd.product_cost = 1010;
    new_Product(pd);

    pd = Product_Search(10);
    // Display_Product(pd);
    // pd = Product_Delete(12);
    pd.product_id = 10;
    strcpy(pd.product_name,"T_34");
    pd.product_quantity = 22;
    pd.product_cost = 1010;
    // strcpy(pd.product_name,"T_34");
    Product_Update(pd);
    return 0;
}