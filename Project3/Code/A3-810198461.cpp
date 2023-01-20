#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;


struct Movie
{
	string CinemaName;
	string MovieName;
	string Day;
	string StartingTime;
	string FinishingTime;
	string Price;
	string Hall;
	double Start;
	double Finish;
};

vector<string> Separator(string oneline, char character)
{
	stringstream current(oneline);
	vector<string> result;

	while (current.good())
	{
		string substr;
		getline(current, substr, character);
		result.push_back(substr);
	}
	return result;
}

map<string, int> savecolumn(vector<string>separatedline)
{
	map<string, int>column;
	column[separatedline[0]] = 0;
	column[separatedline[1]] = 1;
	column[separatedline[2]] = 2;
	column[separatedline[3]] = 3;
	column[separatedline[4]] = 4;
	column[separatedline[5]] = 5;
	column[separatedline[6]] = 6;
	return column;
}

void readfile(string oneline, vector<Movie>& Movies, int numberofline, map<string, int>column)
{
	vector<string> separatedline = Separator(oneline, ',');
	Movie OneMovie;
	for (int i = 0; i < 7; i++)
	{
		if (i == column["CinemaName"])
			OneMovie.CinemaName = separatedline[i];
		else if (i == column["MovieName"])
			OneMovie.MovieName = separatedline[i];
		else if (i == column["Day"])
			OneMovie.Day = separatedline[i];
		else if (i == column["StartingTime"])
			OneMovie.StartingTime = separatedline[i];
		else if (i == column["FinishingTime"])
			OneMovie.FinishingTime = separatedline[i];
		else if (i == column["Price"])
			OneMovie.Price = separatedline[i];
		else if (i == column["Hall"])
			OneMovie.Hall = separatedline[i];
	}
	Movies.push_back(OneMovie);
}

vector<Movie> saveinfo(string input_address, int& numberofline, map<string, int>& column)
{
	ifstream inputfileCSV(input_address);
	string oneline;
	getline(inputfileCSV, oneline);

	vector<string> separatedline = Separator(oneline, ',');
	column = savecolumn(separatedline);

	vector<Movie> Movies;
	while (getline(inputfileCSV, oneline))
	{
		readfile(oneline, Movies, numberofline, column);
		numberofline++;
	}
	return Movies;
}

vector<string> SortingMovieName(int numberofline, vector<Movie> Movies, int& SortedMoviesNum)
{
	vector<string> SortMovieName;
	SortMovieName.push_back(Movies[0].MovieName);

	for (int j = 1; j < numberofline; j++)
	{
		int Repetition = 0;
		for (int k = 0; k < (j - 1); k++)
		{
			if (Movies[j].MovieName == Movies[k].MovieName)
			{
				Repetition = 1;
				break;
			}
		}
		if (Repetition == 1)
			continue;

		SortMovieName.push_back(Movies[j].MovieName);
		SortedMoviesNum++;
	}
	sort(SortMovieName.begin(), SortMovieName.end());
	return SortMovieName;
}

void printnameofmovies(vector<string>SortMovieName, int SortedMoviesNum)
{
	for (int i = 0; i < SortedMoviesNum; i++)
	{
		cout << SortMovieName[i] << "\n";
	}
}

string checkinput(int& WrongInput, string input)
{
	vector<string> Input = Separator(input, ' ');
	string MovieName;

	if (Input.size() <= 2)
	{
		WrongInput = 1;
		return " ";
	}

	if ((Input[1] != "SCHEDULE") || (Input[0] != "GET"))
	{
		WrongInput = 1;
		return " ";
	}

	for (int i = 2; i < Input.size(); i++)
	{
		if (i != 2)
		{
			MovieName += " " + Input[i];
		}
		else if (i == 2)
		{
			MovieName = Input[i];
		}
	}
	return MovieName;
}

vector<Movie>SortRequestedMovies(vector<Movie> Movies, int numberofline, string MovieName, int& NumberOfRequestedMovie)
{
	vector<Movie>RequestedMovie;
	for (int i = 0; i < numberofline; i++)
	{
		if (MovieName == Movies[i].MovieName)
		{
			RequestedMovie.push_back(Movies[i]);
			NumberOfRequestedMovie++;
		}
	}
	return RequestedMovie;
}

double ClockToDouble(string Time)
{
	vector<string>SeparatedTime = Separator(Time, ':');

	int hour = stoi(SeparatedTime[0]);
	int min = stoi(SeparatedTime[1]);
	double result = double(hour) + (((double(min) * 100.0) / 60.0) / 100.0);
	return result;
}

