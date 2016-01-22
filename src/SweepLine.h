#ifndef __SWEEPLINE_H__
#define __SWEEPLINE_H__

#include "main.h"
#include "bintree.h"
#include "EventQueue.h"

struct PointSL;

class SweepLine {
	vector <SLseg *> SLsegmenty;
	CBinTree Tree;

public:
	SweepLine() { Tree = *(new CBinTree()); }
	~SweepLine(void) { Tree.freetree(); }

	SLseg   *add(Event *);
	SLseg   *find(Event *);
	void     intersect(SLseg *, SLseg *, EventQueue *);
	void     remove(SLseg *);
	PointSL   *intersect_point(const PointSL *p1, const PointSL *p2, const PointSL *p3, const PointSL *p4);
	bool contains(set <PointSL *> *s, PointSL *p);
};

/* Add event to sweepline by creating new SLseg */
SLseg *SweepLine::add(Event *E)
{
	/* assigned to the segment edge number */
	SLseg *s = new SLseg(E->edge);
	/* attachments => LEFT edge event */
	/* find out which position is the CCW */
	if (xyorder(&(E->eV[0]), E->another_vertex) < 0) {
		/* determine which is leftmost */
		s->lP = E->eV[0];
		s->rP = *E->another_vertex;
	}
	else {
		s->rP = E->eV[0];
		s->lP = *E->another_vertex;  /* E->eV[1]; */
	}

	s->above = NULL;
	s->below = NULL;

	Tnode *nd = Tree.insert(s);
	Tnode *nx = Tree.next(nd);
	Tnode *np = Tree.prev(nd);
	/* If there is another node */
	if (nx != NULL) {
		s->above = (SLseg *)nx->val;
		s->above->below = s;
	}
	/* if there is a previous node */
	if (np != NULL) {
		s->below = (SLseg *)np->val;
		s->below->above = s;
	}
	return s;
}

/* finds a segment in the tree */
SLseg *SweepLine::find(Event *E)
{
	SLseg *s = new SLseg(E->edge);
	s->above = NULL;
	s->below = NULL;

	Tnode *nd = Tree.find(s);
	delete s;
	if (nd == NULL) {
		return NULL;
	}

	return (SLseg *)nd->val;
}
void SweepLine::remove(SLseg *s)
{
	Tree.Remove_public(s);
	return;
}
void SweepLine::intersect(SLseg *s1, SLseg *s2, EventQueue *Eq)
{
	/* if there is, over - does not become */
	if (s1 == NULL || s2 == NULL) {
		return;
	}

#ifdef DEBUG
	cout << "Porovnavam segmenty hran " << s1->edge << " a " << s2->edge << endl;
#endif

	/* The same segment - It's not */
	if (s1->edge == s2->edge) return;

	/* tests the intersection */
	float lsign, rsign;
	lsign = is_left(s1->lP, s1->rP, s2->lP);  /* position of the PointSL of the segment s2 relative to s1 */
	rsign = is_left(s1->lP, s1->rP, s2->rP);  /* working PointSL position with respect to segment s2 s1 */
	if (lsign * rsign > 0) {
		/* If both lie on the one hand, it can not intersect */
		return ;
	}
	if (lsign == 0 && rsign == 0) {  /* if it lies on the line */
		if (overlap(s1, s2)) {  /* find out if they do not overlap */
			cout << "Prekryvajuce sa segmenty ciar " << s1->edge << " a " << s2->edge << endl;
			return;
		}
	}
	lsign = is_left(s2->lP, s2->rP, s1->lP);  /* ^^ */
	rsign = is_left(s2->lP, s2->rP, s1->rP);  /* ^^ */
	if (lsign * rsign > 0) {
		return;  /* ^^ */
	}

	/* the intersection */
	PointSL *intersectPointSL = intersect_point(&s1->lP, &s1->rP, &s2->lP, &s2->rP);
	/* round */
	intersectPointSL->Sanitize();

	/* intersect other segments */
	if (s1->above == s2) {
		Eq->add(intersectPointSL, s2, s1);
	}
	else {
		Eq->add(intersectPointSL, s1, s2);
	}
}
PointSL *SweepLine::intersect_point(const PointSL *p1, const PointSL *p2, const PointSL *p3, const PointSL *p4)
{
	/* formula to find the PointSL where these two lines cross the */
	float f = ((((p4->x - p3->x) * (p1->y - p3->y)) - ((p4->y - p3->y) * (p1->x - p3->x))) /
	           (((p4->y - p3->y) * (p2->x - p1->x)) - ((p4->x - p3->x) * (p2->y - p1->y))));
	return new PointSL(p1->x + f * (p2->x - p1->x), p1->y + f * (p2->y - p1->y));
}

#endif  /* __SWEEPLINE_H__ */
