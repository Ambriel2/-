#include<memory>
#include<vector>
#include"nlohmann/json.hpp"
#include<exception>
#include<fstream>
using namespace std;
using json = nlohmann::ordered_json;
enum class icon
{
	normal,
	poker_face
};
class InvalidInputStyle : public std::exception { //处理异常输入
public:
    const char* what() const throw() 
	{
        return "Invalid input style";
    }
};
class InvalidInputIcon : public std::exception { //处理异常输入
public:
    const char* what() const throw() 
	{
        return "Invalid input icon";
    }
};
class JsonNode
{
	public:
		JsonNode(int l,bool judge,string name) : level(l), isLeaf(judge), name(name){}
		JsonNode(int l,bool judge,string name,string value) : level(l), isLeaf(judge), name(name), value(value){}
		int getLevel(){return this->level;}
		bool getIsLeaf(){return this->isLeaf;}
		string getName(){return this->name;}
		string getValue(){return this->value;}
	private:
		int level;
		bool isLeaf;
		string name;
		string value;
};
class Container
{
	public:
		Container(string input)
		{
			nodes = {};
			if(input == "poker_face")
			{
				ic = icon::poker_face;
			}
			else if(input == "normal")
			{
				ic = icon::normal;
			}
			else throw InvalidInputIcon();
		}
		void readjson(std::string path);
		icon getIcon(){return this->ic;}
		void createNodes(json jsonData,int level);
		vector<JsonNode> getNodes(){return this->nodes;}
	private:
		icon ic;
		vector<JsonNode> nodes;
};
class Builder  //抽象工厂
{
	public:
	    Builder() {}
	    virtual ~Builder() = default ;
	    virtual void draw(Container con) = 0;
};
//两种风格的工厂
class TreeBuilder : public Builder  
{
	public:
	    TreeBuilder() {}
	    void draw(Container con) override;
};

class RectBuilder : public Builder 
{
	public:
	    RectBuilder() {}
	    void draw(Container con) override;
};

class FJE {
public:
    FJE(string style) {
        if (style == "tree" || style == "Tree") 
		{
            this->builder = new TreeBuilder();
        } 
		else if (style == "rect" || style == "Rect" || style == "rectangle" || style == "Rectangle") 
		{
            this->builder = new RectBuilder();
        }
        else
        {
        	throw InvalidInputStyle();
		}
    }

    unique_ptr<Builder> getBuilder() { return unique_ptr<Builder>(this->builder); }
    
private:
    Builder* builder;
};

bool theLastLevelNode(int index,vector<JsonNode> nodes);
