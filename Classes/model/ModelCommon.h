//
//  ModelCommon.h
//  SeaFight
//
//  Created by 杜一飞 on 14-5-10.
//
//

#ifndef SeaFight_ModelCommon____FILEEXTENSION___
#define SeaFight_ModelCommon____FILEEXTENSION___

#include <utility>
#include <map>
using namespace std;

#define SEA_PAD_PICE_ROW 10

// 舰船的分类
#define SHIP_TYPE_FRIGATE           "frigate"
#define SHIP_TYPE_SUBMARINE         "submarine"
#define SHIP_TYPE_DESTROYER         "destroyer"
#define SHIP_TYPE_CRUISER           "cruiser"
#define SHIP_TYPE_CARRIER           "carrier"

enum ForceType {
    Left = 0,
    Right
};

enum RotateType {
    Vertical,
    Horizontal
};

enum ShipType {

};

typedef pair<int, int> MatrixPos;

class Ship;
typedef std::map<std::string, Ship*> ShipMap;

#endif
