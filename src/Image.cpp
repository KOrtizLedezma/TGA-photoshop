//
// Created by kenet on 10/14/2023.
//

#include "Image.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

Image::Image(){}

void Image::read(const string& inName) {

    stream.open(inName, ios::binary);

    stream.read(&head.idLength, sizeof(head.idLength));
    stream.read(&head.colorMapType, sizeof(head.colorMapType));
    stream.read(&head.imageType, sizeof(head.imageType));
    stream.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
    stream.read((char*)&head.colorMapLength, sizeof(head.colorMapLength));
    stream.read(&head.colorMapDepth, sizeof(head.colorMapDepth));
    stream.read((char*)&head.xOrigin, sizeof(head.xOrigin));
    stream.read((char*)&head.yOrigin, sizeof(head.yOrigin));
    stream.read((char*)&head.imageWidth, sizeof(head.imageWidth));
    stream.read((char*)&head.imageHeight, sizeof(head.imageHeight));
    stream.read(&head.pixelDepth, sizeof(head.pixelDepth));
    stream.read(&head.imageDescriptor, sizeof(head.imageDescriptor));

    int size = head.imageWidth * head.imageHeight;

    for (int i = 0 ; i < size ; i++){
        Pixel pix{};
        stream.read((char*)&pix.blue, sizeof(pix.blue));
        stream.read((char*)&pix.green, sizeof(pix.green));
        stream.read((char*)&pix.red, sizeof(pix.red));
        pixels.push_back(pix);
    }
}

void Image::write(const string& outName) {

    ofstream streamOut(outName, ios_base::binary);

    streamOut.write(&head.idLength, sizeof(head.idLength));
    streamOut.write(&head.colorMapType, sizeof(head.colorMapType));
    streamOut.write(&head.imageType, sizeof(head.imageType));
    streamOut.write((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
    streamOut.write((char*)&head.colorMapLength, sizeof(head.colorMapLength));
    streamOut.write(&head.colorMapDepth, sizeof(head.colorMapDepth));
    streamOut.write((char*)&head.xOrigin, sizeof(head.xOrigin));
    streamOut.write((char*)&head.yOrigin, sizeof(head.yOrigin));
    streamOut.write((char*)&head.imageWidth, sizeof(head.imageWidth));
    streamOut.write((char*)&head.imageHeight, sizeof(head.imageHeight));
    streamOut.write(&head.pixelDepth, sizeof(head.pixelDepth));
    streamOut.write(&head.imageDescriptor, sizeof(head.imageDescriptor));

    int size = head.imageWidth * head.imageHeight;

    for (int i = 0 ; i < size ; i++){
        Pixel pix = pixels[i];
        streamOut.write((char*)&pix.blue, sizeof(pix.blue));
        streamOut.write((char*)&pix.green, sizeof(pix.green));
        streamOut.write((char*)&pix.red, sizeof(pix.red));
    }
}

void Image::multiply(const Image& P1){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        pixels[i].blue = recoverValue(NormalizeValue(pixels[i].blue) * NormalizeValue(P1.pixels[i].blue));
        pixels[i].green = recoverValue(NormalizeValue(pixels[i].green) * NormalizeValue(P1.pixels[i].green));
        pixels[i].red = recoverValue(NormalizeValue(pixels[i].red) * NormalizeValue(P1.pixels[i].red));
    }
}

void Image::screen(const Image& P1){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        pixels[i].blue = recoverValue(1 - abs((1 - NormalizeValue(pixels[i].blue)) * (1 - NormalizeValue(P1.pixels[i].blue))));
        pixels[i].green = recoverValue(1 - abs((1 - NormalizeValue(pixels[i].green)) * (1 - NormalizeValue(P1.pixels[i].green))));
        pixels[i].red = recoverValue(1 - abs((1 - NormalizeValue(pixels[i].red)) * (1 - NormalizeValue(P1.pixels[i].red))));
    }
}

void Image::subtract(const Image& P1){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].blue - P1.pixels[i].blue < 0) pixels[i].blue = 0;
        else pixels[i].blue = pixels[i].blue - P1.pixels[i].blue;
        if(pixels[i].green - P1.pixels[i].green < 0)pixels[i].green = 0;
        else pixels[i].green = pixels[i].green - P1.pixels[i].green;
        if(pixels[i].red - P1.pixels[i].red < 0)pixels[i].red = 0;
        else pixels[i].red = pixels[i].red - P1.pixels[i].red;
    }

}

