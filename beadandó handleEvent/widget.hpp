#include "graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>

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
    int mouseX; /// eg�r helye, a mozgat�s szempontj�b�l
    int mouseY;
    bool clicked; /// le van-e nyomva a bal-eg�r
    bool selected;
public:
    Widget(int x, int y, int w, int h);
    virtual void handleTimer(event ev) = 0;
    virtual bool handleSelection(event ev) = 0;
    virtual void handleMouse(event ev,int W, int H) = 0;
    virtual void handleKeys(event ev) = 0;
    virtual string handleOutput() = 0;
};
#endif // WIDGET_HPP_INCLUDED

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

class Number : public Widget
{
private:
    int mini;
    int maxi;
    int NUM; /// a t�rolt �rt�k, ezt �rja ki a f�jlba is
    int operated_NUM; /// az oper�lt �rt�k, amit l�tni lehet oper�l�s k�zben
    bool operated; /// oper�l�s alatt van-e Widget(z�ld, ha igen)
public:
    Number(int x,int y,int w,int h,int mini,int maxi);

    // OVERRIDE FUNCTIONS
    void handleTimer(event ev) override;
    bool handleSelection(event ev) override;
    void handleMouse(event ev,int W, int H) override;
    void handleKeys(event ev) override;
    string handleOutput() override;

    // LOCAL FUNCTIONS
    void show();
    bool is_selected(int pos_x, int pos_y);
    void setMouse(int pos_x, int pos_y);
    void drag(int pos_x, int pos_y);
    void boundaries(int W, int H);
    void setNUM(int x);
    void operation(int pos_x, int pos_y); /// plusz-m�nusz jel kezel�se
    void setSIGN(); /// neg�l�s
    void addNUMBER(char s); /// �j sz�mjegy hozz�ad�sa
    void deleteDigit(); /// utols� sz�mjegy elv�tele
    void checkNumber(); /// ez teszi egyenl�ve a NUM-ot az operation_NUM-mal, ha az intervallumba esik. Csak ennek teljes�l�sekor hiteles�tett az eredeti sz�m �t�r�sa
};
#endif // NUMBER_HPP_INCLUDED

#ifndef DROPDOWN_HPP_INCLUDED
#define DROPDOWN_HPP_INCLUDED

class DropDown : public Widget
{
private:
    vector<string> items;
    string highlight_string;
    int scroll_Count; ///h�nyszor g�rgetett le eddig a user
    int max_h;
    bool opened;
public:
    DropDown(int x,int y,int w,int h,int max_h, vector<string> items);

    // OVERRIDE FUNCTIONS
    void handleTimer(event ev) override;
    bool handleSelection(event ev) override;
    void handleMouse(event ev,int W, int H) override;
    void handleKeys(event ev) override;
    string handleOutput() override;

    // LOCAL FUNCTIONS
    void show();
    bool is_selected(int pos_x, int pos_y);
    void setMouse(int pos_x, int pos_y);
    void drag(int pos_x, int pos_y);
    void boundaries(int W, int H);
    void setTEXT(int pos_x, int pos_y); /// �j text kiv�laszt�sa
    void scroll(int s); /// g�rget�s megold�sa
};
#endif // DROPDOWN_HPP_INCLUDED