void TimeConverter(vector<Movie>& RequestedMovie, int NumberOfRequestedMovie)
{
	for (int i = 0; i < NumberOfRequestedMovie; i++)
	{
		RequestedMovie[i].Start = (ClockToDouble(RequestedMovie[i].StartingTime));
		RequestedMovie[i].Finish = (ClockToDouble(RequestedMovie[i].FinishingTime));
	}
}

vector<vector<Movie> > DaySeparator(vector<Movie>RequestedMovie, int NumberOfRequestedMovie, vector<int>& NumDailyMovie)
{
	vector<vector<Movie> >SortedSchedule(7);
	for (int i = 0; i < NumberOfRequestedMovie; i++)
	{
		if (RequestedMovie[i].Day == "Saturday")
		{
			NumDailyMovie[0]++;
			SortedSchedule[0].push_back(RequestedMovie[i]);
		}
		else if (RequestedMovie[i].Day == "Sunday")
		{
			NumDailyMovie[1]++;
			SortedSchedule[1].push_back(RequestedMovie[i]);
		}
		else if (RequestedMovie[i].Day == "Monday")
		{
			NumDailyMovie[2]++;
			SortedSchedule[2].push_back(RequestedMovie[i]);
		}
		else if (RequestedMovie[i].Day == "Tuesday")
		{
			NumDailyMovie[3]++;
			SortedSchedule[3].push_back(RequestedMovie[i]);
		}
		else if (RequestedMovie[i].Day == "Wednesday")
		{
			NumDailyMovie[4]++;
			SortedSchedule[4].push_back(RequestedMovie[i]);
		}
		else if (RequestedMovie[i].Day == "Thursday")
		{
			NumDailyMovie[5]++;
			SortedSchedule[5].push_back(RequestedMovie[i]);
		}
		else if (RequestedMovie[i].Day == "Friday")
		{
			NumDailyMovie[6]++;
			SortedSchedule[6].push_back(RequestedMovie[i]);
		}
	}
	return SortedSchedule;
}

void sortbyname(vector<vector<Movie> >& ScheduledPlan, int Day, int j, int k)
{
	Movie current;
	if (ScheduledPlan[Day][j].CinemaName > ScheduledPlan[Day][k].CinemaName)
	{
		current = ScheduledPlan[Day][j];
		ScheduledPlan[Day][j] = ScheduledPlan[Day][k];
		ScheduledPlan[Day][k] = current;
	}
}

void sortbyprice(vector<vector<Movie> >& ScheduledPlan, int Day, int j, int k)
{
	Movie current;
	if (ScheduledPlan[Day][j].Price > ScheduledPlan[Day][k].Price)
	{
		current = ScheduledPlan[Day][j];
		ScheduledPlan[Day][j] = ScheduledPlan[Day][k];
		ScheduledPlan[Day][k] = current;
	}
	else if (ScheduledPlan[Day][j].Price == ScheduledPlan[Day][k].Price)
	{
		sortbyname(ScheduledPlan, Day, j, k);
	}
}

void SortSchedule(vector<int> NumDailyMovie, vector<vector<Movie> >& ScheduledPlan)
{
	Movie current;
	for (int Day = 0; Day < 7; Day++)
	{
		for (int j = 0; j < NumDailyMovie[Day]; j++)
		{
			for (int k = j + 1; k < NumDailyMovie[Day]; k++)
			{
				if (ScheduledPlan[Day][j].Start > ScheduledPlan[Day][k].Start)
				{
					current = ScheduledPlan[Day][j];
					ScheduledPlan[Day][j] = ScheduledPlan[Day][k];
					ScheduledPlan[Day][k] = current;
				}
				else if (ScheduledPlan[Day][j].Start == ScheduledPlan[Day][k].Start)
				{
					sortbyprice(ScheduledPlan, Day, j, k);
				}
			}
		}
	}
}

