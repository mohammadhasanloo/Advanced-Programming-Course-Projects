all: utunes.out

utunes.out: artist_filter.o bad_request.o command_handle.o comment.o criteria.o empty.o filter_song.o like_filter.o main.o not_found.o permission_denied.o playlist.o song.o user.o utunes.o year_filter.o recommended_songs.o
	g++ -std=c++11 artist_filter.o bad_request.o command_handle.o comment.o criteria.o empty.o filter_song.o like_filter.o main.o not_found.o permission_denied.o playlist.o song.o user.o utunes.o year_filter.o recommended_songs.o -o utunes.out

main.o: main.cpp command_handle.hpp
	g++ -std=c++11 -c main.cpp -o main.o

artist_filter.o: artist_filter.cpp criteria.hpp song.hpp
	g++ -std=c++11 -c artist_filter.cpp -o artist_filter.o

bad_request.o: bad_request.cpp
	g++ -std=c++11 -c bad_request.cpp -o bad_request.o

command_handle.o: command_handle.cpp utunes.hpp not_found.hpp bad_request.hpp permission_denied.hpp
	g++ -std=c++11 -c command_handle.cpp -o command_handle.o

comment.o: comment.cpp
	g++ -std=c++11 -c comment.cpp -o comment.o

criteria.o: criteria.cpp song.hpp
	g++ -std=c++11 -c criteria.cpp -o criteria.o

empty.o: empty.cpp
	g++ -std=c++11 -c empty.cpp -o empty.o

filter_song.o: filter_song.cpp criteria.hpp artist_filter.hpp year_filter.hpp like_filter.hpp song.hpp
	g++ -std=c++11 -c filter_song.cpp -o filter_song.o

like_filter.o: like_filter.cpp criteria.hpp song.hpp
	g++ -std=c++11 -c like_filter.cpp -o like_filter.o

not_found.o: not_found.cpp
	g++ -std=c++11 -c not_found.cpp -o not_found.o

permission_denied.o: permission_denied.cpp
	g++ -std=c++11 -c permission_denied.cpp -o permission_denied.o

playlist.o: playlist.cpp user.hpp song.hpp permission_denied.hpp empty.hpp bad_request.hpp
	g++ -std=c++11 -c playlist.cpp -o playlist.o

song.o: song.cpp comment.hpp empty.hpp
	g++ -std=c++11 -c song.cpp -o song.o

user.o: user.cpp song.hpp bad_request.hpp empty.hpp
	g++ -std=c++11 -c user.cpp -o user.o

utunes.o: utunes.cpp user.hpp song.hpp empty.hpp not_found.hpp playlist.hpp permission_denied.hpp filter_song.hpp recommended_songs.hpp
	g++ -std=c++11 -c utunes.cpp -o utunes.o

year_filter.o: year_filter.cpp criteria.hpp song.hpp
	g++ -std=c++11 -c year_filter.cpp -o year_filter.o

recommended_songs.o: recommended_songs.cpp song.hpp user.hpp
	g++ -std=c++11 -c recommended_songs.cpp -o recommended_songs.o

clean:
	rm *.o utunes.out
