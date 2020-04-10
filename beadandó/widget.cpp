#include "widget.hpp"

Widget::Widget(int x_,int y_,int w_,int h_) : x(x_), y(y_), w(w_), h(h_)
{
    kijelolt = false;
    opened = false;
}
bool Widget::is_selected(int pos_x, int pos_y)
{
    if(opened)
    {
        if(pos_x>x && pos_x<x+w && pos_y>y && pos_y<y+max_h+h)
        {
            kijelolt = true;
            return true;
        }
        else
        {
            kijelolt = false;
            return false;
        }
    }
    else
    {
        if(pos_x>x && pos_x<x+w && pos_y>y && pos_y<y+h)
        {
            kijelolt = true;
            return true;
        }
        else
        {
            kijelolt = false;
            return false;
        }
    }

}

Number::Number(int x,int y,int w,int h,int mini,int maxi) : Widget(x,y,w,h)
{
    this->mini=mini;
    this->maxi=maxi;
    NUM = (mini+maxi)/2;
}
void Number::show()
{
    int part = w - h/2;
    int r,g,b;

    if(kijelolt)
    {
        r=255;
        g=0;
        b=0;
    }
    else
    {
        r=0;
        g=128;
        b=255;
    }

    // szines szele
    gout << color(r,g,b) << move_to(x-2,y-2) << box(w+4,h+4);
    // textbox
    gout << color(220,220,220) << move_to(x,y) << box(part-1,h);
    // pluszos
    gout << color(220,220,220) << move_to(x+part+1,y) << box(h/2,h/2-1);
    gout << color(r,g,b) << move_to(x+part+5, y+h*0.25 - 1) << box(h/2-8,2);
    gout << color(r,g,b) << move_to(x+part+h/4, y + 4) << box(2,h*0.5 - 8);

    // minuszos
    gout << color(220,220,220) << move_to(x+part+1,y+h/2 + 2) << box(h/2,h/2 - 2);
    gout << color(r,g,b) << move_to(x+part+5, y+h*0.75 + 1) << box(h/2-8,2);

    stringstream ss;
    ss << NUM;
    gout << color(0,0,0) << move_to(x+5,y+h/2+10) << text(ss.str());
}

void Number::write(char s)
{
    stringstream ss;
    ss << NUM << s;

    stringstream zz(ss.str());
    zz >> NUM;
    if(NUM > maxi)
    {
        NUM = maxi;
        ss.str("");
    }
    if(NUM < mini)
    {
        NUM = mini;
        ss.str("");
    }
}

void Number::changeNUM(int x)
{
    if(x>0 && NUM < maxi)
    {
        NUM+=x;
    }
    if(x<0 && NUM > mini)
    {
        NUM+=x;
    }
}

void Number::drag(int pos_x, int pos_y)
{
    x = pos_x - mouseX;
    y = pos_y - mouseY;
}

void Number::boundaries(int maxW, int maxH)
{
    if(x<2)
    {
        x=2;
    }
    if(y<2)
    {
        y=2;
    }
    if(x+w>maxW+3)
    {
        x= maxW - w - 3;
    }
    if(y+h>maxH+3)
    {
        y = maxH - h - 3;
    }
}

void Number::deleteDigit()
{
    NUM /= 10;
}

void Number::operation(int pos_x, int pos_y)
{
    int part = w - h/2;
    int r=255;
    int g=0;
    int b=0;
    if(pos_x>x+part && pos_x < x+w && pos_y>y && pos_y < y + h/2)
    {
        // pluszos
        gout << color(255,255,255) << move_to(x+part+1,y) << box(h/2,h/2-1);
        gout << color(r,g,b) << move_to(x+part+5, y+h*0.25 - 1) << box(h/2-8,2);
        gout << color(r,g,b) << move_to(x+part+h/4, y + 4) << box(2,h*0.5 - 8);
        changeNUM(1);
    }

    if(pos_x>x+part && pos_x < x+w && pos_y>y + h/2 && pos_y < y + h)
    {
        // minuszos
        gout << color(255,255,255) << move_to(x+part+1,y+h/2 + 2) << box(h/2,h/2 - 2);
        gout << color(r,g,b) << move_to(x+part+5, y+h*0.75 + 1) << box(h/2-8,2);
        changeNUM(-1);
    }
}

void Number::setMouse(int pos_x, int pos_y)
{
    mouseX = pos_x - x;
    mouseY = pos_y - y;
}

void Number::setVersus(int x)
{
    NUM*=x;
}

string Number::writeData()
{
    stringstream ss;
    ss << NUM;
    return ss.str();
}

//---------------------------------------------------------------------------------------

