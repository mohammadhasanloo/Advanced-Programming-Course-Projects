#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Car
{
public:
	Car(int Car_Id, int Luxury_Coefficient);

	int get_luxury_coefficient() { return luxury_coefficient; }
	int get_car_id() { return car_id; }
private:
	int car_id;
	int luxury_coefficient;
};

class Worker
{
public:
	Worker(int Time_Coefficient, int Worker_Id, bool Free, int Time_Left, int Car_Work_On_Id);

	void change_worker_info(int lux_coefficient, bool Free, int Car_Id);
	void print_worker_info(int luxury_coefficient);
	void decrease_one_sec() { time_left--; }

	int get_car_work_on_id() { return car_work_on_id; }
	int get_worker_id() { return worker_id; }
	int get_time_left() { return time_left; }
	bool get_free() { return free; }
private:
	int worker_id;
	int time_coefficient;
	bool free;
	int time_left;
	int car_work_on_id;
};

class Stage
{
public:
	Stage(vector<string> SeparatedInput, int& WorkerNum, int StageNum, bool Free_Worker);

	void add_car_to_waiting_car(Car transmission_car) { WaitingCars.push_back(transmission_car); };
	Car get_free_car(int WorkerNum, Car transmission_car);
	Car take_waiting_car() { return WaitingCars[0]; }
	void erase_waiting_car() { WaitingCars.erase(WaitingCars.begin()); };
	Car decrease_time(bool& existence_transmission_car, Car transmission_car);
	void add_waiting_car_to_worker(Car car);
	void show_stage_info(int StageNum);
	void print_waiting_cars();

	vector<Car> get_WaitingCars() { return WaitingCars; }
	int get_WaitingCarsSize() { return WaitingCars.size(); }
	bool get_free_worker() { return free_worker; }
private:
	vector<Car> WaitingCars;
	vector<Car> WashingCars;
	vector<Worker> Workers;
	bool free_worker;
	int stage_id;
};

class Carwash
{
public:
	void add_new_car(int CarNum, int lux_coefficient) { NewCars.push_back(Car(CarNum, lux_coefficient)); }
	vector<string> separate(string input, char character);
	void move_car_to_next_stage(int StageNum);
	void print_finished_car();
	void show_carwash_info();
	void advance_one_sec();
	void print_new_cars();
	void finish_program();
	void start_program();
	void advance_time();
	void add_stage();
	void add_car();
private:
	vector<Stage> Stages;
	vector<Car> FinishedCars;
	vector<string> SeparatedInput;
	vector<Car> NewCars;
	string input;
	int WorkerNum=0;
	int StageNum=0;
	int CarNum=0;
	int Time=0;
};


Worker::Worker(int Time_Coefficient, int Worker_Id, bool Free, int Time_Left, int Car_Work_On_Id)
{
	worker_id = Worker_Id;
	time_coefficient = Time_Coefficient;
	free = Free;
	time_left = Time_Left;
	car_work_on_id = Car_Work_On_Id;
}

Stage::Stage(vector<string> SeparatedInput, int& WorkerNum, int StageNum, bool Free_Worker)
{
	free_worker = Free_Worker;
	stage_id = StageNum;

	for (int i = 0; i < stoi(SeparatedInput[1]); i++)
	{
		Workers.push_back(Worker(stoi(SeparatedInput[i + 2]), WorkerNum, true, -1, -1));
		WorkerNum++;
	}
}

Car::Car(int Car_Id, int Luxury_Coefficient)
{
	car_id = Car_Id;
	luxury_coefficient = Luxury_Coefficient;
}



void Carwash::add_stage()
{
	Stages.push_back(Stage(SeparatedInput, WorkerNum, StageNum, true));
	StageNum++;
	cout << "OK" << endl;
}

void Carwash::show_carwash_info()
{
	print_new_cars();
	for (int i = 0; i < Stages.size(); i++)
		Stages[i].show_stage_info(i);
	print_finished_car();
}

void Carwash::add_car()
{
	add_new_car(CarNum, stoi(SeparatedInput[1]));
	CarNum++;
	cout << "OK" << endl;
}

void Carwash::finish_program()
{
	while (CarNum != FinishedCars.size())
		advance_one_sec();
	cout << "OK" << endl;
}

void Carwash::advance_time()
{
	for (int i = 0; i < stoi(SeparatedInput[1]); i++)
		advance_one_sec();
	cout << "OK" << endl;
}

void Carwash::start_program()
{
	while (getline(cin,input))
	{
		SeparatedInput = separate(input, ' ');

		if (SeparatedInput[0] == "add_stage")
			add_stage();

		else if (SeparatedInput[0] == "add_car")
			add_car();

		else if (SeparatedInput[0] == "advance_time")
			advance_time();

		else if (SeparatedInput[0] == "show_stage_info")
			Stages[stoi(SeparatedInput[1])].show_stage_info(stoi(SeparatedInput[1]));

		else if (SeparatedInput[0] == "show_carwash_info")
			 show_carwash_info();

		else if (SeparatedInput[0] == "finish")
			finish_program();
	}
}

