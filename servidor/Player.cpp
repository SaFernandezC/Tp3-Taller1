#include "Player.h"


Player::Player(Socket player_sock):player_socket(std::move(player_sock)){
}

void Player::run(){}

Player::~Player(){
  player_socket.close();
}
