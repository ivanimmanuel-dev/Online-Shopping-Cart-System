#include <stdio.h>
#include "main.h"
//  Function to add items to cart 
int addItemToCart(int currentItems, int itemsToAdd) 
{
    if (currentItems < 0 || itemsToAdd < 0)                // returns INVALID_VALUE (-1) if inputs are negative
        return INVALID_VALUE;
    return currentItems + itemsToAdd;                      //Returns new total item count
}



int removeItemFromCart(int currentItems, int itemsToRemove) 
{
    return -7;
}

double calculateTotalPrice(double itemPrice, int quantity, double taxRate) 
{
    return -7;
}

double applyDiscount(double totalPrice, double discountRate, double maxDiscount) 
{
    return -7;
}

int main(void) 
{
    return 0;
}