#pragma once
#if defined(__cplusplus)
extern "C" {
#endif

	
#define INVALID_VALUE -1
#define EMPTY_CART 0

int addItemToCart(int currentItems, int itemsToAdd);
int removeItemFromCart(int currentItems, int itemsToRemove);
double calculateTotalPrice(double itemPrice, int quantity, double taxRate);
double applyDiscount(double totalPrice, double discountRate, double maxDiscount);

#if defined(__cplusplus)
}
#endif
