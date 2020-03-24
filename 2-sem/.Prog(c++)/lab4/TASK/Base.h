#ifndef PROGA_BASE_H
#define PROGA_BASE_H

#include <iostream>
#include <cmath>

class IGeoFig {
public:

    virtual double square() = 0;

    virtual double perimeter() = 0;
};

class CVector2D {
public:
    double x, y;
    CVector2D(){ x = 0; y = 0;};
};

class IPhysObject {
public:

    virtual double mass() const = 0;

    virtual CVector2D position() = 0;

    virtual bool operator== ( const IPhysObject& ob ) const = 0;

    virtual bool operator< ( const IPhysObject& ob ) const = 0;
};

class IPrintable {
public:

    virtual void draw() = 0;
};

class IDialogInitiable {

    virtual void initFromDialog() = 0;
};

class BaseCObject {
public:

    virtual const char* classname() = 0;

    virtual unsigned int size() = 0;
};

class IFigure : public IGeoFig, public IPhysObject, public IPrintable, public IDialogInitiable, public BaseCObject {};

#endif //PROGA_BASE_H
