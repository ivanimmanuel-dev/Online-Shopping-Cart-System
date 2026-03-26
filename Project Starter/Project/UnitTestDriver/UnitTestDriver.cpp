#include "pch.h"
#include "CppUnitTest.h"
#include "../main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestDriver
{
	TEST_CLASS(AddItemToCartTests)
	{
	public:

		//Normal Cases

		TEST_METHOD(AddItems_NormalCase_ReturnsCorrectTotal)
		{
			// This is a standard case of adding items to the cart
			Assert::AreEqual(8, addItemToCart(5, 3));
		}

		TEST_METHOD(AddItems_AddZeroItems_ReturnsSameCount)
		{
			// Adding 0 should not change the cart
			Assert::AreEqual(5, addItemToCart(5, 0));
		}

		TEST_METHOD(AddItems_ToEmptyCart_ReturnsItemsAdded)
		{
			// Start from an empty cart
			Assert::AreEqual(4, addItemToCart(0, 4));
		}

		//Edge Case

		TEST_METHOD(AddItems_BothZero_ReturnsZero)
		{
			Assert::AreEqual(0, addItemToCart(0, 0));
		}

		//Invalid Input Cases

		TEST_METHOD(AddItems_NegativeCurrentItems_ReturnsInvalid)
		{
			Assert::AreEqual(INVALID_VALUE, addItemToCart(-1, 3));
		}

		TEST_METHOD(AddItems_NegativeItemsToAdd_ReturnsInvalid)
		{
			Assert::AreEqual(INVALID_VALUE, addItemToCart(5, -2));
		}

		TEST_METHOD(AddItems_BothNegative_ReturnsInvalid)
		{
			Assert::AreEqual(INVALID_VALUE, addItemToCart(-3, -2));
		}
	};

	TEST_CLASS(RemoveItemFromCartTests)
	{
	public:

		//Normal Cases

		TEST_METHOD(RemoveItems_NormalCase_ReturnsCorrectTotal)
		{
			// This is a standard case of removing items from the cart
			Assert::AreEqual(3, removeItemFromCart(5, 2));
		}

		TEST_METHOD(RemoveItems_ExactAmount_ReturnsZero)
		{
			// Removing all items should return EMPTY_CART (0)
			Assert::AreEqual(0, removeItemFromCart(5, 5));
		}

		TEST_METHOD(RemoveItems_RemoveZero_ReturnsSameCount)
		{
			Assert::AreEqual(5, removeItemFromCart(5, 0));
		}

		//Edge Cases

		TEST_METHOD(RemoveItems_MoreThanPresent_ReturnsEmptyCart)
		{
			// Removing more than cart holds returns EMPTY_CART (0)
			Assert::AreEqual(EMPTY_CART, removeItemFromCart(3, 10));
		}

		TEST_METHOD(RemoveItems_FromEmptyCart_ReturnsEmptyCart)
		{
			Assert::AreEqual(EMPTY_CART, removeItemFromCart(0, 0));
		}

		//Invalid Input Cases

		TEST_METHOD(RemoveItems_NegativeCurrentItems_ReturnsInvalid)
		{
			Assert::AreEqual(INVALID_VALUE, removeItemFromCart(-1, 2));
		}

		TEST_METHOD(RemoveItems_NegativeItemsToRemove_ReturnsInvalid)
		{
			Assert::AreEqual(INVALID_VALUE, removeItemFromCart(5, -1));
		}

		TEST_METHOD(RemoveItems_BothNegative_ReturnsInvalid)
		{
			Assert::AreEqual(INVALID_VALUE, removeItemFromCart(-5, -3));
		}
	};

	TEST_CLASS(CalculateTotalPriceTests)
	{
	public:

		//Normal Cases

		TEST_METHOD(CalcTotal_NormalCase_ReturnsCorrectPrice)
		{
			// Price * Quantity * (1 + TaxRate)
			Assert::AreEqual(22.00, calculateTotalPrice(10.00, 2, 0.10), 0.001);
		}

		TEST_METHOD(CalcTotal_ZeroTax_ReturnsSubtotal)
		{
			// 10.00 * 3 = 30.00
			Assert::AreEqual(30.00, calculateTotalPrice(10.00, 3, 0.00), 0.001);
		}

		TEST_METHOD(CalcTotal_QuantityOne_ReturnsPriceWithTax)
		{
			// Single item with tax
			Assert::AreEqual(11.30, calculateTotalPrice(10.00, 1, 0.13), 0.001);
		}

		//Edge Cases

		TEST_METHOD(CalcTotal_ZeroQuantity_ReturnsZero)
		{
			// Even with a price and tax, if quantity is 0, total should be 0
			Assert::AreEqual(0.00, calculateTotalPrice(9.99, 0, 0.13), 0.001);
		}

		TEST_METHOD(CalcTotal_ZeroPriceZeroTax_ReturnsZero)
		{
			Assert::AreEqual(0.00, calculateTotalPrice(0.00, 5, 0.00), 0.001);
		}

		//Invalid Input Cases

		TEST_METHOD(CalcTotal_NegativePrice_ReturnsInvalid)
		{
			Assert::AreEqual((double)INVALID_VALUE, calculateTotalPrice(-5.00, 3, 0.10), 0.001);
		}

		TEST_METHOD(CalcTotal_NegativeQuantity_ReturnsInvalid)
		{
			Assert::AreEqual((double)INVALID_VALUE, calculateTotalPrice(5.00, -1, 0.10), 0.001);
		}

		TEST_METHOD(CalcTotal_NegativeTaxRate_ReturnsInvalid)
		{
			Assert::AreEqual((double)INVALID_VALUE, calculateTotalPrice(5.00, 3, -0.10), 0.001);
		}
	};

	TEST_CLASS(ApplyDiscountTests)
	{
	public:

		//Normal Cases

		TEST_METHOD(ApplyDiscount_NormalCase_ReturnsDiscountedPrice)
		{
			// Discount is less than max, so full discount applies
			Assert::AreEqual(90.00, applyDiscount(100.00, 0.10, 20.00), 0.001);
		}

		TEST_METHOD(ApplyDiscount_DiscountExceedsCap_AppliesMaxDiscount)
		{
			// This tests that the function correctly applies the max discount when the calculated discount exceeds it
			Assert::AreEqual(85.00, applyDiscount(100.00, 0.30, 15.00), 0.001);
		}

		TEST_METHOD(ApplyDiscount_DiscountEqualsMax_ReturnsDiscountedPrice)
		{
			// Exactly at the cap: 100.00 * 10% = 10.00 = maxDiscount
			Assert::AreEqual(90.00, applyDiscount(100.00, 0.10, 10.00), 0.001);
		}

		//Edge Cases

		TEST_METHOD(ApplyDiscount_ZeroDiscountRate_ReturnsSamePrice)
		{
			// Even if max discount is 50, 0% means no discount applied
			Assert::AreEqual(100.00, applyDiscount(100.00, 0.00, 50.00), 0.001);
		}

		TEST_METHOD(ApplyDiscount_ZeroMaxDiscount_ReturnsSamePrice)
		{
			// Even if discount rate is 50%, max discount of 0 means no discount applied
			Assert::AreEqual(100.00, applyDiscount(100.00, 0.50, 0.00), 0.001);
		}

		TEST_METHOD(ApplyDiscount_ZeroTotalPrice_ReturnsZero)
		{
			Assert::AreEqual(0.00, applyDiscount(0.00, 0.10, 20.00), 0.001);
		}

		//Invalid Input Cases

		TEST_METHOD(ApplyDiscount_NegativeTotalPrice_ReturnsInvalid)
		{
			Assert::AreEqual((double)INVALID_VALUE, applyDiscount(-50.00, 0.10, 20.00), 0.001);
		}

		TEST_METHOD(ApplyDiscount_NegativeDiscountRate_ReturnsInvalid)
		{
			Assert::AreEqual((double)INVALID_VALUE, applyDiscount(100.00, -0.10, 20.00), 0.001);
		}

		TEST_METHOD(ApplyDiscount_NegativeMaxDiscount_ReturnsInvalid)
		{
			Assert::AreEqual((double)INVALID_VALUE, applyDiscount(100.00, 0.10, -5.00), 0.001);
		}
	};
}