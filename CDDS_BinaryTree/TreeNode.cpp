#include "TreeNode.h"
#include <iostream>
#include "raylib.h"

TreeNode::TreeNode(int value)
{
	m_value = value;
}

void TreeNode::draw(int x, int y, bool selected)
{
	//Creates an array to store the value converted to a string
	static char buffer[10];

	//Converts the value given to a string and stores it in the buffer
	sprintf(buffer, "%d", m_value);

	//Draws outer circle of a node
	DrawCircle(x, y, 30, YELLOW);

	//If the node is selected, the color is green. If not selected, color is black
	if (selected)
		DrawCircle(x, y, 28, GREEN);
	else
		DrawCircle(x, y, 28, BLACK);

	//Draws the text in the center of the node
	DrawText(buffer, x - 12, y - 12, 12, WHITE);
}