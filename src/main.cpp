#include <ostream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "Image.h"
using namespace std;

//Address
string car =  "input/car.tga";
string circles =  "input/circles.tga";
string layer1 =  "input/layer1.tga";
string layer2 =  "input/layer2.tga";
string layer_blue =  "input/layer_blue.tga";
string layer_green =  "input/layer_green.tga";
string layer_red =  "input/layer_red.tga";
string pattern1 =  "input/pattern1.tga";
string pattern2 =  "input/pattern2.tga";
string text =  "input/text.tga";
string text2 =  "input/text2.tga";


void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();
void makeTask();
void printHelpMessage();
bool isValidTgaFile(const string& filename);
bool fileExists(const string& filename);
void flip(string& filename, string& output);
void onlyred(string& filename, string& output);
void onlygreen(string& filename, string& output);
void onlyblue(string& filename, string& output);
void combine(string& filename1, string& filename2, string& filename3, string& output);
void scaleblue(string& filename, string& output, int& value);
void scalegreen(string& filename, string& output, int& value);
void scalered(string& filename, string& output, int& value);
void addblue(string& filename, string& output, int& value);
void addgreen(string& filename, string& output, int& value);
void addred(string& filename, string& output, int& value);
void overlay(string& filename1, string& filename2, string& output);
void addition(string& filename1, string& filename2, string& output);
void subtract(string& filename1, string& filename2, string& output);
void screen(string& filename1, string& filename2, string& output);
void multiply(string& filename1, string& filename2, string& output);

