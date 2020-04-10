#include "graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
using namespace genv;

#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED
class Widget
{
protected:
    int x;
    int y;
    int w;
    int h;
    int max_h;
    int mouseX;
    int mouseY;
    bool opened;
    bool kijelolt;
public:
    Widget(int x, int y, int w, int h);
    virtual bool is_selected(int pos_x, int pos_y);
    virtual void show() = 0;
    virtual void write(char s) = 0;
    virtual void changeNUM(int x) = 0;
    virtual void drag(int x, int y) = 0;
    virtual void boundaries(int maxW, int maxH) = 0;
    virtual void deleteDigit() = 0;
    virtual void operation(int pos_x, int pos_y) = 0;
    virtual void setMouse(int pos_x, int pos_y) = 0;
    virtual void setVersus(int x) = 0;
    virtual string writeData() = 0;
};
#endif // WIDGET_HPP_INCLUDED

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

class Number : public Widget
{
private:
    int mini;
    int maxi;
    int NUM;
public:
    Number(int x,int y,int w,int h,int mini,int maxi);
    void show() override;
    void write(char s) override;
    void changeNUM(int x) override;
    void drag(int x, int y) override;
    void boundaries(int maxW, int maxH) override;
    void deleteDigit() override;
    void operation(int pos_x, int pos_y) override;
    void setMouse(int pos_x, int pos_y) override;
    void setVersus(int x) override;
    string writeData() override;
};
#endif // NUMBER_HPP_INCLUDED

#ifndef DROPDOWN_HPP_INCLUDED
#define DROPDOWN_HPP_INCLUDED

class DropDown : public Widget
{
private:
    vector<string> items;
    string highlight_string;
    int rollCount;
public:
    DropDown(int x,int y,int min_w,int min_h,int max_h, vector<string> items);
    void show() override;
    void write(char s) override;
    void changeNUM(int x) override;
    void drag(int x, int y) override;
    void boundaries(int maxW, int maxH) override;
    void deleteDigit() override;
    void operation(int pos_x, int pos_y) override;
    void setMouse(int pos_x, int pos_y) override;
    void setVersus(int x) override;
    string writeData() override;
};

#endif // DROPDOWN_HPP_INCLUDED




