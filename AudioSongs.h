#pragma once

#include <SFML/Audio.hpp>
#include <vector>
using namespace std;
using namespace sf;

class AudioSongs
{
private:
    vector<shared_ptr<SoundBuffer>> buffers;
    vector<Sound> sounds;
    int currentSongIndex; 

    public:
    AudioSongs(const vector<string>& filepaths);
    void Update(); 
};