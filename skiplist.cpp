//
// Created by Kaib Cropley on 5/7/2018.
// Last edited by Kaib Cropley on 5/13/2018.
//

#include <iostream>
#include <climits>
#include "skiplist.h"

// Constructor - creates rear and front guards
SkipList::SkipList(int depth) : depth{depth} {
	frontGuards = new SNode *[depth];
	rearGuards = new SNode *[depth];

	frontGuards[0] = new SNode(INT_MIN);
	rearGuards[0] = new SNode(INT_MAX);
	frontGuards[0]->next = rearGuards[0];
	rearGuards[0]->prev = frontGuards[0];

	for (int i{1}; i < depth; i++) {
		// Create nodes
		frontGuards[i] = new SNode(INT_MIN);
		rearGuards[i] = new SNode(INT_MAX);

		// Set nodes down level
		frontGuards[i]->downLevel = frontGuards[i - 1];
		rearGuards[i]->downLevel = rearGuards[i - 1];

		// Set last nodes up level
		frontGuards[i - 1]->upLevel = frontGuards[i];
		rearGuards[i - 1]->upLevel = rearGuards[i];

		// Set nodes next and prev
		frontGuards[i]->next = rearGuards[i];
		rearGuards[i]->prev = frontGuards[i];
	}
	srand(static_cast<unsigned int>(time(0)));
}

// Destructor
SkipList::~SkipList() {
	SNode *curr = frontGuards[0]->next;
	SNode *nextNode;
	while (curr != rearGuards[0]) {
		nextNode = curr->next;
		this->Remove(curr->data);
		curr = nextNode;
	}
	for (int i{0}; i < depth; i++) {
		delete frontGuards[i];
		delete rearGuards[i];
	}
	delete[] frontGuards;
	delete[] rearGuards;
}

// Used to print out skip list
std::ostream &operator<<(std::ostream &os, const SkipList &list) {
	SNode *curr = nullptr;
	for (int i{list.depth - 1}; i >= 0; i--) {
		os << "Level: " << i << " -- ";
		curr = list.frontGuards[i];
		while (curr != nullptr) {
			os << curr->data << ", ";
			curr = curr->next;
		}
		os << std::endl;
	}
	return os;
}

// return true if successfully added, no duplicates
bool SkipList::Add(int data) {
	int level{0};
	SNode *newNode = new SNode(data);

	if (!findSpotAndAdd(newNode, level)) {
		return false;
	}

	SNode *lowerNode = newNode;
	while (alsoHigher() && level < depth) {
		SNode *newHigherNode = new SNode(data);
		newHigherNode->downLevel = lowerNode;
		lowerNode->upLevel = newHigherNode;
		findSpotAndAdd(newHigherNode, level);
	}
	return true;
}

// return true if successfully removed
bool SkipList::Remove(int data) {
	if (!this->Contains(data)) {
		return false;
	}
	int level{depth - 1};
	SNode *curr;
	while (level >= 0) {
		curr = frontGuards[level];
		while (curr != nullptr) {
			if (curr->data == data) {
				SNode *next = curr->next;
				SNode *prev = curr->prev;
				next->prev = prev;
				prev->next = next;
				delete curr;
				curr = next;
			}
			curr = curr->next;
		}
		level--;
	}
	return true;
}

// return true if found in
bool SkipList::Contains(int data) {
	SNode *curr = frontGuards[depth - 1]->next;
	for (int i{depth - 1}; i >= 0; i--) {
		bool checkLevel = true;
		while (checkLevel) {
			if (curr == nullptr || curr == rearGuards[0]) {
				return false;
			}
			if (curr->data == data) {
				return true;
			}
			if (curr->data > data) {
				curr = curr->prev;
				curr = curr->downLevel;
				checkLevel = false;
			} else {
				curr = curr->next;
			}

		}
	}
	return false;
}

// Adds a new node before the current node
void SkipList::addBefore(SNode *newNode, SNode *curNode) {
	newNode->prev = curNode->prev;
	newNode->next = curNode;
	curNode->prev->next = newNode;
	curNode->prev = newNode;
}

// 50% it returns true or false
bool SkipList::alsoHigher() const {
	return rand() % 2 == 1;
}

// Will add a node to given level and increase level by one.
// Returns false if is already in list.
bool SkipList::findSpotAndAdd(SNode *newNode, int &level) {
	SNode *curr = frontGuards[level];

	while (curr->data < newNode->data) {
		curr = curr->next;
		if (curr->data == newNode->data) {
			return false;
		}
	}
	addBefore(newNode, curr);
	level++;
	return true;
}
