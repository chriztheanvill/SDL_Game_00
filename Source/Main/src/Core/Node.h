#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

class Node
{
  public:
	Node(Node* parent)
		: mParent(parent)
	{
	}

	virtual ~Node( )
	{
		std::cout << "\n\n ---- NODE Destructor : " << mName;
		// std::cout << "\nDelete parent: " << mParent->mName;
		// if (mParent) delete mParent;

		if (!mChildren.empty( ))
			std::cout << "\nDelete Children: " << mChildren.capacity( );
		for (const auto& fc : mChildren)
		{
			if (std::is_pointer_v<Node>)
			{
				std::cout << "\nChild name: " << fc->mName;
				delete fc;
			}
			else
			{
				std::cout << "\nIs not a pointer, Cant be deleted!!!: "
						  << fc->mName;
			}
		}
	}

  protected:
	void SetChild(Node* node) { mChildren.emplace_back(node); }
	void SetParent(Node* node) { mParent = node; }

	void SetName(const std::string& name) { mName = name; }
	std::string GetName( ) const { return mName; }
	Node& GetChild(int index) { return *mChildren.at(index); }
	Node& GetParent( ) const { return *mParent; }

	void Log( ) const { std::cout << "\n\nLog: " << mName << "\n"; }
	void LogComplete( ) const
	{
		std::cout << "\n\nLog-Complete: " << mName	 //
				  << "\nParent: " << mParent->mName;

		std::cout << "\nChildren: " << mChildren.capacity( );
		for (const auto& fc : mChildren)
		{
			std::cout << "\nChild name: " << fc->mName;
		}
	}

  private:
	std::string mName;
	std::vector<Node*> mChildren;
	Node* mParent;
};

#endif	 // NODE_H
