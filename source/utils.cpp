#import "utils.hpp"

#define strtk_no_tr1_or_boost
#import "strtk.hpp"

template<typename T>
void fast_stack_malloc(const size_t n, void(^f)(T*)) {
// Clang crashes on std::function, so until then we use macros
//void fast_stack_malloc(const size_t n, std::function<void(T*)> f) {
    
    // 128 bytes is a reasonable amount to allocate on the stack
    const size_t bytes = sizeof(T) * n;
    if (bytes <= 128) {
        
        T* const p0 = alloca(bytes);
        T* const p = new (p0) T[n];
        
        f(p);
        
        for (size_t i = 0; i < n; i++) {
            p[i].~T();
        } 
    }
    else {
        // Too big! Put it on the heap
        T* const p = new T[n]; 
        f(p);
        delete[] p;
    }
}

#define fast_stack_malloc(T, n, b) do { \
const size_t bytes = sizeof(T) * n; \
if (bytes <= 128) { \
T* const p0 = alloca(bytes); \
T* const p = new (p0) T[n]; \
b \
for (size_t i = 0; i < n; i++) { p[i].~T(); } \
} \
else { \
T* const p = new T[n]; \
b \
delete[] p; \
} \
} while(0)


bool string_ends_with(std::string &haystack, std::string &needle) {
    if (haystack.length() < needle.length())
        return false;
    
    return 0 == haystack.compare(haystack.size() - needle.size(), needle.size(), needle);
}

std::string trim(std::string str) {
    strtk::remove_leading_trailing(" \t\n\r\f", str);
    return str;
}

void split_and_trim_into(std::string str, std::string delim, std::vector<std::string>& into) {
    
    std::deque<std::string> parts;
    strtk::split_options::type split_options = strtk::split_options::default_mode;
    
    strtk::split(strtk::multiple_char_delimiter_predicate(delim),
                 str,
                 strtk::range_to_type_back_inserter(parts),
                 split_options);
    
    for (std::string& neatlyTrimmedPart : parts) {
        strtk::remove_leading_trailing(" \t\n\r\f", neatlyTrimmedPart);
        
        if (neatlyTrimmedPart.size())
            into.push_back(neatlyTrimmedPart);
    }
    
//    into.push_back(str);
}