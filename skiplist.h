//
// Created by Kaib Cropley on 5/7/2018.
// Last edited by Kaib Cropley on 5/13/2018.
//

#ifndef ASS4_SKIPLIST_H
#define ASS4_SKIPLIST_H

#include <iostream>
#include "snode.h"

class SkipList {
	friend std::ostream &operator<<(std::ostream &os, const SkipList &list);

public:
	// default SkipList has depth of 1, just one doubly-linked list
	explicit SkipList(int depth = 1);

	// destructor
	virtual ~SkipList();

	// return true if successfully added, no duplicates
	bool Add(int data);

	// return true if successfully removed
	bool Remove(int data);

	// return true if found in
	bool Contains(int data);

private:
	// Keeps track of depth
	int depth;
	// Head and tail nodes
	SNode **frontGuards;
	SNode **rearGuards;

	// 50% it returns true or false
	bool alsoHigher() const;

	// Adds a new node before the current node
	void addBefore(SNode *newNode, SNode *curNode);

	// Will add a node to given level and increase level by one.
	// Returns false if is already in list.
	bool findSpotAndAdd(SNode *newNode, int &level);
};


#endif //ASS4_SKIPLIST_H
