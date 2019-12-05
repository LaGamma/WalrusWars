#ifndef _SoundManager_H_
#define _SoundManager_H_

#include <SFML/Audio.hpp>
class SoundManager {
  public:
    SoundManager() = default;
    enum Music{title,battle};
    enum SFX{bump,splash,menuSelect,menuMove,fish};
    void playSound(SFX, float);
    void playMusic(Music);
    void load();
    void setMusicVolume(float);
  private:
    sf::SoundBuffer bumpBuffer;
    sf::SoundBuffer splashBuffer;
    sf::SoundBuffer menuSelectBuffer;
    sf::SoundBuffer menuMoveBuffer;
    sf::SoundBuffer fishBuffer;

    sf::Music menuMusic;
    sf::Music battleMusic;
    sf::Sound bumpSound;
    sf::Sound splashSound;
    sf::Sound menuSelectSound;
    sf::Sound menuMoveSound;
    sf::Sound fishSound;

};

#endif
