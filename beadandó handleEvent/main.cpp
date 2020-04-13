#include "widget.hpp"

const int w = 600;
const int h = 600;

void background()
{
    gout << move_to(0,0) << color(0,0,0) << box(w,h);
}

void debug(Widget* selected)
{
    if(selected!=nullptr)
    {
        stringstream ss;
        ss << "Selected: " << selected->handleOutput();
        gout << color(211,255,0) << move_to(20,20) << text(ss.str());
    }
    else
    {
        gout << color(211,255,0) << move_to(20,20) << text("Selected: nullptr");
    }
}

void writeDATA(vector<Widget*> widgets)
{
    ofstream ki;
    ki.open("adatok.txt");
    if(ki.is_open())
    {
       for(int i = 0; i < widgets.size(); i++)
        {
            ki << i + 1 << ". Widget: " << widgets[i]->handleOutput() << endl;
        }
    }
    ki.close();

    gout << color(255,211,0) << move_to(30,30) << text("Mentve!");
}

int main()
{
    gout.open(w,h);
    gin.timer(35);

    vector<Widget*> widgets;
    vector<string> items1{"alma","korte","szilva","barack","retek","repa","brokkoli","kókusz","rizs","krumpli"};
    vector<string> items2{"cica","kutya","vaddiszno","nyufi","sundiszno","panda"};
    Widget* n = new Number(100,100,200,50,100,200); /// (x,y w,h, mini,maxi)
    Widget* m = new Number(400,75,100,100,-5000,5000);
    Widget* d = new DropDown(100,350,400,50,100,items2); /// (x,y,w,h,max_h,items vector) (max_h legyen többszöröse a h-nak, vagy a scrollBar rosszul viselkedik)
    Widget* f = new DropDown(200,250,100,25,100,items1);
    widgets.push_back(n);
    widgets.push_back(m);
    widgets.push_back(d);
    widgets.push_back(f);

    Widget* selected = nullptr;

    event ev;
    while(gin >> ev)
    {
        if(ev.type==ev_timer)
        {
            background(); ///háttér
            debug(selected); /// kiírja az aktuálisan kiválasztott widgetet debug célokra
            for(Widget* wi : widgets)
            {
                wi->handleTimer(ev);
            }
        }

        if(ev.type==ev_mouse)
        {
            if(ev.button == btn_left)
            {
                selected = nullptr;
                for(Widget* wi : widgets)
                {
                    if(wi->handleSelection(ev))
                    {
                        selected = wi;
                    }
                }
            }
            if(selected!= nullptr)
            {
                selected->handleMouse(ev,w,h);
            }
        }

        if(ev.type == ev_key)
        {
            for(Widget* wi : widgets)
            {
                wi->handleKeys(ev);
            }

            if(ev.keycode == key_insert)
            {
                writeDATA(widgets);
            }
        }
        gout << refresh;
    }
    return 0;
}

