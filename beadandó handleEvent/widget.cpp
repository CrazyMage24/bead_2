#include "widget.hpp"

Widget::Widget(int x_,int y_,int w_,int h_) : x(x_), y(y_), w(w_), h(h_)
{
    selected = false;
}




///---------------------------------------------------------------------------------------------------------------------------------
Number::Number(int x,int y,int w,int h,int mini,int maxi) : Widget(x,y,w,h)
{
    this->mini=mini;
    this->maxi=maxi;
    NUM = (mini+maxi)/2;
    operated_NUM = NUM;
    operated = false;
}




/// OVERRIDE FUNCTIONS
void Number::handleTimer(event ev)
{
    show();
}
bool Number::handleSelection(event ev)
{
    if(is_selected(ev.pos_x,ev.pos_y))
    {
        return true;
    }
    else
    {
        checkNumber();
        selected = false;
        return false;
    }
}
void Number::handleMouse(event ev,int W, int H)
{
    selected = true;
    if(ev.button == btn_left && selected)
    {
        clicked = true;
        setMouse(ev.pos_x,ev.pos_y);
        operation(ev.pos_x,ev.pos_y);
    }

    if(ev.button == -btn_left)
    {
        clicked = false;
    }

    if(ev.button == 0 && selected && clicked)
    {
        drag(ev.pos_x,ev.pos_y);
        boundaries(W,H);
    }

    if(ev.button == btn_wheelup)
    {
        if(selected)
        {
            setNUM(1);
        }
    }

    if(ev.button == btn_wheeldown)
    {
        if(selected)
        {
            setNUM(-1);
        }
    }
}

void Number::handleKeys(event ev)
{
    if(ev.keycode > 47 && ev.keycode < 58 || ev.keycode == 45)
    {
        if(ev.keycode == 45)
        {
            if(selected)
            {
                operated = true;
                setSIGN();
            }
        }
        else
        {
            if(selected)
            {
                operated = true;
                addNUMBER(ev.keycode);
            }
        }
    }

    if(ev.keycode == key_pgdn)
    {
        if(selected)
        {
            operated = true;
            setNUM(-10);
        }
    }

    if(ev.keycode == key_pgup)
    {
        if(selected)
        {
            operated = true;
            setNUM(10);
        }
    }

    if(ev.keycode == key_down)
    {
        if(selected)
        {
            operated = true;
            setNUM(-1);
        }
    }

    if(ev.keycode == key_up)
    {
        if(selected)
        {
            operated = true;
            setNUM(1);
        }
    }

    if(ev.keycode == key_backspace)
    {
        if(selected)
        {
            operated = true;
            deleteDigit();
        }
    }

    if(ev.keycode == key_enter)
    {
        if(selected)
        {
            checkNumber();
            operated = false;
        }
    }

}




/// LOCAL FUNCTIONS
void Number::show()
{
    int part = w - h/2; // választóvonal helye
    int r,g,b; // színkódok

    if(selected)
    {
        if(operated)
        {
            r=0;
            g=255;
            b=0;
        }
        else
        {
            r=255;
            g=0;
            b=0;
        }
    }
    else
    {
        r=0;
        g=128;
        b=255;
    }

    // szines szele
    gout << color(r,g,b) << move_to(x-2,y-2) << box(w+4,h+4);
    // box
    gout << color(220,220,220) << move_to(x,y) << box(part-1,h);
    // pluszjel + box
    gout << color(220,220,220) << move_to(x+part+1,y) << box(h/2,h/2-1);
    gout << color(r,g,b) << move_to(x+part+5, y+h*0.25 - 1) << box(h/2-8,2);
    gout << color(r,g,b) << move_to(x+part+h/4, y + 4) << box(2,h*0.5 - 8);

    // minuszjel + box
    gout << color(220,220,220) << move_to(x+part+1,y+h/2 + 2) << box(h/2,h/2 - 2);
    gout << color(r,g,b) << move_to(x+part+5, y+h*0.75 + 1) << box(h/2-8,2);

    // NUM kiiratas
    stringstream ss;
    ss << operated_NUM;
    gout << color(0,0,0) << move_to(x+5,y+h/2+10) << text(ss.str());
}

bool Number::is_selected(int pos_x, int pos_y)
{
    return pos_x>x && pos_x<x+w && pos_y>y && pos_y<y+h;
}

void Number::setMouse(int pos_x, int pos_y)
{
    mouseX = pos_x - x;
    mouseY = pos_y - y;
}
void Number::drag(int pos_x, int pos_y)
{
    x = pos_x - mouseX;
    y = pos_y - mouseY;
}

