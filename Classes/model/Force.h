//
// Created by 杜一飞 on 14-5-11.
//


#ifndef __Force_H_
#define __Force_H_

#include <string>
#include <map>
#include "Ship.h"
#include "SeaPad.h"
#include "ModelCommon.h"

class Force {
public:

    ForceType const &getType() const {
        return type;
    }

    void setType(ForceType const &type) {
        Force::type = type;
    }

    ShipMap& getShipMap() {
        return shipMap;
    }

    void setShipMap(const ShipMap &shipMap) {
        Force::shipMap = shipMap;
    }

    SeaPad *getSeaPad() const {
        return seaPad;
    }

    void setSeaPad(SeaPad *seaPad) {
        Force::seaPad = seaPad;
    }

    void addShip(Ship *ship);
    Ship* getShipById(int id);

    bool isAllDestroyed();
private:
    ForceType type;
    ShipMap shipMap;
    SeaPad *seaPad;
};


#endif //__Force_H_