vector<vector<Movie> > DeleteExtraMovie(vector<int>& NumDailyMovie, vector<vector<Movie> >ScheduledPlan)
{
	vector<vector<Movie> >FinalScheduledPlan(7);
	vector<int>NewNumDailyMovie(7, 0);
	for (int Day = 0; Day < 7; Day++)
	{
		int pre = 0;
		if (NumDailyMovie[Day] > 0)
		{
			double width = ScheduledPlan[Day][pre].Finish - ScheduledPlan[Day][pre].Start;
			FinalScheduledPlan[Day].push_back(ScheduledPlan[Day][pre]);
			NewNumDailyMovie[Day]++;
			for (int curr = 1; curr < NumDailyMovie[Day]; curr++)
			{
				if (ScheduledPlan[Day][curr].Start >= (width + ScheduledPlan[Day][pre].Start))
				{
					FinalScheduledPlan[Day].push_back(ScheduledPlan[Day][curr]);
					pre = curr;
					NewNumDailyMovie[Day]++;
				}
			}
		}
	}
	NumDailyMovie = NewNumDailyMovie;
	return FinalScheduledPlan;
}

void dayofweek(int Day, vector<string>& line, string space)
{
	if (Day == 2)
	{
		line.push_back("Saturday  " + space);
	}
	else if (Day == 4)
	{
		line.push_back("Sunday    " + space);
	}
	else if (Day == 6)
	{
		line.push_back("Monday    " + space);
	}
	else if (Day == 8)
	{
		line.push_back("Tuesday   " + space);
	}
	else if (Day == 10)
	{
		line.push_back("Wednesday " + space);
	}
	else if (Day == 12)
	{
		line.push_back("Thursday  " + space);
	}
	else if (Day == 14)
	{
		line.push_back("Friday    " + space);
	}
}

void InitializeLines(vector<string>& line)
{
	string a = " ", space = "";
	for (int i = 0; i < (line[0].size() - 10); i++)
	{
		space += a;
	}
	for (int i = 1; i < 16; i++)
	{
		if ((i == 2) || (i == 4) || (i == 6) || (i == 8) || (i == 10) || (i == 12) || (i == 14))
		{
			dayofweek(i, line, space);
		}
		else
		{
			line.push_back(space + "          ");
		}
	}
}

void MinusSign(vector<string>& line, int DayLine, int startchar, int width)
{
	line[DayLine - 1][startchar] = '+';
	line[DayLine + 1][startchar] = '+';
	line[DayLine - 1][startchar + width + 1] = '+';
	line[DayLine + 1][startchar + width + 1] = '+';
	line[DayLine][startchar] = '|';
	line[DayLine][startchar + width + 1] = '|';
	for (int i = (startchar + 1); i < (startchar + width + 1); i++)
	{
		if (line[DayLine - 1][i] != '+')
		{
			line[DayLine - 1][i] = '-';
		}
		if (line[DayLine + 1][i] != '+')
		{
			line[DayLine + 1][i] = '-';
		}
	}
}

void WriteCinemaName(vector<string>& line, int DayLine, int startchar, Movie FinalScheduledPlan)
{
	int character = startchar + 1;
	for (int i = 0; FinalScheduledPlan.CinemaName[i] != '\0'; i++)
	{
		line[DayLine][character] = FinalScheduledPlan.CinemaName[i];
		character++;
	}
}

vector<string> ScheduleLines(vector<vector<Movie> >FinalScheduledPlan, vector<int> NumDailyMovie)
{
	vector<string> line;
	line.push_back("          08:00               10:00               12:00               14:00               16:00               18:00               20:00               22:00               00:00");
	InitializeLines(line);
	int DayLine = 2;

	for (int Day = 0; Day < 7; Day++)
	{
		if (NumDailyMovie[Day] <= 0)
		{
			DayLine += 2;
			continue;
		}
		int width = ((10 * (FinalScheduledPlan[Day][0].Finish - FinalScheduledPlan[Day][0].Start)) - 1);

		for (int i = 0; i < NumDailyMovie[Day]; i++)
		{
			int startchar = ((10 * (FinalScheduledPlan[Day][i].Start - 8.0)) + 10);

			MinusSign(line, DayLine, startchar, width);
			WriteCinemaName(line, DayLine, startchar, FinalScheduledPlan[Day][i]);
		}
		DayLine += 2;
	}
	return line;
}

void printinterminal(vector<string> lines)
{
	for (int i = 0; i < 16; i++)
	{
		cout << lines[i] << "\n";;
	}
}

