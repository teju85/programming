//
// Challenge name: URI Comparison
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/80/
// Compile       : g++ -Wall -g -o UriComparison UriComparison.cpp
//

#include <stdio.h>
#include <string>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 1024
using namespace std;


int find(const char* str, int start, int len, char c) {
    for(;start<len;start++) {
        if(str[start] == c) {
            return start;
        }
    }
    return start;
}

void toUpperStr(string& str) {
    size_t s = str.size();
    if(s <= 0) {
        return;
    }
    for(size_t i=0;i<s;++i) {
        str[i] = (char)toupper((int)str[i]);
    }
}

struct Uri {
    string scheme;
    string username;
    string password;
    string host;
    string port;
    string path;

    Uri(const char* str, int len) {
        int i = getScheme(str, len);
        i += 3;  // ftp://....
        int p = find(str, i, len, '/');
        path.assign(str+p, len-p);
        getHostname(str, i, p);
        if(port == "") {
            port = "80";
        }
        postProcess();
        //printf("Scheme   = %s\n", scheme.c_str());
        //printf("user     = %s\n", username.c_str());
        //printf("password = %s\n", password.c_str());
        //printf("host     = %s\n", host.c_str());
        //printf("port     = %s\n", port.c_str());
        //printf("path     = %s\n", path.c_str());
    }
    string construct() const {
        string out(scheme);
        out += "://";
        if((username != "") && (password != "")) {
            out += username;
            out += ":";
            out += password;
            out += "@";
        }
        out += host;
        out += ":";
        out += port;
        out += path;
        return out;
    }

private:
    int getScheme(const char* str, int len) {
        int i;
        for(i=0;i<len;++i) {
            if(str[i] == ':') {
                break;
            }
            scheme += str[i];
        }
        return i;
    }
    void getHostname(const char* str, int s, int e) {
        int at = find(str, s, e, '@');
        if(at < e) {
            --at;
            int colon = find(str, s, at, ':');
            if(colon != at) {
                password.assign(str+colon+1, at-colon);
            }
            username.assign(str+s, colon-s);
            s = at + 2;
        }
        int colon = find(str, s, e, ':');
        if(colon < e) {
            port.assign(str+colon+1, e-colon-1);
        }
        int len = colon - s;
        if(str[colon] == '\0') {
            --len;
        }
        host.assign(str+s, len);
    }
    void postProcess() {
        toUpperStr(scheme);
        toUpperStr(host);
        string temp;
        size_t s = path.size();
        char prev = '\0';
        for(size_t i=0;i<s;++i) {
            if((path[i] == prev) && (prev == '/')) {
                continue;
            }
            if((path[i] == '%') && isHexDigit(path[i+1]) && isHexDigit(path[i+2])) {
                char t = uriDecode(path[i+1], path[i+2]);
                temp += t;
                i += 2;
                prev = t;
                continue;
            }
            temp += path[i];
            prev = path[i];
        }
        path = temp;
    }
    char uriDecode(char c1, char c2) const {
        c1 = (char)tolower((int)c1);
        c2 = (char)tolower((int)c2);
        c1 = charToHex(c1);
        c2 = charToHex(c2);
        c1 <<= 4;
        return (c1 + c2);
    }
    char charToHex(char c) const {
        if((c >= '0') && (c <= '9')) {
            return (c - '0');
        }
        if((c >= 'a') && (c <= 'f')) {
            return (c - 'a' + 10);
        }
        return c;
    }
    bool isHexDigit(char c) const {
        if((c >= '0') && (c <= '9')) {
            return true;
        }
        if(((c >= 'a') && (c <= 'f'))  ||  ((c >= 'A') && (c <= 'F'))) {
            return true;
        }
        return false;
    }
};

int stringLen(char* str, int max) {
    int i;
    for(i=0;i<max;i++) {
        if((str[i] == '\n') || (str[i] == '\r') || (str[i] == '\0')) {
            str[i] = '\0';
            return i;
        }
    }
    return max;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: UriComparison <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        char currentLine[MAX_LINE];
        currentLine[0] = '\0';
        fgets(currentLine, MAX_LINE, fp);
        int len = stringLen(currentLine, MAX_LINE);
        if(len <= 0) {
            continue;
        }
        int semi = find(currentLine, 0, len, ';');
        string s1 = Uri(currentLine, semi).construct();
        string s2 = Uri(currentLine+semi+1, len-semi).construct();
        printf("%s\n", (strcmp(s1.c_str(), s2.c_str()) == 0)? "True" : "False");
    }
    fclose(fp);
    return 0;
}
