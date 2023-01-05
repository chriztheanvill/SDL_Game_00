#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Node
{
  public:
	Node(Node* parent = nullptr, const std::string& name = "")
		: mParent(parent)
		, mName(name)
	{
		std::cout << "\n\n  ******** Constructor : " << mName;
		if (!parent) return;
		std::cout << "\n  ***** mParent : " << mParent->mName;
		parent->AddChild(this);
	}

	virtual ~Node( )
	{
		std::cout << "\n\n ---- NODE Destructor : " << mName;
		std::cout << "\n ---- Address : " << this;

		// Delete from parent
		if (mParent)
		{
			std::cout << "\n	Parent Name: " << mParent->mName;
			// std::cout << "\n	Parent: " << mParent;

			// auto aaa = std::find_if(mParent->mChildren.begin( ),
			// 						mParent->mChildren.end( ),
			// 						[&](Node* tmp)
			// 						{
			// 							if (tmp == this)
			// 							{
			// 								std::cout << "\n	Deleting This: "
			// 										  << &tmp;
			// 								// delete tmp;
			// 								tmp = nullptr;
			// 								return true;
			// 							}
			// 							std::cout << "\n	Cant find it: ";
			// 							return false;
			// 						});

			// if (std::find(mParent->mChildren.begin( ),
			// 			  mParent->mChildren.end( ),
			// 			  this) != mParent->mChildren.end( ))
			// {
			// 	std::cout << "\n	Deleting parent: " << mParent->mName;

			std::erase(mParent->mChildren, this);	// C++20
			// }
			// else { std::cout << "\n	Cant find the parent: " <<
			// mParent->mName; }
		}

		if (mChildren.empty( )) { std::cout << "\n	Children: EMPTY \n"; }
		else
		{
			std::cout << "\n	Delete Children: " << mChildren.capacity( );
			for (Node* fc : mChildren)
			{
				// std::cout << "\n		Parent: " << mParent;
				// std::cout << "\n		Child: " << fc;
				if (fc)
				{
					std::cout << "\n		Child name: " << fc->mName;
					std::cout << "\n		Child address: " << fc;
					if (fc->mParent)
					{
						std::cout << "\n		Parent name: "
								  << fc->mParent->mName;
						// delete fc;
						// std::erase(mChildren, fc);	 // C++20
						if (fc->mParent == this)
						{
							std::cout << "\n		Delete Parent from child: "
									  << fc->mParent;
							fc->mParent = nullptr;
						}
					}
					fc = nullptr;
				}
				// else
				// {
				// 	std::cout
				// 		<< "\n		Is not a pointer, Cant be deleted!!! "
				// 		<< fc->mName;
				// }
			}
		}
	}

	std::string GetName( ) const { return mName; }
	void SetName(const std::string& name) { mName = name; }
	void AddChild(Node* node) { mChildren.emplace_back(node); }
	void SetParent(Node* node)
	{
		mParent = node;
		mParent->AddChild(this);
	}

  protected:
	Node& GetChild(int index) { return *mChildren.at(index); }
	Node& GetParent( ) const { return *mParent; }

	void NodeLog( ) const { std::cout << "\n\nLog: " << mName << "\n"; }
	void NodeLogComplete( ) const
	{
		std::cout << "\n	Log-Complete: " << mName;	//
		if (mParent) { std::cout << "\n	Parent: " << mParent->mName; }
		else { std::cout << "\n	Parent: EMPTY ---"; }

		std::cout << "\n	Children: " << mChildren.capacity( );
		for (const auto& fc : mChildren)
		{
			std::cout << "\n		Child name: " << fc->mName;
		}
	}

  private:
	std::string mName;
	std::vector<Node*> mChildren;
	Node* mParent;
};

#endif	 // NODE_H