DropDown::DropDown(int x,int y,int min_w,int min_h, int max_h, vector<string> items) : Widget(x,y,min_w,min_h)
{
    this->max_h = max_h;
    this->items=items;
    highlight_string = items[0];
    opened = false;
    rollCount = 0;
}
void DropDown::show()
{
    int part = w-h;
    int r,g,b;

    int full_h = items.size() * h;
    int kifer = max_h / h;

    int max_letekeres = items.size() / kifer;

    if(kijelolt)
    {
        r=255;
        g=0;
        b=0;
    }
    else
    {
        r=41;
        g=132;
        b=65;
    }

    if(opened)
    {
        //textbox
        gout << color(r,g,b) << move_to(x-2,y-2) << box(w+4,h+4);
        gout << color(220,220,220) << move_to(x,y) << box(part-1,h);
        gout << color(220,220,220) << move_to(x+part+1,y) << box(w-part,h);

        for(int i = 0; i < 5; i++)
        {
            gout << color(r,g,b) << move_to(x+part+1,y+h/3+i + h/2) << line(h/2+1,-h/2+1);
            gout << color(r,g,b) << move_to(x+w,y+h/3+i + h/2) << line(-h/2-1,-h/2+1);
        }
    }
    else
    {
        //textbox
        gout << color(r,g,b) << move_to(x-2,y-2) << box(w+4,h+4);
        gout << color(220,220,220) << move_to(x,y) << box(part-1,h);
        gout << color(220,220,220) << move_to(x+part+1,y) << box(w-part,h);

        for(int i = 0; i < 5; i++)
        {
            gout << color(r,g,b) << move_to(x+part+1,y+h/3+i) << line(h/2+1,h/2+1);
            gout << color(r,g,b) << move_to(x+w,y+h/3+i) << line(-h/2-1,h/2+1);
        }
    }
    gout << color(0,0,0) <<move_to(x+2,y+h/1.5) << text(highlight_string);

    if(opened && kijelolt)
    {
        for(size_t i = 0; i < items.size(); i++)
        {
            if((i+1)*h<= max_h)
            {
                if(items[i]==highlight_string)
                {
                    gout << color(r,g,b) << move_to(x-2,y+(i+1)*h-2) << box(w+4,h+4);
                    gout << color(r,g,b) << move_to(x,y+(i+1)*h) << box(w,h);
                    gout << color(255,255,255) <<move_to(x+2,y+(i+1)*h + h/1.5) << text(items[i]);
                }
                else
                {
                    gout << color(r,g,b) << move_to(x-2,y+(i+1)*h-2) << box(w+4,h+4);
                    gout << color(220,220,220) << move_to(x,y+(i+1)*h) << box(w,h);
                    gout << color(0,0,0) <<move_to(x+2,y+(i+1)*h + h/1.5) << text(items[i]);
                }
            }
        }

        if(max_h < full_h)
        {
            gout << color(120,120,120) << move_to(x+w*0.9,y+h+rollCount) << box(w*0.1,h*max_h/full_h);
        }
    }
}
void DropDown::write(char s)
{

}
void DropDown::changeNUM(int x)
{
    if(opened && rollCount < items.size())
    {
        rollCount+=x;
    }
}
void DropDown::drag(int pos_x, int pos_y)
{
    x = pos_x - mouseX;
    y = pos_y - mouseY;
}
void DropDown::boundaries(int maxW, int maxH)
{
    if(opened)
    {
        if(x<2)
        {
            x=2;
        }
        if(y<2)
        {
            y=2;
        }
        if(x+w>maxW+3)
        {
            x= maxW - w - 3;
        }
        if(y + h + max_h >maxH+3)
        {
            y = maxH - max_h - h - 3;
        }
    }
    else
    {
        if(x<2)
        {
            x=2;
        }
        if(y<2)
        {
            y=2;
        }
        if(x+w>maxW+3)
        {
            x= maxW - w - 3;
        }
        if(y+h>maxH+3)
        {
            y = maxH - h - 3;
        }
    }
}
void DropDown::deleteDigit()
{

}
void DropDown::operation(int pos_x, int pos_y)
{
    int part = w - h;
    int r,g,b;

    if(kijelolt)
    {
        r=255;
        g=0;
        b=0;
    }
    else
    {
        r=41;
        g=132;
        b=65;
    }
    if(pos_x>x+part && pos_x < x+w && pos_y>y && pos_y < y + h)
    {
        opened = !opened;
    }

    if(opened)
    {
        for(size_t i = 0; i < items.size(); i++)
        {
            if((i+1)*h<= max_h)
            {
                if(items[i]==highlight_string)
                {
                    gout << color(r,g,b) << move_to(x-2,y+(i+1)*h-2) << box(w+4,h+4);
                    gout << color(r,g,b) << move_to(x,y+(i+1)*h) << box(w,h);
                    gout << color(255,255,255) <<move_to(x+2,y+(i+1)*h + h/1.5) << text(items[i]);
                }
                else
                {
                    gout << color(r,g,b) << move_to(x-2,y+(i+1)*h-2) << box(w+4,h+4);
                    gout << color(220,220,220) << move_to(x,y+(i+1)*h) << box(w,h);
                    gout << color(0,0,0) <<move_to(x+2,y+(i+1)*h + h/1.5) << text(items[i]);
                }
            }
            if(pos_x > x && pos_x < x + w)
            {
                if(pos_y > y+(i+1)*h && pos_y < y+(i+2)*h)
                {
                    highlight_string = items[i];
                    opened = false;
                }
            }
        }
    }
}
void DropDown::setMouse(int pos_x, int pos_y)
{
    mouseX = pos_x - x;
    mouseY = pos_y - y;
}
void DropDown::setVersus(int x)
{

}
string DropDown::writeData()
{
    return highlight_string;
}
