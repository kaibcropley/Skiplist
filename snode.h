//
// Created by Kaib Cropley on 5/7/2018.
// Last edited by Kaib Cropley on 5/13/2018.
//

#ifndef ASS4_SNODE_H
#define ASS4_SNODE_H


class SNode {
public:
	// SNode stores int as data
	explicit SNode(int data);

	// data for SNode
	int data;

	// link to next SNode
	SNode *next;

	// link to prev SNode
	SNode *prev;

	// link to up one level
	SNode *upLevel;

	// link to down one level
	SNode *downLevel;
};

#endif //ASS4_SNODE_H
