//
// Created by Kaib Cropley on 5/7/2018.
// Last edited by Kaib Cropley on 5/13/2018.
//

#include "snode.h"

SNode::SNode(int data) : data{data}, upLevel{nullptr}, downLevel{nullptr},
						 next{nullptr}, prev{nullptr} {

}