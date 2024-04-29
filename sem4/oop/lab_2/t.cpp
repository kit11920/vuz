#include<cstdio>

int main() {
    char s[10];
    std::snprintf(s, 10, "%s\n", NULL);
    std::printf("%s", s);
    return 0;
}