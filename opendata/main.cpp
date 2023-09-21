#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <gd.h>
#include <gdfontg.h>
#include <vector>

using namespace std;

typedef struct Datalist Datalist;

struct Datalist{
    int percent;
    string data;

};

Datalist* CompileArgument()
{
    int i;
    int size = (numArgs-2)/2;
    Datalist* list;
    if((numArgs-2)%2!=0 ||  numArgs<6)
    {
        printf("NOT ENOUGH ARGUMENT\n");
        //return 1;
        list = Init(50, "Placeholder");
        Add(list, 50, "placeholder2");
        filename = "test.png";
        return list;
    }
    int sum=0;
    int tempInt;
    for(i=2; i<size+1; i++)
    {
        tempInt = atoi(args[i]);
        if(i=2)
            list=Init(tempInt, args[i+size]);
        else
            Add(list, tempInt, args[i+size]);
        sum+=tempInt;
    }

    if(sum!=100)
    {
        printf("THERE IS DATA MISSING");
    }
    filename=args[numArgs];
    return list;
}

void MakePieChart(gdImagePtr im, gdFontPtr f, Datalist* data, int colors[], int center, int radius)
{
    int len = LastIndex(data);
    Datalist* currentData;
    int i=0;
    int startP=0;
    int endP;
    for(i=0; i<len+1; i++)
    {
        currentData=GetMember(data,i);
        endP=startP+3.6*currentData->percent;
        gdImageFilledArc(im, center, center, radius*2, radius*2,startP, endP,colors[i],0);
        if(endP<=180)
            gdImageString(im, f, center+radius+strlen(currentData->data), center,currentData->data,colors[i]);
        else
            gdImageString(im, f, center+(radius/2) , center-radius,currentData->data,colors[i]);
        startP=endP;
    }
}




int main()
{
    ifstream fJson("data.json");
    stringstream buffer;
    buffer << fJson.rdbuf();
    //cout<<buffer.str();
    auto json = nlohmann::json::parse(buffer.str());
    gdImagePtr im;
    FILE* pngout;
    int sizeX=256;
    int sizeY=256;
    //colors
    int black;
    int white;
    int red;
    int blue;
    int green;
    im = gdImageCreate(sizeX, sizeY);
    white = gdImageColorAllocate(im, 255,255,255);
    black = gdImageColorAllocate(im, 0, 0 ,0);
    red = gdImageColorAllocate(im,255,0,0);
    blue = gdImageColorAllocate(im, 0,0,255);
    green = gdImageColorAllocate(im,0,255,0);
    gdFontPtr font;

    int colors[4] = {black, red, blue,green};
    font = gdFontGetGiant();
    MakePieChart(im, font, datas, colors, sizeX/2, sizeX/4);
    int capacity;
    int bikeused;
    int bikeavailable;
    for(auto& elm : json.items() )
    {
        nlohmann::json object = elm.value();
        //cout<<object["name"]<<"\n\n";
        capacity += object["capacity"];
        //cout<<object["capacity"]<<"\n\n";
        bikeavailable += object["num bikes available"];
        //cout<<object["num_bikes_available"]<<"\n\n";
    }
    bikeused = capacity-bikeavailable;
    pngout = fopen(file, "wb");
    gdImagePng(im, pngout);
    fclose(pngout);
    free(file);
    gdImageDestroy(im);
    //cout<<json;

    return 0;
}
