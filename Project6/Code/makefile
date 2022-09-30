all: mafia.out

mafia.out: main.o Role.o Game.o Player.o Joker.o Godfather.o Silencer.o Mafia.o Bulletproof.o Detective.o Doctor.o Villager.o CANT_SWAP_BEFORE_END_NIGHT.o CANT_WAKE_UP_DURING_NIGHT.o CHAR_ALREADY_SWAPPED.o DETECTIVE_ALREADY_ASKED.o DOCTOR_ALREADY_HEALED.o GAME_HAS_ALREADY_STARTED.o NO_GAME_CREATED.o PATIENT_IS_DEAD.o PERSON_IS_DEAD.o SOME_PLAYERS_DONT_HAVE_ROLE.o SUSPECT_IS_DEAD.o USER_IS_DEAD.o USER_NOT_JOINED.o VOTEE_ALREADY_DEAD.o VOTER_IS_SILENCED.o VOTING_IN_PROGRESS.o
	g++ -std=c++11 main.o Role.o Game.o Player.o Joker.o Godfather.o Silencer.o Mafia.o Bulletproof.o Detective.o Doctor.o Villager.o CANT_SWAP_BEFORE_END_NIGHT.o CANT_WAKE_UP_DURING_NIGHT.o CHAR_ALREADY_SWAPPED.o DETECTIVE_ALREADY_ASKED.o DOCTOR_ALREADY_HEALED.o GAME_HAS_ALREADY_STARTED.o NO_GAME_CREATED.o PATIENT_IS_DEAD.o PERSON_IS_DEAD.o SOME_PLAYERS_DONT_HAVE_ROLE.o SUSPECT_IS_DEAD.o USER_IS_DEAD.o USER_NOT_JOINED.o VOTEE_ALREADY_DEAD.o VOTER_IS_SILENCED.o VOTING_IN_PROGRESS.o -o mafia.out

main.o: main.cpp Game.hpp Const_Values.hpp
	g++ -std=c++11 -c main.cpp -o main.o

Game.o: Game.cpp Player.hpp Role.hpp Const_Values.hpp CANT_SWAP_BEFORE_END_NIGHT.hpp CANT_WAKE_UP_DURING_NIGHT.hpp CHAR_ALREADY_SWAPPED.hpp DETECTIVE_ALREADY_ASKED.hpp DOCTOR_ALREADY_HEALED.hpp GAME_HAS_ALREADY_STARTED.hpp NO_GAME_CREATED.hpp PATIENT_IS_DEAD.hpp PERSON_IS_DEAD.hpp SOME_PLAYERS_DONT_HAVE_ROLE.hpp SUSPECT_IS_DEAD.hpp USER_IS_DEAD.hpp USER_NOT_JOINED.hpp VOTEE_ALREADY_DEAD.hpp VOTER_IS_SILENCED.hpp VOTING_IN_PROGRESS.hpp
	g++ -std=c++11 -c Game.cpp -o Game.o

Player.o: Player.cpp Role.hpp Joker.hpp Const_Values.hpp Mafia.hpp Villager.hpp Doctor.hpp Detective.hpp Silencer.hpp Godfather.hpp Bulletproof.hpp
	g++ -std=c++11 -c Player.cpp -o Player.o

Role.o: Role.cpp Const_Values.hpp
	g++ -std=c++11 -c Role.cpp -o Role.o

Villager.o: Villager.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Villager.cpp -o Villager.o

Silencer.o: Silencer.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Silencer.cpp -o Silencer.o

Mafia.o: Mafia.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Mafia.cpp -o Mafia.o

Joker.o: Joker.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Joker.cpp -o Joker.o

Godfather.o: Godfather.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Godfather.cpp -o Godfather.o

Doctor.o: Doctor.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Doctor.cpp -o Doctor.o

Detective.o: Detective.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Detective.cpp -o Detective.o

