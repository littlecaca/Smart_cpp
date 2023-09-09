#include <iostream>
#include <algorithm>
#include <memory>

class Str {
    char *elements;
    char *first_free;
    char *cap;
    std::allocator<char> alloc;
    std::pair<char *, char *> alloc_n(size_t n);
    std::pair<char *, char *> alloc_n_copy(const char *b, const char *e);
    void chk_n_copy();
    void reallocate();
    void reallocate(size_t new_cap);
    void free();

  public:
    // Default constructor
    Str() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    // Copy constructor
    Str(const Str &);
    Str(const char *cp);
    Str &operator=(const Str &);
    ~Str() { free(); }

    char *begin() const { return elements; }
    char *end() const { return first_free; }
    size_t capacity() const { return cap - elements; }
    size_t size() const { return first_free - elements; }
    void reserve(size_t);
    void push_back(char c);
    void resize(size_t new_size);
};

std::pair<char *, char *> Str::alloc_n(size_t n) {
    auto cp = alloc.allocate(n);
    return {cp, cp + n};
}

std::pair<char *, char *> Str::alloc_n_copy(const char *b, const char *e) {
    auto cp = alloc.allocate(e - b);
    return {cp, std::uninitialized_copy(b, e, cp)};
}

inline
void Str::free() {
    if (elements)
        alloc.deallocate(elements, capacity());
}

Str::Str(const Str &s) {
    #ifndef NODEBUG
    std::cout << "Copy constructor is called" << std::endl;
    #endif
    auto pc = alloc_n_copy(s.begin(), s.end());
    elements = pc.first;
    first_free = cap = pc.second;
} 

Str::Str(const char *cp) {
    auto end = cp;
    while (*end != 0)
        ++end;
    auto pc = alloc_n_copy(cp, end);
    elements = pc.first;
    first_free = cap = pc.second;
}


Str &Str::operator=(const Str &s) {
    #ifndef NODEBUG
    std::cout << "Copy assignment operator is called" << std::endl;
    #endif
    auto pc = alloc_n_copy(s.begin(), s.end());
    free();
    elements = pc.first;
    first_free = cap = pc.second;
    return *this;
}

inline 
void Str::chk_n_copy() {
    if (first_free == cap)
        reallocate();
}

inline
void Str::reallocate() {
    reallocate(size() ? size() * 2 : 1);
}

void Str::reallocate(size_t new_cap) {
    auto pc = alloc_n(new_cap);
    auto dest = pc.first;
    for (auto elem = elements; elem != first_free; ++elem)
        alloc.construct(dest++, std::move(*elem));
    free();
    elements = pc.first;
    first_free = dest;
    cap = pc.second;
}

void Str::reserve(size_t new_cap) {
    if (elements) {
        if (new_cap < capacity())
            resize(new_cap);
        reallocate(new_cap);
    }
    else {
        auto pc = alloc_n(new_cap);
        elements = pc.first;
        first_free = cap = pc.second;
    }
}

void Str::push_back(char c) {
    chk_n_copy();
    alloc.construct(first_free++, c);
}

void Str::resize(size_t new_size) {
    auto num = new_size - size();
    if (num > 0)
        for (size_t i = 0; i != num; ++i)
            push_back(char());
    else
        // num is negative
        first_free += num;
}

int main(int argc, char const *argv[])
{
    std::vector<Str> vs;
    vs.push_back("you");
    vs.push_back("are");
    // vs.push_back("the");
    
    return 0;
}
