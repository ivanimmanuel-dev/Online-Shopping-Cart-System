#include <stdio.h>
#include "main.h"
//  Function to add items to cart 
int addItemToCart(int currentItems, int itemsToAdd) 
{
    if (currentItems < 0 || itemsToAdd < 0)                // returns INVALID_VALUE (-1) if inputs are negative
        return INVALID_VALUE;
    return currentItems + itemsToAdd;                      //Returns new total item count
}
    // Function to remove items from the cart
int removeItemFromCart(int currentItems, int itemsToRemove) 
{
        if (currentItems < 0 || itemsToRemove < 0)              // if inputs are negative then INVALID_VALUE (-1) is returned
            return INVALID_VALUE;
        if (itemsToRemove > currentItems)                       // if customer enters more items to remove than the items available in the cart then EMPTY_CART (0) is returned
            return EMPTY_CART;
        return currentItems - itemsToRemove;                    // returns new number of items present in the cart after removing items
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