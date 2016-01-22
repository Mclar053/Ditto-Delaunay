#ifndef __BINTREE_H__
#define __BINTREE_H__

#include "main.h"

struct Tnode {
	Tnode *left;            /* left child */
	Tnode *right;           /* right child */
	Tnode *parent;          /* parent */
	SLseg *val;             /* data */
	unsigned left_count;    /* how many visits left */
	unsigned right_count;   /* ~right */

	Tnode(SLseg *_segment)
	{
		left		= NULL;
		right		= NULL;
		parent		= NULL;
		val			= _segment;
		left_count	= 0;
		right_count = 0;
	}
};

/* class of binary tree sweepline it here will store segments */
class CBinTree
{
public:
	Tnode *head;

	CBinTree() 	{ head = NULL; 	}
	~CBinTree() { freetree(head); }
	void freetree(Tnode *node)
	{
		if (node->left != NULL) {
			freetree(node->left);
		}

		if (node->right != NULL) {
			freetree(node->right);
		}

		remove(node, true);
	}
	void freetree()
	{
		freetree(head);
	}
	/* insert adds a node with a data _data, returns a PointSLer to the node added. */
	Tnode *insert(SLseg *data)
	{
		if (data == NULL) {
			throw "NULL PointSLer";
		}

		Tnode *p = new Tnode(data);
		if (p == NULL) {
			throw "Memory allocation failure";
		}

		if (head == NULL) {
			head = p;
			return p;
		}

		try {
			Insert(head, p);
		}
		catch(char *) {
			delete p;
			throw;
		}
		return p;
	}
	/* finds in the tree */
	Tnode *find(SLseg *target)
	{
		if ((target == NULL) || (head == NULL)) {
			return NULL;
		}

		/* return Search(head, target); */
		Tnode *act = head;
		while ((act != NULL) &&
		       (act->val != NULL) &&
		       (act->val->edge != target->edge))
		{
			if (act->val->edge < target->edge) {
				act = act->right;
			}

			if (act->val->edge > target->edge) {
				act = act->left;
			}
		}
		return act;
	}
	/* Remove() is called to delete a node from the tree */
	void Remove_public(SLseg *target)
	{
		if (target == NULL) {
			throw "NULL PointSLer";
		}
#ifdef DEBUG
		cout << "Remove " << target->edge << endl;
#endif
		return Remove(target);
	}
	/* previous and next node */
	Tnode *next(Tnode *node)
	{
		if (node == NULL) {
			return NULL;
		}

		/* the leftmost from the right subtree */
		if (node->right != NULL) {
			Tnode *temp = node->right;
			while (temp->left != NULL) {
				temp = temp->left;
			}
			return temp;
		}

		if (node->parent == NULL) {
			return NULL;
		}

		if (node->parent->left == node) {
			return node->parent;
		}

		return NULL;
	}
	Tnode *prev(Tnode *node)
	{
		if (node == NULL)
			return NULL;

		/* true from the left subtree */
		if (node->left != NULL) {
			Tnode *temp = node->left;
			while (temp->right != NULL) {
				temp = temp->right;
			}
			return temp;
		}

		if (node->parent == NULL) {
			return NULL;
		}

		if (node->parent->right == node) {
			return node->parent;
		}

		return NULL;
	}

private:
	/* deletes a node if the data flag true, erase the data */
	void remove(Tnode *node, bool data)
	{
		if (head == node) head = NULL;
		if (data) delete node->val;
		delete node;
		node = NULL;
	}
	/* add, and once I head is set */
	void Insert(Tnode *_head, Tnode *new_node)
	{
		Tnode *p = _head;
		bool flag_continue = true;

		if (_head->left_count > 100000) {
			cout << "Error occured!" << endl;
			exit(1);
		}

		while (flag_continue) {
			/* if we left pridavat */
			if (new_node->val->edge < p->val->edge) {
				/* add left */
				p->left_count++;
				/* there's nothing left */
				if (p->left == NULL) {
					/* let there this node */
					p->left = new_node;
					new_node->parent = p;
					flag_continue = false;
				}
				else {
					/* keep up the left tree */
					p = p->left;
				}
			}
			/* if we want pridavat right */
			else if (new_node->val->edge > p->val->edge) {
				/* add right */
				p->right_count++;
				/* right is empty */
				if (p->right == NULL) {
					/* let there knot */
					p->right = new_node;
					new_node->parent = p;
					flag_continue = false;
				}
				else {
					/* no further right */
					p = p->right;
				}
			}
			/* equal value */
			else {
				/* throw "Equal values not supported"; */
			}
		}
	}