void Number::boundaries(int W, int H)
{
    if(x<2)
    {
        x=2;
    }
    if(y<2)
    {
        y=2;
    }
    if(x+w>W+2)
    {
        x= W - w - 2;
    }
    if(y+h>H+2)
    {
        y = H - h - 2;
    }
}

void Number::setNUM(int x)
{
    operated_NUM+=x;
}

void Number::operation(int pos_x, int pos_y)
{
    int part = w - h/2;
    int r=255;
    int g=0;
    int b=0;
    if(pos_x>x+part && pos_x < x+w && pos_y>y && pos_y < y + h/2)
    {
        // pluszjel
        gout << color(255,255,255) << move_to(x+part+1,y) << box(h/2,h/2-1);
        gout << color(r,g,b) << move_to(x+part+5, y+h*0.25 - 1) << box(h/2-8,2);
        gout << color(r,g,b) << move_to(x+part+h/4, y + 4) << box(2,h*0.5 - 8);
        operated = true;
        setNUM(1);
    }

    if(pos_x>x+part && pos_x < x+w && pos_y>y + h/2 && pos_y < y + h)
    {
        // minusz jel
        gout << color(255,255,255) << move_to(x+part+1,y+h/2 + 2) << box(h/2,h/2 - 2);
        gout << color(r,g,b) << move_to(x+part+5, y+h*0.75 + 1) << box(h/2-8,2);
        operated = true;
        setNUM(-1);
    }
}

void Number::setSIGN()
{
    operated_NUM*=-1;
}

void Number::addNUMBER(char s)
{
    stringstream ss;
    ss << operated_NUM << s;

    stringstream zz(ss.str());
    zz >> operated_NUM;
    ss.str("");
    zz.str("");
}
void Number::deleteDigit()
{
    operated_NUM/=10;
}

string Number::handleOutput()
{
    stringstream ss;
    ss << NUM;
    return ss.str();
}

void Number::checkNumber()
{
    if(operated_NUM < mini)
    {
        operated_NUM = mini;
    }

    if(operated_NUM > maxi)
    {
        operated_NUM = maxi;
    }

    NUM = operated_NUM;
}


///-----------------------------------------------------------------------------------------------------------------------------------
DropDown::DropDown(int x,int y,int w,int h, int max_h, vector<string> items) : Widget(x,y,w,h)
{
    this->max_h = max_h;
    this->items=items;
    highlight_string = items[0];
    opened = false;
    scroll_Count = 0;
}




/// OVERRIDE FUNCTIONS
void DropDown::handleTimer(event ev)
{
    show();
}
bool DropDown::handleSelection(event ev)
{
    if(is_selected(ev.pos_x,ev.pos_y))
    {
        return true;
    }
    else
    {
        opened = false;
        selected = false;
        return false;
    }
}
void DropDown::handleMouse(event ev, int W, int H)
{
    selected = true;
    if(ev.button == btn_left)
    {
        setMouse(ev.pos_x,ev.pos_y);

        clicked = true;
    }

    if(ev.button == -btn_left)
    {
        setTEXT(ev.pos_x,ev.pos_y);
        clicked = false;
    }

    if(ev.button == 0)
    {
        if(selected && clicked)
        {
            drag(ev.pos_x,ev.pos_y);
            boundaries(W,H);
        }
    }

    if(ev.button == btn_wheelup)
    {
        scroll(1);
    }

    if(ev.button == btn_wheeldown)
    {
        scroll(-1);
    }
}
void DropDown::handleKeys(event ev)
{

}




