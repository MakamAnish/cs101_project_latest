#include "coin.h"
#include "lasso.h"
#include "time.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,10);
void Coin::initCoin() {

  coin_start_x = ((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("yellow"));
  coin_circle.setFill(true);
  addPart(&coin_circle);


}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = -2;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}


//double coin

void Coin2::initCoin() {

  coin_start_x = ((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(true);
  addPart(&coin_circle);


}

void Coin2::resetCoin() {
  double coin_speed = 0;
  double coin_angle_deg = 90;
  coin_ax = 0;
  coin_ay = 0;
  bool paused = true, rtheta = true;
  reset_all(-100, -100, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

void Coin2::ResetCoin(){
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = -2;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  }




  //Magnet
 void Magnet::initCoin() {

  coin_start_x = ((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("red"));
  coin_circle.setFill(true);
  addPart(&coin_circle);


}

void Magnet::resetCoin() {
  double coin_speed = 0;
  double coin_angle_deg = 90;
  coin_ax = 0;
  coin_ay = 0;
  bool paused = true, rtheta = true;
  reset_all(-100, -100, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}


void Magnet::ResetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = -2;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}




void Increase::initCoin() {

  coin_start_x = ((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("green"));
  coin_circle.setFill(true);
  addPart(&coin_circle);


}

void Increase::resetCoin() {
  double coin_speed = 0;
  double coin_angle_deg = 90;
  coin_ax = 0;
  coin_ay = 0;
  bool paused = true, rtheta = true;
  reset_all(-100, -100, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}


void Increase::ResetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = -2;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(((PLAY_X_START+WINDOW_X)/2)-100+(dis(gen)*20)+1, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