int main(int argc, char* argv[]) {

    if (argc <= 1 || strcmp(argv[1], "--help") == 0) {
        printHelpMessage();
    }
    else{
        //check if output is a .tga file
        string outputFileName = argv[1];
        if (!isValidTgaFile(outputFileName)) {
            cout << "Invalid file name." << endl;
            return 0;
        }
        //check if first image exist and check name
        string firstImageFileName = argv[2];
        if (!isValidTgaFile(firstImageFileName)) {
            cout << "Invalid file name." << endl;
            return 0;
        }
        if (!fileExists(firstImageFileName)){
            cout << "File does not exist." << endl;
            return 0;
        }
        //check if method exist
        vector<string> methods{"multiply", "screen", "subtract", "addition", "overlay", "addblue", "addgreen", "addred",
                               "scaleblue", "scalegreen", "scalered", "combine", "onlyblue", "onlygreen", "onlyred", "flip"};

        string method = argv[3];
        bool found = false;
        for (string& current : methods) {
            if (current == method) {
                found = true;
                break;
            }
        }
        if (!found){
            cout << "Invalid method name." << endl;
            return 0;
        }

        //Multiply
        if (method == "multiply" && argc == 5){
            string secondImageFileName = argv[4];
            if (!isValidTgaFile(secondImageFileName)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(secondImageFileName)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            multiply(firstImageFileName, secondImageFileName, outputFileName);
        }
        //Screen
        else if(method == "screen" && argc >= 5){
            string secondImageFileName = argv[4];
            if (!isValidTgaFile(secondImageFileName)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(secondImageFileName)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            screen(firstImageFileName, secondImageFileName, outputFileName);
        }
        //Subtract
        else if(method == "subtract" && argc >= 5){
            string secondImageFileName = argv[4];
            if (!isValidTgaFile(secondImageFileName)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(secondImageFileName)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            subtract(firstImageFileName, secondImageFileName, outputFileName);
        }
        //Addition
        else if(method == "addition" && argc >= 5){
            string secondImageFileName = argv[4];
            if (!isValidTgaFile(secondImageFileName)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(secondImageFileName)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            addition(firstImageFileName, secondImageFileName, outputFileName);
        }
        //Overlay
        else if(method == "overlay" && argc >= 5){
            string secondImageFileName = argv[4];
            if (!isValidTgaFile(secondImageFileName)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(secondImageFileName)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            overlay(firstImageFileName, secondImageFileName, outputFileName);
        }
        //Add Blue
        else if(method == "addblue" && argc >= 5){
            char* value = argv[4];
            try {
                int valueInt = stoi(value);
                addblue(firstImageFileName, outputFileName, valueInt);
            } catch (const std::invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
            }
        }
        //Add Green
        else if(method == "addgreen" && argc >= 5){
            char* value = argv[4];
            try {
                int valueInt = stoi(value);
                addgreen(firstImageFileName, outputFileName, valueInt);
            } catch (const std::invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
            }
        }
        //Add Red
        else if(method == "addred" && argc >= 5){
            char* value = argv[4];
            try {
                int valueInt = stoi(value);
                addred(firstImageFileName, outputFileName, valueInt);
            } catch (const std::invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
            }
        }
        //Scale Blue
        else if(method == "scaleblue" && argc >= 5){
            char* value = argv[4];
            try {
                int valueInt = stoi(value);
                scaleblue(firstImageFileName, outputFileName, valueInt);
            } catch (const std::invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
            }
        }
        //Scale Green
        else if(method == "scalegreen" && argc >= 5){
            char* value = argv[4];
            try {
                int valueInt = stoi(value);
                scalegreen(firstImageFileName, outputFileName, valueInt);
            } catch (const std::invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
            }
        }
        //Scale Red
        else if(method == "scalered" && argc >= 5){
            char* value = argv[4];
            try {
                int valueInt = stoi(value);
                scalered(firstImageFileName, outputFileName, valueInt);
            } catch (const std::invalid_argument& e) {
                cout << "Invalid argument, expected number." << endl;
            }
        }
        //Combine
        else if(method == "combine" && argc >= 6){
            string greenChannel = argv[4];
            if (!isValidTgaFile(greenChannel)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(greenChannel)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            string blueChannel = argv[5];
            if (!isValidTgaFile(blueChannel)) {
                cout << "Invalid argument, invalid file name." << endl;
                return 1;
            }
            if (!fileExists(blueChannel)) {
                cout << "Invalid argument, file does not exist." << endl;
                return 1;
            }
            combine(firstImageFileName, blueChannel, greenChannel, outputFileName);
        }
        //Only Blue
        else if(method == "onlyblue" && argc >= 4){
            onlyblue(firstImageFileName, outputFileName);
        }
        //Only Green
        else if(method == "onlygreen" && argc >= 4){
            onlygreen(firstImageFileName, outputFileName);
        }
        //Only Red
        else if(method == "onlyred" && argc >= 4){
            onlyred(firstImageFileName, outputFileName);
        }
        //Flip
        else if(method == "flip" && argc >= 4){
            flip(firstImageFileName, outputFileName);
        }

        else{
            cout << "Missing argument." << endl;
        }
    }
}

void multiply(string& filename1, string& filename2, string& output){
    Image firstImage, secondImage;
    firstImage.read(filename1);
    secondImage.read(filename2);
    firstImage.multiply(secondImage);
    firstImage.write(output);
}

void screen(string& filename1, string& filename2, string& output){
    Image firstImage, secondImage;
    firstImage.read(filename2);
    secondImage.read(filename1);
    firstImage.screen(secondImage);
    firstImage.write(output);
}

void subtract(string& filename1, string& filename2, string& output){
    Image firstImage, secondImage;
    firstImage.read(filename2);
    secondImage.read(filename1);
    firstImage.subtract(secondImage);
    firstImage.write(output);
}

void addition(string& filename1, string& filename2, string& output){
    Image firstImage, secondImage;
    firstImage.read(filename1);
    secondImage.read(filename2);
    firstImage.addition(secondImage);
    firstImage.write(output);
}

void overlay(string& filename1, string& filename2, string& output){
    Image firstImage, secondImage;
    firstImage.read(filename1);
    secondImage.read(filename2);
    firstImage.overlay(secondImage);
    firstImage.write(output);
}

void addblue(string& filename, string& output, int& value){
    Image firstImage;
    firstImage.read(filename);
    firstImage.addBlue(value);
    firstImage.write(output);
}

void addgreen(string& filename, string& output, int& value){
    Image firstImage;
    firstImage.read(filename);
    firstImage.addGreen(value);
    firstImage.write(output);
}

void addred(string& filename, string& output, int& value){
    Image firstImage;
    firstImage.read(filename);
    firstImage.addRed(value);
    firstImage.write(output);
}

void scaleblue(string& filename, string& output, int& value){
    Image firstImage;
    firstImage.read(filename);
    firstImage.scaleBlue(value);
    firstImage.write(output);
}

void scalegreen(string& filename, string& output, int& value){
    Image firstImage;
    firstImage.read(filename);
    firstImage.scaleGreen(value);
    firstImage.write(output);
}

void scalered(string& filename, string& output, int& value){
    Image firstImage;
    firstImage.read(filename);
    firstImage.scaleRed(value);
    firstImage.write(output);
}

void combine(string& filename1, string& filename2, string& filename3, string& output){
    Image blue, green, red;
    blue.read(filename2);
    green.read(filename3);
    red.read(filename1);
    blue.combine(green,red);
    blue.write(output);
}

void onlyblue(string& filename, string& output){
    Image firstImage;
    firstImage.read(filename);
    firstImage.onlyBlue();
    firstImage.write(output);
}

void onlygreen(string& filename, string& output){
    Image firstImage;
    firstImage.read(filename);
    firstImage.onlyGreen();
    firstImage.write(output);
}

void onlyred(string& filename, string& output){
    Image firstImage;
    firstImage.read(filename);
    firstImage.onlyRed();
    firstImage.write(output);
}

void flip(string& filename, string& output){
    Image firstImage;
    firstImage.read(filename);
    firstImage.flip();
    firstImage.write(output);
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool isValidTgaFile(const string& filename) {
    return filename.size() >= 4 && filename.substr(filename.size() - 4) == ".tga";
}

void printHelpMessage(){
    cout << "Project 2: Image Processing, Fall 2023" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}

void makeTasks(){
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
    task10();
}

void task10() {
    Image toFlip;
    toFlip.read(text2);
    toFlip.flip();
    toFlip.write("output/part10.tga");
}

void task9() {
    Image p1, p2, p3;
    p1.read(layer_blue);
    p2.read(layer_green);
    p3.read(layer_red);
    p1.combine(p2,p3);
    p1.write("output/part9.tga");
}

void task8() {
    Image partB, partG, partR;
    partB.read(car);
    partG.read(car);
    partR.read(car);
    partB.onlyBlue();
    partG.onlyGreen();
    partR.onlyRed();
    partB.write("output/part8_b.tga");
    partG.write("output/part8_g.tga");
    partR.write("output/part8_r.tga");
}

void task7() {
    Image top;
    top.read(car);
    top.scaleRed(4);
    top.scaleBlue(0);
    top.write("output/part7.tga");
}

void task6() {
    Image top;
    top.read(car);
    top.addGreen(200);
    top.write("output/part6.tga");
}

void task5() {
    Image top, bottom;
    top.read(layer1);
    bottom.read(pattern1);
    top.overlay(bottom);
    top.write("output/part5.tga");
}

void task4() {
    Image top, bottom, aux1;
    top.read(layer2);
    bottom.read(circles);
    aux1.read(pattern2);
    top.multiply(bottom);
    top.subtract(aux1);
    top.write("output/part4.tga");
}

void task3() {
    Image top, bottom, aux1;
    top.read(layer1);
    bottom.read(pattern2);
    aux1.read(text);
    top.multiply(bottom);
    aux1.screen(top);
    aux1.write("output/part3.tga");
}

void task2() {
    Image top, bottom;
    top.read(car);
    bottom.read(layer2);
    top.subtract(bottom);
    top.write("output/part2.tga");
}

void task1() {
    Image top, bottom;
    top.read(layer1);
    bottom.read(pattern1);
    top.multiply(bottom);
    top.write("output/part1.tga");
}