/// LOCAL FUNCTIONS
void DropDown::show()
{
    int part = w-h; // választóvonal helye
    int r,g,b; // színkódok
    double full_h = items.size() * h; // a teljes magassag, ha az osszes elem kiferne(az eppen kivalasztotton kivul)
    int kifer = max_h / h; // annyi elemnek a szama, ami kifer a max magassag miatt
    int max_letekeres = items.size() / kifer; // az a szam, ahanyszor maximum le lehet tekerni
    int index = scroll_Count * kifer; // ahanyadik elemnel most járunk az egyes letekerések után

    if(selected)
    {
        r=255;
        g=0;
        b=0;
    }
    else
    {
        r=148;
        g=0;
        b=211;
    }

    //box
    gout << color(r,g,b) << move_to(x-2,y-2) << box(w+4,h+4);
    gout << color(220,220,220) << move_to(x,y) << box(part-1,h);
    gout << color(220,220,220) << move_to(x+part+1,y) << box(w-part,h);

    // kinyitas
    if(opened)
    {
        for(int i = 0; i < 5; i++)
        {
            gout << color(r,g,b) << move_to(x+part+1,y+h/3+i + h/2) << line(h/2+1,-h/2+1);
            gout << color(r,g,b) << move_to(x+w,y+h/3+i + h/2) << line(-h/2-1,-h/2+1);
        }
    }
    else
    {
        for(int i = 0; i < 5; i++)
        {
            gout << color(r,g,b) << move_to(x+part+1,y+h/3+i) << line(h/2+1,h/2+1);
            gout << color(r,g,b) << move_to(x+w,y+h/3+i) << line(-h/2-1,h/2+1);
        }
    }
    gout << color(0,0,0) <<move_to(x+2,y+h/1.5) << text(highlight_string);

    if(opened && selected)
    {
        if(index+kifer > items.size())
        {
            index-= index+kifer - items.size();
        }

        for(int i = index; i < index + kifer; i++)
        {
            if(i<items.size())
            {
                if(items[i]==highlight_string)
                {
                    gout << color(r,g,b) << move_to(x-2,y+(i-index+1)*h-2) << box(w+4,h+4);
                    gout << color(r,g,b) << move_to(x,y+(i-index+1)*h) << box(w,h);
                    gout << color(255,255,255) <<move_to(x+2,y+(i-index+1)*h + h/1.5) << text(items[i]);
                }
                else
                {
                    gout << color(r,g,b) << move_to(x-2,y+(i-index+1)*h-2) << box(w+4,h+4);
                    gout << color(220,220,220) << move_to(x,y+(i-index+1)*h) << box(w,h);
                    gout << color(0,0,0) <<move_to(x+2,y+(i-index+1)*h + h/1.5) << text(items[i]);
                }
            }
        }

        // Scrollbar
        if(max_h < full_h)
        {
            if(items.size() * h % max_h !=0)
            {
                gout << color(120,120,120) << move_to(x+w-25,y+h+scroll_Count*h*kifer/2/max_letekeres) << box(25,h*kifer/max_letekeres);
            }
            else
            {
                gout << color(120,120,120) << move_to(x+w-25,y+h+(scroll_Count*h*kifer)/max_letekeres) << box(25,h*kifer/max_letekeres);
            }
        }
    }
}

bool DropDown::is_selected(int pos_x, int pos_y)
{
    if(opened)
    {
        return pos_x>x && pos_x<x+w && pos_y>y && pos_y<y+h+max_h;
    }
    else
    {
        return pos_x>x && pos_x<x+w && pos_y>y && pos_y<y+h;
    }
}

void DropDown::setMouse(int pos_x, int pos_y)
{
    mouseX = pos_x - x;
    mouseY = pos_y - y;
}
void DropDown::drag(int pos_x, int pos_y)
{
    x = pos_x - mouseX;
    y = pos_y - mouseY;
}

void DropDown::boundaries(int W, int H)
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
        if(x+w>W+2)
        {
            x= W - w - 2;
        }
        if(y + h + max_h >H+2)
        {
            y = H - max_h - h - 2;
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
        if(x+w>W+2)
        {
            x= W - w - 2;
        }
        if(y+h>H+2)
        {
            y = H - h - 2;
        }
    }
}

string DropDown::handleOutput()
{
    return highlight_string;
}

void DropDown::setTEXT(int pos_x, int pos_y)
{
    int part = w - h;
    int r,g,b;

    double kifer = max_h / h; // annyi elemnek a szama, ami kifer a max magassag miat
    double index = scroll_Count * kifer; // ahanyadik elemnel most járunk az egyes letekerések után

    if(pos_x>x+part && pos_x < x+w && pos_y>y && pos_y < y + h)
    {
        opened = !opened;
    }
    if(opened)
    {
        if(index+kifer > items.size())
        {
            index-= index+kifer - items.size();
        }

        for(int i = index; i < index + kifer; i++)
        {
            if(pos_x > x && pos_x < x + w)
            {
                if(pos_y > y+(i-index+1)*h && pos_y < y+(i-index+2)*h)
                {
                    highlight_string = items[i];
                    opened = false;
                }
            }
        }
    }
}

void DropDown::scroll(int z)
{
    double kifer = max_h / h;
    z = -z; /// csak hogy a lefelé görgetés legyen a pozitív irányú elmozdulás
    if(z>0)
    {
        double c = items.size() / kifer;
        if(opened && scroll_Count < c - 1)
        {
            scroll_Count+=z;
        }
    }
    if(z<0)
    {
        if(scroll_Count > 0)
        {
            scroll_Count+=z;
        }
    }
}







