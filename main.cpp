#include <cstdio>
#include <cstdlib>
#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "time.h"
#include <ctime>
#include <fstream>

using namespace simplecpp;

main_program {

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0,level=1;
  float stepTime = STEP_TIME;
  float runTime = 20; // sec; -ve means infinite
  float currTime = 0;

  int lives=3;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256],Timeremaining[256],Lives[256],Level[256],ctocollect[256],Score[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  sprintf(Timeremaining, "Time remaining: %d", int(20-currTime));
  sprintf(Lives,"Lives Remaining : %d",lives);
  sprintf(Level,"LEVEL- %d",level);
  sprintf(ctocollect,"Coins to collect: %d",2*level-lasso.getNumCoins());
  sprintf(Score,"SCORE: %d",lasso.score);
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);
  Text timedisplay(PLAY_X_START+200,PLAY_Y_HEIGHT+50,Timeremaining);
  Text livesdisplay(PLAY_X_START+200,PLAY_Y_HEIGHT+20,Lives);
  Text leveldisplay(PLAY_X_START+300,PLAY_Y_START+50,Level);
  Text collectdisplay(PLAY_X_WIDTH-30,PLAY_Y_START+100,ctocollect);
  Text scoredisplay(PLAY_X_START+35,PLAY_Y_START+100,Score);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = -2;
  double coin_ay = COIN_G;
   Coin coin1 = Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Coin coin2 = Coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Coin coin[2] = {coin1, coin2};





  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  for(;;) {
    if(((runTime > 0) && (currTime > runTime))||lasso.getNumCoins()>=2*level) {
        if(lasso.getNumCoins()<2*level){
         if(lives==1){
          Text go(PLAY_X_START+300,PLAY_Y_START+100,"LEVEL FAILED");
          char yscore[256],hscore[256],hname[256];
            sprintf(yscore,"Your Score: %d",lasso.getNumCoins());
            Text yourscore(PLAY_X_START+300,PLAY_Y_START+150,yscore);
            yourscore.setMessage(yscore);
            int s;
            ifstream infile("Highest score.txt");
            ofstream outfile("Highest score.txt");
            ofstream outfile2("Highest name.txt");
            infile >> s;
            if(lasso.score>=s){
               outfile << lasso.score;
               sprintf(hscore,"Highest Score: %d",lasso.score);
               Text highscore(PLAY_X_START+300,PLAY_Y_START+180,hscore);
               highscore.setMessage(hscore);
               Text enter(PLAY_X_START+300,PLAY_Y_START+200,"Enter your name");
               cin.getline(hname,256);
               outfile2 << hname;
               }
               getClick();
          wait(2.5);
          break;
        }
         else{
            Text remaininglives(PLAY_X_START+300,PLAY_Y_START+100,"TRY AGAIN lives decreased");
         lives=lives-1;
         sprintf(Lives,"Lives Remaining: %d",lives);
         livesdisplay.setMessage(Lives);
         wait(2.5);
         for(int i=0;i<2;i++){
         coin[i].resetCoin();
         }
         currTime=0;
         lasso.yank();
          last_coin_jump_end = currTime;
          lasso.num_coins=0;
          sprintf(ctocollect,"Coins to collect: %d",2*level-lasso.getNumCoins());
          collectdisplay.setMessage(ctocollect);
          lasso.score=level*(level-1);
          sprintf(Score,"SCORE: %d",lasso.score);
          scoredisplay.setMessage(Score);
           }
          }
       else{Text go(PLAY_X_START+300,PLAY_Y_START+100,"LEVEL COMPLETED");
            level=level+1;
            sprintf(Level,"LEVEL- %d",level);
            leveldisplay.setMessage(Level);
            char yscore[256];
            sprintf(yscore,"Coins collected: %d",lasso.getNumCoins());
            Text yourscore(PLAY_X_START+300,PLAY_Y_START+150,yscore);
            yourscore.setMessage(yscore);
            wait(3);
            for(int i=0;i<2;i++){
            coin[i].resetCoin();
             }
            currTime=0;
            lasso.yank();
            last_coin_jump_end=currTime;
            lasso.num_coins=0;
            lives=3;
            runTime=runTime+20;
            sprintf(ctocollect,"Coins to collect: %d",2*level-lasso.getNumCoins());
            collectdisplay.setMessage(ctocollect);
            }

    }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(coin);
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
	exit(0);
	  case 'p':
    getClick();
    break;
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    for(int i=0;i<2;i++){
    coin[i].nextStep(stepTime);

    if(coin[i].isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin[i].unpause();
      }
    }
    if(coin[i].getYPos() > PLAY_Y_HEIGHT) {
      coin[i].resetCoin();
      last_coin_jump_end = currTime;
    }
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    sprintf(Score,"SCORE: %d",lasso.score);
    scoredisplay.setMessage(Score);

    sprintf(ctocollect,"Coins to collect: %d",2*level-lasso.getNumCoins());
    collectdisplay.setMessage(ctocollect);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);

    sprintf(Timeremaining,"Time remaining: %d",int(20*level-currTime)+1) ;
    timedisplay.setMessage(Timeremaining);
  } // End for(;;)

  wait(3);
} // End main_program
