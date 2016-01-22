#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <iostream>

struct PointSL {
	float x;
	float y;

public:
	PointSL()
	{
		x = 0.0f;
		y = 0.0f;
	}
	PointSL(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	void Sanitize()
	{
		int tempx, tempy;
		tempx = ((int)(x * 100));
		tempy = ((int)(y * 100));
		x = (float)tempx / 100;
		y = (float)tempy / 100;
	}
};
typedef struct _event Event;
struct SLseg {
public:
	int      edge;
	PointSL    lP;       /* left top */
	PointSL    rP;       /* right top */
	SLseg   *above;    /* segment over */
	SLseg   *below;    /* segment below */

	SLseg(int _edge)
	{
		edge  = _edge;
		lP = *(new PointSL(0, 0));
		rP = *(new PointSL(0, 0));
	}
	SLseg(PointSL *p1, PointSL *p2)
	{
		lP = *p1;
		rP = *p2;
	}
	void Print()
	{
		std::cout << "Edge: " << edge << std::endl;
	}

	bool  lt(SLseg &rhs ) { return ( lP.x < rhs.lP.x ); }
	bool  gt(SLseg &rhs ) { return ( lP.x > rhs.lP.x ); }
	bool lt2(SLseg &rhs ) { return ( lP.y > rhs.lP.y ); }
	bool gt2(SLseg &rhs ) { return ( lP.y > rhs.lP.y ); }
};
struct _event {
	int      edge;
	int      type;              /* event type LEFT/RIGHT/INTERSECTION */
	PointSL   *eV;                /* top */
	PointSL   *another_vertex;    /* the second peak segment */
	bool served;                /* eventa-served? */

	SLseg  *intersectUpper;     /* due intersection */
	SLseg  *intersectLower;     /* ~ */
};

#endif  /* __STRUCTURES_H__ */
