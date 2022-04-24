#include <iostream>
#include <list>
#include <eigen-3.4.0/Eigen/Dense>

class vertex{
	Eigen::Vector2i pose;
	int g;
	int f;
	Eigen::Vector2i parent;
	//int id;
	//int parent_id;
public:
	vertex(int x, int y) : pose{x,y}, g {0}, f{0} {}
	int get_g() {return g;}
	Eigen::Vector2i get_pose () {return pose;}

	bool operator == (vertex op) {return pose == op.get_pose();}
};


main()
{
	Eigen::MatrixXi map(10,10);
	map << Eigen::MatrixXi::Ones(1,10),
			Eigen::MatrixXi::Ones(8,1),
			Eigen::MatrixXi::Zero(8,8),
			Eigen::MatrixXi::Ones(8,1),
			Eigen::MatrixXi::Ones(1,10);
	for(int i =2;i<=7; ++i) {map(i,5) = 1; }
	for(int i =3;i<=5; ++i) {map(2,i) = 1; }
	for(int i =3;i<=5; ++i) {map(7,i) = 1; }

	vertex start (3,1);
	vertex end (5,7);

	map(start.get_pose().x(), start.get_pose().y()) = 100;
	map(end.get_pose().x(), end.get_pose().y()) = -200;

	std::list<vertex> open_list;
	std::list<vertex> close_list;

	open_list.push_back(start);

	while(std::find(open_list.begin(),open_list.end(), end) == open_list.end())
	{
		open_list.push_back(end);
	}
	
	std::cout<<std::abs(start.get_g())<<std::endl;

	auto it_start = std::find(open_list.begin(),open_list.end(), start);

	open_list.erase(it_start);


	std::cout << map;
}