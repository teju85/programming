//
// Challenge name: Color Code Converter
// Difficulty    : moderate
// Link          : https://www.codeeval.com/open_challenges/148/
// Compile       : g++ -Wall -g -lm -o ColorCodeConverter ColorCodeConverter.cpp
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#define uint unsigned int

void printRgb(uint r, uint g, uint b) {
    printf("RGB(%u,%u,%u)\n", r, g, b);
}

bool hex2rgb(FILE* fp) {
    uint data;
    if(fscanf(fp, "#%x", &data) != 1) {
        return false;
    }
    uint b = data & 0xff;
    data >>= 8;
    uint g = data & 0xff;
    data >>= 8;
    uint r = data & 0xff;
    data >>= 8;
    printRgb(r, g, b);
    return true;
}

float modulo(float in, int mod) {
    int div = (int) (in / mod);
    float out = (in - (mod * div));
    return out;
}

void hsl2rgb(uint h, float s, float l) {
    float c = s * (1 - fabs((2*l)-1));
    float tmp = modulo(h / 60.0f, 2);
    float x = c * (1 - fabs(tmp - 1));
    float m = l - (c / 2);
    float r, g, b;
    r = g = b = m;
    if(h < 60) {
        r += c;
        g += x;
        b += 0;
    }
    else if(h < 120) {
        r += x;
        g += c;
        b += 0;
    }
    else if(h < 180) {
        r += 0;
        g += c;
        b += x;
    }
    else if(h < 240) {
        r += 0;
        g += x;
        b += c;
    }
    else if(h < 300) {
        r += x;
        g += 0;
        b += c;
    }
    else {
        r += c;
        g += 0;
        b += x;
    }
    printRgb(round(r*255), round(g*255), round(b*255));
}

void hsv2rgb(uint h, float s, float v) {
    float c = v * s;
    float tmp = modulo(h / 60.0f, 2);
    float x = c * (1 - fabs(tmp - 1));
    float m = v - c;
    float r, g, b;
    r = g = b = m;
    if(h < 60) {
        r += c;
        g += x;
        b += 0;
    }
    else if(h < 120) {
        r += x;
        g += c;
        b += 0;
    }
    else if(h < 180) {
        r += 0;
        g += c;
        b += x;
    }
    else if(h < 240) {
        r += 0;
        g += x;
        b += c;
    }
    else if(h < 300) {
        r += x;
        g += 0;
        b += c;
    }
    else {
        r += c;
        g += 0;
        b += x;
    }
    printRgb(round(r*255), round(g*255), round(b*255));
}

bool hslv2rgb(FILE* fp) {
    char type[4];
    uint h, s, lv;
    if(fscanf(fp, "%[^(](%d,%d,%d)", type, &h, &s, &lv) != 4) {
        return false;
    }
    if(strcmp(type, "HSV") == 0) {
        hsv2rgb(h, s/100.0f, lv/100.0f);
        return true;
    }
    if(strcmp(type, "HSL") == 0) {
        hsl2rgb(h, s/100.0f, lv/100.0f);
        return true;
    }
    return false;
}

bool cmyk2rgb(FILE* fp) {
    float c, m, y, k;
    if(fscanf(fp, "(%f,%f,%f,%f)", &c, &m, &y, &k) != 4) {
        return false;
    }
    float k1 = 1 - k;
    printRgb(round(255*(1-c)*k1),
             round(255*(1-m)*k1),
             round(255*(1-y)*k1));
    return true;
}

int main(int argc, char** argv) {
    FILE* fp;
    if(argc != 2) {
        printf("USAGE: ColorCodeConverter <fileContainingTestVectors>\n");
        return 1;
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Failed to open the input file '%s' for reading!\n", argv[1]);
        return 2;
    }
    while(!feof(fp)) {
        if(hex2rgb(fp)) {
            fscanf(fp, "\n");
            continue;
        }
        if(hslv2rgb(fp)) {
            fscanf(fp, "\n");
            continue;
        }
        if(cmyk2rgb(fp)) {
            fscanf(fp, "\n");
            continue;
        }
    }
    fclose(fp);
    return 0;
}
