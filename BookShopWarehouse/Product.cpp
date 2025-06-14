#include "Product.h"

using namespace std;

Product::Product(int idProduct, wstring nameProduct, wstring purchasePrice, wstring sellingPrice, wstring article, wstring quantityOfProduct, wstring dateOfReceipt, int counterpartyId, int typeOfProduct)
	: idProduct(idProduct), nameProduct(nameProduct), purchasePrice(purchasePrice), sellingPrice(sellingPrice), article(article), quantityOfProduct(quantityOfProduct), dateOfReceipt(dateOfReceipt), counterpartyId(counterpartyId), typeOfProduct(typeOfProduct){}

int Product::getIdProduct() const { return idProduct; }
wstring Product::getNameProduct() const { return nameProduct; }
wstring Product::getPurchasePrice() const { return purchasePrice; }
wstring Product::getSellingPrice() const { return sellingPrice; }
wstring Product::getArticle() const { return article; }
wstring Product::getQuantityOfProduct() const { return quantityOfProduct; }
wstring Product::getDateOfReceipt() const { return dateOfReceipt; }
int Product::getCounterpartyId() const { return counterpartyId; }
int Product::getTypeOfProduct() const { return typeOfProduct; }
