#pragma once
#include <vector>
#include <string>

struct QueryDescriptor{
	std::vector<std::wstring> headers;
	std::wstring sqlQuery;
	std::wstring name;

};

extern const std::vector<QueryDescriptor> Queries;