Bulletproof.o: Bulletproof.cpp Const_Values.hpp Role.hpp
	g++ -std=c++11 -c Bulletproof.cpp -o Bulletproof.o

VOTING_IN_PROGRESS.o: VOTING_IN_PROGRESS.cpp
	g++ -std=c++11 -c VOTING_IN_PROGRESS.cpp -o VOTING_IN_PROGRESS.o

VOTER_IS_SILENCED.o: VOTER_IS_SILENCED.cpp
	g++ -std=c++11 -c VOTER_IS_SILENCED.cpp -o VOTER_IS_SILENCED.o

VOTEE_ALREADY_DEAD.o: VOTEE_ALREADY_DEAD.cpp
	g++ -std=c++11 -c VOTEE_ALREADY_DEAD.cpp -o VOTEE_ALREADY_DEAD.o

USER_NOT_JOINED.o: USER_NOT_JOINED.cpp
	g++ -std=c++11 -c USER_NOT_JOINED.cpp -o USER_NOT_JOINED.o

USER_IS_DEAD.o: USER_IS_DEAD.cpp
	g++ -std=c++11 -c USER_IS_DEAD.cpp -o USER_IS_DEAD.o

SUSPECT_IS_DEAD.o: SUSPECT_IS_DEAD.cpp
	g++ -std=c++11 -c SUSPECT_IS_DEAD.cpp -o SUSPECT_IS_DEAD.o

SOME_PLAYERS_DONT_HAVE_ROLE.o: SOME_PLAYERS_DONT_HAVE_ROLE.cpp
	g++ -std=c++11 -c SOME_PLAYERS_DONT_HAVE_ROLE.cpp -o SOME_PLAYERS_DONT_HAVE_ROLE.o

PERSON_IS_DEAD.o: PERSON_IS_DEAD.cpp
	g++ -std=c++11 -c PERSON_IS_DEAD.cpp -o PERSON_IS_DEAD.o

PATIENT_IS_DEAD.o: PATIENT_IS_DEAD.cpp
	g++ -std=c++11 -c PATIENT_IS_DEAD.cpp -o PATIENT_IS_DEAD.o

NO_GAME_CREATED.o: NO_GAME_CREATED.cpp
	g++ -std=c++11 -c NO_GAME_CREATED.cpp -o NO_GAME_CREATED.o

GAME_HAS_ALREADY_STARTED.o: GAME_HAS_ALREADY_STARTED.cpp
	g++ -std=c++11 -c GAME_HAS_ALREADY_STARTED.cpp -o GAME_HAS_ALREADY_STARTED.o

DOCTOR_ALREADY_HEALED.o: DOCTOR_ALREADY_HEALED.cpp
	g++ -std=c++11 -c DOCTOR_ALREADY_HEALED.cpp -o DOCTOR_ALREADY_HEALED.o

DETECTIVE_ALREADY_ASKED.o: DETECTIVE_ALREADY_ASKED.cpp
	g++ -std=c++11 -c DETECTIVE_ALREADY_ASKED.cpp -o DETECTIVE_ALREADY_ASKED.o

CHAR_ALREADY_SWAPPED.o: CHAR_ALREADY_SWAPPED.cpp
	g++ -std=c++11 -c CHAR_ALREADY_SWAPPED.cpp -o CHAR_ALREADY_SWAPPED.o

CANT_WAKE_UP_DURING_NIGHT.o: CANT_WAKE_UP_DURING_NIGHT.cpp
	g++ -std=c++11 -c CANT_WAKE_UP_DURING_NIGHT.cpp -o CANT_WAKE_UP_DURING_NIGHT.o

CANT_SWAP_BEFORE_END_NIGHT.o: CANT_SWAP_BEFORE_END_NIGHT.cpp
	g++ -std=c++11 -c CANT_SWAP_BEFORE_END_NIGHT.cpp -o CANT_SWAP_BEFORE_END_NIGHT.o

clean:
	rm *.o mafia.out
