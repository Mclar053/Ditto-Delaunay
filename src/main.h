#ifndef __MAIN_H__
#define __MAIN_H__

//#define DEBUG 1

#include <string>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include "structures.h"

#define LEFT			0
#define RIGHT			1
#define INTERSECTION	2

using namespace std;

/* order x, y : (+1) if p1 > p2; (-1) if p1 < p2; (0) p1 = p2 */
int xyorder(const PointSL *p1, const PointSL *p2)
{
	/* x-coord */
	if (p1->x > p2->x) return  1;
	if (p1->x < p2->x) return -1;
	/* y-coord */
	if (p1->y > p2->y) return  1;
	if (p1->y < p2->y) return -1;
	return 0;  /* they are the same PointSL */
}

/* sequence of events e1, e2: according PointSLs, + if the points are the same,
 * according to the type of event */
int eventorder(const Event *e1, const Event *e2)
{
	const int xy = xyorder( e1->eV, e2->eV);
	switch (xy) {
		case 1: return 1;
		case -1: return -1;
		case 0:
			/* sort the events according to the type of event */
			if (e1->type == LEFT) return -1;
			if (e2->type == LEFT) return 1;
			if (e1->type == INTERSECTION) return -1;
			if (e2->type == INTERSECTION) return 1;
			return 0;
		default:
			return 0;
	}
}

/* p2 location relative to the segment p0 p1,
 * > 0 if left 0 if the line <0 if the right of the segment */
inline float is_left(PointSL P0, PointSL P1, PointSL P2 )
{
	return (P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y);
}

/* Kit contains the following coordinates peak? */
bool set_contains(set<PointSL *> *s, PointSL *p)
{
	set<PointSL *>::iterator it;

	for (it = s->begin(); it != s->end(); ++it) {
		if (((*it)->x == p->x) &&
		    ((*it)->y == p->y))
		{
			return true;
		}
	}
	return false;
}

/* for two parallel touchline, find out if p1 lies on s1 */
bool liesOn(SLseg *s1, PointSL p1)
{
	/* x coord ok */
	if ((s1->lP.x <= p1.x) && (s1->rP.x >= p1.x))
		/* y coord ok */
		if ((s1->lP.y <= p1.y) && (s1->rP.y >= p1.y))
			return true;
	return false;
}

/* find out whether the s1 and s2 partially / wholly overlays */
bool overlap(SLseg *s1, SLseg *s2)
{
	if (liesOn(s1, s2->lP) ||
	    liesOn(s1, s2->rP) ||
	    liesOn(s2, s1->lP) ||
	    liesOn(s2, s1->rP))
	{
		return true;
	}
	else {
		return false;
	}
}
bool from_string(float& t, const string& s, ios_base& (*f)(ios_base&))
{
	istringstream iss(s);
	return (iss >> f >> t).fail();
}
#endif  /* __MAIN_H__ */
