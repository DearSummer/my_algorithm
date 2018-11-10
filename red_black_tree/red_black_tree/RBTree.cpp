#include "RBTree.h"
#include <iostream>


/*
 * 左旋操作
 * 
 *     p                         p
 *    /                         /
 *   n         ------>         y
 *  / \                       / \
 * ln  y                     n  ry
 *    / \                   / \
 *   ly ry                 ln ly
 */
void RBTree::leftRotation(RBNode * n)
{
	RBNode * y = n->right;
	n->right = y->left;

	if (y->left != nullptr)
		y->left->parent = n;

	y->parent = n->parent;

	if (n->parent == nullptr)
		root = y;
	else
	{
		if (n->parent->left == n)
			n->parent->left = y;
		else
			n->parent->right = y;
	}

	y->left = n;
	n->parent = y;
}

/*
 * 右旋操作
 * 
 *       p                                    p  
 *      /                                    /
 *     n            ------------>           y
 *    / \                                  /  \
 *   y   rn                               ly   n
 *  / \                                       / \
 * ly ry                                     ry  rn
 */
void RBTree::rightRotation(RBNode * n)
{
	RBNode * y = n->left;
	n->left = y->right;

	if (y->right != nullptr)
		y->right->parent = n;

	y->parent = n->parent;
	if (n->parent == nullptr)
		root = y;
	else
	{
		if (n->parent->right == n)
			n->parent->right = y;
		else
			n->parent->left = y;
	}

	y->right = n;
	n->parent = y;
}

void RBTree::insert(RBNode * n)
{
	//前面的插入操作和平衡二叉树一样

	RBNode * current = nullptr;
	RBNode * x = root;

	while (x != nullptr)
	{
		current = x;
		if (x->value < n->value)
			x = x->right;
		else
			x = x->left;
	}

	n->parent = current;

	if (current == nullptr)
		root = n;
	else
	{
		if (current->value < n->value)
			current->right = n;
		else
			current->left = n;
	}

	//插入完成之后,就要调整红黑树的颜色了(因为插入操作有可能破坏了红黑树的平衡)
	insertFixUp(n);

}

void RBTree::insertFixUp(RBNode * n)
{
	// 父亲节点和祖父节点
	RBNode * parent;

	//需要调整的树的条件 : 父亲节点存在且父亲节点是红色的
	while((parent = n->parent) != nullptr && parent->red )
	{
		//获取祖父节点
		RBNode * grandfather = parent->parent;

		//若父节点是祖父节点的左节点
		if (parent == grandfather->left)
		{
			RBNode * uncle = grandfather->right;

			//case 1 : 叔叔节点也是红色的
			if (uncle != nullptr && uncle->red)
			{
				//将父亲和叔叔节点涂黑
				parent->red = false;
				uncle->red = false;

				//把祖父节点涂红
				grandfather->red = true;

				//将节点放置成祖父节点
				n = grandfather;

				continue;
			}

			//case 2 : 叔叔节点是黑色的,而且当前节点是右节点
			if (n == parent->right && uncle != nullptr && !uncle->red)
			{
				//从父节点处左旋
				leftRotation(parent);

				//将父节点和自己调换一遍
				RBNode * temp = parent;
				parent = n;
				n = temp;
			}

			//case 3 : 叔叔节点是黑色,且当前节点是左节点
			parent->red = false;
			grandfather->red = true;
			rightRotation(grandfather);

		}
		else
		{
			//右节点和左节点的操作是一样的
			RBNode * uncle = grandfather->left;
			if(uncle != nullptr && uncle->red)
			{
				parent->red = false;
				uncle->red = false;
				grandfather->red = true;
				n = grandfather;
				continue;
			}

			if(n == parent->left)
			{
				rightRotation(parent);
				RBNode * temp = parent;
				parent = n;
				n = temp;
			}

			parent->red = false;
			grandfather->red = true;
			leftRotation(grandfather);
		}

	}

	root->red = false;
}

