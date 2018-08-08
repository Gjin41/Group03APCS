#include "TrieLib.h"
#include <time.h>
//-------------------------------------------------------------
Trie T;
int main()
{
    clock_t t;
    t= clock();
    T.DocumentInsert();
    T.Print("was just when you",1*1000+1);
    t= clock()-t;
    return 0;
}
