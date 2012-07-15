#import <stdlib.h>
#import <stdio.h>
#import "re2tags.hpp"

#include <string>
#include <fstream>
#include <streambuf>


int main(int argc, char *argv[]) {
    
    std::ifstream t("/Users/alexgordon/Downloads/Python-3.2.3/Lib/test/test_class.py");//("/Users/alexgordon/Temporary/re2tags/dependencies/jsoncpp-src-0.5.0/makerelease.py");
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
//    std::string str = "\n\n\n\n\n\n\n\n\n\n\r\n\r\n\n\r";
    std::vector<rtt::Tag> tags =
    rtt::tagsForFile("/Users/alexgordon/Temporary/re2tags/defs/compiled.json", "foo.py", str);//"class Foo\n\tdef bar():\n\t\tpass\n\n");
    
    for (rtt::Tag tag : tags) {
        printf("Found [%s] %s%s\n", tag.kind.c_str(), tag.parents.c_str(), tag.name.c_str());
    }
    
    return 0;
}
