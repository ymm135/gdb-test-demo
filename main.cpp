#include <iostream>  

struct address_range {
    enum type {
        CONTENTS,     // may have contents
        NO_CONTENTS,  // must be uninitialized
        IGNORE        // will be ignored
    };
    type type;
};

int main(int argc,char *argv[])  
{  
    std::cout << "hello, world" << std::endl;  
    return(0);  
}  