#include <stdio.h>
#include <stdlib.h>

#include "cyberdash_string.h"

#include "test.h"

int main()
{
	test_StringCopy();

    TestStringCompare();

	test_StringConCat();

	test_SubString();

    TestStringInsert();

    TestStringSearch();
}
