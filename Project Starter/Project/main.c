#include <stdio.h>
#include <string.h>
#include "main.h"

/* ========================================================================
 *                              CORE Functions       
 *=========================================================================*/

//  Function to add items to cart 
int addItemToCart(int currentItems, int itemsToAdd) 
{
    if (currentItems < 0 || itemsToAdd < 0) // returns INVALID_VALUE (-1) if inputs are negative
    {
        return INVALID_VALUE;
    }
    return currentItems + itemsToAdd; // returns new total item count
}

// Function to remove items from the cart
int removeItemFromCart(int currentItems, int itemsToRemove) 
{
    if (currentItems < 0 || itemsToRemove < 0) // if inputs are negative then INVALID_VALUE (-1) is returned
    {
        return INVALID_VALUE;
    }
    if (itemsToRemove > currentItems) // if customer enters more items to remove than the items available in the cart then EMPTY_CART (0) is returned
    {
        return EMPTY_CART;
    }
    return currentItems - itemsToRemove; // returns new number of items present in the cart after removing items
}

// Function to calculate total price with tax
double calculateTotalPrice(double itemPrice, int quantity, double taxRate)
{
    if (itemPrice < 0 || quantity < 0 || taxRate < 0) // if inputs are negative then INVALID_VALUE (-1) is returned
    {
        return INVALID_VALUE;
    }
	return (itemPrice * quantity) * (1.0 + taxRate); // returns total price after applying tax
}

// Function to apply discount with cap
double applyDiscount(double totalPrice, double discountRate, double maxDiscount)
{
	if (totalPrice < 0 || discountRate < 0 || maxDiscount < 0) // if inputs are negative then INVALID_VALUE (-1) is returned
    {
        return INVALID_VALUE;
    }
	double discount = totalPrice * discountRate; // calculates discount based on the total price and discount rate
	if (discount > maxDiscount) // if calculated discount exceeds the max discount, then max discount is applied instead
    {
        discount = maxDiscount;
    }
	return totalPrice - discount; // returns total price after applying discount
}

/*=========================================================================
 *                              GUI Functions
 *=========================================================================*/

void printSeparator(void) // prints a separator line for better readability
{
    printf("--------------------------------------------------------\n");
}

void printHeader(void) // prints the header for the shopping cart system
{
    printf("\n========================================================\n");
    printf("         ONLINE SHOPPING CART SYSTEM\n");
    printf("========================================================\n\n");
}

void showCatalog(const Product catalog[], int count) // displays the product catalog in a formatted manner
{
    printf("\n  %-4s  %-28s  %8s  %s\n", "ID", "Product", "Price", "Stock");
    printSeparator();
	for (int i = 0; i < count; i++) // iterates through the catalog and prints each product's details
    {
        printf("  [%d]   %-28s  $%7.2f  %d\n",catalog[i].id,catalog[i].name,catalog[i].price,catalog[i].stock);
    }
    printf("\n");
}

int findProduct(const Product catalog[], int count, int productId) // searches for a product by ID in the catalog and returns its index, or -1 if not found
{
    for (int i = 0; i < count; i++)
    {
        if (catalog[i].id == productId) return i;
    }
    return -1;
}

int findCartSlot(const CartItem cart[], int cartSize, int productId) // searches for a product in the cart by product ID and returns its index, or -1 if not found
{
    for (int i = 0; i < cartSize; i++)
    {
        if (cart[i].productId == productId) return i;
    }
    return -1;
}

void showCart(const CartItem cart[], int cartSize, const Product catalog[], int catalogCount) // displays the contents of the shopping cart, including product names, quantities, and subtotals
{
    if (cartSize == 0) 
    {
        printf("\n  Your cart is empty.\n\n");
        return;
    }
    printf("\n  %-28s  %5s  %10s\n", "Product", "Qty", "Subtotal");
    printSeparator();
    int totalItems = 0;
    for (int i = 0; i < cartSize; i++) 
    {
        int pi = findProduct(catalog, catalogCount, cart[i].productId);
        if (pi < 0)
        {
            continue;
        }
        double sub = catalog[pi].price * cart[i].quantity;
        printf("  %-28s x%5d  $%9.2f\n", catalog[pi].name, cart[i].quantity, sub);
        totalItems = addItemToCart(totalItems, cart[i].quantity);
    }
    printSeparator();
    printf("  Total items in cart: %d\n\n", totalItems);
}

void showReceipt(const CartItem cart[], int cartSize, const Product catalog[], int catalogCount, int applyingDiscount) // generates and displays a receipt
{
	if (cartSize == 0) // if cart is empty, informs the user and exits the function
    {
        printf("\n  Nothing to check out.\n\n");
        return;
    }
	printf("\n==================================================\n"); 
	printf("                    RECEIPT\n");                          // prints the receipt header
    printf("==================================================\n");
    double subtotal = 0.0;
    int totalQty = 0;
	for (int i = 0; i < cartSize; i++) // iterates through the cart items, finds the corresponding product in the catalog, calculates line totals, and prints each line item
    {
        int pi = findProduct(catalog, catalogCount, cart[i].productId);
        if (pi < 0)
        {
            continue;
        }
        double lineTotal = catalog[pi].price * cart[i].quantity;
        printf("  %-28s x%d   $  %.2f\n", catalog[pi].name, cart[i].quantity, lineTotal);
        subtotal = subtotal + lineTotal;
        totalQty = addItemToCart(totalQty, cart[i].quantity);
    }
    printf("--------------------------------------------------\n");
    printf("  Subtotal (%d item(s)):             $%8.2f\n", totalQty, subtotal);
	double afterDiscount = subtotal;
	if (applyingDiscount) // if the user chose to apply the loyalty discount, calculates the discounted price and prints the discount amount
    {
        double discounted = applyDiscount(subtotal, DISCOUNT_RATE, MAX_DISCOUNT);
        double saved = subtotal - discounted;
        printf("  Loyalty discount (10%%, max $%.0f): - $%8.2f\n", MAX_DISCOUNT, saved);
		afterDiscount = discounted;
    }
    double total = calculateTotalPrice(afterDiscount, 1, TAX_RATE);
    double taxAmt = total - afterDiscount;
    printf("  HST (13%%):                         $%8.2f\n", taxAmt);
    printf("--------------------------------------------------\n");
    printf("  TOTAL:                             $%8.2f\n", total);
    printf("==================================================\n\n");
}

/*=========================================================================
 *                              MAIN Function
 *=========================================================================*/

int main(void) // entry point of the program, calls the main shopping loop function
{
	return 0; // returns 0 to indicate successful execution
}