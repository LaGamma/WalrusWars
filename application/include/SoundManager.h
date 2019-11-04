#ifndef _SoundManager_H_
#define _SoundManager_H_

#include <SFML/Audio.hpp>
class SoundManager {
  public:
    SoundManager();
    enum Music{title,battle,victory};
    enum SFX{bump,splash,menuSelect,menuMove,fish};
    void playSound(SFX, int);
    void playMusic(Music);
    void load();
  private:
    sf::SoundBuffer bumpBuffer;
    sf::SoundBuffer splashBuffer;
    sf::SoundBuffer menuSelectBuffer;
    sf::SoundBuffer menuMoveBuffer;
    sf::SoundBuffer fishBuffer;

    sf::Music menuMusic;
    sf::Music battleMusic;
    sf::Music victoryMusic;
    sf::Sound bumpSound;
    sf::Sound splashSound;
    sf::Sound menuSelectSound;
    sf::Sound menuMoveSound;
    sf::Sound fishSound;

};

#endif