void Image::addition(const Image& P1){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].blue + P1.pixels[i].blue > 255) pixels[i].blue = 255;
        else pixels[i].blue = pixels[i].blue + P1.pixels[i].blue;
        if(pixels[i].green + P1.pixels[i].green > 255) pixels[i].green  = 255;
        else pixels[i].green = pixels[i].green + P1.pixels[i].green;
        if(pixels[i].red + P1.pixels[i].red > 255)pixels[i].red = 255;
        else pixels[i].red = pixels[i].red + P1.pixels[i].red;
    }
}

void Image::overlay(const Image& P1){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(NormalizeValue(P1.pixels[i].blue) <= 0.5){
            pixels[i].blue = recoverValue(((2 * NormalizeValue(pixels[i].blue) * NormalizeValue(P1.pixels[i].blue))));
        }
        else{
            pixels[i].blue = recoverValue((1 - abs(2 * (1 - NormalizeValue(pixels[i].blue)) * (1 - NormalizeValue(P1.pixels[i].blue)))));
        }
        if(NormalizeValue(P1.pixels[i].green) <= 0.5){
            pixels[i].green = recoverValue(((2 * NormalizeValue(pixels[i].green) * NormalizeValue(P1.pixels[i].green))));
        }
        else{
            pixels[i].green = recoverValue((1 - abs(2 * (1 - NormalizeValue(pixels[i].green)) * (1 - NormalizeValue(P1.pixels[i].green)))));
        }
        if(NormalizeValue(P1.pixels[i].red) <= 0.5){
            pixels[i].red = recoverValue(((2 * NormalizeValue(pixels[i].red) * NormalizeValue(P1.pixels[i].red))));
        }
        else{
            pixels[i].red = recoverValue((1 - abs(2 * (1 - NormalizeValue(pixels[i].red)) * (1 - NormalizeValue(P1.pixels[i].red)))));
        }
    }
}

void Image::addBlue(int valueBlue){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].blue + valueBlue  > 255) pixels[i].blue = 255;
        else pixels[i].blue = pixels[i].blue + valueBlue;
    }
}

void Image::addGreen(int valueGreen){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].green + valueGreen  > 255) pixels[i].green = 255;
        else pixels[i].green = pixels[i].green + valueGreen;
    }
}

void Image::addRed(int valueRed){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].red + valueRed  > 255) pixels[i].red = 255;
        else pixels[i].red = pixels[i].red + valueRed;
    }
}

void Image::scaleBlue(int valueBlue){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].blue * valueBlue  > 255)pixels[i].blue = 255;
        else pixels[i].blue = pixels[i].blue * valueBlue;
    }
}

void Image::scaleGreen(int valueGreen){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].green * valueGreen  > 255)pixels[i].green = 255;
        else pixels[i].green = pixels[i].green * valueGreen;
    }
}

void Image::scaleRed(int valueRed){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        if(pixels[i].red * valueRed  > 255)pixels[i].red = 255;
        else pixels[i].red = pixels[i].red * valueRed;
    }
}

void Image::onlyBlue(){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        pixels[i].blue = pixels[i].blue;
        pixels[i].green = pixels[i].blue;
        pixels[i].red = pixels[i].blue;
    }
}

void Image::onlyGreen(){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        pixels[i].blue = pixels[i].green;
        pixels[i].green = pixels[i].green;
        pixels[i].red = pixels[i].green;
    }
}

void Image::onlyRed(){
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        pixels[i].blue = pixels[i].red;
        pixels[i].green = pixels[i].red;
        pixels[i].red = pixels[i].red;
    }
}

void Image::combine(const Image& Green, const Image& Red) {
    int size = head.imageWidth * head.imageHeight;
    for(int i = 0 ; i < size ; i++){
        pixels[i].green = Green.pixels[i].green;
        pixels[i].red = Red.pixels[i].red;
    }
}

void Image::flip(){
    int size = head.imageWidth * head.imageHeight;
    vector<Pixel> rearranged = pixels;
    invertVector(rearranged);

    for(int i = 0; i < size ; i++){
        pixels[i].blue = rearranged[i].blue;
        pixels[i].green = rearranged[i].green;
        pixels[i].red = rearranged[i].red;
    }
}

void Image::invertVector(std::vector<Pixel>& vec) {
    reverse(vec.begin(), vec.end());
}

unsigned char Image::recoverValue(float value){
    return (unsigned char)((value*255)+0.5f);
}

float Image::NormalizeValue(float value){
    return value / 255;
}
