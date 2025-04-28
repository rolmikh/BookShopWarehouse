#include "Product.h"

using namespace std;

Product::Product(int idProduct, wstring nameProduct, float purchasePrice, float sellingPrice, wstring article, int quantityOfProduct, chrono::system_clock::time_point dateOfReceipt, int counterpartyId, int typeOfProduct)
	: idProduct(idProduct), nameProduct(nameProduct), purchasePrice(purchasePrice), sellingPrice(sellingPrice), article(article), quantityOfProduct(quantityOfProduct), dateOfReceipt(dateOfReceipt), counterpartyId(counterpartyId), typeOfProduct(typeOfProduct){}
