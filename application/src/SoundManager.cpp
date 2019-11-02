#include "SoundManager.h"

SoundManager::SoundManager(){

};



void SoundManager::playSound(SoundManager::SFX sound){
  if(sound == SoundManager::SFX::bump){
    //load and play sound
  };
  if(track == SoundManager::SFX::splash){
    //load and play sound
  };
  if(track == SoundManager::SFX::menuSelect){
    //load and play sound
  };
  if(track == SoundManager::SFX::menuMove){
    //load and play sound
  };
  if(track == SoundManager::SFX::fish){
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
