#include "widget.hpp"

const int w = 600;
const int h = 600;

void hatter()
{
    gout << move_to(0,0) << color(0,0,0) << box(w,h);
}

void fajlbair(vector<Widget*> widgets)
{
    ofstream ki;
    ki.open("adatok.txt");
    if(ki.is_open())
    {
       for(int i = 0; i < widgets.size(); i++)
        {
            ki << i + 1 << ". Widget: " << widgets[i]->writeData() << endl;
        }
    }
    ki.close();
}

int main()
{
    gout.open(w,h);
    gin.timer(35);
    vector<Widget*> widgets;
    vector<string> items1{"alma","korte","szilva","kemence"};
    vector<string> items2{"cica","kutya","vaddiszno","nyufi","sundiszno","edes istenem"};
    Widget* n = new Number(100,100,200,50,100,200);
    Widget* m = new Number(400,75,100,100,-5000,5000);
    Widget* d = new DropDown(200,300,100,25,100,items1);
    Widget* f = new DropDown(100,400,400,50,100,items2);
    widgets.push_back(n);
    widgets.push_back(m);
    widgets.push_back(d);
    widgets.push_back(f);
    Widget* kijelolt = nullptr;

    bool clicked = false;

    event ev;
    while(gin >> ev)
    {
        if(ev.type==ev_timer)
        {
            hatter();
            for(Widget* wi : widgets)
            {
                wi->show();
            }
            if(kijelolt!=nullptr)
            {
                kijelolt->show();
            }
        }
        if(ev.type==ev_mouse)
        {
            if(ev.button == btn_left)
            {
                kijelolt = nullptr;
                for(Widget* wi : widgets)
                {
                    if(wi->is_selected(ev.pos_x,ev.pos_y))
                    {
                        clicked = true;
                        kijelolt = wi;
                    }
                }
                if(kijelolt!=nullptr)
                {
                    kijelolt->operation(ev.pos_x,ev.pos_y);
                    kijelolt->setMouse(ev.pos_x,ev.pos_y);
                }
            }

            if(ev.button == -btn_left)
            {
                clicked = false;
            }

            if(ev.button == 0)
            {
                if(kijelolt!=nullptr && clicked)
                {
                    kijelolt->drag(ev.pos_x,ev.pos_y);
                    kijelolt->boundaries(w,h);
                }
            }

            if(ev.button == btn_wheelup)
            {
                if(kijelolt!=nullptr)
                {
                    kijelolt->changeNUM(1);
                }
            }
            if(ev.button == btn_wheeldown)
            {
                if(kijelolt!=nullptr)
                {
                    kijelolt->changeNUM(-1);
                }
            }
        }

        if(ev.type == ev_key)
        {
            if(ev.keycode > 47 && ev.keycode < 58 || ev.keycode == 45)
            {
                if(ev.keycode == 45)
                {
                    if(kijelolt!=nullptr)
                    {
                        kijelolt->setVersus(-1);
                    }
                }
                else
                {
                    if(kijelolt!=nullptr)
                    {
                        kijelolt->write(ev.keycode);
                    }
                }
            }

            if(ev.keycode == key_pgdn)
            {
                if(kijelolt!=nullptr)
                {
                    kijelolt->changeNUM(-10);
                }
            }

            if(ev.keycode == key_pgup)
            {
                if(kijelolt!=nullptr)
                {
                    kijelolt->changeNUM(10);
                }
            }

            if(ev.keycode == key_backspace)
            {
                if(kijelolt!=nullptr)
                {
                    kijelolt->deleteDigit();
                }
            }

            if(ev.keycode == key_insert)
            {
                fajlbair(widgets);
            }
        }
        gout << refresh;
    }
    return 0;
}

