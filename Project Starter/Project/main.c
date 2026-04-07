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
 *                              TUI Functions
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
 *                              MAIN Loop
 *=========================================================================*/

void runShoppingLoop(void)
{
    // Product Catalog and Shopping Cart initialization
    Product catalog[MAX_CATALOG_ITEMS] = { {1, "Wireless Headphones", 79.99, 10},{2, "Wired Mouse", 34.99, 15},{3, "USB-C Hub", 49.99, 20},{4, "Mechanical Keyboard", 99.99, 5},{5, "Webcam HD", 89.99, 12},{6, "Mouse Pad XL", 19.99, 25},{7, "LED Desk Lamp", 44.99,  15},{8, "Smartphone Stand", 14.99, 30} };
    CartItem cart[MAX_CART_SLOTS];
    int cartSize = 0;
    memset(cart, 0, sizeof(cart)); // initialize cart to empty
    int choice;
    int running = 1; // flag to control the main loop
    printHeader();
    printf("  Welcome to OSC! Use the menu below to shop.\n");
    while (running) // main shopping loop
    {
        printf("\n  MENU\n");
        printSeparator();
        printf("  [1] Browse products\n");
        printf("  [2] Add item(s) to cart\n");
        printf("  [3] Remove item(s) from cart\n");
        printf("  [4] View cart\n");
        printf("  [5] Checkout (no discount)\n");
        printf("  [6] Checkout (with 10%% loyalty discount)\n");
        printf("  [0] Quit\n");
        printSeparator();
        printf("  Enter choice: ");
        if (scanf_s("%d", &choice) != 1) // if input is not a valid integer, flushes the input and prompts again
        {
            while (getchar() != '\n');
            printf("  Invalid input. Please enter a number.\n");
            continue;
        }
        switch (choice) // handles the user's menu choice and calls the appropriate functions based on the selection
        {
        case 1: // displays the product catalog
            showCatalog(catalog, MAX_CATALOG_ITEMS);
            break;
        case 2: // allows the user to add items to their cart, checking for valid input and stock availability
        {
            showCatalog(catalog, MAX_CATALOG_ITEMS);
            int pid, qty;
            printf("  Enter product ID: ");
            if (scanf_s("%d", &pid) != 1) // if input is not a valid integer, flushes the input and breaks out of the case
            {
                while (getchar() != '\n');
                break;
            }
            int pi = findProduct(catalog, MAX_CATALOG_ITEMS, pid);
            if (pi < 0) // if product ID is not found in the catalog, informs the user and breaks out of the case
            {
                printf("  Product not found.\n");
                break;
            }
            printf("  Enter quantity: ");
            if (scanf_s("%d", &qty) != 1) // if quantity is not a valid integer, flushes the input and breaks out of the case
            {
                while (getchar() != '\n');
                break;
            }
            if (qty <= 0) // if quantity is not greater than 0, informs the user and breaks out of the case
            {
                printf("  Quantity must be greater than 0.\n");
                break;
            }
            if (qty > catalog[pi].stock) // if requested quantity exceeds available stock, informs the user of the available stock and breaks out of the case
            {
                printf("  Only %d in stock. Enter a lower quantity.\n", catalog[pi].stock);
                break;
            }
            int slot = findCartSlot(cart, cartSize, pid);
            if (slot >= 0) // if the product is already in the cart, adds to the existing quantity in that slot
            {
                int newQty = addItemToCart(cart[slot].quantity, qty);
                if (newQty == INVALID_VALUE) // if the new quantity calculation returns an invalid value, informs the user and breaks out of the case
                {
                    printf("  Error adding items.\n");
                    break;
                }
                cart[slot].quantity = newQty;
            }
            else // if the product is not already in the cart, creates a new cart item in the next available slot
            {
                if (cartSize >= MAX_CART_SLOTS)
                {
                    printf("  Cart is full.\n");
                    break;
                }
                cart[cartSize].productId = pid;
                cart[cartSize].quantity = addItemToCart(0, qty);
                cartSize++;
            }
            catalog[pi].stock = removeItemFromCart(catalog[pi].stock, qty); // reduces the stock in the catalog by the quantity added to the cart
            printf("  Added %dx %s to your cart.\n", qty, catalog[pi].name);
            break;
        }
        case 3: // allows the user to remove items from their cart, checking for valid input and ensuring the product is in the cart
        {
            showCart(cart, cartSize, catalog, MAX_CATALOG_ITEMS);
            if (cartSize == 0) // if the cart is empty, informs the user and breaks out of the case
            {
                break;
            }
            int pid, qty;
            printf("  Enter product ID to remove: ");
            if (scanf_s("%d", &pid) != 1) // if input is not a valid integer, flushes the input and breaks out of the case
            {
                while (getchar() != '\n');
                break;
            }
            int slot = findCartSlot(cart, cartSize, pid);
            if (slot < 0) // if the product ID is not found in the cart, informs the user and breaks out of the case
            {
                printf("  That product is not in your cart.\n");
                break;
            }
            int pi = findProduct(catalog, MAX_CATALOG_ITEMS, pid);
            printf("  How many to remove (current: %d)? ", cart[slot].quantity);
            if (scanf_s("%d", &qty) != 1) // if input is not a valid integer, flushes the input and breaks out of the case
            {
                while (getchar() != '\n');
                break;
            }
            if (qty <= 0) // if quantity to remove is not greater than 0, informs the user and breaks out of the case
            {
                printf("  Quantity must be greater than 0.\n");
                break;
            }
            int newQty = removeItemFromCart(cart[slot].quantity, qty);
            if (newQty == INVALID_VALUE) // if the new quantity calculation returns an invalid value, informs the user and breaks out of the case
            {
                printf("  Invalid quantity.\n");
                break;
            }
            /* restore stock */
            int actualRemoved = (qty > cart[slot].quantity) ? cart[slot].quantity : qty; // calculates the actual number of items removed and restores that quantity back to the catalog stock
            if (pi >= 0) // if the product is found in the catalog, adds the removed quantity back to the stock
            {
                catalog[pi].stock = addItemToCart(catalog[pi].stock, actualRemoved);
            }
            if (newQty == EMPTY_CART) // if all items of that product are removed from the cart, removes the cart item entirely by shifting the remaining items down
            {
                for (int i = slot; i < cartSize - 1; i++)
                {
                    cart[i] = cart[i + 1];
                }
                cartSize--;
                printf("  Item removed from cart.\n");
            }
            else // if some items remain after removal, updates the quantity in the cart and informs the user of the remaining quantity
            {
                cart[slot].quantity = newQty;
                printf("  Removed %d item(s). %d remaining in cart.\n", actualRemoved, newQty);
            }
            break;
        }
        case 4: // displays the current contents of the cart
            showCart(cart, cartSize, catalog, MAX_CATALOG_ITEMS);
            break;
        case 5: // proceeds to checkout without applying the loyalty discount, generates a receipt, and then clears the cart
            showReceipt(cart, cartSize, catalog, MAX_CATALOG_ITEMS, 0);
            if (cartSize > 0)
            {
                cartSize = 0;
                memset(cart, 0, sizeof(cart));
                printf("  Thank you for your purchase!\n");
            }
            break;
        case 6: // proceeds to checkout with applying the loyalty discount, generates a receipt, and then clears the cart
            showReceipt(cart, cartSize, catalog, MAX_CATALOG_ITEMS, 1);
            if (cartSize > 0)
            {
                cartSize = 0;
                memset(cart, 0, sizeof(cart));
                printf("  Thank you for your purchase!\n");
            }
            break;
        case 0: // exits the program with a goodbye message
            printf("\n  Goodbye! Visit again for more great deals.\n\n");
            running = 0;
            break;
        default: // if the user enters an invalid menu option, informs the user and prompts again
            printf("  Invalid option. Choose options 0-6.\n");
            break;
        }
    }
}

/*=========================================================================
 *                              MAIN Function
 *=========================================================================*/

int main(void) // entry point of the program, calls the main shopping loop function
{
    runShoppingLoop(); // starts the shopping cart system
	return 0; // returns 0 to indicate successful execution
}