RBNode * RBTree::maxNode(RBNode * tree)
{
	if (tree == nullptr)
		return nullptr;

	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

RBNode * RBTree::minNode(RBNode * tree)
{
	if (tree == nullptr)
		return nullptr;

	while (tree->left != nullptr)
		tree = tree->left;

	return tree;
}

RBNode * RBTree::search(RBNode * tree,int target)
{
	while(tree != nullptr)
	{
		const int value = tree->value - target;
		if (value < 0)
		{
			tree = tree->right;
		}
		else if (value > 0)
		{
			tree = tree->left;
		}
		else
			return tree;
	}

	return nullptr;
}

void RBTree::remove(RBNode * node)
{
	RBNode * child;
	RBNode * parent;
	bool red;

	//case 1 : 被删除的节点的左右节点都不为空的情况
	if(node->left != nullptr && node->right != nullptr)
	{
		//先找出被删除节点的后继节点,使用它来代替自己
		RBNode * replace = node;

		//1:获取后继节点
		replace = replace->right;
		while (replace->left != nullptr)
			replace = replace->left;

		//2:处理后继节点与被删除节点的父节点的关系
		if(node->parent != nullptr)
		{
			if (node == node->parent->left)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
		{
			root = replace;
		}

		//3:处理后继节点的子节点与被删除节点的字节的之间的关系
		child = replace->right; // 后继节点不存在左节点(步骤1时已经找到最左的节点了)
		parent = replace->parent;
		red = replace->red;

		//若被删除节点是后继节点的父节点
		if(parent == node)
		{
			parent = replace;
		}
		else {
			if (child != nullptr)
				child->parent = parent;

			parent->left = child;
			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->red = node->red;
		replace->left = node->left;

		node->left->parent = replace;

		//若被删除的节点仍然是红色的那么性质不变,否则就需要重新修正红黑树
		if (!red)
			removeFixUp(child, parent);

		delete node;
		node = nullptr;
		return;
	}

	//case 2 :被删除节点没有子节点,直接删除这个节点
	if (node->left == nullptr || node->right == nullptr)
	{
		child = node->left;
		parent = node->parent;
		if (node->parent->left == node)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;


		delete node;
		node = nullptr;

		return;
	}

	//case 3 : 被删除节点有唯一子节点
	if(node->left != nullptr)
	{
		child = node->left;
		parent = node->parent;
		child->parent = parent;
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
	{
		child = node->right;
		parent = node->parent;

		child->parent = parent;
		if (parent->right == node)
			parent->right = child;
		else
			parent->right = child;
	}

	removeFixUp(child, parent);

	delete node;
	node = nullptr;
}

void RBTree::removeFixUp(RBNode * node, RBNode * parent)
{
	//other 是node的兄弟节点
	RBNode *  other;
	while((node == nullptr || !node->red) && node != root)
	{
		//若是左节点,else 则是相反
		if(parent->left == node)
		{
			other = parent->right;
			//case 1 :  node的兄弟节点是红色的
			if(other->red)
			{
				other->red = false;
				parent->red = true;
				leftRotation(parent);
				other = parent->right;
			}

			//case 2 : other 是黑色的,other的两个子节点也是黑色的
			if(!other->red && 
				(other->left == nullptr || !other->left->red) &&
				(other->right == nullptr || !other->right->red))
			{
				other->red = true;
				node = parent;
				parent = node->parent;
			}
			else
			{
				//若other的两个子节点,右边是黑色左边是红色
				if(other->right == nullptr || !other->right->red)
				{
					other->left->red = false;
					other->red = true;
					rightRotation(other);
					other = parent->right;
				}

				//若other是黑色,右节点是红色(左边任意颜色)
				other->red = parent->red;
				parent->red = false;
				other->right->red = false;
				leftRotation(parent);
				node = this->root;
				break;
			}
			
		}
		else
		{
			//和上面的对称
			other = parent->left;
			if(other->red)
			{
				other->red = false;
				parent->red = true;
				rightRotation(parent);
				other = parent->left;
			}

				
			if(!other->red &&
				(other->left == nullptr || !other->left->red ) &&
				(other->right == nullptr || !other->right->red))
			{
				other->red = true;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if(other->left == nullptr || !other->left->red)
				{
					other->right->red = false;
					other->red = true;
					leftRotation(other);
					other = parent->left;
				}

				other->red = parent->red;
				parent->red = false;
				other->left->red = false;
				rightRotation(parent);
				node = root;
				break;
			}
		}
	}

	if (node != nullptr)
		node->red = false;

}

void RBTree::destory(RBNode * tree)
{
	if(!tree)
		return;

	if (tree->right)
		destory(tree->right);

	if (tree->left)
		destory(tree->left);

	tree = nullptr;
}

void RBTree::perorderPrint(RBNode * tree) const
{
	if (!tree)
		return;
	std::cout << tree->toString();
	perorderPrint(tree->left);
	perorderPrint(tree->right);

}

void RBTree::midorderPrint(RBNode * tree) const
{
	if(!tree)
		return;

	midorderPrint(tree->left);
	std::cout << tree->toString();
	midorderPrint(tree->right);
}



int RBTree::maxValue() const
{
	return maxNode(root)->value;
}

int RBTree::minValue() const
{
	return minNode(root)->value;
}

void RBTree::insert(int value)
{
	RBNode * newNode = new RBNode(value, true, nullptr, nullptr, nullptr);
	insert(newNode);
}

void RBTree::remove(int value)
{
	RBNode * node;
	if((node = search(root, value)) != nullptr)
	{
		remove(node);
	}


}

void RBTree::clear() const
{
	destory(root);
}

void RBTree::perorderPrint() const
{
	perorderPrint(root);
}

void RBTree::midorderPrint() const
{
	midorderPrint(root);
}

RBTree::RBTree():root(nullptr)
{
}


RBTree::~RBTree()
{
	delete root;
}
