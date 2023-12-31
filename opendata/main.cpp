#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <gd.h>
#include <gdfontg.h>
#include <vector>

using namespace std;
//typedef std::basic_string<unsigned char> ustring;

typedef struct Datalist Datalist;

struct Datalist{
    int percent;
    char* data;

};

/*!
 * \brief MakePieChart
 * \param im
 * \param f
 * \param data
 * \param colors
 * \param center
 * \param radius
 * Créer un graphique en camenbert dans une image donnée, supposé créer la légende avec mais ne fonctionne pas
 */

void MakePieChart(gdImagePtr im, gdFontPtr f, vector<Datalist> data, int colors[], int center, int radius)
{
    int len = data.size();
    Datalist currentData;
    int i=0;
    int startP=0;
    int endP;
    for(i=0; i<len+1; i++)
    {
        currentData=data[i];
        endP=startP+3.6*currentData.percent;
        gdImageFilledArc(im, center, center, radius*2, radius*2,startP, endP,colors[i],0);
        /*if(endP<=180)
            gdImageString(im, f, center+radius+strlen(currentData.data), center,currentData.data,colors[i]);
        else
            gdImageString(im, f, center+(radius/2) , center-radius,currentData.data,colors[i]);*/
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
    int capacity=0;
    int bikeused;
    int bikeavailable=0;
    for(auto& elm : json.items() )
    {
        nlohmann::json object = elm.value();

        //cout<<object["name"]<<"\n\n";
        capacity += object["capacity"].get<int>();
        //cout<<object["capacity"]<<"\n\n";
        //cout<<"capacity : "<<capacity<<"\n";

        bikeavailable += object["num_bikes_available"].get<int>();

        //cout<<object["num_bikes_available"]<<"\n\n";
        //cout<<"bike available : "<<bikeavailable<<"\n";
    }

    bikeused = capacity-bikeavailable;
    bikeavailable = (bikeavailable/capacity)*100;
    bikeused = (bikeused/capacity)*100;
    Datalist bikeusedD;
    bikeusedD.percent = bikeused;
    //bikeusedD.data = "bikes used";
    Datalist bikeA;
    bikeA.percent = bikeavailable;
    //bikeA.data= "bikes available";
    vector<Datalist> datas;
    datas.push_back(bikeusedD);
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
    pngout = fopen("graph.png", "wb");
    gdImagePng(im, pngout);
    fclose(pngout);
    gdImageDestroy(im);


    return 0;
}
