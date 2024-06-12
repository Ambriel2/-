#include<iostream>
using namespace std;

#include"fje.hpp"

int main(int argc,char* argv[])
{
	string path,style,icon;
	if(argc == 3)
	{
		path = argv[1];
		style = argv[2];
		icon = "normal";
	}
	else if(argc == 4)
	{
		path = argv[1];
		style = argv[2];
		icon = argv[3];
	}
	else
	{
		cout<<"Invalid input,the num of input is invalid"<<endl;
		return 0;
	}
	try
	{
		FJE fje = FJE(style);
		auto builder = fje.getBuilder();
		Container con = Container(icon);
		con.readjson(path);
		builder->draw(con);
	}
	catch (const std::exception& e) 
	{
        std::cerr << "Error: " << e.what() << std::endl;
    }
	return 0;
}
