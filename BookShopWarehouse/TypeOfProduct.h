#pragma once
#include <string>


class TypeOfProduct
{
private:
	int idTypeOfProduct;
	std::wstring nameTypeOfProduct;

public: 
	TypeOfProduct(int idTypeOfProduct, std::wstring nameTypeOfProduct);

	int getIdTypeOfProduct() const;
	std::wstring getNameTypeOfProduct() const;

};

