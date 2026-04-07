#pragma once
#if defined(__cplusplus)
extern "C" {
#endif
	
#define INVALID_VALUE -1	 //	indicates an invalid input was provided to a function
#define EMPTY_CART 0		 // indicates the cart is empty after removing items
#define MAX_CART_SLOTS 20	 /* max unique products in cart */
#define MAX_CATALOG_ITEMS 8	 /* number of products in store */
#define TAX_RATE 0.13		 /* 13% HST */
#define MAX_DISCOUNT 50.00	 /* hard cap on any discount ($) */
#define DISCOUNT_RATE 0.10	 /* 10% loyalty discount */

/* Core shopping cart functions */
int addItemToCart(int currentItems, int itemsToAdd);
int removeItemFromCart(int currentItems, int itemsToRemove);
double calculateTotalPrice(double itemPrice, int quantity, double taxRate);
double applyDiscount(double totalPrice, double discountRate, double maxDiscount);

typedef struct // defines a product in the catalog with an ID, name, price, and stock quantity
{
	int    id;
	char   name[40];
	double price;
	int    stock;
} Product;

typedef struct // defines an item in the shopping cart with a product ID and quantity
{
	int    productId;
	int    quantity;
} CartItem;

/* GUI functions for displaying the catalog, cart, and receipt */
void   printSeparator(void);
void   printHeader(void);
void   showCatalog(const Product catalog[], int count);
void   showCart(const CartItem cart[], int cartSize, const Product catalog[], int catalogCount);
void   showReceipt(const CartItem cart[], int cartSize, const Product catalog[], int catalogCount, int applyingDiscount);
int    findCartSlot(const CartItem cart[], int cartSize, int productId);
int    findProduct(const Product catalog[], int count, int productId);
void   runShoppingLoop(void);

#if defined(__cplusplus)
}
#endif
