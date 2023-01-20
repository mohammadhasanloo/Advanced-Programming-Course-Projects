#ifndef CONST_VALUES_H
#define CONST_VALUES_H

#include <iostream>
#include "rsdl.hpp"


const double DELAY_TIME = 0.015;
const double FIELD_X = 1400;
const double FIELD_Y = 3*FIELD_X/5;
const double BALL_X=FIELD_X/2;
const double BALL_Y=FIELD_Y/2;
const double BALL_RADIUS = FIELD_X/50;
const double BALL_MASS = FIELD_X/800;
const double BEAD_MASS = 2*FIELD_X/800;
const double BEAD_RADIUS = 3*FIELD_X/100;
const double MAX_INITIAL_SPEED = 5*FIELD_X/8;
const double FRICTION_ACCELERATION = 3*FIELD_X/8;
const double THROW_RADIUS = 3*FIELD_X/40;
const double DOWN_FOOTBALL_GATE = FIELD_Y/3;
const double UP_FOOTBALL_GATE = 2*FIELD_Y/3;
const int BEADS_NUM1 = 5;
const int BEADS_NUM2 = 5;
const int PLAYER_START = 1;
const int SCREEN_FONT_SIZE=FIELD_X/40;
const int FINISH_TEXT_FONT_SIZE=FIELD_X/20;
const int TIME_SHOW_WINNER = 300000;
const int MOUSE_DRAG_DIRECTION=-1;
const RGB PLAYER_1_COLOUR=GREEN;
const RGB PLAYER_2_COLOUR=RED;
const std::string GAME_NAME = "Soccer_Star";
const std::string FONT_NAME = "freeSans.tff";
const std::string BEAD_1_PHOTO = "Player1.png";
const std::string BEAD_2_PHOTO = "Player2.png";
const std::string BALL_PHOTO = "ball.png";
const std::string FIELD_PHOTO = "field.jpg";
const Point START_TEXT_PLAYER_1(FIELD_X/160, FIELD_Y/48);
const Point START_TEXT_PLAYER_2(61*FIELD_X/80, FIELD_Y/48);
const Point SHOW_TURN_PLAYER_1(2*FIELD_X/5, FIELD_Y/48);
const Point SHOW_TURN_PLAYER_2(41*FIELD_X/80, FIELD_Y/48);
const Point SRC_FINISH_TEXT(FIELD_X/8, 5*FIELD_Y/8);

#endif
