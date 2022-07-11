#include <iostream>
#include <algorithm>
#include <list>
#include <ctime>
#include <cstdlib>
#include <eigen-3.4.0/Eigen/Dense>

class vertex{

		Eigen::Vector2i pose;
		int f;
		int g;
		int id;
		int parent_id;

	public:

		vertex(int x, int y, int n) : pose {x,y}, id {n}, f {0}, g {0} {}

		Eigen::Vector2i get_pose	() 						{return pose;}

		int		get_g	()		 	{return g;}
		void	set_g	(int x)		{g = x;}

		int		get_parent_id	()		 	{return parent_id;}
		void	set_parent_id	(int x)		{parent_id = x;}

		int		get_id	()		 	{return id;}
		void	set_id	(int x)		{id = x;}

		int	get_f	()			{return f;}
		void	set_f	(int x)	{f = x;}

		bool operator == (vertex op) {return (pose == op.pose);}
		bool operator != (vertex op) {return (pose != op.pose);}
		bool operator > (vertex op) {return f > op.f;}
		bool operator < (vertex op) {return f < op.f;}
		bool operator > (int op) {return f > op;}
		bool operator < (int op) {return f < op;}
};

/*class a_star{

	Eigen::MatrixXi map;
	int id;
	vertex start;
	vertex end;

	void map_init()
	{
		map = Eigen::MatrixXi();
	    map <<	Eigen::MatrixXi::Ones(1,10),
				Eigen::MatrixXi::Ones(8,1),
				Eigen::MatrixXi::Zero(8,8),
				Eigen::MatrixXi::Ones(8,1),
				Eigen::MatrixXi::Ones(1,10);

	    //add obstacles
	    for(int i = 2; i <= 7; ++i) {	map(i,5) = 1;	}
	    for(int i = 3; i <= 5; ++i) {	map(2,i) = 1;	}
	    for(int i = 3; i <= 5; ++i) {	map(7,i) = 1;	}

	    //add start and end position	

		start.set_f (std::abs(end.get_pose().x() - start.get_pose().x())
				   + std::abs(end.get_pose().y() - start.get_pose().y())); 

		map(start.get_pose().x(),start.get_pose().y()) = 100;
		map(end.get_pose().x(),end.get_pose().y()) = -200;

	}
public:
	a_star(const vertex s, const vertex e) : start {s}, end {e}
	{

	}


};*/



void process_vertex (vertex *current, std::list<vertex>::iterator current_1, vertex *end, int g, 
	std::list<vertex> *open_list, std::list<vertex> *close_list, Eigen::MatrixXi map)
{
	if ((map(current->get_pose().x(), current->get_pose().y()) != 1) && 
		(std::find(close_list->begin(), close_list->end(), *current) == close_list->end()))
	{
		auto temp = std::find(open_list->begin(), open_list->end(), *current);
		int f = g + std::abs(end->get_pose().x() - current->get_pose().x())
					+ std::abs(end->get_pose().y() - current->get_pose().y());
		current->set_g(g);
		current->set_f(f);
		current->set_parent_id(current->get_id());
		if (temp == open_list->end())
		{
			open_list->push_back(*current);
		} else if (*temp > f)
		{
			open_list->erase(temp);
			open_list->push_back(*current);
		}
	}	
}

