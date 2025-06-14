#pragma once
#include <string>
#include <chrono>

using namespace std;

class Product
{
private:

	int idProduct;
	wstring nameProduct;
	wstring purchasePrice;
	wstring sellingPrice;
	wstring article;
	wstring quantityOfProduct;
	wstring dateOfReceipt;
	int counterpartyId;
	int typeOfProduct;

public:
	Product(int idProduct, wstring nameProduct, wstring purchasePrice, wstring sellingPrice, wstring article, wstring quantityOfProduct, wstring dateOfReceipt, int counterpartyId, int typeOfProduct);


	int getIdProduct() const;
	wstring getNameProduct() const;
	wstring getPurchasePrice() const;
	wstring getSellingPrice() const;
	wstring getArticle() const;
	wstring getQuantityOfProduct() const;
	wstring getDateOfReceipt() const;
	int getCounterpartyId() const;
	int getTypeOfProduct() const;
};

