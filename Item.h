#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "CEntity.h"
#include <string>

class Item : public CEntity
{

protected:
    std::string name;

public:
    Item();
    ~Item();

    std::string GetName();

};


#endif // ITEM_H_INCLUDED
