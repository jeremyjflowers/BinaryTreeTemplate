#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
	delete(m_root);
}

void BinaryTree::insert(int value)
{
	//If the tree is empty, set the root to be a new node with the given value.
	if (isEmpty())
	{
		m_root = new TreeNode(value);
	}

	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	TreeNode* currentNode;
	currentNode = m_root;
	//Create a TreeNode pointer that will act as an iterator pointing to the parent of the current node and set it to the root.
	TreeNode* parentNode;
	parentNode = m_root;

	//Loop until the the current node iterator reaches a nullptr.
	if(currentNode)
	{
		//Check if the value we want to add to the tree is less than the value at the current node.
		if (currentNode->hasLeft())
		{
			//Set the parent node to be the current node before the current node moves positions.
			parentNode = currentNode;
			//Change the current node to be the child to its left and continue.
			currentNode->getLeft();
		}

		//Check if the value we want to add to the tree is greater than the value at the current node.
		if (currentNode->hasRight())
		{
			//Set the parent node to be the current node before the current node moves positions.
			parentNode = currentNode;
			//Change the current node to be the child to its right and continue.
			currentNode->getRight();
		}

		//If the value is the same as a value already in the list return 
		if (currentNode->getData() == value)
		{
			return;
		}
	}
	//end loop

	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	if (parentNode->getData() < value)
	{
		parentNode->setLeft(currentNode);
	}
	//Otherwise, insert the value to the right.
	else
	{
		parentNode->setRight(currentNode);
	}
}

void BinaryTree::remove(int value)
{
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	TreeNode* currentNode;
	//and another to hold a reference to its parent.
	TreeNode* parentNode;

	//Try to find the node that matches the value given and its parent in the tree.
	findNode(value, currentNode, parentNode);

	//If the node cannot be found return.
	if (!currentNode)
	{
		return;
	}

	//Check to see if the node has a right
	if(currentNode->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		TreeNode* iterator1;
		TreeNode* iterator2{};

		//Set the first iterator to point to the right child of the node we want to remove.
		iterator1 = currentNode->getRight();

		//Loop while the first iterator has a value to its left.
		while (iterator1->hasLeft() == value)
		{
			//Set the second iterator to be the value of the first iterator.
			iterator2 = iterator1;
			//Set the first iterator to be the value to the left of it
			iterator1->setLeft(iterator1);
		}
		//end loop

		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		currentNode->setData(iterator1->getData());

		//Check if the second iterator has a left child.
		if (iterator2->hasLeft())
		{
			//Check if the left child stores the same data as the node we wanted to remove.
			if (iterator2->getLeft() == currentNode)
			{
				//Set the second iterators left child to be the first iterators right child.
				iterator1->setRight(iterator2->getLeft());
			}
		}

		//Check if the second iterator has a right child.
		if (iterator2->hasRight())
		{
			//Check if the right child contains the same data as the node we want to remove.
			if (iterator2->getRight() == currentNode)
			{
				//Set the right child of the second iterator to be the right child of the first iterator.
				iterator1->setRight(iterator2->getRight());
			}
		}

		//Delete the first iterator
		delete(iterator1);
	}

	//Otherwise, if the node doesn't have a right child
	else if (!currentNode->hasRight())
	{
		//check if the parent of the node to remove has a left child.
		if (parentNode->hasLeft())
		{
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (parentNode->getLeft() == currentNode)
			{
				//Set the left child of the parent node to be the left child of the node to remove.
				currentNode->setLeft(parentNode->getLeft());
			}
		}

		//Check if the parent of the node to remove has a right child.
		if (parentNode->hasRight())
		{
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (parentNode->getRight() == currentNode)
			{
				//Set the right child of the parent node to be the left child of the node to remove.
				currentNode->setLeft(parentNode->getRight());
			}
		}

		//Check if the node we want to remove is the root.
		if (currentNode = m_root)
		{
			//Set the root to be its left child.
			currentNode->setLeft(m_root);
		}

		//Delete the pointer that points to the node to remove.
		delete(currentNode);
	}
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* iterator{};
	//Loop through the tree while the iterator isn't nullptr.
	while (iterator != nullptr)
	{
		//Check if the node has the data we want
		if (iterator->getData() == value)
		{
			//Return the iterator
			return iterator;
		}
		//If the node doesn't have the data we want, check to see if it's higher in value.
		else if (iterator->getData() > value)
		{
			//Set the iterator to be its current right child.
			iterator->setRight(iterator);
		}
		//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (iterator->getData() < value)
		{
			//Set the iterator to be its current left child.
			iterator->setLeft(iterator);
		}
	}
	//end loop

	//Return nullptr
	return nullptr;
}

void BinaryTree::draw(TreeNode* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	//Create two iterators: one that will point to the current node to compare the search value to,
	TreeNode* iterator1{};
	//and the other to hold a reference to the parent.
	TreeNode* iterator2{};

	//Loop while the current node iterator isn't nullptr/
	while (iterator1 != nullptr)
	{
		//Check if the search value is the same as the current nodes data.
		if (searchValue == iterator1->getData())
		{
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			nodeFound->setData(searchValue);
			nodeParent = iterator2;
			//Return true.
			return true;
		}
		//Check if the search value is greater than the value at the current node.
		if (searchValue > iterator1->getData())
		{
			//Set the parent node to be the current node.
			nodeParent = nodeFound;
			//Set the current node to be the child to the right of the current node.
			nodeParent->setRight(nodeFound);
		}
		//Check if the search value is less than the value at the current node.
		if (searchValue < iterator1->getData())
		{
			//Set the parent node to be the current node.
			nodeParent = nodeFound;
			//Set the current node to be its left child.
			nodeParent->setLeft(nodeFound);
		}
	}
	//end loop

	//Return false.
	return false;
}

void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	//Decrease the horizontal space as the nodes draw
	horizontalSpacing /= 2;

	//Checks if the current node is null
	if (currentNode)
	{
		//Draws the left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}
}