main()
{
    //create a map
    Eigen::MatrixXi map (10,10);
    map <<	Eigen::MatrixXi::Ones(1,10),
    		Eigen::MatrixXi::Ones(8,1),
    		Eigen::MatrixXi::Zero(8,8),
    		Eigen::MatrixXi::Ones(8,1),
    		Eigen::MatrixXi::Ones(1,10);

    //add obstacles
    for(int i = 2; i <= 7; ++i) {	map(i,5) = 1;	}
    for(int i = 3; i <= 5; ++i) {	map(2,i) = 1;	}
    for(int i = 3; i <= 5; ++i) {	map(7,i) = 1;	}

    //add start and end position	
    int id = 0;
	vertex start (3,1, id);
	vertex end (8,8,++id);
	start.set_f (std::abs(end.get_pose().x() - start.get_pose().x())
			   + std::abs(end.get_pose().y() - start.get_pose().y())); 

	map(start.get_pose().x(),start.get_pose().y()) = 100;
	map(end.get_pose().x(),end.get_pose().y()) = -200;

	//create lists
	std::list<vertex> open_list;
	std::list<vertex> close_list;

	// add starting point
	open_list.push_back(start);

	//algorithm
	while(std::find(open_list.begin(), open_list.end(), end) == open_list.end())
	{
		auto current = std::min_element(open_list.begin(),open_list.end());
		int g = (*current).get_g() + 1;
		
		vertex current_1((*current).get_pose().x()+1,(*current).get_pose().y(),++id);		
		if ((map(current_1.get_pose().x(), current_1.get_pose().y()) != 1) && 
			(std::find(close_list.begin(), close_list.end(), current_1) == close_list.end()))
		{
			auto temp = std::find(open_list.begin(), open_list.end(), current_1);
			int f = g + std::abs(end.get_pose().x() - current_1.get_pose().x())
						+ std::abs(end.get_pose().y() - current_1.get_pose().y());
			current_1.set_g(g);
			current_1.set_f(f);
			current_1.set_parent_id((*current).get_id());
			if (temp == open_list.end())
			{
				open_list.push_back(current_1);
			} else if (*temp > f)
			{
				open_list.erase(temp);
				open_list.push_back(current_1);
			}
		}

		vertex current_2((*current).get_pose().x(),(*current).get_pose().y()+1,++id);		
		if ((map(current_2.get_pose().x(), current_2.get_pose().y()) != 1) && 
			(std::find(close_list.begin(), close_list.end(), current_2) == close_list.end()))
		{
			auto temp = std::find(open_list.begin(), open_list.end(), current_2);
			int f = g + std::abs(end.get_pose().x() - current_2.get_pose().x())
						+ std::abs(end.get_pose().y() - current_2.get_pose().y());
			current_2.set_g(g);
			current_2.set_f(f);
			current_2.set_parent_id((*current).get_id());;
			if (temp == open_list.end())
			{
				open_list.push_back(current_2);
			} else if (*temp > f)
			{
				open_list.erase(temp);
				open_list.push_back(current_2);
			}
		}

		vertex current_3((*current).get_pose().x(),(*current).get_pose().y()-1,++id);		
		if ((map(current_3.get_pose().x(), current_3.get_pose().y()) != 1) && 
			(std::find(close_list.begin(), close_list.end(), current_3) == close_list.end()))
		{
			auto temp = std::find(open_list.begin(), open_list.end(), current_3);
			int f = g + std::abs(end.get_pose().x() - current_3.get_pose().x())
						+ std::abs(end.get_pose().y() - current_3.get_pose().y());
			current_3.set_g(g);
			current_3.set_f(f);
			current_3.set_parent_id((*current).get_id());;
			if (temp == open_list.end())
			{
				open_list.push_back(current_3);
			} else if (*temp > f)
			{
				open_list.erase(temp);
				open_list.push_back(current_3);
			}
		}

		vertex current_4((*current).get_pose().x()-1,(*current).get_pose().y(),++id);		
		if ((map(current_4.get_pose().x(), current_4.get_pose().y()) != 1) && 
			(std::find(close_list.begin(), close_list.end(), current_4) == close_list.end()))
		{
			auto temp = std::find(open_list.begin(), open_list.end(), current_4);
			int f = g + std::abs(end.get_pose().x() - current_4.get_pose().x())
						+ std::abs(end.get_pose().y() - current_4.get_pose().y());
			current_4.set_g(g);
			current_4.set_f(f);
			current_4.set_parent_id((*current).get_id());;
			if (temp == open_list.end())
			{
				open_list.push_back(current_4);
			} else if (*temp > f)
			{
				open_list.erase(temp);
				open_list.push_back(current_4);
			}
		}

		close_list.push_back(*current);
		map((*current).get_pose().x(),(*current).get_pose().y()) = (*current).get_f();
		open_list.erase(current);
	}

	std::list<vertex>::iterator iter = std::find(open_list.begin(), open_list.end(), end);

	std::list<vertex> path;
	path.push_back(*iter);

	while (iter->get_id() != start.get_id())	
	{
		std::list<vertex>::iterator it = close_list.begin();

		while (iter->get_parent_id() != it->get_id())	
		{
		 	it++;
		}
		iter = it;
		path.push_back(*iter);
		map(iter->get_pose().x(), iter->get_pose().y()) *= -1;
	}

	std::cout << map << std::endl;
	std::cout << "runtime = " << float(clock())/CLOCKS_PER_SEC << std::endl;
}