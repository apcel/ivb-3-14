#pragma warning(disable : 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>


struct __Token      
{ 
	int loc;
	int len;
};

static inline int
__getrandom(int min, int max);
static void
__do(char *buffer);
static void
__split(const char *str, struct __Token **tokens, int *nCount);
static char*
__RandomWords(const char *str, struct __Token *tokens, int nCount);


int
main(int argc, char **argv)
{
	
	static char *str[] = {
		"Today I go to the movies with my mom.",
		"Hello world."
	};
	
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int selectedId = __getrandom(0, sizeof(str) / sizeof(str[0]) - 1);	
	__do(str[selectedId]);
	
	return EXIT_SUCCESS;
}



void
__do(char *buffer)
{
	
	struct __Token *tokens = nullptr;
	int  nCount = 0;

	__split(buffer, &tokens, &nCount);
	auto result =__RandomWords(buffer, tokens, nCount);
	fprintf(stdout, "Selected: %s\n", buffer);
	fprintf(stdout, "Result  : %s\n", result);
	std::free(result);
	system("pause");
}


#define SKIPWS(In) \
		    while (*(In) != 0 && iswspace( (int)(*(In)) )) {    \
		        ++(In);                                         \
		        ++id;                                           \
            }

void
__split(const char *in, struct __Token **tokens, int *nCount)
{
	char *it = const_cast<char *>(in);  
	char *next = it;
	int id = 0;


	(*tokens) = nullptr;
	(*nCount) = 0;
	SKIPWS(it);
	while (*it != 0) {
		if (iswspace((int)(*it))) {
			int len = it - next;
			if ((*tokens) == nullptr) {
				(*tokens) = (struct __Token *)malloc(sizeof(struct __Token));
				(*nCount) = 1;
			} else {
				(*nCount) += 1;
				(*tokens) = (struct __Token *)realloc((*tokens), (*nCount) * sizeof(struct __Token));				
			}
			(*tokens)[(*nCount) - 1].len = len;
			(*tokens)[(*nCount) - 1].loc = id - len;
			SKIPWS(it);
			next = it;
		}
		++it;
		++id;
	}
	if (it != nullptr && next != nullptr) {
		int len = it - next;
		if ((*tokens) == nullptr) {
			(*tokens) = (struct __Token *)malloc(sizeof(struct __Token));
			(*nCount) = 1;
		}
		else {
			(*nCount) += 1;
			(*tokens) = (struct __Token *)realloc((*tokens), (*nCount) * sizeof(struct __Token));
		}
		(*tokens)[(*nCount) - 1].len = len;
		(*tokens)[(*nCount) - 1].loc = id - len;
	}
}

static inline int
__getrandom(int min, int max){
	return min = (std::rand() % (int)(max - min + 1));
}

char*
__RandomWords(const char *str, struct __Token *tokens, int nCount)
{
	int *pId = (int *)std::malloc(nCount * sizeof(int));
	char *newString = (char *)std::calloc(1, std::strlen(str) + 1);
	for (auto i = 0; i < nCount; ++i)
		pId[i] = i;
	for (auto i = 0; i < nCount; i++) {
		int id = __getrandom(0, nCount - 1);
		{
			auto temp = pId[id];
			pId[id] = pId[i];
			pId[i] = temp;
		}
	}
	int it = 0;
	for (auto i = 0; i < nCount; ++i) {
		if (i != 0) {
			std::strcat(newString, " ");
		}
		auto token = tokens[ pId[i] ];
		auto ptr = str + token.loc;
		std::strncpy(newString + it, ptr, token.len);		
		it += token.len + 1;
	}
	std::free(pId);
	return newString;
}
