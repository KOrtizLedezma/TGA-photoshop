//
// Created by kenet on 10/14/2023.
//

#ifndef LAB2MILESTONE1_IMAGE_H
#define LAB2MILESTONE1_IMAGE_H

#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char imageType;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short imageWidth;
    short imageHeight;
    char pixelDepth;
    char imageDescriptor;
};

struct Pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

class Image {
private:
    string name;
    ifstream stream;

public:
    Header head{};
    vector<Pixel> pixels;

    Image();
    void read(const string& inName);
    void write(const string& outName);
    unsigned char recoverValue(float value);
    float NormalizeValue(float value);
    void multiply(const Image &P1);
    void screen(const Image &P1);
    void subtract(const Image &P1);
    void addition(const Image &P1);
    void overlay(const Image &P1);
    void addBlue(int valueBlue);
    void addGreen(int valueGreen);
    void addRed(int valueRed);
    void scaleBlue(int valueBlue);
    void scaleGreen(int valueGreen);
    void scaleRed(int valueRed);
    void onlyBlue();
    void onlyGreen();
    void onlyRed();
    void combine(const Image &Green, const Image &Red);
    void invertVector(vector<Pixel> &vec);
    void flip();
};


#endif //LAB2MILESTONE1_IMAGE_H
