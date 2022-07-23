#include <stdio.h>
#include <stdlib.h>

#include "cyberdash_string.h"

#include "test.h"

int main()
{
    TestStringCopy();

    TestStringCompare();

    TestStringConcat();

	TestStringSubStr();

    TestStringInsert();

    TestStringSearch();
}