void printinHTML(vector<vector<Movie> > FinalScheduledPlan,vector<int> NumDailyMovie, string MovieName)
{
	ofstream HTML(MovieName + ".html");
	HTML << "<html lang='en'>" << endl;
	HTML << "<head>" << endl;
	HTML << "<title></title>" << endl;
	HTML << "<link rel='stylesheet' href='./style.css' />" << endl;
	HTML << "</head>" << endl;
	HTML << "<body>" << endl;

	HTML << "<div class = 'vertical-line' style = 'left: 100px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 200px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 300px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 400px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 500px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 600px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 700px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 800px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 900px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1000px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1100px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1200px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1300px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1400px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1500px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1600px;'></div>" << endl;
	HTML << "<div class = 'vertical-line' style = 'left: 1700px;'></div>" << endl;

	HTML << "<div class = 'time-box' style = 'left: 100px; '> <p>08:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 300px; '> <p>10:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 500px; '> <p>12:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 700px; '> <p>14:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 900px; '> <p>16:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 1100px; '> <p>18:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 1300px; '> <p>20:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 1500px; '> <p>22:00 </p> </div>" << endl;
	HTML << "<div class = 'time-box' style = 'left: 1700px; '> <p>00:00 </p> </div>" << endl;

	HTML << "<div class = 'day-box' style = 'top: 60px;'>Saturday</div>" << endl;
	HTML << "<div class = 'day-box' style = 'top: 110px;'>Sunday</div>" << endl;
	HTML << "<div class = 'day-box' style = 'top: 160px;'>Monday</div>" << endl;
	HTML << "<div class = 'day-box' style = 'top: 210px;'>Tuesday</div>" << endl;
	HTML << "<div class = 'day-box' style = 'top: 260px;'>Wednesday</div>" << endl;
	HTML << "<div class = 'day-box' style = 'top: 310px;'>Thursday</div>" << endl;
	HTML << "<div class = 'day-box' style = 'top: 360px;'>Friday</div>" << endl;

	int width, top;
	for (int Day = 0; Day < 7; Day++)
	{
		if (NumDailyMovie[Day] > 0)
		{
			 width = (100 * (FinalScheduledPlan[Day][0].Finish - FinalScheduledPlan[Day][0].Start));
			 top = 60 + (Day * 50);
		}
		for (int i = 0; i < NumDailyMovie[Day]; i++)
		{
			int left = (100 * (FinalScheduledPlan[Day][i].Start-8)) + 100;
			HTML << "<div class='record-box' style='width: "<< width <<"px; left: "<< left <<"px; top:"<<top<<"px; '>"<< FinalScheduledPlan[Day][i] .CinemaName<<"</div>" << endl;
		}
	}
	HTML << "</body>" << endl;
	HTML << "</html>" << endl;
}

int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		cout << "Enter Schedule file";
	}
	else
	{
		int numberofline = 0;
		map<string, int>column;
		vector<Movie> Movies = saveinfo(argv[1], numberofline, column);

		if (numberofline <= 0)
		{
			cout << "There isn't any movie in this file" << endl;
			return 0;
		}

		string input;
		string inputformat1 = "GET ALL MOVIES";
		while (1)
		{
			getline(cin,input);
			if (input == inputformat1)
			{
				int SortedMoviesNum = 1;
				vector<string> SortMovieName = SortingMovieName(numberofline, Movies, SortedMoviesNum);
				printnameofmovies(SortMovieName, SortedMoviesNum);
			}
			else
			{
				int WrongInput = 0;
				string MovieName = checkinput(WrongInput, input);
				if (WrongInput == 1)
				{
					cout << "The input is not correct" << endl;
					continue;
				}

				int NumberOfRequestedMovie = 0;
				vector<Movie>RequestedMovie = SortRequestedMovies(Movies, numberofline, MovieName, NumberOfRequestedMovie);

				if (NumberOfRequestedMovie <= 0)
				{
					cout << "This movie has not found" << endl;
					continue;
				}

				TimeConverter(RequestedMovie, NumberOfRequestedMovie);

				vector<int> NumDailyMovie(7, 0);
				vector<vector<Movie> >ScheduledPlan = DaySeparator(RequestedMovie, NumberOfRequestedMovie, NumDailyMovie);

				SortSchedule(NumDailyMovie, ScheduledPlan);

				vector<vector<Movie> >FinalScheduledPlan = DeleteExtraMovie(NumDailyMovie, ScheduledPlan);

				vector<string> lines = ScheduleLines(FinalScheduledPlan, NumDailyMovie);

				printinterminal(lines);

				printinHTML(FinalScheduledPlan, NumDailyMovie, MovieName);
			}
		}
	}
	return 0;
}
