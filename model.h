#include<time.h>
#ifndef MODEL_H
#define MODEL_H
struct POS
{
    int bill_id;
    char customer_name[255];
    struct tm transaction_datetime;
    int product_quantity;
    double product_price;
    double product_cost;
};
struct Product
{
    int product_id;
    char product_name[255];
    int product_quantity;
    double product_cost;
};
struct Sale
{
    int product_id;
    char product_name[255];
    int product_quantity;
    double product_price;
    double product_cost;
    double profit;
    struct tm transaction_datetime;
};
#endif