#ifndef _SoundManager_H_
#define _SoundManager_H_

#include <SFML/Audio.hpp>
class SoundManager {
  public:
    SoundManager();
    enum Music{title,battle,victory};
    enum SFX{bump,splash,menuSelect,menuMove,fish};
    void playSound(SFX);
    void playMusic(Music);
  private:
    sf::SoundBuffer buffer;
    sf::Music music;
    sf::Sound sound;

};

#endif
