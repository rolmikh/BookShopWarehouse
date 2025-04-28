#pragma once
#include <string>
#include <chrono>

using namespace std;

class Product
{
private:

	int idProduct;
	wstring nameProduct;
	float purchasePrice;
	float sellingPrice;
	wstring article;
	int quantityOfProduct;
	chrono::system_clock::time_point dateOfReceipt;
	int counterpartyId;
	int typeOfProduct;

public:
	Product(int idProduct, wstring nameProduct, float purchasePrice, float sellingPrice, wstring article, int quantityOfProduct, chrono::system_clock::time_point dateOfReceipt, int counterpartyId, int typeOfProduct);

};

