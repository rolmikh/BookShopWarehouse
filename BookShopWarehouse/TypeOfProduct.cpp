#include "TypeOfProduct.h"

using namespace std;

TypeOfProduct::TypeOfProduct(int idTypeOfProduct, wstring nameTypeOfProduct)
	: idTypeOfProduct(idTypeOfProduct), nameTypeOfProduct(nameTypeOfProduct){}


int TypeOfProduct::getIdTypeOfProduct() const { return idTypeOfProduct; }
wstring TypeOfProduct::getNameTypeOfProduct() const { return nameTypeOfProduct; }
