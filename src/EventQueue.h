#ifndef __EVENTQUEUE_H__
#define __EVENTQUEUE_H__

#include "main.h"
#include "SweepLine.h"
#include "structures.h"

class EventQueue {
	int      ne;               /* search events */
	int      ix;               /* index */
	Event   *Edata;            /* event data */
	Event  **Eq;               /* sort order list PointSLers on field */
public:
	/* create a new series of events from the vector segment */
	EventQueue(vector<SLseg *> seg);
	~EventQueue(void)
	{
		free(Eq);
		delete [] Edata;
	}
	/* returns the next event refused service in the order */
	Event *next();
	/* add a new event, returns success */
	bool add(PointSL *p, SLseg *upper, SLseg *lower);
};

/* compare the events for qsort */
int E_compare(const void *v1, const void *v2)
{
	const Event **e1 = (const Event **)v1;
	const Event **e2 = (const Event **)v2;
	return eventorder(*e1, *e2);
}
EventQueue::EventQueue(vector<SLseg *>P)
{
	ix = 0;
	ne = 2 * P.size();  /* 2 peaks in segment */

	Edata	= (Event *)   new Event[ne];
	Eq		= (Event **)  malloc(sizeof(*Eq) * ne);
	/* init PointSLers */
	for (int i = 0; i < ne; i++) {
		Eq[i] = &Edata[i];
	}

	/* init event */
	for (int i = 0; i < (int)P.size(); i++) {
		Eq[2 * i]->edge = i;
		Eq[2 * i + 1]->edge = i;
		/* first event */
		Eq[2 * i]->eV   = &(P.at(i)->lP);
		Eq[2 * i]->another_vertex = &(P.at(i)->rP);
		/* second event */
		Eq[2 * i + 1]->eV = &(P.at(i)->rP);
		Eq[2 * i + 1]->another_vertex = &(P.at(i)->lP);
		/* type */
		if (xyorder(&(P.at(i)->lP), &(P.at(i)->rP)) < 0) {
			Eq[2 * i]->type = LEFT;
			Eq[2 * i + 1]->type = RIGHT;
		}
		else {
			Eq[2 * i]->type = RIGHT;
			Eq[2 * i + 1]->type = LEFT;
		}
		/* new and refused service */
		Eq[2 * i]->served = Eq[2 * i + 1]->served = false;
	}

	/* organize */
	qsort(Eq, ne, sizeof(Event *), E_compare);

#ifdef DEBUG
	for (int i = 0; i < (int)P.size(); i++) {
		Eq[2 * i]->eV->Print("");
		Eq[2 * i + 1]->eV->Print("");
	}
#endif
}
Event *EventQueue::next()
{
	/* If you already have in the end, returns 0 */
	if (ix >= ne) {
		return NULL;
	}

	/* open field and find prvu event over to serve */
	while (Eq[ix]->served) {
		ix++;
		if (ix >= ne) {
			return NULL;
		}
	}
	Eq[ix]->served = true;
	/* returns the following event */
	return Eq[ix++];
}
bool EventQueue::add(PointSL * p, SLseg * upper, SLseg * lower)
{
	/* verify that it's not yet */
	for (int i = 0; i < ne; i++) {
		if ((Eq[i]->eV->x == p->x) &&
		    (Eq[i]->eV->y == p->y) &&
		    (Eq[i]->type == INTERSECTION))
		{
			return false;
		}
	}

	ne++;
	/* new memory */
	Eq = (Event **)realloc(Eq, ne * sizeof(Event));
	if (Eq == NULL) { cout << "Error (re)allocating memory" << endl; exit (1); }
	/* add event */
	Eq[ne - 1] = new Event();
	Eq[ne - 1]->served = false;
	Eq[ne - 1]->eV = p;
	Eq[ne - 1]->type = INTERSECTION;
	Eq[ne - 1]->intersectUpper = upper;
	Eq[ne - 1]->intersectLower = lower;

	qsort(Eq, ne, sizeof(Event *), E_compare);

	ix = 0;

#ifdef DEBUG
	for (int i = 0; i < ne; i++) {
		Eq[i]->eV->Print("event: ");
	}
#endif
	return true;
}

#endif  /* __EVENTQUEUE_H__ */
