#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager(){

};

void SoundManager::load() {
  if(!bumpBuffer.loadFromFile("../audio/bump.wav")) {
    std::cout << "Could not load audio\n";
  }
  bumpSound.setBuffer(bumpBuffer);
  bumpSound.setVolume(100.0f);
}

void SoundManager::playSound(SoundManager::SFX sfx){
  if(sfx == SoundManager::SFX::bump){
    bumpSound.play();
  };
  if(sfx == SoundManager::SFX::splash){
    //load and play sound
  };
  if(sfx == SoundManager::SFX::menuSelect){
    //load and play sound
  };
  if(sfx == SoundManager::SFX::menuMove){
    //load and play sound
  };
  if(sfx == SoundManager::SFX::fish){
    //load and play sound
  };
};

void SoundManager::playMusic(SoundManager::Music track){
  if(track == SoundManager::Music::title){
    //load and play title music
  };
  if(track == SoundManager::Music::battle){
    //load and play battle music
  };
  if(track == SoundManager::Music::victory){
    //load and play victory music
  };
};
