#include "Node.h"

Node::Node() : Node{ABSENT_NAME} {

}

Node::Node(const char *name) : color{ABSENT_COLOR}, name{name} {

}