	/* called by public Search(), finds the specified data in the tree */
	Tnode *Search(Tnode *head, SLseg *target)
	{
		if (head == NULL) {
			return NULL;
		}

		if (head->left_count > 100000) {
			return NULL;
		}

		bool flag_continue = true;
		Tnode *p = head;

		while (flag_continue) {
			/* left */
			if (target->edge < p->val->edge) {
				if (p->left == NULL) {
					flag_continue = false;
					p = NULL;
				}
				else {
					p = p->left;
				}
			}
			else {
				if (target->edge > p->val->edge) {
					if (p->right == NULL) {
						flag_continue = false;
						p = NULL;
					}
					else {
						p = p->right;
					}
				}
				else {
					flag_continue = false;
				}
			}
		}

		return p;
	}

/* removes the node with the value of the tree */
void Remove(SLseg *target)
{
	bool found = false;
	if (head == NULL) {
		return;
	}

	Tnode *parent;
	Tnode *curr = head;

	while (curr) {
		if (curr->val->edge == target->edge) {
			found = true;
			break;
		}
		else {
			if (curr->val->edge < target->edge) {
				curr = curr->right;
			}
			else {
				curr = curr->left;
			}
		}
	}

	if (!found) {
#ifdef DEBUG
		cout << "Data not found!" << endl;
#endif
		return;
	}
	parent = curr->parent;

	/* single-child */
	if ((curr->left == NULL && curr->right != NULL) ||
	    (curr->left != NULL && curr->right == NULL))
	{
		/* right child */
		if (curr->left == NULL && curr->right != NULL) { /* head */
			if (parent == NULL) {
				head = curr->right;
				head->parent = NULL;
				delete curr;
				return;
			}
			if (parent->left == curr) {
				parent->left = curr->right;
				delete curr;
			}
			else {
				parent->right = curr->right;
				delete curr;
			}
		}
		else {  /* left child */
			/* head */
			if (parent == NULL) {
				head = curr->left;
				head->parent = NULL;
				delete curr;
				return;
			}
			if (parent->left == curr) {
				parent->left = curr->left;
				delete curr;
			}
			else {
				parent->right = curr->left;
				delete curr;
			}
		}
		return;
	}

	/* list */
	if ((curr->left == NULL) && (curr->right == NULL)) {
		if (parent == NULL) {
			delete curr;
			head = NULL;
			return;
		}

		if (parent->left == curr) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
		delete curr;
		return;
	}

	/* two-way, spare smallest right into it */
	if ((curr->left != NULL) && (curr->right != NULL)) {
		Tnode *chkr;
		chkr = curr->right;
		if ((chkr->left == NULL) && (chkr->right == NULL)) {
			curr = chkr;
			delete chkr;
			curr->right = NULL;
		}
		/* rights of the Child has children */
		else {
			/* ma lave child, take largest node of the subtree */
			if (curr->right->left != NULL) {
				Tnode *lcurr;
				Tnode *lcurrp;
				lcurrp = curr->right;
				lcurr = (curr->right)->left;
				while (lcurr->left != NULL) {
					lcurrp = lcurr;
					lcurr = lcurr->left;
				}
				curr->val = lcurr->val;
				delete lcurr;
				lcurrp->left = NULL;
			}
			else {
				Tnode *tmp;
				tmp = curr->right;
				curr->val = tmp->val;
				curr->right = tmp->right;
				delete tmp;
			}
		}
		return;
	}
}
};

#endif  /* __BINTREE_H__ */
