#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "../Utils/Logger.h"

#include <fmt/color.h>

class Node
{
  public:
	Node(Node* parent = nullptr, std::string_view name = "")
		: mParent(parent)
		, mName(name)
	{
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::azure),
		// 		   "\n\n ******** Node Constructor : {}",
		// 		   mName);

		Logger::Debug(LogType::Log, "******** Node Constructor : ", mName);
		if (!parent) return;
		Logger::Debug(LogType::Log, "***** Node mParent : ", mParent->mName);
		parent->AddChild(this);
	}

	virtual ~Node( )
	{
		Logger::Debug(LogType::Log, "---- NODE Destructor : ", mName);
		Logger::Debug(LogType::Debug, "---- Address : ", this);
		// std::cout << "---- Address : " << this;

		// Delete from parent
		if (mParent)
		{
			Logger::Debug(LogType::Debug, "Parent Name: ", mParent->mName);
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

		if (mChildren.empty( ))
		{
			Logger::Debug(LogType::Debug, "Children: EMPTY");
		}
		else
		{
			Logger::Debug(LogType::Log,
						  "Delete Children: ",
						  mChildren.capacity( ));
			for (Node* fc : mChildren)
			{
				// std::cout << "\n		Parent: " << mParent;
				// std::cout << "\n		Child: " << fc;
				if (fc)
				{
					Logger::Debug(LogType::Debug, "Child name: ", fc->mName);
					Logger::Debug(LogType::Debug, "Child address: ", fc);
					if (fc->mParent)
					{
						Logger::Debug(LogType::Log,
									  "Parent name: {}",
									  fc->mParent->mName);
						// delete fc;
						// std::erase(mChildren, fc);	 // C++20
						if (fc->mParent == this)
						{
							Logger::Debug(LogType::Debug,
										  "Delete Parent from child: ",
										  fc->mParent);
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

	std::string_view GetName( ) const { return mName; }
	// std::string GetName( ) const { return static_cast<std::string>(mName); }
	void SetName(std::string_view name) { mName = name; }
	void AddChild(Node* node) { mChildren.emplace_back(node); }
	void SetParent(Node* node)
	{
		mParent = node;
		mParent->AddChild(this);

		// fmt::print(fmt::emphasis::bold | fg(fmt::color::azure),
		// 		   "\n--- Node::SetParent --- \n");
		// for (auto* const c : mChildren)
		// {
		// 	fmt::print("- Parent: {} - Child: {} \n", mParent->mName, c->mName);
		// }
	}

  protected:
	Node& GetChild(int index) { return *mChildren.at(index); }
	Node& GetParent( ) const { return *mParent; }

	void NodeLog( ) const { Logger::Debug(LogType::Log, "Log: ", mName); }
	void NodeLogComplete( ) const
	{
		Logger::Debug(LogType::Log, "Log-Complete: ", mName);
		if (mParent)
		{
			Logger::Debug(LogType::Log, "Parent: ", mParent->mName);
		}
		else { Logger::Debug(LogType::Log, "Parent: EMPTY ---"); }

		Logger::Debug(LogType::Log, "Children: ", mChildren.capacity( ));
		for (const auto& fc : mChildren)
		{
			Logger::Debug(LogType::Log, "Child name: ", fc->mName);
		}
	}

  private:
	std::string_view mName;
	std::vector<Node*> mChildren;
	Node* mParent;
};

#endif	 // NODE_H
