#include<stdio.h>
#include "file_utility.h"
#include<string.h>
#include "model.h"
#include "env.h"

int main(){
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
    // pd = Product_Delete(12);
    pd.product_id = 10;
    strcpy(pd.product_name,"T_34");
    pd.product_quantity = 22;
    pd.product_cost = 1010;
    Product_Update(pd);
    return 0;
}