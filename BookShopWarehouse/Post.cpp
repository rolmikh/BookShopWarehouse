#include "Post.h"

using namespace std;

Post::Post(int idPost, wstring namePost)
	: idPost(idPost), namePost(namePost){}


int Post::getIdPost() const { return idPost; }
wstring Post::getNamePost() const { return namePost; }