void Carwash::print_finished_car()
{
	cout << "Cars finished:" << endl;
	for (int i = 0; i < FinishedCars.size(); i++)
	{
		cout << "Car ID: " << FinishedCars[i].get_car_id() << endl;
		cout << "Luxury coefficient: " << FinishedCars[i].get_luxury_coefficient() << endl;
	}
}

void Carwash::print_new_cars()
{
	cout << "Passed time: " << Time << endl;
	cout << "Cars waiting:" << endl;
	for (int i = 0; i < NewCars.size(); i++)
	{
		cout << "Car ID: " << NewCars[i].get_car_id() << endl;
		cout << "Luxury coefficient: " << NewCars[i].get_luxury_coefficient() << endl;
	}
	cout << "Stages info:" << endl;
}

vector<string> Carwash::separate(string input, char character)
{
	stringstream current(input);
	vector<string> result;

	while (current.good())
	{
		string substr;
		getline(current, substr, character);
		result.push_back(substr);
	}
	return result;
}

void Worker::print_worker_info(int luxury_coefficient)
{
	cout << "Worker ID: " << worker_id << endl;
	if (free)
		cout << "Free" << endl;
	else
	{
		cout << "Car ID: " << car_work_on_id << endl;
		cout << "Luxury coefficient: " << luxury_coefficient << endl;
		cout << "Time left: " << time_left << endl;
	}
}

void Stage::show_stage_info(int StageNum)
{
	cout << "Stage ID: " << StageNum << endl;

	int luxury_coefficient = -1;
	int car_work_on = -1;
	for (int i = 0; i < Workers.size(); i++)
	{
		car_work_on = Workers[i].get_car_work_on_id();
		for (int j = 0; j < WashingCars.size(); j++)
		{
			if (car_work_on == WashingCars[j].get_car_id())
			{
				luxury_coefficient = WashingCars[j].get_luxury_coefficient();
				break;
			}
		}
		Workers[i].print_worker_info(luxury_coefficient);
	}

	cout << "Cars in waiting queue:" << endl;
	print_waiting_cars();
}

void Stage::print_waiting_cars()
{
	for (int i = 0; i < WaitingCars.size(); i++)
	{
		cout << "Car ID: " << WaitingCars[i].get_car_id() << endl;
		cout << "Luxury coefficient: " << WaitingCars[i].get_luxury_coefficient() << endl;
	}
}

void Worker::change_worker_info(int lux_coefficient, bool Free, int Car_Id)
{
	free = Free;
	time_left = lux_coefficient * time_coefficient;
	car_work_on_id = Car_Id;
}

void Stage::add_waiting_car_to_worker(Car car)
{
	for (int i = 0; i < Workers.size(); i++)
	{
		if (Workers[i].get_free())
		{
			if (i == (Workers.size() - 1))
				free_worker = false;

			Workers[i].change_worker_info(car.get_luxury_coefficient(), false, car.get_car_id());
			WashingCars.push_back(car);
			break;
		}
	}
}

Car Stage::get_free_car(int WorkerNum,Car transmission_car)
{
	for (int j = 0; j < WashingCars.size(); j++)
	{
		if (WashingCars[j].get_car_id() == Workers[WorkerNum].get_car_work_on_id())
		{
			transmission_car = WashingCars[j];
			WashingCars.erase(WashingCars.begin() + j);
			Workers[WorkerNum].change_worker_info(-1, true, -1);
			if (!free_worker)
				free_worker = true;
			break;
		}
	}
	return transmission_car;
}

Car Stage::decrease_time(bool& existence_transmission_car, Car transmission_car)
{
	for (int i = 0; i < Workers.size(); i++)
	{
		if (Workers[i].get_time_left() == 0)
		{
			transmission_car = get_free_car(i, transmission_car);
			existence_transmission_car = true;
			break;
		}
	}

	for (int i = 0; i < Workers.size(); i++)
	{
		if (Workers[i].get_time_left() > 0)
			Workers[i].decrease_one_sec();
	}
	return transmission_car;
}

void Carwash::move_car_to_next_stage(int StageNumber)
{
	Car transmission_car(Car(-1, -1));
	bool existence_transmission_car = false;
	transmission_car=Stages[StageNumber].decrease_time(existence_transmission_car, transmission_car);
	if (existence_transmission_car)
	{
		if (StageNumber != (Stages.size() - 1))
			Stages[StageNumber + 1].add_car_to_waiting_car(transmission_car);
		else
			FinishedCars.push_back(transmission_car);
	}
}

void Carwash::advance_one_sec()
{
	for (int i = 0; i < Stages.size(); i++)
		move_car_to_next_stage(i);

	for (int i = 0; i < NewCars.size(); i++)
	{
		Stages[0].add_car_to_waiting_car(NewCars[0]);
		NewCars.erase(NewCars.begin());
	}

	for (int i = 0; i < Stages.size(); i++)
	{
		if ((Stages[i].get_free_worker()) && (Stages[i].get_WaitingCarsSize() > 0))
		{
			Stages[i].add_waiting_car_to_worker(Stages[i].take_waiting_car());
			Stages[i].erase_waiting_car();
		}
	}

	Time++;
}

int main()
{
	Carwash Pipeline;
	Pipeline.start_program();
	return 0;
}