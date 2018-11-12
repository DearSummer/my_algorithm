#include "RBTree.h"
#include <iostream>


/*
 * ��������
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
 * ��������
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
	//ǰ��Ĳ��������ƽ�������һ��

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

	//�������֮��,��Ҫ�������������ɫ��(��Ϊ��������п����ƻ��˺������ƽ��)
	insertFixUp(n);

}

void RBTree::insertFixUp(RBNode * n)
{
	// ���׽ڵ���游�ڵ�
	RBNode * parent;

	//��Ҫ�������������� : ���׽ڵ�����Ҹ��׽ڵ��Ǻ�ɫ��
	while((parent = n->parent) != nullptr && parent->red )
	{
		//��ȡ�游�ڵ�
		RBNode * grandfather = parent->parent;

		//�����ڵ����游�ڵ����ڵ�
		if (parent == grandfather->left)
		{
			{
				 RBNode * uncle = grandfather->right;

				//case 1 : ����ڵ�Ҳ�Ǻ�ɫ��
				if (uncle && uncle->red)
				{
					//�����׺�����ڵ�Ϳ��
					parent->red = false;
					uncle->red = false;

					//���游�ڵ�Ϳ��
					grandfather->red = true;

					//���ڵ���ó��游�ڵ�
					n = grandfather;

					continue;
				}
			}

			//case 2 : ����ڵ��Ǻ�ɫ��,���ҵ�ǰ�ڵ����ҽڵ�
			if (n == parent->right /* && uncle != nullptr && !uncle->red */ )
			{
				//�Ӹ��ڵ㴦����
				leftRotation(parent);

				//�����ڵ���Լ�����һ��
				RBNode * temp = parent;
				parent = n;
				n = temp;
			}

			//case 3 : ����ڵ��Ǻ�ɫ,�ҵ�ǰ�ڵ�����ڵ�
			parent->red = false;
			grandfather->red = true;
			rightRotation(grandfather);

		}
		else
		{
			{
				//�ҽڵ����ڵ�Ĳ�����һ����
				RBNode * uncle = grandfather->left;
				if (uncle  && uncle->red)
				{
					parent->red = false;
					uncle->red = false;
					grandfather->red = true;
					n = grandfather;
					continue;
				}
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

	if (!node->right)
		child = node->left;
	else if (!node->left)
		child = node->right;
	//case 1 : ��ɾ���Ľڵ�����ҽڵ㶼��Ϊ�յ����
	else
	{
		//���ҳ���ɾ���ڵ�ĺ�̽ڵ�,ʹ�����������Լ�
		RBNode * replace = node;

		//1:��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left != nullptr)
			replace = replace->left;

		//2:�����̽ڵ��뱻ɾ���ڵ�ĸ��ڵ�Ĺ�ϵ
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

		//3:�����̽ڵ���ӽڵ��뱻ɾ���ڵ���ֽڵ�֮��Ĺ�ϵ
		child = replace->right; // ��̽ڵ㲻������ڵ�(����1ʱ�Ѿ��ҵ�����Ľڵ���)
		parent = replace->parent;
		red = replace->red;

		//����ɾ���ڵ��Ǻ�̽ڵ�ĸ��ڵ�
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

		//����ɾ���Ľڵ���Ȼ�Ǻ�ɫ����ô���ʲ���,�������Ҫ�������������
		if (!red)
			removeFixUp(child, parent);

		delete node;
		node = nullptr;
		return;
	}

	parent = node->parent;
	red = node->red;

	//case 2 :��ɾ���ڵ�û���ӽڵ�,ֱ��ɾ������ڵ�
	//case 3 : ��ɾ���ڵ���Ψһ�ӽڵ�
	//�����������һ������

	if (child)
		child->parent = parent;
	if (parent)
	{
		if (parent->right == node)
			parent->right = child;
		else
			parent->left = child;
	}
	else
		root = child;
	

	if (!red)
		removeFixUp(child, parent);

	delete node;
	node = nullptr;
}

void RBTree::removeFixUp(RBNode * node, RBNode * parent)
{
	//other ��node���ֵܽڵ�
	RBNode *  other;
	while((!node || !node->red) && node != root)
	{
		//������ڵ�,else �����෴
		if(parent->left == node)
		{
			other = parent->right;
			//case 1 :  node���ֵܽڵ��Ǻ�ɫ��
			if(other->red)
			{
				other->red = false;
				parent->red = true;
				leftRotation(parent);
				other = parent->right;
			}

			//case 2 : other �Ǻ�ɫ��,other�������ӽڵ�Ҳ�Ǻ�ɫ��
			if(/*!other->red && */ 
				(!other->left || !other->left->red) &&
				(!other->right|| !other->right->red))
			{
				other->red = true;
				node = parent;
				parent = node->parent;
			}
			else
			{
				//case 3 :��other�������ӽڵ�,�ұ��Ǻ�ɫ����Ǻ�ɫ(case 3 ��Ϊ�˽����ת��Ϊcase 4 ���н������)
				if(!other->right|| !other->right->red)
				{
					other->left->red = false;
					other->red = true;
					rightRotation(other);
					other = parent->right;
				}

				//case 4 :��other�Ǻ�ɫ,�ҽڵ��Ǻ�ɫ(���������ɫ)
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
			//������ĶԳ�
			other = parent->left;
			if(other->red)
			{
				other->red = false;
				parent->red = true;
				rightRotation(parent);
				other = parent->left;
			}

				
			if(/*!other->red && */
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

	if (node)
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

RBNode * RBTree::next(RBNode * node)
{
	RBNode * parent;
	if (!node || node->parent == node)
		return nullptr;

	/**
	 * �������ҽڵ�,��ô��һ���ڵ�һ�������ҽڵ㵱�е�����ڵ�
	 */
	if(node->right)
	{
		node = node->right;
		while (node->left)
			node = node->left;

		return node;
	}

	/**
	 * ���ýڵ㲻�����ҽڵ�
	 * ���������º�������Ҷ���ʹ�ýڵ��СԽ��ԽС,������һ���ڵ�Ӧ���Ǳȵ�ǰ�ڵ���һ����С�Ľڵ�
	 * ��������Ҫ���ϲ��������,����ǰ�ڵ����丸�׽ڵ���Һ��Ӿͼ�����,ֱ����ǰ�ڵ����丸�׽ڵ������λ��
	 * (��Ϊ����ǰ�ڵ��Ǹ��׽ڵ���Һ���˵����ǰ�ڵ�ȸ��׽ڵ��,��һ���������Ǹ��׽ڵ�����ӵ�ʱ��,������׽ڵ������һ���ڵ�)
	 */
	while ((parent = node->parent) != nullptr && node == parent->right)
		node = parent;

	return parent;
}

RBNode * RBTree::prev(RBNode * node)
{
	//Ѱ�ҷ���ͬnext
	RBNode * parent;

	if (!node || node->parent == node)
		return nullptr;

	if(node->left)
	{
		node = node->left;
		while (node->right)
			node = node->right;

		return  node;
	}


	while ((parent = node->parent) != nullptr && node == parent->left)
		node = parent;

	return parent;
}

RBNode * RBTree::getRoot() const
{
	return root;
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
