#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager(){

};

void SoundManager::load() {
  if(!bumpBuffer.loadFromFile("../audio/bump.wav")) {
    std::cout << "Could not load audio\n";
  }
  bumpSound.setBuffer(bumpBuffer);
  if(!fishBuffer.loadFromFile("../audio/fish.wav")) {
    std::cout << "Could not load audio\n";
  }
  fishSound.setBuffer(fishBuffer);
  if(!menuMoveBuffer.loadFromFile("../audio/menuMove.wav")) {
    std::cout << "Could not load audio\n";
  }
  menuMoveSound.setBuffer(menuMoveBuffer);
  if(!menuSelectBuffer.loadFromFile("../audio/menuSelect.wav")) {
    std::cout << "Could not load audio\n";
  }
  menuSelectSound.setBuffer(menuSelectBuffer);
  if(!splashBuffer.loadFromFile("../audio/splash.wav")) {
    std::cout << "Could not load audio\n";
  }
  splashSound.setBuffer(splashBuffer);
}

void SoundManager::playSound(SoundManager::SFX sfx, float vol){
  if(sfx == SoundManager::SFX::bump){
    bumpSound.setVolume(vol);
    bumpSound.play();
  };
  if(sfx == SoundManager::SFX::splash){
    splashSound.setVolume(vol*3.5);
    splashSound.play();
  };
  if(sfx == SoundManager::SFX::menuSelect){
    menuSelectSound.setVolume(vol);
    menuSelectSound.play();
  };
  if(sfx == SoundManager::SFX::menuMove){
    menuMoveSound.setVolume(vol);
    menuMoveSound.play();
  };
  if(sfx == SoundManager::SFX::fish){
    fishSound.setVolume(vol);
    fishSound.play();
  };
};

void SoundManager::playMusic(SoundManager::Music track){
  if(track == SoundManager::Music::title){
    //load and play title music
  };
  if(track == SoundManager::Music::battle){
    //load and play battle music
  };
};
