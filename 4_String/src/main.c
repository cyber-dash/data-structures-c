#include <stdio.h>
#include <stdlib.h>

#include "cyberdash_string.h"

#include "test.h"

int main()
{
	test_StringCopy();

	test_StringCompare();

	test_StringConCat();

	test_SubString();

	test_Insert();

	test_Index();
}
